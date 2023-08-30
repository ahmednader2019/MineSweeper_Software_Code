//BTS7960 motor driver sketch 

int R_IS = 6;
int R_EN = 2;
int R_PWM = 3;
int L_IS = 7;
int L_EN = 4;
int L_PWM = 5;

void setup() {
  // put your setup code here, to run once:
 pinMode(R_IS, OUTPUT);
 pinMode(R_EN, OUTPUT);
 pinMode(R_PWM, OUTPUT);
 pinMode(L_IS, OUTPUT);
 pinMode(L_EN, OUTPUT);
 pinMode(L_PWM, OUTPUT);
 digitalWrite(R_IS, LOW);
 digitalWrite(L_IS, LOW);
 digitalWrite(R_EN, HIGH);
 digitalWrite(L_EN, HIGH);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int i;
  String x ;
  if(x=="on")
  {
    for(i = 0; ; i= i+10)
    { 
    //clockwise rotation
     if(x=="off")
     break;
   analogWrite(R_PWM, i);
   analogWrite(L_PWM, 0);
   delay(500);
   }
  }
  delay(500);
  if(x=="on")
  {
  for(i = 0; ; i= i+10)
  { 
    //counter clockwise rotation
    if(x== "off")
     break;
   analogWrite(R_PWM, 0);
   analogWrite(L_PWM, i);
   delay(500);
  }
  }
}
