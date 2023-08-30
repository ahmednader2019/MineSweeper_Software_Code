/*
 * Date:    27 Dec,2021
 * Subject: MPU6050-Encoder
 * Project: MineSweeper
 */

/* 
 *  Variables needed 
 *  
 *  isMetal
 *  Radius of the tire
 *  N --> number of steps in one rotation of the tire
 */
 
 /*
  * Variables to be sent
  * 
  * Distance ---> distance
  * Direction ---> direc
  */
#include "Wire.h"
#include <MPU6050_light.h>
#define inputCLK 4 // Input pin for Encoder
#define inputDT 5 // Input pin for Encoder
MPU6050 mpu(Wire);
// Variables for MPU
unsigned long timer = 0;
float currentAngle =0;
float previousAngle =0;
String direc;
int angle = 0; 
// Variables for Encoder
int currentStateCLK,previousStateCLK, IsMetal, counter = 0 ;
float distance = 0;
const float pi = 3.14;
const float R = 3.25;
const int N = 40;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  byte status = mpu.begin();
  
  // Set encoder pins as inputs  
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);
  
  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);
  
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  
}

void loop()
{
  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);
    
  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK)
  { 
       
    // If the inputDT state is different than the inputCLK state then 
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK)
    { 
      counter --;
    } 
    else if(digitalRead(inputDT) == currentStateCLK)
    {
      counter ++;
    }
    
     distance = (((2*pi*R)/N) * counter)/100 ;
     Serial.print("Distance : ");
     Serial.println(distance);

  } 
  // Update previousStateCLK with the current state
  if(IsMetal == 1)
  {
    counter = 0;
  }
 
  previousStateCLK = currentStateCLK;

  /*****************************/
  
  mpu.update();
  angle = mpu.getAngleZ();
  
  // print data every 10ms
  if((millis()-timer)>10)
  { 
  Serial.print("Angle : ");
  Serial.println(angle);
  timer = millis();  
  }
  // if angle = 0, 90, 180, -90, -180 Start calculating the direction
  // Angle Range [-180,180]
  if(angle % 90 == 0 ) // To be revised later 
  {
    currentAngle = angle;
    if ( distance >=0.5 && distance <= 2)
    {
     if (currentAngle >= -30 && currentAngle <= 30)
     {
       direc ="up";
       counter = 0;
     }
     else if(currentAngle <= -150 && currentAngle >= -180)  // To be revised later 
     {
       direc ="Down";
       counter = 0;
     }
    }
    if (distance >= 17 && distance <= 20)
    {
      if(currentAngle > previousAngle)
      {
        direc ="Left"; // Direction is Left 
        counter = 0; 
      }
      else if(currentAngle < previousAngle)
      {
        direc ="Right"; // Direction is Right
        counter = 0;
      }
    }
 
    previousAngle = currentAngle;
  }
}
