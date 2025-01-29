#include <LiquidCrystal.h>
#include <stdio.h>
#include <SoftwareSerial.h>

#include <Wire.h>
#include "dht.h"

SoftwareSerial mySerial(A4, A5);

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
// defines pins numbers

char gchr;

#define dht_apin 8
dht DHT;

int trigPin = A2;
int echoPin = A3;

int vib = A1;
int ir  = 9;
int buzzer  = A0;

int led1 = 10;
int led2 = 11;
int led3 = 12;
int led4 = 13;


int tempc=0,humc=0;

int dist1,dist2,dist3;
int sts1=0,sts2=0,sts3=0,sts4=0;

long duration;
int distanceCm, distanceInch;
 
int sti=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


unsigned int ultra_dist()
{
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   //delayMicroseconds(2);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   
   duration = pulseIn(echoPin, HIGH);
   distanceCm= duration*0.034/2;
   //distanceInch = duration*0.0133/2;   
   //lcd.setCursor(2,0);
   //convertl(distanceCm);
   dist1 = distanceCm;
   delay(100);
   return dist1;
}


 void beep()
 {
  digitalWrite(buzzer, LOW);delay(2000);digitalWrite(buzzer, HIGH);
 }
void setup() 
{
 Serial.begin(9600);//serialEvent();

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input 
    pinMode(buzzer, OUTPUT);
    pinMode(vib, INPUT_PULLUP);
    pinMode(ir, INPUT);
    pinMode(led1, OUTPUT);pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);pinMode(led4, OUTPUT);
    
    digitalWrite(buzzer, HIGH); 
    digitalWrite(led1, HIGH); digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH); digitalWrite(led4, HIGH);
    
  lcd.begin(16, 2);lcd.cursor();
  lcd.print(" Blind Stick");
  delay(3000);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("U:");//2,0
   
   lcd.setCursor(8,0);
   lcd.print("T:");//10,0

   lcd.setCursor(0,1);
   lcd.print("I:");//2,1

   lcd.setCursor(8,1);
   lcd.print("V:");//10,1
}

int distz=0;
void loop() 
{
  dist1=0;
  dist2=0;
  
 for(int pi=0;pi<2;pi++)
    {
     distz = ultra_dist();delay(10);
     dist1 = (dist1 + distz); 
    }
 dist1 = (dist1/2);
 lcd.setCursor(2,0);convertl(dist1);
 if(dist1 < 30)
   {
    digitalWrite(led1, LOW);
    digitalWrite(buzzer, LOW);
   }
 else
   {
    digitalWrite(led1, HIGH);  
   }
   
    DHT.read11(dht_apin);

      tempc = DHT.temperature;
      humc  = DHT.humidity;

   lcd.setCursor(10,0);convertl(tempc);
   //lcd.setCursor(2,1);convertl(humc);
  
   if(tempc > 39)
     {
      digitalWrite(led2, LOW);
      digitalWrite(buzzer, LOW);
     }
   else
     {
      digitalWrite(led2, HIGH);
     }
     
   if(digitalRead(ir) == LOW)
     {
      lcd.setCursor(2,1);lcd.print("ON  ");       
      digitalWrite(led3, LOW);
      digitalWrite(buzzer, LOW);
     }
   if(digitalRead(ir) == HIGH)
     {
      lcd.setCursor(2,1);lcd.print("OFF ");       
      digitalWrite(led3, HIGH);
     }

   if(digitalRead(vib) == LOW)
     {
      lcd.setCursor(10,1);lcd.print("ON  ");       
      digitalWrite(led4, LOW);
      digitalWrite(buzzer, LOW);
     }
   if(digitalRead(vib) == HIGH)
     {
      lcd.setCursor(10,1);lcd.print("OFF ");       
      digitalWrite(led4, HIGH);
     }

   if(dist1 > 30 && tempc < 39 && digitalRead(ir) == HIGH && digitalRead(vib) == HIGH)
     {
      digitalWrite(buzzer, HIGH);    
     }
}


void serialEvent() 
{
  while (Serial.available()) 
        {
         
         char inChar = (char)Serial.read();
           if(inChar == '*')
             {
              ;
             // gchr = Serial.read();              
             }
                 
        }
}




void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
//   lcd.write(a);
   lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}

void convertk(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
  // lcd.write(e); 
  // lcd.write(g);
   lcd.write(h);
}
