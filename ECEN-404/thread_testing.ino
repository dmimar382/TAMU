#include "SoftwareSerial.h"
#include <pt.h>
SoftwareSerial MyBlue(1, 0); // RX | TX 


// Define Connections to LEDs 74HC595
const int led_latchPin = 3;
const int led_clockPin = 2;
const int led_dataPin = 4;


// Define Connections to Sensors 74HC595
const int latchPin = A0;
const int clockPin = A2;
const int dataPin = A1;

// Define Connections to Sensors 74HC165
int col_load = 7;
int col_dataIn = 9;
int col_clockIn = 8;


//define the arrays needed to control the LEDs 
int row_num[8] = {1,2,4,8,16,32,64,128};
int col_num[8] = {128,64,32,16,8,4,2,1};

//define the LED and Sensor matrix
int sensor_matrix[16][16], prev_sens[16][16];
int led_matrix[8][8];

bool data_logging = true;
int cycles=0;

int zeros = 0;

static struct pt pt1, pt2, pt3;//protothreads

void setup ()
{

  MyBlue.begin(38400);
    // Setup LED 595 pins as Outputs
  pinMode(led_latchPin, OUTPUT);
  pinMode(led_clockPin, OUTPUT);
  pinMode(led_dataPin, OUTPUT);

  
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

  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  

}

String oldFunc(int var) 
{
  String str;
  for (int i = 0; i < 8; i++)  
  {
    str.concat(((var >> i) & 1) == 1 ? "1" : "0");
  }
  return str;
}

void reset_leds(){
  digitalWrite(led_latchPin, LOW);
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, 0); //this first statement goes to the chained shift reg- columns
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, 0); //this statment goes to the first shift reg - rows 
  digitalWrite(led_latchPin, HIGH);
}

String format_string(byte incoming, byte incoming2)
{
    //correctly formatting the incoming information 
    String str1 = oldFunc(incoming);
    String str2 = oldFunc(incoming2);

    String total = str1 + str2;
    String correct_total;
    correct_total.concat(total.charAt(0));

    for(int i = 15; i > 0 ; i --)
    {
      correct_total.concat(total.charAt(i));
    }

    return correct_total;
  
}
void send_bluetooth()
{
//  if(MyBlue.available())
  {
    for(int i = 0; i < 16; i ++)
    {
      for( int j = 0; j < 16; j++)
      {
        Serial.print(sensor_matrix[i][j]);
      }
      Serial.println();
    }
    Serial.println();
  }  
}

void read_sensors(){
//  Serial.print("s");
    for (int numberToDisplay = 0; numberToDisplay < 16; numberToDisplay++) 
  {  
    
    digitalWrite(latchPin, LOW);
    int shiftin = 1 << numberToDisplay;
    shiftOut(dataPin, clockPin, MSBFIRST, shiftin>>8); //this first statement goes to the chained shift reg
    shiftOut(dataPin, clockPin, MSBFIRST, shiftin); //goes to the first shift reg
    digitalWrite(latchPin, HIGH);
//    delay(500);

    digitalWrite(col_load, LOW);
//    delayMicroseconds(5);
    digitalWrite(col_load, HIGH);
//    delayMicroseconds(5);

    digitalWrite(col_clockIn, HIGH);
    byte incoming = shiftIn(col_dataIn, col_clockIn, MSBFIRST);
    byte incoming2 = shiftIn(col_dataIn, col_clockIn, MSBFIRST);
    digitalWrite(col_clockIn, LOW);


    //format the string correctly
    String correct_total = format_string(incoming, incoming2);
  
    //inputting the information into a 16x16 sensor matrix and displaying
//    if(MyBlue.available())
//    {
        
        for( int i = 0; i < 16; i++)
        {
          sensor_matrix[numberToDisplay][i] = correct_total.charAt(i)- 48;
//          Serial.print(sensor_matrix[numberToDisplay][i]);
          if(sensor_matrix[numberToDisplay][i] == 0 )
            zeros++;
          if (zeros == 256)
          {
            reset_leds();
            zeros = 0;
          }
             
        }
         
      
//    }
  }
}

void led_on(int row, int col){
  digitalWrite(led_latchPin, LOW);
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, col); //this first statement goes to the chained shift reg- columns
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, row); //this statment goes to the first shift reg - rows 
  digitalWrite(led_latchPin, HIGH);
  //delay(0.5);
  //reset_leds();
}

void sensor_to_led(){
  //converting the sensor 16x16 matrix to the 8x8 led matrix;
  int led_row = 0;
  int led_col = 0;

  //light up LEDS according to the matrix 
  int row_light = 0;
  int col_light = 0;

  int count_cols = 0;
  int count_rows = 0;


  
//  Serial.println("LED MATRIX:");

  for (int i = 0; i < 15; i ++)
  {
    for (int j = 0; j < 15; j++)
    {
      
      led_matrix[led_row][led_col] = sensor_matrix[i][j] | sensor_matrix[i][j+1] | sensor_matrix[i+ 1][j] | sensor_matrix[i+1][j+1];
//      Serial.print(led_matrix[led_row][led_col]);
      if(led_matrix[led_row][led_col] == 1)
      {          
        row_light = row_num[led_row];
        col_light = col_num[led_col];
        led_on(row_light, col_light);
//        reset_leds();
      }

      count_cols += 1;
      led_col = (count_cols)%8;
      j +=1;
      
    }
  
    i += 1;
    count_rows += 1;
    led_row = count_rows %8;
  }
}

//blue_sensor, turn_leds
static int protothread1(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) { // never stop 
    /* each time the function is called the second boolean
    *  argument "millis() - timestamp > interval" is re-evaluated
    *  and if false the function exits after that. */
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis(); // take a new timestamp
    send_bluetooth();
  }
  PT_END(pt);
}

static int protothread2(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) { // never stop 
    /* each time the function is called the second boolean
    *  argument "millis() - timestamp > interval" is re-evaluated
    *  and if false the function exits after that. */
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis(); // take a new timestamp
    read_sensors();
//    sensor_to_led();
  }
  PT_END(pt);
}

static int protothread3(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) { // never stop 
    /* each time the function is called the second boolean
    *  argument "millis() - timestamp > interval" is re-evaluated
    *  and if false the function exits after that. */
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis(); // take a new timestamp
//    read_sensors();
    sensor_to_led();
  }
  PT_END(pt);
}








void loop() 
{
  protothread2(&pt2, 25);
  protothread3(&pt3, 25);
  
//  read_sensors();
//  sensor_to_led();
//  protothread1(&pt1, 1500); // schedule the two protothreads
    
}
