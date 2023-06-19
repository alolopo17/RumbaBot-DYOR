//#include "BluetoothSerial.h"
#include "bluetooth.h"
#include "movement.h"
#include "control.h"
//#include <ESP32Servo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

NormalizeConfig_t normRot = {-75, 75, -900, 900, -5, 5};
NormalizeConfig_t normLin = {15, 30, 0, 90, -25, 100};

bool isFollowLines = false;

void setup() {
  Serial.begin(115200);
  BTInit();
  Move_ServosInit();
  Control_FL_Init();
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  BTResponse response = BTreceiveData();
  if(response == BT_MSG_OK){

    BTMessage msg = BTgetLastMessage();
    if(msg.code == BT_CODE_MANUAL){
      ProcessManualMovement(msg);
    }
    isFollowLines = (msg.code == BT_CODE_FOLLOW_LINES);
    
  }
  else if(response == BT_MSG_FAIL) Serial.println("Message failed");

  if(isFollowLines) Control_FL_Update();

}

void ProcessManualMovement(BTMessage msg){
  int8_t rot = Control_NormalizeParam(msg.rotation, normRot);
  int8_t lin = Control_NormalizeParam(msg.linear, normLin);
  RobotSpeed_t robotSpeed = {lin, rot};
  Move_RobotMove(robotSpeed);
}
