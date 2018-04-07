#include "BasicStepperDriver.h"
#include <StackList.h>
#include <QueueList.h>

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

//navigation command for the robot
//implement by a queue to simulate recursion on the robots
QueueList<command> commands;

int orientation[] = {1,2,4,8};

//maze constant
#define X 6
#define Y 6

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

//calculate optimistic distance from one cell to another cell
void int calcDist(int x, int y, int goalX, int goalY){
  return abs(goalY - y) + abs(goalX - x);
}

//optimistic distance from one cell to the square in the center
void int calcDistToGoal(int x, int y, int maze_dimension){
  int center = maze_dimension/2;
  int dist = 0;

  if (y < center){
    if (x < center){
      //top left of the maze
      dist = calcDist(x,y, (center-1),(center-1)); //distance to top left center
    } else{
      //top right
      dist = calcDist(x,y, (center-1),center);
    }
  } else{
    if (posx > center){
      //bottom right
      dist = calcDist(x,y,center,center);
    } else{
      //top left
      dist = calcDist(x,y,center,center-1);
    }
  }

  return dist;
}

//get new coordinate based on the current coord and the heading
coord getNewCoordinate(coord current, int orientation){
  coord newCoord = {0,0};

  if (orientation == 1){
    newCoord.x = current.x;
    newCoord.y = current.y - 1;
  } else if (orientation == 2){
    newCoord.x = current.x;
    newCoord.y = current.y + 1;
  } else if (orientation == 4){
    newcoord.x = current.x + 1;
    newCoord.y = current.y;
  } else if (orientation == 8){
    newCoord.x = current.x - 1;
    newCoord.y = current.y;
  }

  return newCoord;
}

//get neighbors' minimum distance
int getMinimumNeighbors(coord current){
  int minVal = -1;

  for (int i = 0; i < sizeof(orientation); i++){

    //check if accessbile

    if (maze[current.x][current.y].walls && orientation[i] != 0){
      coord neighbor = getNewCoordinate(current, orientation[i]);

      //if valid cell

      if (isValid(neighbor)){
        if (minVal == -1){
          minval = maze[neighbor.x][neighbor.y].distance;
        } else{
          if (maze[neighbor.x][neighbor.y] < minVal){
            minVal = maze[neighbor.x][neighbor.y].distance;
          }
        }
      }
    }
  }

  return minval;
}

//check if a coord is valid
bool isValid(coord current){
  if (current.x < 0 || current.x >= X || current.y < 0 || current.y >= Y){
    return false;
  }
  return true;
}

//check if a cell is bounded on three sides
bool isDeadEnd(coord current){
  if (isValid(current)){
    int walls = maze[current.x][current.y].walls;

    if (walls == 1 || walls == 2 || walls == 3 || walls == 4){
      return true; //bounded on three sides
    }
    return false;
  }
  return false;
}

bool win(coord current, coord[] goals){
  if (isValid(current)){
    for (int i = 0; i < sizeof(goals); i++){
      if (current.x == goals[i].x && current.y == goals[i].y){
        return true;
      }
    }
    return false;
  }
  return false;
}

//add a wall to a cell
void updatecoord(coord current, int walldir){
  if (isValid(current)){
    if (maze[current.x][current.y].walls & walldir != 0){
      maze[current.x][current.y].walls -= walldir;
    }
  }
}

int optimalDirection(coord current, int heading){
  coord leastNext = {0,0};

  int leastNextVal = sizeof(maze)*sizeof(maze);
  int leastDir = heading;

  if (maze[current.x][current.y].walls & heading != 0){
    coord leastnextTemp = updatecoord(current, heading);

    if (isValid(leastnextTemp)){
      leastNext = leastnextTemp;
      leastNextVal = maze[leastNext.x][leastNext.y].distance;
    }
  }

  for (int i =0; i < sizeof(orientation); i++){
    int dir = orientation[i];

    if (maze[current.x][current.y].walls & dir != 0){
      coord dirCoord = updatecoord(current, dir);

      if (isValid(dirCoord)){
        if (maze[dirCoord.x][dirCoord.y].distance < leastNextVal){
          leastNextVal = maze[dirCoord.x][dirCoord.y].distance;
          leastNext = dirCoord;
          leastDir = dir;
        }
      }
    }
  }

  return leastDir;
}
