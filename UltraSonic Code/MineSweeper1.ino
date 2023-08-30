

 #define inputCLK 4
 #define inputDT 5

 const byte trig = 8;
 const byte echo = 9 ;
 long ultradistance = 0 ;
 long cm = 0 ;
 int counter = 0; 
 int currentStateCLK;
 int previousStateCLK; 
 int IsMetal ;
 int distance ;
 String Where ;
 
 const float pi = 3.14;
 const float R = 3.25;
 const int N = 40;

 String encdir ="";

 void setup() { 
   
   // Set encoder pins as inputs  
   pinMode (inputCLK,INPUT);
   pinMode (inputDT,INPUT);

   pinMode(trig,OUTPUT);
   pinMode(echo,INPUT);
   // Setup Serial Monitor
   Serial.begin (9600);
   
   // Read the initial state of inputCLK
   // Assign to previousStateCLK variable
   previousStateCLK = digitalRead(inputCLK);

 } 

 void loop()
 { 
         // Ultrasonic Sesnor
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    digitalWrite(echo,HIGH);
    if(IsMetal==1)
    {
    ultradistance = pulseIn(echo,HIGH);
    cm = ultradistance / 58 ;
        if(cm > 10 && cm < 25 )
        {
           Where = "S" ;                     //        if the distance between 10 cm and 25 cm it means the metal is on the surface               S->surface               
        }
        else
        {
           Where = "B" ;                      //        otherwise the metal is buried                                                             B->Buried
        }
    Serial.print("The Distance is : ");
    Serial.println(cm);
    }
   // Read the current state of inputCLK
    currentStateCLK = digitalRead(inputCLK);
    
   // If the previous and the current state of the inputCLK are different then a pulse has occured
    if (currentStateCLK != previousStateCLK){ 
       
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(inputDT) != currentStateCLK)
     { 
       counter --;
     } 
     else
     {
       counter ++;
     }
    
      distance = ((2*pi*R)/N) * counter ;

   } 
   // Update previousStateCLK with the current state
   if(IsMetal == 1 )
   counter = 0;
   
   previousStateCLK = currentStateCLK;
 }
