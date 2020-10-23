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

  // Create loop with name 'test'
  MapLooper::Loop* loop = mapLooper.createLoop("test");

  // Automap loop control parameters
  loop->mapInput("slider1/output");
  loop->mapDelay("slider2/output");
  loop->mapModulation("slider3/output");
  loop->mapRecord("slider1/touch");
  loop->mapOutput("slider4/input");

  loop->setPulsesPerQuarterNote(16);

  for (;;) {
    mapLooper.update(1);
  }
  return 0;
}
