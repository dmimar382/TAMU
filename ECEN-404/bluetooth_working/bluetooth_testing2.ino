/* 
HC05 - Bluetooth AT-Command mode 
modified on 10 Feb 2019 
by Saeed Hosseini 
https://electropeak.com/learn/guides
*/ 
#include "SoftwareSerial.h"
SoftwareSerial MyBlue(1, 0); // RX | TX 
void setup() 
{ 
  Serial.begin(9600); 
  MyBlue.begin(38400);  //Baud Rate for AT-command Mode.  
  Serial.println("***AT commands mode***"); 
} 
void loop() 
{ 
  //from bluetooth to Terminal. 
  if (MyBlue.available())
  {
//    Serial.write("Howdy\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n");
    Serial.write("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n"); 
    Serial.write("\n\n\n");

    delay(1000);
//    MyBlue.print("[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1]\n"); 
    
     
  }
     
  //from termial to bluetooth 
  if (Serial.available())
  {
//     MyBlue.write(Serial.read());
//     MyBlue.print("SHOOBIE");
  }
    
}
