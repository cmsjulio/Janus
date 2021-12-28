#include "IRremote.h"
#include "CppList.h"
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);


#define TRIGGER_PINF  13  
#define ECHO_PINF     12 
#define TRIGGER_PINR  11
#define ECHO_PINR     10
#define TRIGGER_PINL   9
#define ECHO_PINL      8
#define MAX_DISTANCE 200
#define rightIRpin     6
#define leftIRpin      5
#define TURNTIME     600
#define BEACONTIME   100


IRrecv rightIR(rightIRpin);
IRrecv leftIR(leftIRpin);


decode_results resultsL;
decode_results resultsR;


int leftdist;
int rightdist;
int frontaldist;
boolean beaconL = false;
boolean beaconR = false;

NewPing sonarF(TRIGGER_PINF, ECHO_PINF, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarR(TRIGGER_PINR, ECHO_PINR, MAX_DISTANCE);
NewPing sonarL(TRIGGER_PINL, ECHO_PINL, MAX_DISTANCE);

void setup() {
  AFMS.begin();  // create with the default frequency 1.6KHz
  Serial.begin(9600);
  myMotor->setSpeed(255);
  myMotor2->setSpeed(255);  
  rightIR.enableIRIn(); // Start the IR receivers
  leftIR.enableIRIn();
}

void loop() {
  uint8_t i;
  leftdist=sonarL.ping_cm();
  rightdist=sonarR.ping_cm();
  frontaldist=sonarF.ping_cm();
  
  if (leftdist==0) {leftdist=MAX_DISTANCE;}
  if (rightdist==0) {rightdist=MAX_DISTANCE;}
  if (frontaldist==0) {frontaldist=MAX_DISTANCE;}
  
    if (leftIR.decode(&resultsL)) {
    if (resultsL.value==0xa90) {
      beaconL=true;}
    else {
      beaconL=false;}
    leftIR.resume();
  }
    if (rightIR.decode(&resultsR)) {
    if (resultsR.value==0xa90){
      beaconR=true;}
    else{
      beaconR=false;}
    rightIR.resume();
  }
  
  if (frontaldist<30){
      if (rightdist>=leftdist) {
        turnRight(TURNTIME);
      }
      else {
        turnLeft(TURNTIME); 
      }
  }
  else {
      if (beaconL&&!beaconR) {
        turnLeft(BEACONTIME);}
      else {
        if (beaconR&&!beaconL) {
          
          turnRight(BEACONTIME);}
      else {
      goForward();
      }
  }
}
}

void turnRight(int time){
    myMotor->run(BACKWARD);
    myMotor2->run(FORWARD);
    delay(time);
}

void goForward(){
      myMotor->run(FORWARD);
      myMotor2->run(FORWARD);
}

void turnLeft(int time){
    myMotor->run(FORWARD);
    myMotor2->run(BACKWARD);
    delay(time);
}

