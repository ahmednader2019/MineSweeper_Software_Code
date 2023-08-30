
#include <Wire.h>
#define inputCLK 2
#define inputDT 3

int currentStateCLK,previousStateCLK, IsMetal, counter = 0 ;
float distance = 0;
const float pi = 3.14;
const float R = 6.5;
const int N = 40;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);
  
  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);
}

void loop() {
   //   Serial.println("BEGIN");

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
    
     distance = (((2*pi*R)/N) * counter) ;
     Serial.print("Counter : ");
     Serial.println(counter);
     Serial.print("Distance : ");
     Serial.println(distance);

  } 
  previousStateCLK = currentStateCLK;

}
