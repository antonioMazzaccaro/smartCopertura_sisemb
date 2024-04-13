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

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

#define FINE_CORSA_GIU 4
#define FINE_CORSA_SU 16

Stepper myStepper(100, IN1, IN3, IN2, IN4);

void setupMotor() {

  pinMode(FINE_CORSA_GIU, INPUT);
  pinMode(FINE_CORSA_SU, INPUT);

  myStepper.setSpeed(350);

}

bool isCoperturaChiusa() {
  return (digitalRead(FINE_CORSA_GIU) == HIGH);
}

bool isCoperturaAperta() {
  return (digitalRead(FINE_CORSA_SU) == HIGH);
}

void tiraSu() {
  while (digitalRead(FINE_CORSA_SU) != HIGH) {
    Serial.println("clockwise");
    myStepper.step(-100);
  }
}

void tiraGiu() {
  while (digitalRead(FINE_CORSA_GIU) != HIGH) {
    Serial.println("counterclockwise");
    myStepper.step(100);
  }
}