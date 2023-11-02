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
 
void setup ()
{

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

}

String oldFunc(int var) 
{
  String str;
  for (int i = 0; i < 8; i++)  
  {
//    Serial.print(((var >> i) & 1) == 1 ? "1" : "0");
    str.concat(((var >> i) & 1) == 1 ? "1" : "0");
  }
  return str;

}
 
void loop() 
{

  //define the arrays needed to control the LEDs 
  int row_num[8] = {1,2,4,8,16,32,64,128};
  int col_num[8] = {128,64,32,16,8,4,2,1};//,2,4,8,16,32,64,128};

  //define the LED and Sensor matrix
  int sensor_matrix[16][16];
  int led_matrix[8][8];
  
  //For sensor rows 0-16
  Serial.println("Sensor Matrix");
  for (int numberToDisplay = 0; numberToDisplay < 16; numberToDisplay++) 
  {  
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
    //format is now correct
    
    //inputting the information into a 16x16 sensor matrix
    for( int i = 0; i < 16; i++)
    {
      sensor_matrix[numberToDisplay][i] = correct_total.charAt(i)- 48;
      //displaying the sensor matrix row by row 
      Serial.print(sensor_matrix[numberToDisplay][i]);
    }
    Serial.println();
//    delay(50);
    
    

  }
//  Serial.println("END:");

  //converting the sensor 16x16 matrix to the 8x8 led matrix;
  int led_row = 0;
  int led_col = 0;

  //light up LEDS according to the matrix 
  int row_light = 0;
  int col_light = 0;

  int count_cols = 0;
  int count_rows = 0;


  
  Serial.println("LED MATRIX:");

  for (int i = 0; i < 15; i ++)
  {
    for (int j = 0; j < 15; j++)
    {
      led_matrix[led_row][led_col] = sensor_matrix[i][j] | sensor_matrix[i][j+1] | sensor_matrix[i+ 1][j] | sensor_matrix[i+1][j+1];
      Serial.print(led_matrix[led_row][led_col]);
      if(led_matrix[led_row][led_col] == 1)
      {
         Serial.println("ROW COL");
         Serial.println(led_row);
         Serial.println(led_col);  
        row_light = row_light | row_num[led_row];
        col_light = col_light | col_num[led_col];
      }

      count_cols += 1;
      led_col = (count_cols)%8;
     
      j +=1;
      
    }
  
    i += 1;
    count_rows += 1;
    led_row = count_rows %8;

    Serial.println();
  }//led matrix is now complete 

  
  Serial.println("ROW LIGHT AND COL LIGHT");
  Serial.println(row_light);
  Serial.println(col_light);
  delay(10);
 



//  for(int rows = 0; rows <8; rows++) 
//  {  
//
//    for (int cols =0; cols <8; cols++)
//    {
//      if(led_matrix[rows][cols] == 1)
//      {
//          
//        row_light = row_light | row_num[rows];
//        col_light = col_light | col_num[cols];
//      }
//    }
//  }


digitalWrite(led_latchPin, LOW);
shiftOut(led_dataPin, led_clockPin, MSBFIRST, col_light); //this first statement goes to the chained shift reg- columns
shiftOut(led_dataPin, led_clockPin, MSBFIRST, row_light); //this statment goes to the first shift reg - rows 
digitalWrite(led_latchPin, HIGH);
delay(10); 



//  delay(1000);


  
}
