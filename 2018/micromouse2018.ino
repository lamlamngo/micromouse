/*
 * Simple demo, should work with any driver board
 *
 * Connect STEP, DIR as indicated
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 120

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR1 3
#define DIR2 7
#define STEP1 2
#define STEP2 6

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper1(MOTOR_STEPS, DIR1,STEP1);
BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);

//Uncomment line to use enable/disable functionality
//BasicStepper
boolean run = false;
void setup() {
    stepper1.begin(RPM, MICROSTEPS);
    stepper2.begin(RPM, MICROSTEPS);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);

    Serial.begin(9600);
}

void loop() {
  
  Serial.print("Left Sensor Reading: ");
  Serial.println(analogRead(A4));

  Serial.print("Right Sensor Reading: ");
  Serial.println(analogRead(A2));

  Serial.print("Front Sensor Reading: ");
  Serial.println(analogRead(A0));

  delay(1000);
}
