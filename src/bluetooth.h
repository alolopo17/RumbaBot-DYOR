#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include "BluetoothSerial.h"

//Codes
#define BT_CODE_MANUAL 10
#define BT_CODE_FOLLOW_LINES 20

const char separator = '@';
const char btName[] = "ESP32-Alvaro";

typedef struct{
  uint8_t code;
  int16_t linear;
  int16_t rotation;
} BTMessage;

typedef enum{
  BT_NO_MSG = 0,
  BT_MSG_OK = 1,
  BT_MSG_FAIL = 2
} BTResponse;

void BTInit();
BTResponse BTreceiveData();
BTMessage BTgetLastMessage();

//void BTSendMessage(char message[]);

bool isNumber(char c, uint8_t& number);
bool isNegativeSign(char c);
bool isEOL(char c);
bool isSeparator(char c);

#endif