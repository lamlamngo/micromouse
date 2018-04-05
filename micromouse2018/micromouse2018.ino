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

    pinMode(LEDR, OUTPUT);
    pinMode(LEDB, OUTPUT);
    pinMode(LEDG, OUTPUT);
}

void loop() {
  if (checkFront()){
    resetLEDs();
    digitalWrite(LEDR,HIGH);
    moveOneBlock();
  } else if (checkLeft()){
    resetLEDs();
    digitalWrite(LEDB,HIGH);
    rotateLeft90();
    moveOneBlock();
  } else if (checkRight()){
    resetLEDs();
    digitalWrite(LEDG,HIGH);
    rotateRight90();
    moveOneBlock();
  } else{
    resetLEDs();
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,HIGH);
    rotate180();
    moveOneBlock();
  }
  delay(100);
}

void resetLEDs(){
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);
}

void moveOneBlock(){
  for (int i = 0; i < 191; i++){
    stepper1.move(1);
    stepper2.move(1);
    delay(20);
  }
  //stop();
}

void rotateLeft90(){
  for (int i = 0; i < 95; i++){
    stepper1.move(-1);
    stepper2.move(1);
    delay(20);
  }
}

void rotateRight90(){
  for (int i = 0; i < 95; i++){
    stepper1.move(1);
    stepper2.move(-1);
    delay(20);
  }
}

void rotate180(){
  for (int i = 0; i < 95*2; i++){
    stepper1.move(1);
    stepper2.move(-1);
    delay(20);
  }  
}

void stop(){
  stepper1.startBrake();
  stepper2.startBrake();
}

bool checkFront(){
  return analogRead(FRONT) <= 50;
}

bool checkLeft(){
  return analogRead(LEFT) <= 150;
}

bool checkRight(){
  return analogRead(RIGHT) <= 150;
}

