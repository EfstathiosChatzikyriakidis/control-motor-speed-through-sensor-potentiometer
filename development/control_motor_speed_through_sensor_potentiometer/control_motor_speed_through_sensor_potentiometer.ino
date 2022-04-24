/*
 *  Control Motor Speed Through Sensor (Potentiometer).
 *
 *  Copyright (C) 2010 Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

const int motorPin = 9;    // the pin number (PWM) for the motor.
const int sensorPin = 0;   // the pin number for the input sensor.
const int ledPin = 13;     // calibration status led.
const long delayTime = 30; // motor delay time in millis.

// the following two bounds are important for the sensor calibration.
int sensorMin = 1023;
int sensorMax = 0;

// calibration time in millis.
const int CAL_TIME = 10000;

// default value for motor device.
int valMotor = 0;

// startup point entry (runs once).
void setup () {
  // set motor as output.
  pinMode(motorPin, OUTPUT);

  // set led as output.
  pinMode(ledPin, OUTPUT);

  // set sensor as input.
  pinMode(sensorPin, INPUT);

  // perform the calibration.
  calibrationPeriod();
}

// loop the main sketch.
void loop () {
  // get the value from the sensor.
  valMotor = analogRead(sensorPin); 

  // map the value for the motor (PWM).
  valMotor = map(valMotor, 0, 1023, 20, 255);

  // set the signal to the motor.
  analogWrite(motorPin, valMotor);

  // delay some time.
  delay(delayTime);
}

// input sensor calibration process.
void calibrationPeriod () {
  // the value that input sensor sends.
  int sensorValue = 0;

  // signal the start of the calibration period.
  digitalWrite(ledPin, HIGH);

  // calibrate during the some time.
  while (millis() < CAL_TIME) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value.
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value.
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period.
  digitalWrite(ledPin, LOW);
}
