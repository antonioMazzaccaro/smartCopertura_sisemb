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

#define MIC_PIN 35
#define MAX_TIME_RANGE 200

#define NUM_READ_CALIBRAZ_MIC 100

bool lastTimeHigh = false;
uint16_t threshold = 0;
uint16_t count = 0;
uint16_t remainingTimeRange = MAX_TIME_RANGE;

void setupAudio() {
  pinMode(MIC_PIN, INPUT);
  threshold = 0;
  for (uint8_t i = 0; i < NUM_READ_CALIBRAZ_MIC; i++) {
    threshold += analogRead(MIC_PIN);
    delay(50);
  }
  threshold /= NUM_READ_CALIBRAZ_MIC;
  threshold = (uint16_t)((float)threshold * 1.2f);  // aumentata del 20%
}

void campionaAudio() {
  int n = analogRead(MIC_PIN);
  if (n > threshold) {
    if (!lastTimeHigh) {
      lastTimeHigh = true;
      count++;
    }
  } else {
    lastTimeHigh = true;
  }

  if (remainingTimeRange == 0) {
    remainingTimeRange = MAX_TIME_RANGE;
    count = 0;
  } else {
    remainingTimeRange--;
  }

  if (remainingTimeRange < (MAX_TIME_RANGE / 2)) {
    if (count > (uint16_t)(0.25f * (float)(MAX_TIME_RANGE - remainingTimeRange) / 2.0f)) {
      seriesOfKnocksDetected = true;
    } else {
      seriesOfKnocksDetected = false;
    }
  }
}
