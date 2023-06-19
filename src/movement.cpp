#include "movement.h"

#include <Arduino.h>
#include <ESP32Servo.h>

Servo motorLeft;
Servo motorRight;

void Move_ServosInit(){
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  motorLeft.setPeriodHertz(50);// Standard 50hz servo
  motorLeft.attach(motorLeftPin, 1000, 2000);
  motorRight.setPeriodHertz(50);// Standard 50hz servo
  motorRight.attach(motorRightPin, 1000, 2000);
}

void Move_ServosSetSpeed(int8_t left, int8_t right){
  if(left > 100)    left = 100;
  if(right > 100)   right = 100;
  if(left < -100)   left = -100;
  if(right < -100)  right = -100;

  left *= leftCorrection;
  right *= rightCorrection;
  uint8_t left_w = map(left, -100, 100, 0, 180);
  uint8_t right_w = map(right, -100, 100, 0, 180);

  motorLeft.write(left_w);
  motorRight.write(right_w);
}

void Move_RobotMove(RobotSpeed_t rs){
  int8_t left  =  rs.lin_speed + wheel_sep * rs.rot_speed;
  int8_t right =  rs.lin_speed - wheel_sep * rs.rot_speed;
  Move_ServosSetSpeed(left, right);
}

