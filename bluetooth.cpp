#include "bluetooth.h"

BluetoothSerial SerialBT;
BTMessage lastMessage;

void BTInit(){
  SerialBT.begin(btName);
}

BTResponse BTreceiveData(){
  if (SerialBT.available()) {
    //Clear code
    uint8_t code = 0;
    int16_t linear = 0;
    int16_t rotation = 0;
    
    
    char c = SerialBT.read();

    //Read code
    while(!isSeparator(c)){
      if(isEOL(c)) return BT_MSG_FAIL;
      uint8_t num;
      if(isNumber(c, num)) code = code * 10 + num;
      c = SerialBT.read();
    }

    c = SerialBT.read();

    //Read first param
    bool isNegative = false;
    while(!isSeparator(c)){
      if(isEOL(c)) return BT_MSG_FAIL;
      if(isNegativeSign(c)) isNegative = true;
      uint8_t num;
      if(isNumber(c, num)) linear = linear * 10 + num;
      c = SerialBT.read();
    }
    if(isNegative) linear *= -1;

    
    //Read second param
    isNegative = false;
    c = SerialBT.read();

    while(!isEOL(c)){
      if(isNegativeSign(c)) isNegative = true;
      uint8_t num;
      if(isNumber(c, num)) rotation = rotation * 10 + num;
      c = SerialBT.read();
    }
    if(isNegative) rotation *= -1;

    lastMessage = {code, linear, rotation};
    return BT_MSG_OK;
  }
  return BT_NO_MSG;
}

BTMessage BTgetLastMessage(){
  return lastMessage;
}

bool isNumber(char c,uint8_t& number){
  if(c >= '0' && c <= '9'){
    number = c - '0';
    return true;
  }
  return false;
}

bool isNegativeSign(char c){
  return c == '-';
}
bool isEOL(char c){
  return (c == '\r' || c == '\n');
}
bool isSeparator(char c){
  return c == separator;
}