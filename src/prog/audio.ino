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
#define MAX_TIME_RANGE 1000

#define NUM_READ_CALIBRAZ_MIC 100

uint32_t thresholdUp = 0;
uint32_t thresholdDown = 0;
uint16_t count = 0;
uint16_t remainingTimeRange = MAX_TIME_RANGE;

void setupAudio() {
  pinMode(MIC_PIN, INPUT);
  uint32_t threshold = 0;
  for (uint8_t i = 0; i < NUM_READ_CALIBRAZ_MIC; i++) {
    threshold += analogRead(MIC_PIN);
    delay(50);
  }
  threshold /= NUM_READ_CALIBRAZ_MIC;
  thresholdUp = (uint32_t)((float)threshold * 1.1f);  // aumentata del 10%
  thresholdDown = (uint32_t)((float)threshold * 0.9f);  // diminuita del 10%
  Serial.println(threshold);
}

void campionaAudio() {
  uint32_t n = analogRead(MIC_PIN);
  if (n > thresholdUp || n < thresholdDown) {
    count++;
  }

  if (remainingTimeRange == 0) {
    remainingTimeRange = MAX_TIME_RANGE;
    count = 0;
  } else {
    remainingTimeRange--;
  }

  if (remainingTimeRange < (MAX_TIME_RANGE / 2)) {
    if (count > (uint16_t)(0.03f * (float)MAX_TIME_RANGE)) {
      
      seriesOfKnocksDetected = true;
    } else {
      seriesOfKnocksDetected = false;
    }
  }
}
