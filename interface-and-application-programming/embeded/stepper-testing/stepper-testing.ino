#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>

#define BAUD 9600
#define STEPS 200

#define STEP_PIN 8
#define DIR_PIN 9
#define ENABLE_PIN 8

enum MachineStatus {ON, WORKING};

MachineStatus machineStatus = ON;

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(STEPS, 8, 9, 10, 11);
int x;
int stepCount = 0;  // number of steps the motor has taken
int angle;
int endPoint = 0;

void setup() {
  Serial.begin(BAUD);           // set up Serial library at 9600 bps

  pinMode(ENABLE_PIN,OUTPUT); // Enable
  pinMode(STEP_PIN,OUTPUT); // Step
  pinMode(DIR_PIN,OUTPUT); // Dir
  //digitalWrite(ENABLE_PIN,LOW); // Set Enable low
  Serial.println("START");
}


void loop(){
  //digitalWrite(ENABLE_PIN,LOW); // Set Enable low
  digitalWrite(DIR_PIN,HIGH); // Set Dir high
  Serial.println("Loop 200 steps (1 rev)");
  for(x = 0; x < 200; x++) // Loop 200 times
  {
    digitalWrite(STEP_PIN,HIGH); // Output high
    delay(10); // Wait
    digitalWrite(STEP_PIN,LOW); // Output low
    delay(100); // Wait
  }
  Serial.println("Pause");
  delay(100); // pause one second
}

