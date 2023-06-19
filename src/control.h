#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>

//Pin input
#define L1 26
#define L2 32
#define L3 33
#define L4 27
#define L5 25

//Speed parameters
const int16_t fast_speed = 60;
const int16_t medium_speed = 30;
const int16_t slow_speed = 10;
const int16_t rotation_slow = 1;
const int16_t rotation_medium = 2;
const int16_t rotation_fast = 4;

//Normalize struct to configure
typedef struct{
  int16_t lDZ;
  int16_t hDZ;
  int16_t minIn;
  int16_t maxIn;
  int16_t minOut;
  int16_t maxOut;
} NormalizeConfig_t;

void Control_FL_Init();
void Control_FL_Update();
int16_t Control_NormalizeParam(int16_t val, NormalizeConfig_t normConfig);

#endif