#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>
#include <A4990MotorShield.h>
#include <Adafruit_L3GD20_U.h>
A4990MotorShield motors;
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
Encoder leftEnc(3,4);
Encoder rightEnc(2,11);

int leftEncVal = 0;
int rightEncVal = 0;

int front = A2;
int right = A3;
int left = A0;
int leftDiag = A1;
int rightDiag = A4;
int speed = 50;
int turnHead = 0;
void stopAndReset(){
  motors.setM1Speed(0);
  motors.setM2Speed(0);
  leftEnc.write(0);
  rightEnc.write(0);
}



void setup(){
  Serial.begin(9600);
  Serial.println("MicroMouse Test Begin");
  motors.setM1Speed(0);
  motors.setM2Speed(0);
  pinMode(5,INPUT);
  gyro.begin();
}
void moveOneBlock(){
   motors.setSpeeds(50,50);
   delay(200);
   while (rightEnc.read() < 740){
        sensors_event_t event; 
        gyro.getEvent(&event);
        Serial.println(event.gyro.z);
        motors.setSpeeds(speed,speed*(rightEnc.read()/leftEnc.read()));
        Serial.println(leftEnc.read());
        Serial.println(rightEnc.read());
   }
}

void followright(){
  motors.setSpeeds(50,50);
    if (analogRead(right) < 300){
      motors.setSpeeds(speed*(300.0/400),speed);
    }
    else if (analogRead(right) > 500){
      motors.setSpeeds(speed*(500.0/400),speed);
      
    }
    else{
    motors.setSpeeds(speed*((analogRead(right))/400.0),speed); 
    }
}

void followleft(){
  motors.setSpeeds(50,50);
    if (analogRead(left) < 300){
      motors.setSpeeds(speed,speed*(300.0/390));
    }
    else if (analogRead(left) > 500){
      motors.setSpeeds(speed,speed*(500.0/390));
      
    }
    else{
    motors.setSpeeds(speed,speed*(analogRead(left)/390.0)); 
    }
}

void turnRight(){
  
   motors.setSpeeds(-50,50);
  double angle = 0;
  while (angle >= -0.7){
    sensors_event_t event; 
    gyro.getEvent(&event);
    double angleSpeed = event.gyro.z;
    double angleTraveled = angleSpeed * 0.016;
    Serial.print("AngularSpped: ");
    Serial.println(event.gyro.z);
    delay(15);
    angle = angle + angleTraveled;
    Serial.println(angle);
  }
  motors.setSpeeds(0,0);
}

void turnLeft(){
  
   motors.setSpeeds(50,-50);
  double angle = 0;
  while (angle <= 0.7){
    sensors_event_t event; 
    gyro.getEvent(&event);
    double angleSpeed = event.gyro.z;
    double angleTraveled = angleSpeed * 0.016;
    Serial.print("AngularSpped: ");
    Serial.println(event.gyro.z);
    delay(15);
    angle = angle + angleTraveled;
    Serial.println(angle);
  }
  motors.setSpeeds(0,0);
}

void turnAround(){
  
   motors.setSpeeds(50,-50);
  double angle = 0;
  while (angle <= 1.63){
    sensors_event_t event; 
    gyro.getEvent(&event);
    double angleSpeed = event.gyro.z;
    double angleTraveled = angleSpeed * 0.016;
    Serial.print("AngularSpped: ");
    Serial.println(event.gyro.z);
    delay(15);
    angle = angle + angleTraveled;
    Serial.println(angle);
  }
  motors.setSpeeds(0,0);
}


void readDiag(){
  Serial.print("Left ");
  Serial.println(analogRead(leftDiag));
  Serial.print("Right ");
  Serial.println(analogRead(rightDiag));
}


void moveForward(){
    motors.setM1Speed(speed);
    motors.setM2Speed(speed);
    leftEncVal = leftEnc.read();
    rightEncVal = rightEnc.read();
    Serial.print("front sensor: ");
    Serial.println(analogRead(front));
    while(leftEncVal< rightEncVal){
       // Left side is spinnign slower 
       motors.setM1Speed(speed*(leftEncVal/rightEncVal));
       motors.setM2Speed(speed);
       leftEncVal = leftEnc.read();
      rightEncVal = rightEnc.read();
    }
    while ( leftEncVal > rightEncVal ){
       motors.setM2Speed(speed*(rightEncVal/leftEncVal));
       motors.setM1Speed(speed);
       leftEncVal = leftEnc.read();
      rightEncVal = rightEnc.read();
    }
    leftEncVal = leftEnc.read();
    rightEncVal = rightEnc.read();
    Serial.println(leftEnc.read());
    Serial.println(rightEnc.read());
}

boolean checkRight(){
  if (analogRead(right) < 100){
    return false;
  }
    return true;
}

boolean checkLeft(){
  if (analogRead(left) < 100){
    return false;
  }
    return true;
}

boolean predictRight(){
   if (digitalRead(5) == 0) {
    return true;
   }
    return false;
}

boolean predictLeft(){
  if (analogRead(leftDiag) > 110 ){
    return true;
  }
    return false;
}


void fuckGo(){
  if (predictLeft() && checkLeft()){
    followleft();
  }
  else if ( checkRight()) {
    followright();
  }
  else{
    moveForward();
  }
}

void dTurn(){
  if (checkLeft() && checkRight()){
  turnAround();
  stopAndReset();
  delay(1000);
  turnHead ++;
}
else if (checkLeft() && !checkRight()){
  turnRight();
  stopAndReset();
  delay(1000);
}
else if (!checkLeft() && checkRight()){
  turnLeft();
  stopAndReset();
  delay(1000);
}
else {
  if ( random (1,2) == 1){
    turnLeft();
    stopAndReset();
    delay(1000);
  }
  else {
    turnRight();
    stopAndReset();
    delay(1000);
  }
}
}

void moveAlittleForward(){
      motors.setM1Speed(speed);
    motors.setM2Speed(speed);
    leftEncVal = leftEnc.read();
    rightEncVal = rightEnc.read();
    Serial.print("front sensor: ");
    Serial.println(analogRead(front));
    while(leftEncVal< rightEncVal){
       // Left side is spinnign slower 
       motors.setM1Speed(speed*(leftEncVal/rightEncVal));
       motors.setM2Speed(speed);
       leftEncVal = leftEnc.read();
      rightEncVal = rightEnc.read();
    }
    while ( leftEncVal > rightEncVal ){
       motors.setM2Speed(speed*(rightEncVal/leftEncVal));
       motors.setM1Speed(speed);
       leftEncVal = leftEnc.read();
      rightEncVal = rightEnc.read();
    }
    leftEncVal = leftEnc.read();
    rightEncVal = rightEnc.read();
    Serial.println(leftEnc.read());
    Serial.println(rightEnc.read());
}


//random (1,2)


void play(){
  while (analogRead(front) < 400){
  fuckGo();
}
  stopAndReset();
  dTurn();
if (turnHead >= 2){
  while (analogRead(front) < 400 || !(!checkRight() || !checkLeft())){
    fuckGo();
    stopAndReset();
//    dTurn(); 
  }
  moveOneBlock();
  stopAndReset();
  dTurn();
  turnHead = 0;
}
}
void loop(){
  play();
  delay(3000);
  //moveOneBlock();
  //stopAndReset();
 // followright();
 // stopAndReset();
  //turnRight();
  //stopAndReset();
  //delay(1000);
  //moveOneBlock();
//  followleft();
//  stopAndReset();
//    readDiag();
  //followleft();
//  while(analogRead(front) < 200){ 
//      moveForward();
//  }
  //turnRight();
//  delay(5000);

}
