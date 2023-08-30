/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
int angle,previousAngle = 0,currentAngle;
String direc ="0";
String pDirec = "1";
String dist ;
MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  
  if((millis()-timer)>10){ // print data every 10ms
	//Serial.print("Z : ");
  angle = mpu.getAngleZ();
	
	timer = millis();  
  }
  
  if(angle % 90 == 0) 
  {
     currentAngle = angle;
     previousAngle = previousAngle %360;
     currentAngle = currentAngle %360;
       if (currentAngle % 360==0)
       {
        //Serial.println(angle);
        //if( pDirec != direc)
          direc ="Up";
         //counter = 0; 
       }
       
       else if(currentAngle %180 == 0 )  
       {
        //Serial.println(angle);
        //if( pDirec != direc)
          direc ="Down";
         
         //Serial.println(direc);
         //counter =0;
       }
       else if( previousAngle%180==0 && previousAngle!=0)
       {
       
           if((previousAngle-currentAngle)%90 ==0  && (previousAngle-currentAngle)< 0)
           {
           // Serial.println(angle);
            if( pDirec != direc)
              direc ="Right"; // Direction is Right
           // Serial.println(direc);
           }
           else if((previousAngle-currentAngle)%90 ==0 && (previousAngle-currentAngle)>0)
           {
            //Serial.println(angle);
            direc ="Left"; // Direction is Right
           // Serial.println(direc);
           }
        
        }
    
      else if(currentAngle > previousAngle)
      {
        //Serial.println(angle);
        direc ="Left"; // Direction is Left 
      //  Serial.println(direc);
        //counter = 0; 
      }
      else if(currentAngle < previousAngle)
      {
        //Serial.println(angle);
        direc ="Right"; // Direction is Right
        //Serial.println(direc);
        //counter = 0;
      }
      if( previousAngle %360 ==0 && (previousAngle - currentAngle)==270 )
      {
        if(direc =="Right")
        {
          direc = "Left";
         // Serial.println(direc);
        }
        else if(direc == "Left")
        {
          direc = "Right";
         // Serial.println(direc);
        }
      }
    
    //Serial.println(direc);
    if( pDirec != direc)
    {
      dist = direc;
      Serial.print("Destination: ");
      Serial.println(dist);
    }
   
 
    previousAngle = currentAngle;
    pDirec = direc;
    /*
    Serial.print("Direction : ");
    Serial.println(direc);
    Serial.print("Previous Direction : ");
    Serial.println(pDirec);
    */
  }
  
}
