#define MUX_A 3
#define MUX_B 4
#define MUX_C 5


void setup() {
  Serial.begin(9600);
  
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);

}

void cases(byte bits){
  switch(bits){
    case 0b000:
        digitalWrite(MUX_A, LOW);
        digitalWrite(MUX_B, LOW);
        digitalWrite(MUX_C, LOW);
        break;
    case 0b001:
        digitalWrite(MUX_A, LOW);
        digitalWrite(MUX_B, LOW);
        digitalWrite(MUX_C, HIGH);
        break;
    case 0b010:
        digitalWrite(MUX_A, LOW);
        digitalWrite(MUX_B, HIGH);
        digitalWrite(MUX_C, LOW);
        break;
    case 0b011:
        digitalWrite(MUX_A, LOW);
        digitalWrite(MUX_B, HIGH);
        digitalWrite(MUX_C, HIGH);
        break;
    case 0b100:
        digitalWrite(MUX_A, HIGH);
        digitalWrite(MUX_B, LOW);
        digitalWrite(MUX_C, LOW);
        break;
    case 0b101:
        digitalWrite(MUX_A, HIGH);
        digitalWrite(MUX_B, LOW);
        digitalWrite(MUX_C, HIGH);
        break;
    case 0b110:
        digitalWrite(MUX_A, HIGH);
        digitalWrite(MUX_B, HIGH);
        digitalWrite(MUX_C, LOW);
        break;
    case 0b111:
        digitalWrite(MUX_A, HIGH);
        digitalWrite(MUX_B, HIGH);
        digitalWrite(MUX_C, HIGH);
        break;
  }
}

void loop() {
  cases(0b000);
  delay(10);
  cases(0b001);
  delay(10);
  cases(0b010);
  delay(10);
  cases(0b011);
  delay(10);
  cases(0b100);
  delay(10);
  cases(0b101);
  delay(10);
  cases(0b110);
  delay(10);
  cases(0b111);
  delay(10);

}
