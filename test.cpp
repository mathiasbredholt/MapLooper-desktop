/*
 MapLooper - Embedded Live-Looping Tools for Digital Musical Instruments
 Copyright (C) 2020 Mathias Bredholt

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "MapLooper/MapLooper.hpp"

int main(int argc, char const *argv[]) {
  MapLooper::MapLooper mapLooper;

  MapLooper::Loop* loop = mapLooper.createLoop("test", MPR_FLT, 1);
  loop->mapInput("out/slider1");
  loop->mapOutput("in/slider2");
  loop->mapMix("out/button1");
  loop->mapModulation("out/slider3");
  loop->setPulsesPerQuarterNote(8);

  for (;;) {
    mapLooper.update(1);
  }
  return 0;
}
