#include <HC595.h>
#include <SoftwareSerial.h> 
#include <Wire.h>

const int chipCount = 2;  // Number of serialy connected 74HC595 (8 maximum)
const int latchPin = 4;  // Pin ST_CP (12) of the 74HC595
const int clockPin = 3;  // Pin SH_CP (11) of the 74HC595
const int dataPin = 2;   // Pin DS (14) of the 74HC595
int Sensor_col[6]={7,6,0,16,15,14};
int Sensor_row[6]={8,9,10,11,12,13};

int led_col[5]={0,1,2,3,4};
int led_row[5]={5,6,7,8,9};
int cycles=0;

int sens_status[6][6]={{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
//Constructor
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);
SoftwareSerial MyBlue(5,17); // RX | TX 

int delayMs = 30;
int lastPin = ledArray.lastPin();

void setup() {
  // put your setup code here, to run once:
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(0,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
//  Serial.begin(9600);
  MyBlue.begin(9600); 
  ledArray.reset();
  Wire.begin(8);
  Wire.onRequest(send_i2c_data);
}

void rst(){
  ledArray.setPin(5, ON);
  ledArray.setPin(6, ON);
  ledArray.setPin(7, ON);
  ledArray.setPin(8, ON);
  ledArray.setPin(9, ON);

  ledArray.setPin(0, OFF);
  ledArray.setPin(1, OFF);
  ledArray.setPin(2, OFF);
  ledArray.setPin(3, OFF);
  ledArray.setPin(4, OFF);
}

void Sens_col(int col_no){
  int col=Sensor_col[col_no];
  digitalWrite(col,HIGH);
  int r1= digitalRead(Sensor_row[5]);
  int r2= digitalRead(Sensor_row[4]);
  int r3= digitalRead(Sensor_row[3]);
  int r4= digitalRead(Sensor_row[2]);
  int r5= digitalRead(Sensor_row[1]);
  int r6= digitalRead(Sensor_row[0]);
  digitalWrite(col,LOW);
  sens_status[col_no][0]=r1;
  sens_status[col_no][1]=r2;
  sens_status[col_no][2]=r3;
  sens_status[col_no][3]=r4;
  sens_status[col_no][4]=r5;
  sens_status[col_no][5]=r6;
}
void send_blue_data(){
//  for( int i=0; i<6; ++i){
//    for (int j=0; j<6; ++j)
//      MyBlue.print(sens_status[i][j]);
//    MyBlue.println();
//  }
//  MyBlue.println();
//  MyBlue.println();
  MyBlue.print("[0,0,0,0,0,0]\n"); 
  MyBlue.print("[0,1,1,0,0,0]\n"); 
  MyBlue.print("[0,1,1,0,0,0]\n"); 
  MyBlue.print("[0,0,0,0,0,0]\n"); 
  MyBlue.print("[0,0,0,0,0,0]\n"); 
  MyBlue.print("[0,0,0,0,0,0]\n"); 
  MyBlue.print("\n\n\n");
  MyBlue.print("\n\n\n");
}

void send_i2c_data(){
  bool val=false;
  for( int i=0; i<6; ++i){
    for (int j=0; j<6; ++j){
      if(sens_status[i][j]==1)
        val=true;
    }
  }
  Wire.write(val);
}
void led_status(){
  //inner square:
   for( int i=1; i<5; ++i){
      for (int j=1; j<5; ++j)
        if(sens_status[i][j]==1){
          ledArray.setPin(led_col[5-i], ON);
          ledArray.setPin(led_col[5-i-1], ON);

          ledArray.setPin(led_row[j], OFF);
          ledArray.setPin(led_row[j-1], OFF);
          rst();
        }
  }
  //top and bottom 4 sens
  for(int j=1; j<5; ++j){
    if(sens_status[0][j]==1){
          ledArray.setPin(led_col[4], ON);

          ledArray.setPin(led_row[j], OFF);
          ledArray.setPin(led_row[j-1], OFF);
          rst();
        }
  }

   for(int j=1; j<5; ++j){
    if(sens_status[5][j]==1){
          ledArray.setPin(led_col[5-5], ON);

          ledArray.setPin(led_row[j], OFF);
          ledArray.setPin(led_row[j-1], OFF);
          rst();
        }
  }
  //left and right 4 sens
    for(int i=1; i<5; ++i){
    if(sens_status[i][0]==1){
          ledArray.setPin(led_col[5-i], ON);
          ledArray.setPin(led_col[5-i-1], ON);

          ledArray.setPin(led_row[0], OFF);
          rst();
        }
  }


  for(int i=1; i<5; ++i){
    if(sens_status[i][5]==1){
          ledArray.setPin(led_col[5-i], ON);
          ledArray.setPin(led_col[5-i-1], ON);

          ledArray.setPin(led_row[4], OFF);
          rst();
        }
  }
   
  //cornors

  if( sens_status[0][0]==1){
     ledArray.setPin(led_col[4], ON);

     ledArray.setPin(led_row[0], OFF);
     rst();
  }
  if( sens_status[0][5]==1){
     ledArray.setPin(led_col[4], ON);

     ledArray.setPin(led_row[4], OFF);
     rst();
  }
  if( sens_status[5][5]==1){
     ledArray.setPin(led_col[0], ON);

     ledArray.setPin(led_row[4], OFF);
     rst();
  }
  if( sens_status[5][0]==1){
     ledArray.setPin(led_col[0], ON);

     ledArray.setPin(led_row[0], OFF);
     rst();
  }

}
void loop() {

  
  for(int i=0; i<6; ++i){
    Sens_col(i);
  }
  cycles+=1;
  if(cycles==1400){
    cycles=0;
    send_blue_data();
  }
  led_status();
}
