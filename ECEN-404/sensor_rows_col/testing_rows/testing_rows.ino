
// Define Connections to 74HC595
const int latchPin = A0;
const int clockPin = A2;
const int dataPin = A1;

// Define Connections to 74HC165
int col_load = 7;
int col_dataIn = 9;
int col_clockIn = 8;
 
void setup ()
{
  // Setup 595 pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Setup Serial Monitor
  Serial.begin(9600);
 
  // Setup 74HC165 connections
  pinMode(col_load, OUTPUT);
  pinMode(col_clockIn, OUTPUT);
  pinMode(col_dataIn, INPUT);

}

String oldFunc(int var) {
  
  String str;
//  Serial.print("Sting is:");
//  Serial.println(str);
  for (int i = 0; i < 8; i++)  {
//    Serial.print(((var >> i) & 1) == 1 ? "1" : "0");
    str.concat(((var >> i) & 1) == 1 ? "1" : "0");
  }

  return str;
//
//    Serial.print("Sting is:");
//  Serial.println(str);
//  Serial.println();
}
 
void loop() {


  //row rows 0-8
  for (int numberToDisplay = 0; numberToDisplay < 16; numberToDisplay++) 
  {  

    //for sensor row 0-7
    digitalWrite(latchPin, LOW);
    int shiftin = 1 << numberToDisplay;
    shiftOut(dataPin, clockPin, MSBFIRST, shiftin>>8); //this first statement goes to the chained shift reg
    shiftOut(dataPin, clockPin, MSBFIRST, shiftin); //goes to the first shift reg
    digitalWrite(latchPin, HIGH);
//    delay(500);


//    checking the column states for each row
//    Serial.print("Pin States for row:");
//    Serial.println(numberToDisplay);

    digitalWrite(col_load, LOW);
    delayMicroseconds(5);
    digitalWrite(col_load, HIGH);
    delayMicroseconds(5);

    digitalWrite(col_clockIn, HIGH);
    byte incoming = shiftIn(col_dataIn, col_clockIn, MSBFIRST);
    byte incoming2 = shiftIn(col_dataIn, col_clockIn, MSBFIRST);
    digitalWrite(col_clockIn, LOW);


    String str1 = oldFunc(incoming);
    String str2 = oldFunc(incoming2);

    String total = str1 + str2;
    String correct_total;
    correct_total.concat(total.charAt(0));

    for(int i = 15; i > 0 ; i --)
    {
      correct_total.concat(total.charAt(i));
    }

    Serial.println(correct_total);
    
//    Serial.print(incoming, BIN);
//    Serial.println(incoming2, BIN);

//    delay(50);

  }
  Serial.println("END:");

  delay(1000);


  
}
