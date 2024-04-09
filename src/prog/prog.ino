/*
    Copyright (C) 2024  Antonio Mazzaccaro

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

#include "lib.h"

//Tasks
Task audioTask(40, TASK_FOREVER, &campionaAudio);
Task chiediMeteoTask(120000, TASK_FOREVER, &chiediMeteoCallback);
Task leggiRispMeteoTask(5000, TASK_FOREVER, &leggiRispMeteo);
Task checkTask(500, TASK_FOREVER, &check);

Scheduler runner;

void setupScheduler() {
  runner.init();

  runner.addTask(audioTask);
  runner.addTask(chiediMeteoTask);
  runner.addTask(leggiRispMeteoTask);
  runner.addTask(checkTask);

  audioTask.enable();
  chiediMeteoTask.enable();
  leggiRispMeteoTask.enable();
  checkTask.enable();
}

void setup() {
  Serial.begin(115200);

  connectToWifi();

  setupAudio();
  Serial.println("audio OK");
  setupMotor();
  Serial.println("motore OK");
  setupContenitore();
  Serial.println("sensori/attuatori contenitore OK");
  setupScheduler();
  Serial.println("scheduler OK");
}

void loop() {
  runner.execute();
}
