#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <Arduino.h>

#define motorLeftPin 22
#define motorRightPin 23
const int8_t leftCorrection = 1;
const int8_t rightCorrection = -1;

const uint8_t wheel_sep = 12; // 12 cm
const float wheel_radius = 6.6; // 66mm

typedef struct{
  int16_t lin_speed;
  int16_t rot_speed;
} RobotSpeed_t;

void Move_ServosInit();
void Move_RobotMove(RobotSpeed_t robotSpeed);
void Move_ServosSetSpeed(int8_t left, int8_t right);
int8_t Move_NormalizeParameter(int16_t val, const int8_t lDZ, const int8_t hDZ, const int8_t minIn, const int8_t maxIn, const int8_t minOut, const int8_t maxOut);


#endif