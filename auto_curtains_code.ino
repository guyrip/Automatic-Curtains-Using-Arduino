#include <Servo.h>
Servo servo1; /* TO DECLARE THE SERVO OBJ */ 
int ldr=A0,srv=11,pot=A1,bulb=10; /* pin assigned to LDR,Bulb,Potentiometer */
int potVal,srvPos,ldrVal,bulbFlg,srvHold; 
int stat,ch; /* stat=To store input value by user HIGH/LOW,and ch=Choice for first input*/

void setup()
{
  servo1.attach(srv);
  pinMode(ldr,INPUT);
  pinMode(pot,INPUT);
  pinMode(bulb,OUTPUT);
  Serial.begin(9600);
  servo1.write(0);
}
void loop()
{
  potVal=analogRead(pot); /*here analog input from POT is stored and sent to Bulb */
  ldrVal=analogRead(ldr);/* while ldr value is read from here */
  potVal=map(potVal,0,5,0,255); /*map the value 0,5V analog to 0,255 PWM signal */
  constrain(potVal,0,5); /* limit the potVal b/w 0 & 5V */
  if(ldrVal<=750) { /*if val is less than 750, flag=1(Night) */
    bulbFlg=0; }
  else {
  bulbFlg=1; }   /*if val is less than 750, flag=0(Day) */
  Serial.println("Enter some no. quickly in 5s");
  ch=Serial.parseInt();
  delay(5500);
  if(Serial.available()==0) /* here to check if any input is given by usr ==0 means NO input and >0 means input given*/
  {
    
    if(bulbFlg==1)
  {  
   analogWrite(bulb,potVal);
    Serial.println("Bulb is Glowing: NIGHT");
     servo1.write(180);
       delay(20);
     }
  else 
  {
   analogWrite(bulb,LOW);
    Serial.println("Bulb is not Glowing: DAY");
    for(int j=180;j>0;j--) {
    servo1.write(j);
       delay(20);
       
    }
  
  }
  }
  else if(Serial.available()>0)
  {
    switch(bulbFlg) /*cases according to Day(0)/Night(1) situation*/
    {
    case 0:  Serial.println("Enter position of curtain except 0: Light/Day");
             srvPos=Serial.parseInt();
            for(int i=0;i<=srvPos;i++) {
             servo1.write(i);
               delay(20);
            }/*motor(curtains) starts and returns to original position*/
            for(int j=srvPos;j>=0;j--){
              servo1.write(j);
               delay(20);
            }
       delay(5000);
            break;
    case 1:  Serial.println("Enter position of curtain except/> 0 :Dark/Night");
             srvPos=Serial.parseInt();
             for(int j=srvPos;j>=0;j--){
              servo1.write(j);
               delay(20);
             }/*same here also, motor(curtains) starts and returns to original position*/
            for(int i=0;i<=srvPos;i++) {
             servo1.write(i);
              delay(20);
            }
      delay(5000);
            break;
    }
  }
  Serial.println("to keep Bulb ON/OFF INPUT 1 or 0");
  stat=Serial.parseInt();
  delay(1000);
  if(stat==1) {  digitalWrite(bulb,HIGH); }
  else {digitalWrite(bulb,LOW); }
delay(5000);
  Serial.println("Where to stop the curtain");
  srvHold=Serial.parseInt();
  servo1.write(srvHold);
  delay(6000);
}
    
  

  


 

  
  

 
    
    
  
