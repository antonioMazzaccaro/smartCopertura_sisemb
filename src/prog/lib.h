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

#include <WiFi.h>
#include <TaskScheduler.h>
#include <ArduinoJson.h>
#include <Stepper.h>
#include <PID_v1.h>

bool seriesOfKnocksDetected = false;

struct {
  uint16_t id;
  const char* main;
  const char* description;
} meteo;

// Callback methods prototypes
void check();
void campionaAudio();
void chiediMeteoCallback();
void leggiRispMeteo();