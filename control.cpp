#include "control.h"

#include <Arduino.h>
#include "movement.h"

void Control_FL_Init(){
  pinMode(L1,INPUT);
  pinMode(L2,INPUT);
  pinMode(L3,INPUT);
  pinMode(L4,INPUT);
  pinMode(L5,INPUT);
}
void Control_FL_Update(){
  uint8_t l1 = !digitalRead(L1);
  uint8_t l2 = !digitalRead(L2);
  uint8_t l3 = !digitalRead(L3);
  uint8_t l4 = !digitalRead(L4);
  uint8_t l5 = !digitalRead(L5);

  int16_t lin_speed = fast_speed * l3 + medium_speed * (l2 * l4) + slow_speed * (l1 * l5);
  int16_t rot_speed = rotation_slow * (l4 - l2) + rotation_medium * (l5 - l1);

  RobotSpeed_t robotSpeed = {lin_speed, rot_speed};
  
  Move_RobotMove(robotSpeed);
}

int16_t Control_NormalizeParam(int16_t val, NormalizeConfig_t normConfig){
  //Dead Zone -> 0
  int16_t out = 0;
  //Value over max input  -> max output
  if(val >= normConfig.maxIn)         out = normConfig.maxOut;
  //Value below min input -> min output
  else if(val <= normConfig.minIn)    out = normConfig.minOut;
  //Value over Dead Zone  -> 0 to maxOutput
  else if(val >= normConfig.hDZ)      out = map(val, normConfig.hDZ, normConfig.maxIn, 0, normConfig.maxOut);
  //Value below Dead Zone -> minOutput to 0
  else if(val <= normConfig.lDZ)      out = map(val,normConfig.minIn, normConfig.lDZ, normConfig.minOut, 0);

  return out;
}