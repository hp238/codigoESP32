//HARDWARE
//portas ADS1299
const int RESET = 12;   //LOW p/ resetar
const int START = 13;   //HIGH p/ iniciar conversão e LOW p/ parar a conversão
const int PWDN = 14;    //LOW para não alimentar todos os circuitos
const int CLK = 27;   //clock input
const int DOUT = 25;    //saída serial
const int CLKSEL = 26;    //LOW p/ clock externo e HIGH p/ clock interno
const int SCLK = 32;    //entrada clock serial
const int DIN = 33;   //entrada serial
const int DRDY = 34;    //HIGH p/ dados em conversão e LOW p/ dados disponíveis para leitura
const int CS = 35;    //LOW p/ comunicação serial

//Registros p/ configurar ADS1299
const int REGIST[] = {B00100000, B00011001, B00011110, B10010100, B11010010, B01101001,
                      B00000111, B01100000, B01100000, B01100000, B01100000, B01100000,
                      B01100000, B01100000, B01100000, B00000000, B00000000, B00000000, 
                      B00000000, B00000000, B00000000, B00000000, B00000000, B00100000, 
                      B00000000, B00000000};


//SOFTWARE


void setup() {
  //HARDWARE
  //configurando portas
  pinMode(RESET, INPUT);
  pinMode(START, OUTPUT);
  pinMode(PWDN, INPUT);
  pinMode(CLK, INPUT);
  pinMode(DOUT, OUTPUT);
  pinMode(CLKSEL, INPUT);
  pinMode(SCLK, INPUT);
  pinMode(DIN, OUTPUT);
  pinMode(DRDY, OUTPUT);
  pinMode(CS, OUTPUT);

  digitalWrite(PWDN, HIGH);
  delay(1000);
  digitalWrite(CS, LOW);
  delay(1000);
  digitalWrite(START, LOW);
  
  registro();

  digitalWrite(START, HIGH);


  //SOFTWARE

}

void loop() {
  //HARDWARE

  //SOFTWARE

}

//HARDWARE
void registro(){
  for(int i=0 ; i<26 ; i++){
    for(int k=0 ; k<8 ; k++){
      analogWrite(SCLK , 127);
      analogWrite(DIN , bitRead(REGIST[i] , k));
    }
    analogWrite(SCLK , LOW);
    delay(10);
  }
  delay(10);
}

//SOFTWARE
