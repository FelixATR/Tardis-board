#include <RH_ASK.h>    //I'm using the Radio Head library
#include <SPI.h>     //I notest that when I use the SPI library the serial monitor won't work.

//object
//RH_ASK rf_driver;

//input from receiver
int data_0 = "A2";
int data_1 = "A3";
int data_2 = "A4";
int data_3 = "A5";

int boxPin = 9;
int lampPin = 10;
int signPin = 11;

void setup() {

// initalize object
//rf_driver.init();
//serial setup
Serial.begin(9600);
pinMode(data_0, INPUT);
pinMode(data_1, INPUT);
pinMode(data_2, INPUT);
pinMode(data_3, INPUT);
//Identify the output pins
pinMode(boxPin,OUTPUT);
pinMode(lampPin,OUTPUT);
pinMode(signPin,OUTPUT);

}
void loop(){
 
    if (data_0 == HIGH)
     {
      fadeOn1(1000,5);
      Serial.print("message data_0")
      fadeOff1(1000,5);
      fadeOn2(1000,5);
      fadeOff2(1000,5);
      fadeOn3(1000,5);
      fadeOff3(1000,5);
      delay(1000);
     }
    
    else if (data_1 == HIGH)
     {
      fadeOn1(1000,5);
      fadeOff1(1000,5);
      Serial.print("message data_1");
      delay(1000);
     }
    
    else if (data_2 == HIGH)
     {
      fadeOn2(1000,5);
      fadeOff2(1000,5);
      Serial.print("message data_2");
      delay(1000);
     }
    
    else if (data_3 == HIGH)
     {
      fadeOn3(1000,5);
      fadeOff3(1000,5);
      Serial.print("message data_3");
      delay(1000);
     }
    
    else
     {
      digitalWrite(boxPin, HIGH);
      digitalWrite(lampPin, HIGH);
      digitalWrite(signPin, HIGH);
      Serial.print("message data_none");
      delay(1000);
     }
}
void fadeOn1(unsigned int time,int increament){
for (byte value = 0 ; value < 255; value+=increament){
analogWrite(boxPin, value);
delay(time/(255/5));
}
}
void fadeOff1(unsigned int time,int decreament){
for (byte value = 255; value >0; value-=decreament){
analogWrite(boxPin, value);
delay(time/(255/5));
}
}
void fadeOn2(unsigned int time,int increament){
for (byte value = 0 ; value < 255; value+=increament){
analogWrite(lampPin, value);
delay(time/(255/5));
}
}
void fadeOff2(unsigned int time,int decreament){
for (byte value = 255; value >0; value-=decreament){
analogWrite(lampPin, value);
delay(time/(255/5));
}
}
void fadeOn3(unsigned int time,int increament){
for (byte value = 0 ; value < 255; value+=increament){
analogWrite(signPin, value);
delay(time/(255/5));
}
}
void fadeOff3(unsigned int time,int decreament){
for (byte value = 255; value >0; value-=decreament){
analogWrite(signPin, value);
delay(time/(255/5));
}
}