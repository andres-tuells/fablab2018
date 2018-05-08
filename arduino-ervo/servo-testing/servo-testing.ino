#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>

#define BAUD 9600
#define STEPS 200
#define PIN_MOTOR1 9

enum MachineStatus {ON, WORKING};

MachineStatus machineStatus = ON;

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(STEPS, 8, 9, 10, 11);
Servo servo1;

int stepCount = 0;  // number of steps the motor has taken
int angle;

void setup() {
  Serial.begin(BAUD);           // set up Serial library at 9600 bps

  pinMode(PIN_MOTOR1,OUTPUT);
  Serial.println("START");
  servo1.attach(PIN_MOTOR1);
}

void printStatus(){
  Serial.print("STATUS:");
  Serial.println(machineStatus);
}

void processMove(){
    for(angle=0; angle <= 180; angle++){
      servo1.write(angle);
      delay(15);
    }
    for(angle=180; angle >= 0; angle--){
      servo1.write(angle);
      delay(15);
    } 
    angle = 90;
    servo1.write(angle);    
}

void processAngle(){
  Serial.print("ANGLE:");
  Serial.println(angle);
}

void processCommand(String input){
  processMove();
  Serial.print("RECEIVED:");
  Serial.println(input);
  if (input.startsWith("MOVE")){
    processMove();
  }
  if (input.startsWith("ANGLE")){
    processAngle();
  }

}

void loop(){
    printStatus();
    if(Serial.available()){//user input
      String input = Serial.readString();
      processCommand(input);     
    }
    delay(1000);
}

