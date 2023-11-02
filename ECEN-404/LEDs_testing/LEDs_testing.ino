 
// Define Connections to 74HC595
const int led_latchPin = 3;
const int led_clockPin = 2;
const int led_dataPin = 4;


void setup ()
{
   Serial.begin(9600);
  // Setup 595 pins as Outputs
  pinMode(led_latchPin, OUTPUT);
  pinMode(led_clockPin, OUTPUT);
  pinMode(led_dataPin, OUTPUT);


}
 
void loop() {

int row_num[8] = {128,64,32,16,8,4,2,1};//,2,4,8,16,31,64,128};
int col_num[8] = {128,64,32,16,8,4,2,1};//,2,4,8,16,32,64,128};
  
  //row rows 0-8
  for (int rows = 7; rows >=0; rows--) 
  {  

//    //for sensor row 0-7
//    digitalWrite(led_latchPin, LOW);
//    int led_shiftin_rows = 1 << rows;
//    row_num[rows] = led_shiftin_rows;
//    Serial.print("Row number:");
//    Serial.println(led_shiftin_rows);
//    shiftOut(led_dataPin, led_clockPin, MSBFIRST, led_shiftin>>8);  //this first statement goes to the chained shift reg
////    shiftOut(led_dataPin, led_clockPin, MSBFIRST, led_shiftin); //goes to the first shift reg
//    digitalWrite(led_latchPin, HIGH);
//    delay(1000);
    
    for (int cols =0; cols <8; cols++)
    {
        digitalWrite(led_latchPin, LOW);
//        int led_shiftin_col = 1 << cols;
//        col_num[cols] = led_shiftin_col;
//        Serial.println(led_shiftin_col);
//        Serial.println(col_num[cols]);
        shiftOut(led_dataPin, led_clockPin, MSBFIRST, col_num[cols]); //this first statement goes to the chained shift reg- columns
        shiftOut(led_dataPin, led_clockPin, MSBFIRST, row_num [2] | row_num[3]); //this statment goes to the first shift reg - rows 

         
//        shiftOut(led_dataPin, led_clockPin, MSBFIRST, led_shiftin); 
//        shiftOut(led_dataPin, led_clockPin, MSBFIRST, shiftin>>8);//goes to the first shift reg
        digitalWrite(led_latchPin, HIGH);
        delay(100);
        
    }


  }


  
}
