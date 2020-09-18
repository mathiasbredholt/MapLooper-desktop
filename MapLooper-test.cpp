#include <mapper/mapper.h>
#include <stdio.h>
#include <string.h>

float buffer = 0;
float output = 0;

void sigLoopInHandler(mpr_sig sig, mpr_sig_evt evt, mpr_id inst, int length,
                      mpr_type type, const void *value, mpr_time time) {
  buffer = *((float *)value);
}

void sigHandler(mpr_sig sig, mpr_sig_evt evt, mpr_id inst, int length,
                mpr_type type, const void *value, mpr_time time) {
  output = *((float *)value);
}

void automap(mpr_graph graph) {
  mpr_graph_subscribe(graph, 0, MPR_SIG, -1);
  mpr_graph_add_cb(
      graph,
      [](mpr_graph g, mpr_obj obj, const mpr_graph_evt evt, const void *data) {
        const char *sigName = mpr_obj_get_prop_as_str(obj, MPR_PROP_NAME, 0);

        mpr_list sigs = mpr_graph_get_objs(g, MPR_SIG);
        if (strcmp(sigName, "button1") == 0) {
          sigs = mpr_list_filter(sigs, MPR_PROP_NAME, 0, 1, MPR_STR, "mix",
                                 MPR_OP_EQ);
          mpr_obj_push(mpr_map_new(1, &obj, 1, (mpr_sig *)sigs));
        }
      },
      MPR_SIG, 0);
}

int main(int argc, char const *argv[]) {
  mpr_dev dev = mpr_dev_new("feedback-test", 0);

  mpr_sig sigTest =
      mpr_sig_new(dev, MPR_DIR_OUT, "sigTest", 1, MPR_FLT, 0, 0, 0, 0, 0, 0);

  mpr_sig sigLoopIn = mpr_sig_new(dev, MPR_DIR_IN, "loopIn", 1, MPR_FLT, 0, 0,
                                  0, 0, sigLoopInHandler, MPR_SIG_UPDATE);

  mpr_sig sigLoopOut =
      mpr_sig_new(dev, MPR_DIR_OUT, "loopOut", 1, MPR_FLT, 0, 0, 0, 0, 0, 0);

  mpr_sig sigMix =
      mpr_sig_new(dev, MPR_DIR_IN, "mix", 1, MPR_FLT, 0, 0, 0, 0, 0, 0);

  mpr_sig sigLocalOut =
      mpr_sig_new(dev, MPR_DIR_OUT, "localOut", 1, MPR_FLT, 0, 0, 0, 0, 0, 0);

  mpr_sig sigLocalIn = mpr_sig_new(dev, MPR_DIR_IN, "localIn", 1, MPR_FLT, 0, 0,
                                   0, 0, sigHandler, MPR_SIG_UPDATE);

  while (!mpr_dev_get_is_ready(dev)) {
    mpr_dev_poll(dev, 100);
  }

  mpr_sig sigs[] = {sigLocalOut, sigMix};
  mpr_map map = mpr_map_new(2, sigs, 1, &sigLocalIn);
  // const char *expr = "y=(1-x1)*x0+x1*y{-127}";
  const char *expr = "y=y{-127}";
  mpr_obj_set_prop(map, MPR_PROP_EXPR, 0, 1, MPR_STR, expr, 1);
  mpr_obj_push(map);

  mpr_obj_push(mpr_map_new(1, &sigTest, 1, &sigLoopIn));

  automap(mpr_obj_get_graph(dev));

  float mix = 0.0;
  mpr_sig_set_value(sigMix, 0, 1, MPR_FLT, &mix);

  float value = 0.0;
  for (;;) {
    mpr_sig_set_value(sigLocalOut, 0, 1, MPR_FLT, &buffer);
    mpr_sig_set_value(sigTest, 0, 1, MPR_FLT, &value);
    mpr_sig_set_value(sigLoopOut, 0, 1, MPR_FLT, &output);

    value += 0.01;
    if (value > 10) {
      value = 0;
    }

    printf("out: %f\n", output);

    mpr_dev_poll(dev, 10);
  }

  return 0;
}
