#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int s1 = 32;
const int muxA = 33;
const int muxB = 19;
const int muxC = 18;
int tamanho = 1;

int sinal[8][1];
boolean set = false;


void setup() {
  // put your setup code here, to run once:
  //SerialBT.begin("ESP32LLL");
  Serial.begin(115200);
  pinMode(muxA, OUTPUT);
  pinMode(muxB, OUTPUT);
  pinMode(muxC, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);

}

void loop() {
  readData();
  sendData();

}

void readData(){
  for(int i=0 ; i<tamanho ; i++){
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
  }
}

void sendData(){
  //SerialBT.println("------------------------------");
  for(int i = 0; i<tamanho ; i++){
    //SerialBT.println(i);
    //SerialBT.println("----------");
    for(int y = 0; y<8 ; y++){
      Serial.println(sinal[y][i]);
      
      //SerialBT.println(sinal[y][i]);
    }
  }
}
