#include <Arduino_FreeRTOS.h>
#include "BluetoothSerial.h"
   
BluetoothSerial SerialBT;

void TaskMUX( void *pvParameters );
void TaskSendData( void *pvParameters );

const int muxA = 23;
const int muxB = 24;
const int muxC = 25;

const int datPort = 26;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32LLL");

  pinMode(muxA, OUTPUT);  //A
  pinMode(muxB, OUTPUT);  //B
  pinMode(muxC, OUTPUT);  //C
}

xTaskCreate(
  TaskMUX
  , "MUX"
  , 128
  , NULL
  , 1
  , NULL);

xTaskCreate(
  TaskSendData
  , "SendData"
  , 128
  , NULL
  , 2
  , NULL);

void loop() {

}

void cases(byte bits){
  switch(bits){
    case 0b000:
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, LOW);
        break;
    case 0b001:
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, HIGH);
        break;
    case 0b010:
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, LOW);
        break;
    case 0b011:
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, HIGH);
        break;
    case 0b100:
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, LOW);
        break;
    case 0b101:
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, HIGH);
        break;
    case 0b110:
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, LOW);
        break;
    case 0b111:
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, HIGH);
        break;
  }
}

void TaskMUX(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  byte mux = 0b000;

  for(;;)
  {
    if(mux > 0b111){
      mux = 0b000;
    }
    cases(0b000);
    mux = mux + 0b001;
    vTaskDelay(100);
  }
}

void TaskSendData(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  for (;;)
  {
    int dat = analogRead(datPort);
    SerialBT.println(dat);
    vTaskDelay(1);
  }
}
  

  









  
