#include <Arduino.h>
#include <analogWrite.h>

#define s1 34
#define s2 35
#define s3 32
#define s4 33
#define s5 25
#define s6 26
#define s7 27
#define s8 14

#define com 13


float sine1;
float sine2;
float sine3;
float sine4;
float sine5;
float sine6;
float sine7;
float sine8;
int sine_i;

void setup() {
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s5, OUTPUT);
  pinMode(s6, OUTPUT);
  pinMode(s7, OUTPUT);
  pinMode(s8, OUTPUT);
  Serial.begin(115200);

  pinMode(com, INPUT);

}

void loop() {
  for(int i=-180; i<180;i++){
    if(digitalRead(com)==HIGH){
      sine1 = sin(i*(3.1415/180.0));
      sine2 = 2*sin(i*(3.1415/180.0));
      sine3 = 3*sin(i*(3.1415/180.0));
      sine4 = 4*sin(i*(3.1415/180.0));
      sine5 = 5*sin(i*(3.1415/180.0));
      sine6 = 6*sin(i*(3.1415/180.0));
      sine7 = 7*sin(i*(3.1415/180.0));
      sine8 = 8*sin(i*(3.1415/180.0));
      
      //sine_i=127+int(sine*255.0/2.0);
  
      analogWrite(s1, 127+int(sine1*255.0/2.0));
      analogWrite(s2, 127+int(sine2*255.0/2.0));
      analogWrite(s3, 127+int(sine3*255.0/2.0));
      analogWrite(s4, 127+int(sine4*255.0/2.0));
      analogWrite(s5, 127+int(sine5*255.0/2.0));
      analogWrite(s6, 127+int(sine6*255.0/2.0));
      analogWrite(s7, 127+int(sine7*255.0/2.0));
      analogWrite(s8, 127+int(sine8*255.0/2.0));
    }else{
      i=i-1;
    }
  }

}
