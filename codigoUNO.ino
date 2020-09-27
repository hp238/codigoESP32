//Developed by Conor Russomanno (June 2013)
//This example uses the ADS1299 Arduino Library, a software bridge between the ADS1299 TI chip and 
//Arduino. See http://www.ti.com/product/ads1299 for more information about the device and the reference
//folder in the ADS1299 directory for more information about the library.

#include <ADS1299.h>

ADS1299 ADS;

//Arduino Uno - Pin Assignments; Need to use ICSP for later AVR boards
// SCK = 13
// MISO [DOUT] = 12
// MOSI [DIN] = 11
// CS = 10; 
// DRDY = 9;

//  0x## -> Arduino Hexadecimal Format
//  0b## -> Arduino Binary Format

boolean deviceIDReturned = false;
boolean startedLogging = false;

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("ADS1299-bridge has started!");
  
  ADS.setup(9, 10); // (DRDY pin, CS pin);
  delay(10);  //delay to ensure connection
  
  ADS.RESET();
}

void loop(){
  
  if(deviceIDReturned == false){
    
    ADS.getDeviceID(); //Funciton to return Device ID
    
    //prints dashed line to separate serial print sections
    Serial.println("----------------------------------------------");
    
    //Read ADS1299 Register at address 0x00 (see Datasheet pg. 35 for more info on SPI commands)
    ADS.RREG(0x00);
    Serial.println("----------------------------------------------");
    
    //PRINT ALL REGISTERS... Read 0x17 addresses starting from address 0x00 (these numbers can be replaced by binary or integer values)
    ADS.RREG(0x00, 0x17);
    Serial.println("----------------------------------------------");
    
    //Write register command (see Datasheet pg. 38 for more info about WREG)
    ADS.WREG(CONFIG3, 0b11010110);
    Serial.println("----------------------------------------------");

    ADS.WREG(CONFIG1, 0b11010000);
    Serial.println("----------------------------------------------");

    ADS.WREG(CONFIG2, 0b11010110);
    Serial.println("----------------------------------------------");

    ADS.WREG(CH1SET, 0b01100110);
    Serial.println("----------------------------------------------");

    ADS.WREG(CH2SET, 0b01100110);
    Serial.println("----------------------------------------------");

    ADS.WREG(CH3SET, 0b01100110);
    Serial.println("----------------------------------------------");

    ADS.WREG(CH4SET, 0b01100110);
    Serial.println("----------------------------------------------");

    ADS.WREG(MISC1, 0b0010000);
    Serial.println("----------------------------------------------");
    Serial.println("----------------------------------------------");
    Serial.println("----------------------------------------------");

    ADS.RREG(CONFIG1);
    Serial.println("----------------------------------------------");

    ADS.RREG(CONFIG2);
    Serial.println("----------------------------------------------");

    ADS.RREG(CONFIG3);
    Serial.println("----------------------------------------------");
    
    ADS.RREG(CH1SET);
    Serial.println("----------------------------------------------");

    ADS.RREG(CH2SET);
    Serial.println("----------------------------------------------");

    ADS.RREG(CH3SET);
    Serial.println("----------------------------------------------");

    ADS.RREG(CH4SET);
    Serial.println("----------------------------------------------");

    ADS.RREG(MISC1);
    Serial.println("----------------------------------------------");
    
    //Repeat PRINT ALL REGISTERS to verify that WREG changed the CONFIG1 register
    ADS.RREG(0x00, 0x17);
    Serial.println("----------------------------------------------");
    
    //Start data conversions command
    ADS.START(); //must start before reading data continuous
    deviceIDReturned = true;
  }
  
  //print data to the serial console for only the 1st 10seconds of 
  while(millis()<10000){
    if(startedLogging == false){
      Serial.print("Millis: "); //this is to see at what time the data starts printing to check for timing accuracy (default sample rate is 250 sample/second)
      Serial.println(millis());
      startedLogging = true;
    }
    
    //Print Read Data Continuous (RDATAC) to Ardiuno serial monitor... 
    //The timing of this method is not perfect yet. Some data is getting lost 
    //and I believe its due to the serial monitor taking too much time to print data and not being ready to recieve to packets
    ADS.updateData();  
  }
  
  
}
