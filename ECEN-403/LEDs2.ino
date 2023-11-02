//Pin connected to ST_CP of 74HC595
int latchPin = 3;
//Pin connected to SH_CP of 74HC595
int clockPin = 2;
//Pin connected to DS of 74HC595
int dataPin = 4;
byte  rowBitsToSend = 0;
byte columnBitsToSend = 0;
 
void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for( int i = 0; i < 5; i++)
    { 
        bitWrite(columnBitsToSend, i, HIGH);
    }
  shiftOut(dataPin, clockPin, MSBFIRST, columnBitsToSend);
  store();
//  shiftOut(dataPin, clockPin, MSBFIRST, 0);
}

void rowON(int rowNumber)
{
   bitWrite(rowBitsToSend, rowNumber, HIGH);
   shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
   store();
//   delay(2000);
}

void rowOFF(int rowNumber)
{
  bitWrite(rowBitsToSend, rowNumber, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
  store();
}

void allRowsOn()
{
    rowON(0);
    rowON(1);
    rowON(2);
    rowON(3);
    rowON(4);
}

void columnON(int colNumber)
{
  allRowsOn();
  for( int i = 0; i < 5; i++)
  {
    if( i == colNumber)
      continue;
    else 
      bitWrite(columnBitsToSend, i, HIGH);
  }
  shiftOut(dataPin, clockPin, MSBFIRST, columnBitsToSend);
  store();

}

void store()
{
   digitalWrite(latchPin, HIGH);
   delay(1);
   digitalWrite(latchPin, LOW);
//   delay(2);
}
 
void loop() 
{
  byte columnBitsToSend = 0;
  byte rowBitsToSend = 0;
  shiftOut(dataPin, clockPin, MSBFIRST, columnBitsToSend);
 
  
  
  
  rowON(1);
  delay(2000);
  rowOFF(1);
  delay(2000);


  allRowsOn();
  
  

}
















//  shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend);

//  store();
//  delay(2000);
//  rowON(0);
//  rowON(1);
//  rowON(2);
//  rowON(3);
//  rowON(4);
//  rowON(1);
//  rowON(0);
//  store();
//  delay(1000);
//  rowOFF(3);

//  store();
//  delay(1000);

//    allRowsOn();
//    delay(2000);

    
//    store();
//    delay(2000);


//  digitalWrite(*latchPin, LOW);
//  bitWrite(rowBitsToSend, 2, LOW);
//  shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
//  digitalWrite(latchPin, HIGH);
//  
//  digitalWrite(latchPin, LOW);
//  bitWrite(rowBitsToSend, 0, HIGH); // Gives us 00000001
//  bitWrite(rowBitsToSend, 3, HIGH); // Adds on to the previous modified bits to give us 00001001
//  shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
//  digitalWrite(latchPin, HIGH); // Tell the shift register we are done sending data so it can enable the outputs
//  delay(1000); // Not really necess
//
//  digitalWrite(latchPin, LOW);
//  bitWrite(rowBitsToSend, 0, LOW); // Gives us 00000001
//  bitWrite(rowBitsToSend, 3, LOW);
////  Serial.print(rowBitsToSend);
////  bitWrite(rowBitsToSend, 4, HIGH); // Adds on to the previous modified bits to give us 00001001
//  shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
//  digitalWrite(latchPin, HIGH); // 
////   
//  delay(1000);
//
//
//
//  digitalWrite(latchPin, LOW);
//    bitWrite(rowBitsToSend, 4, HIGH); // Adds on to the previous modified bits to give us 00001001
//    shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
//    digitalWrite(latchPin, HIGH); // 
//      delay(1000);
    
//}
    
 // Adds on to the previous modified bits to give us 00001001
//  shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
//  digitalWrite(latchPin, HIGH); // Tell the shift register we are done sending data so it can enable the outputs
//  delay(2); // Not really necessary in this example but it will be for lighting up multiple columns


//}
