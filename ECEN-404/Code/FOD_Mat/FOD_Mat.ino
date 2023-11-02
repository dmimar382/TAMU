#include "SoftwareSerial.h"
//define the pins on arduino that are connected to Bluetooth module 
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
//this is the number needed to send a signal to an LED row / column to turn on a certain LED
//Example: row_num[0] = 1, col_num[0] = 128 will turn on LED at position (0,0) - top left corner
//of PCB  
int row_num[8] = {1,2,4,8,16,32,64,128};
int col_num[8] = {128,64,32,16,8,4,2,1};

//define the LED and Sensor, and Bluetooth matrix
//Sensor matrix stores data about the sensors triggered on a single mat
//LED matrix will be calculted based on the sensor matrix & stores which LEDs need to be triggered
//Bluetooth matrix stores information that is sent to app in set time periods 
int sensor_matrix[16][16], bluetooth_matrix[16][16];
int led_matrix[8][8];

//cycles are meant to keep track how many times the code goes through loop(). At cycles = # bluetooth 
//data is sent 
int cycles=0;

//Variable keeps track of how many sensors are not triggered. When zeros = 256 (total number of sensors)
//LEDs are reset
int zeros = 0;

void setup ()
{

  //setup for bluetooth data being sent 
  MyBlue.begin(38400);

  // Setup Serial Monitor
  Serial.begin(9600);
  
  // Setup LED 595 pins as Outputs
  pinMode(led_latchPin, OUTPUT);
  pinMode(led_clockPin, OUTPUT);
  pinMode(led_dataPin, OUTPUT);

  
  // Setup Sensor 595 pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Setup 74HC165 connections
  pinMode(col_load, OUTPUT);
  pinMode(col_clockIn, OUTPUT);
  pinMode(col_dataIn, INPUT);

}

//This function is meant to format the incomming data from the sensors to the correct datatype
//The int needs to be converted to a string, so that in the format_string function an reorder the 
//incoming bytes, making the bits correspond 1-to-1 with the PCB board.  
String format(int var) 
{
  String str;
  for (int i = 0; i < 8; i++)  
  {
    str.concat(((var >> i) & 1) == 1 ? "1" : "0");
  }
  return str;
}

//This function turns all of the LEDs OFF
void reset_leds(){
  digitalWrite(led_latchPin, LOW);
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, 0); //this first statement goes to the chained shift reg- columns
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, 0); //this statment goes to the first shift reg - rows 
  digitalWrite(led_latchPin, HIGH);
}

//This function is needed in order to have a 1-to-1 ratio between the code and the board. The top left corner is sensor (0,0), the bottom right corner
//is sensor (255,255).Because of incorrect wiring in Altium, this needs to be corrected in code to make this happen.
String format_string(byte incoming, byte incoming2)
{
    //correctly formatting the incoming information 
    String str1 = format(incoming);
    String str2 = format(incoming2);

    String total = str1 + str2;
    String correct_total;
    
    //The first character is correct, the rest are flipped
    correct_total.concat(total.charAt(0));
    for(int i = 15; i > 0 ; i --)
    {
      correct_total.concat(total.charAt(i));
    }

    return correct_total;
  
}

//This function reads in data from the sensors and inputs that data into a 16x16 matrix
int cycle = 0;
void read_sensors()
{
  for (int i = 0; i < 16; i++) 
  {  
    //595 shift regs to sensors
    //This turns on each row one by one
    digitalWrite(latchPin, LOW);
    int shiftin = 1 << i;
    shiftOut(dataPin, clockPin, MSBFIRST, shiftin>>8); //this first statement goes to the chained shift reg
    shiftOut(dataPin, clockPin, MSBFIRST, shiftin); //goes to the first shift reg
    digitalWrite(latchPin, HIGH);

    //recieving data from 165 shift regs 
    digitalWrite(col_load, LOW);
    digitalWrite(col_load, HIGH);

    //storing data from 165 shift regs
    //with a known row on, check the columns and store if anything is "high"
    //incoming is from the first 8 columns, incoming2 is from the next 8 columns
    digitalWrite(col_clockIn, HIGH);
    byte incoming = shiftIn(col_dataIn, col_clockIn, MSBFIRST);
    byte incoming2 = shiftIn(col_dataIn, col_clockIn, MSBFIRST);
    digitalWrite(col_clockIn, LOW);


    //format the string correctly
    String correct_total = format_string(incoming, incoming2);
  
    //inputting the information into a 16x16 sensor matrix
    for( int j = 0; j < 16; j++)
    {
      //need to account for ascii, so -48 
      sensor_matrix[i][j] = correct_total.charAt(j)- 48;

      //counting zeros in the matrix. If all values == 0, reset all leds
      if(sensor_matrix[i][j] == 0 )
        zeros++;
      //when nothing is detected on the board, set all leds to 0
      
      if (zeros == 256)
      {
        reset_leds();
        zeros = 0;
      }     
    }     
  }       
}


//function to turn on a specified led
void led_on(int row, int col)
{
  digitalWrite(led_latchPin, LOW);
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, col); //this first statement goes to the chained shift reg- columns
  shiftOut(led_dataPin, led_clockPin, MSBFIRST, row); //this statment goes to the first shift reg - rows 
  digitalWrite(led_latchPin, HIGH);
}

//function to convert the 16x16 sensor matrix to an 8x8 led matrix
void sensor_to_led()
{
  //variables to indicate which led to light up; goes from 0 to 7
  int led_row = 0;
  int led_col = 0;

  //light up LEDS according to the matrix, variables passed into led_on function
  int row_light = 0;
  int col_light = 0;

  //variables needed to keep track of the position in the 8x8 led matrix
  int count_cols = 0;
  int count_rows = 0;

  for (int i = 0; i < 15; i ++)
  {
    for (int j = 0; j < 15; j++)
    {
      //this converts the sensor matrix to the led matrix.
      //does so by preforming the OR operation on the bit to the right, bottom and diagonally from the current position. 
      //if any of the sensors are triggered in the "square", then the LED will be "on"
      led_matrix[led_row][led_col] = sensor_matrix[i][j] | sensor_matrix[i][j+1] | sensor_matrix[i+ 1][j] | sensor_matrix[i+1][j+1];

      //turning on led as soon as a 1 is detected 
      if(led_matrix[led_row][led_col] == 1 && led_row !=0 && led_col !=0)
      {          
        row_light = row_num[led_row] | row_num[led_row+1] | row_num[led_row-1];
        col_light = col_num[led_col] | col_num[led_col+1] | col_num[led_col-1];
        led_on(row_light, col_light);
      }
      if(led_matrix[led_row][led_col] == 1 && led_row ==0 && led_col !=0 )
      {          
        row_light = row_num[led_row] | row_num[led_row+1];
        col_light = col_num[led_col] | col_num[led_col+1] | col_num[led_col-1];
        led_on(row_light, col_light);
      }
      if(led_matrix[led_row][led_col] == 1 && led_row ==7 && led_col !=0 )
      {          
        row_light = row_num[led_row] | row_num[led_row-1];
        col_light = col_num[led_col] | col_num[led_col+1] | col_num[led_col-1];
        led_on(row_light, col_light);
      }
      if(led_matrix[led_row][led_col] == 1 && led_row !=0 && led_col ==0)
      {          
        row_light = row_num[led_row] | row_num[led_row+1] | row_num[led_row-1];
        col_light = col_num[led_col] | col_num[led_col+1];
        led_on(row_light, col_light);
      }
      if(led_matrix[led_row][led_col] == 1 && led_row !=0 && led_col ==7)
      {          
        row_light = row_num[led_row] | row_num[led_row+1] | row_num[led_row-1];
        col_light = col_num[led_col] | col_num[led_col-1];
        led_on(row_light, col_light);
      }
      if(led_matrix[led_row][led_col] == 1 && led_row ==0 && led_col ==0)
      {          
        row_light = row_num[led_row] | row_num[led_row+1] ;
        col_light = col_num[led_col] | col_num[led_col+1];
        led_on(row_light, col_light);
      }


      count_cols += 1;
      led_col = count_cols%8;
      //increment j by 1 here, and the loop increments it again, so we go through the 16x16 matrix on even rows and columns
      j +=1;
    }

    //increment i by 1 here, and the loop increments it again, so we go through the 16x16 matrix on even rows and columns
    i += 1;
    count_rows += 1;
    led_row = count_rows %8;
  }
}

//void turn_on_all_needed()
//{ 
//   //light up LEDS according to the matrix, variables passed into led_on function
//  int row_light = 0;
//  int col_light = 0;
//  for (int led_row = 0; led_row <8; led_row++)
//  {
//    for (int led_col = 0; led_col <8; led_col++)
//    {
//      if(led_matrix[led_row][led_col] == 1)
//      {
//        row_light = row_num[led_row];
//        col_light = col_num[led_col] ;
//        led_on(row_light, col_light);
//    
//      }
//      
//    }
//  }
//  
//        
//}

//function sends bluetooth data to android application 
void send_bluetooth()
{
//  if(MyBlue.available())
  Serial.print("s");
  for(int i = 0; i < 16; i ++)
  {
    for( int j = 0; j < 16; j++)
    {
      //sending data and setting the matrix value to zero after sending the bit
      //resets the bluetooth matrix in this way
      Serial.print(bluetooth_matrix[i][j]);
      bluetooth_matrix[i][j] = 0;
    }
//    Serial.println();
  }
//  Serial.println("e");
 
}

//function that collects data to send over bluetooth over a spefied number of cycles
void monitor_bluetooth()
{

  //send bluetooth data once cycle count is reached
  cycles++;
  if(cycles == 1000)
  {
    send_bluetooth();
    cycles = 0;
   
  }
  //if cycle count is not reached, then preform the OR operation on the existing Bluetooth matrix
  //with the sensor matrix. This will give '1's everywhere that a 1 appeared in the sensor matrix
  //over the specified number of cycles.
  else
  {
    for(int i = 0; i < 16; i ++)
    {
      for( int j = 0; j < 16; j++)
      {
        bluetooth_matrix[i][j] = (bluetooth_matrix[i][j] | sensor_matrix[i][j]);
      }
    }
  } 
}

void loop() 
{
    read_sensors();
    sensor_to_led();
//    turn_on_all_needed(); 
    monitor_bluetooth();
}
