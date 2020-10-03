#include "BluetoothSerial.h"
   
BluetoothSerial SerialBT;

const int s1 = 14;
#define com 15

void setup() {
  //Serial.begin(115200);
  SerialBT.begin("ESP32_TTT");
  pinMode(com, OUTPUT);
  digitalWrite(com, LOW);
  delay(1000);
}

void loop() {
  SerialBT.println(analogRead(s1));
  digitalWrite(com, HIGH);
  //Serial.println(analogRead(s1));
  //Serial.print("");

}
