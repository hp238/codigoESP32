#include "BluetoothSerial.h"
#include <SPI.h>
   
BluetoothSerial SerialBT;

//pinagem do ESP32
//#define pinDIN 12     //MISO
//#define pinDOUT 13    //MOSI
#define pinCS 3       //CS
#define pinSCLK 14    //SCLK
#define pinSTART 4
#define pinRESET 2
#define pinPWDN 22
#define pinDRDY 16
#define pinCLK 6

//comandos ADS
uint8_t SDATAC = 0x11;
uint8_t START = 0X08;
uint8_t STOP = 0x0A;
uint8_t WREG = 0x40;
uint8_t RREG = 0x20;

//Registradores
uint8_t CONFIG1 = 0x01;
uint8_t CONFIG2 = 0x02;
uint8_t CONFIG3 = 0x03;
uint8_t LOFF = 0x04;
uint8_t CH1SET = 0x05;
uint8_t CH2SET = 0x06;
uint8_t CH3SET = 0x07;
uint8_t CH4SET = 0x08;
uint8_t BIAS_SENSP = 0x0D;
uint8_t BIAS_SENSN = 0x0E;
uint8_t LOFF_SENSP = 0x0F;
uint8_t LOFF_SENSN = 0x10;
uint8_t LOFF_FLIP = 0x11;
uint8_t LOFF_STATP = 0x12;
uint8_t LOFF_STATN = 0x13;
//uint8_t GPIO = 0x14;
uint8_t MISC1 = 0x15;
uint8_t MISC2 = 0x16;

/**************************************************************************************************
 * Inicialização
 **************************************************************************************************/
 
//inicialização das portas do ESP
void gpioStartup() {
  //pinMode(pinDIN, INPUT);        //entrada serial 
  //pinMode(pinDOUT, OUTPUT);      //saída serial
  pinMode(pinCS, OUTPUT);        //LOW p/ ativar comunicação SPI
  pinMode(pinSCLK, OUTPUT);      //entrada do clock da comunicação SPI
  pinMode(pinSTART, OUTPUT);     //HIGH p/ iniciar conversão
                                  //LOW p/ para conversão (ou STOP)
  pinMode(pinRESET, OUTPUT);
  pinMode(pinPWDN, OUTPUT); 
  pinMode(pinDRDY, INPUT);       //HIGH durante a conversão dos dados
                                  //LOW p/ informar a existência de dados disponíveis p/ leitura  
  pinMode(pinSCLK, OUTPUT);       //entrada do clock
  
  digitalWrite(pinRESET, HIGH);  //LOW p/ resetar
  digitalWrite(pinPWDN, HIGH);   //alimentar os circuitos
  digitalWrite(pinSTART, LOW);   
  digitalWrite(pinCS, HIGH);     //desativar comunicação SPI
  
}



/*************************************************************************************************
 * Comandos ADS
 **************************************************************************************************/

//resetar ADS
void adsReset(){
  delay(150);
  digitalWrite(pinRESET, LOW);    //reset
  delay(1);
  digitalWrite(pinRESET, HIGH);
  delay(1);
}

//configurar ADS
void configADS(){
  writeReg(CONFIG1,0xB0);     //7 - 1 (reservado)
                              //6 - 0 : modo daisy-chain
                              //5 - 1 : clock externo habilitado
                              //4 - 1 (reservado)
                              //3 - 0 
                              //2 - 0 : 16kSPS
                              //1 - 0
                              //0 - 0
                              
  writeReg(CONFIG2, 0xC0);    //7 - 1 (reservado)
                              //6 - 1
                              //5 - 0
                              //4 - 0 : sinais de testes externos
                              //3 - 0 (reservado)
                              //2 - 0 : (VREFP-VREFN)/2400 (amplitude do sinal de teste)
                              //1 - 0 : fCLK/2^21 (frequência do sinal de teste)
                              //0 - 0
                          
  writeReg(CONFIG3, 0xEF);    //7 - 1 : buffer de referência interno ativado
                              //6 - 1 (reservado)
                              //5 - 1
                              //4 - 0 : BIAS aberto
                              //3 - 1 : BIASref ...
                              //2 - 1 : buffer BIAS ativado
                              //1 - 1 : BIAS sense ativado
                              //0 - 1 : BIAS conectado

  writeReg(CH1SET, 0x66);     //7 - 0 : ativado
                              //6 - 1 : ganho 24
                              //5 - 1
                              //4 - 0
                              //3 - 0 : SRB2 fechado
                              //2 - 1 : eletrodo positivo
                              //1 - 1
                              //0 - 0

  writeReg(CH2SET, 0x66);     //7 - 0 : ativado
                              //6 - 1 : ganho 24
                              //5 - 1
                              //4 - 0
                              //3 - 0 : SRB2 fechado
                              //2 - 1 : eletrodo positivo
                              //1 - 1
                              //0 - 0

  writeReg(CH3SET, 0x66);     //7 - 0 : ativado
                              //6 - 1 : ganho 24
                              //5 - 1
                              //4 - 0
                              //3 - 0 : SRB2 fechado
                              //2 - 1 : eletrodo positivo
                              //1 - 1
                              //0 - 0

  writeReg(CH4SET, 0x66);     //7 - 0 : ativado
                              //6 - 1 : ganho 24
                              //5 - 1
                              //4 - 0
                              //3 - 0 : SRB2 fechado
                              //2 - 1 : eletrodo positivo
                              //1 - 1
                              //0 - 0

  writeReg(BIAS_SENSP, 0X0F);     //7 - 0 
                                  //6 - 0 
                                  //5 - 0
                                  //4 - 0
                                  //3 - 1 
                                  //2 - 1 
                                  //1 - 1
                                  //0 - 1
                              
  writeReg(BIAS_SENSN, 0x0F);     //7 - 0 
                                  //6 - 0 
                                  //5 - 0
                                  //4 - 0
                                  //3 - 1 
                                  //2 - 1 
                                  //1 - 1
                                  //0 - 1

  
}

/**************************************************************************************************
 * Comandos ESP (SPI)
 **************************************************************************************************/

//inicializar comunicação SPI
void spiStartup() {
  SPI.begin();
  SPI.beginTransaction(SPISettings(2048000, MSBFIRST, SPI_MODE1));  //clock de 2.048MHz
                                                                    //transmissao pelo Most Significant Bit (MSB)
                                                                    //captura do dado na descida do clock
}

 //enviar dados de configuração p/ o ADS
 void commandSPI(uint8_t command){
  digitalWrite(pinCS, LOW);             //ativar comunicação SPI
  SPI.transfer(command);                //envio dos dados
  digitalWrite(pinCS, HIGH);            //desativar comunicação SPI
 }

 //enviar dados via SPI
 void writeReg(uint8_t reg, uint8_t dat){
  digitalWrite(pinCS, LOW);             //ativar comunicação SPI
  SPI.transfer(WREG|reg);
  SPI.transfer(0);
  SPI.transfer(dat);
  digitalWrite(pinCS, HIGH);            //desativar comunicação SPI
 }

 //ler dados via SPI
 uint8_t readReg(uint8_t reg){
  uint8_t dat;
  digitalWrite(pinCS, LOW);             //ativar comunicação SPI
  SPI.transfer(RREG|reg);
  SPI.transfer(0);
  dat = SPI.transfer(0);
  digitalWrite(pinCS, HIGH);            //desativar comunicação SPI
  return dat;
 }
//
/**************************************************************************************************
 * SETUP e LOOP
 **************************************************************************************************/
void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32test");    //inicialização bluetooth
  
  //delay(1000);
  //inicialização do ADS e do ESP
  gpioStartup();
  spiStartup();
  adsReset();

  //comandos ADS
  commandSPI(SDATAC);                //SDATAC cancela o modo de leitura contínua de dados
  commandSPI(STOP);                  //STOP para conversão dos dados

  //verificação do ADS1299-4PAGR

  //configurar ADS
  configADS();

  commandSPI(START);

}
    
void loop()
{
   if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
