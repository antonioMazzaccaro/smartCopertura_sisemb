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

#define WEIGHT_CONTENITORE_SENSOR 32
#define TEMP_CONTENITORE_SENSOR 33
#define OUTPUT_RESISTANCE 25

#define NUM_READ_CALIBRAZ_CONTENITORE 20

#define SOGLIA_CONFIDENZA 0.55f

int16_t sogliaPeso = 0;
float previousConfidenza = 0.0f;

double Setpoint, Input, Output;
double Kp=0.8, Ki=0, Kd=0.01;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setupContenitore() {
  pinMode(WEIGHT_CONTENITORE_SENSOR, INPUT);
  pinMode(TEMP_CONTENITORE_SENSOR, INPUT);
  pinMode(OUTPUT_RESISTANCE, OUTPUT);

  setSogliaTempSensor();
  myPID.SetMode(AUTOMATIC);

  for (uint8_t i = 0; i < NUM_READ_CALIBRAZ_CONTENITORE; i++) {
    sogliaPeso += analogRead(WEIGHT_CONTENITORE_SENSOR);
    delay(100);
  }
  sogliaPeso /= NUM_READ_CALIBRAZ_CONTENITORE;
  sogliaPeso = (int16_t)((float)sogliaPeso * 1.2f);  // aumentata del 20%
}

void setSogliaTempSensor() {
  Setpoint = analogRead(TEMP_CONTENITORE_SENSOR) * 0.95;
  Setpoint = map(Setpoint, 0, 4095, 0, 1023);
}

float evalMeteoCoeff() {
  if (meteo.id == 0) {  // meteo non presente
    return 0.0;
  }

  if (meteo.id == 511) { // caso esplicito freezing rain
  return 1.0;
  }

  if (meteo.id == 762) { // caso esplicito volcanic ash
  return 1.0;
  }

  if (meteo.id == 800) { // caso esplicito sole
  return 0.0;
  }

  return (float)(meteo.id - ((meteo.id / 5) * 5) + 1) / 5.0f; // l'output è tanto più alto quanto la differenza tra l'id e il precedente multiplo di 5 è alta
}

void check() {

  int16_t weight = analogRead(WEIGHT_CONTENITORE_SENSOR);

  Serial.print("Peso: ");
  Serial.println(weight);
  Serial.print("Rumori: ");
  Serial.println(seriesOfKnocksDetected);
  

  if (isCoperturaChiusa() && seriesOfKnocksDetected) {
    analogWrite(OUTPUT_RESISTANCE, 0);
    return;
  }

  float meteoCoeff = evalMeteoCoeff();
  float newConfidenza = ((0.35f * ((weight > sogliaPeso)? 1.0f : 0.0f)) + (0.45f * ((seriesOfKnocksDetected) ? 1.0f : 0.0f)) + (0.2f * meteoCoeff));
  
  float combinedConfidenza = ((0.4f * previousConfidenza) + (0.6f * newConfidenza));
  previousConfidenza = combinedConfidenza;

  if (combinedConfidenza > SOGLIA_CONFIDENZA) {
    analogWrite(OUTPUT_RESISTANCE, 0);
    tiraGiu();
  } else if (!isCoperturaAperta()) {
    tiraSu();
  } else if (weight > sogliaPeso) {
    
    Input = analogRead(TEMP_CONTENITORE_SENSOR);
    Input = map(Input, 0, 4095, 0, 1023);
    
    myPID.Compute();
    
    Output = map(Output, 0, 255, 0, 1023);
    
    analogWrite(OUTPUT_RESISTANCE, Output);

    Serial.print("Input Temp: ");
    Serial.println(Input);
    Serial.print("Output PID: ");
    Serial.println(Output);

  } else {
    analogWrite(OUTPUT_RESISTANCE, 0);
  }
}
