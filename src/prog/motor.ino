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

#define FINE_CORSA_GIU 16
#define FINE_CORSA_SU 4

#define MOTOR_SPEED 4

void setupMotor() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(FINE_CORSA_GIU, INPUT);
  pinMode(FINE_CORSA_SU, INPUT);
}

bool isCoperturaChiusa() {
  return (digitalRead(FINE_CORSA_GIU) == HIGH);
}

bool isCoperturaAperta() {
  return (digitalRead(FINE_CORSA_SU) == HIGH);
}

void tiraGiu() {
  while (digitalRead(FINE_CORSA_GIU) != HIGH) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(MOTOR_SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(MOTOR_SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(MOTOR_SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(MOTOR_SPEED);
  }
}

void tiraSu() {
  while (digitalRead(FINE_CORSA_SU) != HIGH) {
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
    delay(MOTOR_SPEED);
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
    delay(MOTOR_SPEED);
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);
    delay(MOTOR_SPEED);
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, HIGH);
    delay(MOTOR_SPEED);
  }
}
