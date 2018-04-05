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

//define pin outs sensors
#define LEFT A4
#define RIGHT A2
#define FRONT A0

//define pin outs button and LEDS
#define LEDR 13
#define LEDB 11
#define LEDG 10
#define button 12

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

////Mode Acceleration
//stepper1.Mode current_mode_1 = LINEAR_SPEED;
//stepper2.Mode current_mode_2 = LINEAR_SPEED;
BasicStepperDriver::Mode current_mode = BasicStepperDriver::Mode::CONSTANT_SPEED;
short accel = 200;
short decel = 200;

void setup() {

    //setup two stepper motors in full step mode
    stepper1.begin(RPM, MICROSTEPS);
    stepper1.setSpeedProfile(current_mode, accel, decel);
    stepper2.begin(RPM, MICROSTEPS);
    stepper2.setSpeedProfile(current_mode, accel, decel);
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
  rotate90();
  delay(5000);
}

void moveOneBlock(){
  for (int i = 0; i < 191; i++){
    stepper1.move(1);
    stepper2.move(1);
    delay(20);
  }
}

void rotate90(){
  for (int i = 0; i < 95; i++){
    stepper1.move(-1);
    stepper2.move(1);
    delay(20);
  }
}

