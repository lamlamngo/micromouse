#include "BasicStepperDriver.h"

//define pin out for sensors
#define LEFT A4
#define RIGHT A2
#define FRONT A5

//define pin for buttons and LEDs
#define LEDR 13
#define LEDB 11
#define LEDG 10
#define button 12

//motor step per revolution
#define MOTOR_STEPS 200
#define RPM 60

#define MICROSTEPS 1

//Motor pins
#define DIR1 3
#define STEP1 2
#define DIR2 7
#define STEP2 6

//setting up motors
BasicStepperDriver stepper1(MOTOR_STEPS, DIR1, STEP1);
BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);

//Acceleration mode
BasicStepperDriver::Mode current_mode = BasicStepperDriver::Mode::LINEAR_SPEED;
short accel = 100;
short decel = 100;

//struct for a coordinate
typedef struct _coord{
  int x;
  int y;
} coord;

//struct for a cell in a maze
typedef struct _entry{
  int distance;
  byte walls;
} entry;

//struct for a command
typedef struct _command{
  float pos;
  float orientation;
} command;

void setup(){
  stepper1.begin(RPM, MICROSTEPS);
  stepper1.setSpeedProfile(current_mode, accel, decel);
  stepper2.begin(RPM, MICROSTEPS);
  stepper2.setSpeedProfile(current_mode, accel, decel);

  //setting microsteps for the two motors
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(button, OUTPUT);
}
