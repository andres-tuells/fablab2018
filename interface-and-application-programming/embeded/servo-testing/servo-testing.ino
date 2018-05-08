#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>

#define BAUD 9600
#define STEPS 200
#define PIN_MOTOR1 9
#define PIN_ENDPOINT 10

enum MachineStatus {ON, WORKING};

MachineStatus machineStatus = ON;

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(STEPS, 8, 9, 10, 11);
Servo servo1;

int stepCount = 0;  // number of steps the motor has taken
int angle;
int endPoint = 0;

void setup() {
  Serial.begin(BAUD);           // set up Serial library at 9600 bps

  pinMode(PIN_MOTOR1,OUTPUT);
  pinMode(PIN_ENDPOINT,INPUT);
  Serial.println("START");
  servo1.attach(PIN_MOTOR1);
}

void printStatus(){
  Serial.print("STATUS:");
  Serial.println(machineStatus);
}

void processMoveTo(String input){
    String value = input.substring(7);
    angle = value.toInt();
    servo1.write(angle);  
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
  if (input.startsWith("MOVETO:")){
    processMoveTo(input);
  }  
  if (input.startsWith("MOVE:")){
    processMove();
  }
  if (input.startsWith("ANGLE:")){
    processAngle();
  }

}

void checkEndPoint(){
    int oldEndPoint = endPoint;
    endPoint = digitalRead(PIN_ENDPOINT);
    if(endPoint - oldEndPoint){ //endPoint has chaged value
      Serial.print("ENDPOINT:");
      Serial.println(endPoint);
    }
}

void loop(){
    checkEndPoint();
    if(Serial.available()){//user input
      String input = Serial.readString();
      processCommand(input);     
    }
    delay(1);
}

