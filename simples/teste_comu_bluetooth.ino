#include "BluetoothSerial.h"
   
BluetoothSerial SerialBT;

int aux[50];
float sine;
int sine_i;
    
void setup()
{
  SerialBT.begin("ESP32tes");
  delay(1000);
}
    
void loop()
{
  String inputFromOtherSide;
  //if (SerialBT.available()) {
    for(int x=-180; x<=180; x++){
    sine = sin(x*(3.1415/180.0));
    sine_i = (127+int(sine*255.0/2.0));
    //for(int o =0; o<8; o++){
      SerialBT.println(sine_i);
    //}
  //}
  }
}
