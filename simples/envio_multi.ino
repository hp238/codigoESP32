#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
TaskHandle_t TaskReadData;
TaskHandle_t TaskSendData;

const int s1 = 32;
const int muxA = 33;
const int muxB = 19;
const int muxC = 18;

int tamanho = 100;
int sinal[8][100];
boolean set = false;



  void setup() {
  //SerialBT.begin("ESP32SSS");
  Serial.begin(115200);
  pinMode(muxA, OUTPUT);
  pinMode(muxB, OUTPUT);
  pinMode(muxC, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);

  xTaskCreatePinnedToCore(
                    TaskReadDatacode,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    5,           /* priority of the task */
                    &TaskReadData,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  xTaskCreatePinnedToCore(
                    TaskSendDatacode,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &TaskSendData,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

}

void TaskSendDatacode (void * pvParameters){
  //int i = 0;
  int k = 0;
  int t = 0;
  for(;;){
    
    k++;
    //Serial.println("*******\\\\\\\********");
    //Serial.println("");
    if(set == true){
      //t++;
      //SerialBT.begin("ESP32SSS");
      //SerialBT.println(t);
      for(int i = 0; i<tamanho; i++){
        for(int y = 0; y<8 ; y++){
          Serial.println(sinal[y][i]);
          //SerialBT.println(sinal[y][i]);
          //delay(10);
        }
        //Serial.print(i);
        //Serial.println("-----------");
      }
      set = false;
      vTaskDelay(800);
      /*
      i = i+1;
      if(i==1000){
        i=0;
        set = false;
        vTaskDelay(1000);
        
      }*/
    }
  }
}

int i = 0;

void TaskReadDatacode (void * pvParameters){
  byte mux = 0b000;
  //int i = 0;
  for(;;){
    //Serial.println("~~~~~~~~~~~~~~~~~~~~");
    if(set == false){
      //cases(mux);
      //delay(500);
      for(int i = 0; i<tamanho; i++){
        //Serial.println("i");
        //Serial.print(i);
        //Serial.println("-----------");
        /*
        for(int y = 0; y<8 ; y++){
          //Serial.println("y");
          //Serial.print(y);
          
          //sinal[y][i] = analogRead(s1);
        }*/
        /*
        i++;
        if(i==20){
          i=0;
        }*/
        //Serial.println("+++++++++++");
        
        //delay(1);
        int y = 0;
        int del = 1;
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, LOW);
        delay(del);
        sinal[y][i] = analogRead(s1);
        //sinal[y][i] = i+10;
        y++;
        
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, HIGH);
        delay(del);
        sinal[y][i] = analogRead(s1);
        //sinal[y][i] = i+10;
        y++;
        
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, LOW);
        delay(del);
        sinal[y][i] = analogRead(s1);
        //sinal[y][i] = i+10;
        //sinal[y][i] = i+y;
        y++;
        
        digitalWrite(muxC, LOW);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, HIGH);
        delay(del);
        sinal[y][i] = analogRead(s1);
        //sinal[y][i] = i+10;
        y++;
        
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, LOW);
        delay(del);
        sinal[y][i] = analogRead(s1);
        //sinal[y][i] = i+10;
        y++;
        
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, LOW);
        digitalWrite(muxA, HIGH);
        delay(del);
        sinal[y][i] = analogRead(s1);
        //sinal[y][i] = i+10;
        y++;
        
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, LOW);
        delay(del);
        sinal[y][i] = i+10;
        y++;
        
        digitalWrite(muxC, HIGH);
        digitalWrite(muxB, HIGH);
        digitalWrite(muxA, HIGH);
        delay(del);
        sinal[y][i] = analogRead(s1);
        //sinal[y][i] = i+10;
        y = 0;
        //delay(del);
        //Serial.println(i);
      }
      set = true;
      //Serial.println("////1////");
      //vTaskDelay(500);
      
      /*
      i = i+1;
      if(i==1000){
        i=0;
        set = true;
        vTaskDelay(1000);
      }*/
      vTaskDelay(500);
    }
  }
}


void loop() {

}
