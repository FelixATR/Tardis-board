//https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial


// initialize pins and set as outputs
int boxPin = 9;
int lampPin = 10;
int signPin = 11;
// read the input on analog pin 0:
int sensorValue1 = digitalRead(A2);
int sensorValue2 = digitalRead(A3);
int sensorValue3 = digitalRead(A4);
int sensorValue4 = digitalRead(A5);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(sensorValue1, INPUT);
  pinMode(sensorValue2, INPUT);
  pinMode(sensorValue3, INPUT);
  pinMode(sensorValue4, INPUT);

  pinMode(boxPin,OUTPUT);
  pinMode(lampPin,OUTPUT);
  pinMode(signPin,OUTPUT);

  digitalWrite(boxPin, LOW);
  digitalWrite(lampPin, LOW);
  digitalWrite(signPin, LOW);

}

// the loop routine runs over and over again forever:
void loop() {
  // print out the value you read:
  if (digitalRead(sensorValue1) == 1) box();//Box on/off
  //Serial.println(sensorValue1);
  delay(1);  // delay in between reads for stability
  if (digitalRead(sensorValue2) == 1) lamp();//Lamp on/off
  //Serial.println(sensorValue2);
  delay(1);  // delay in between reads for stability
  if (digitalRead(sensorValue3) == 1) sign();//Sign on/off
  //Serial.println(sensorValue3);
  delay(1);  // delay in between reads for stability
  if (digitalRead(sensorValue4) == 1) allSet();//all on/off
  //Serial.println(sensorValue4);
  delay(1);  // delay in between reads for stability
}
void box (){
  if (digitalRead(boxPin) == HIGH){
    digitalWrite(boxPin, LOW);
  }
  else {digitalWrite(boxPin, HIGH);
  }
}
void lamp (){
  if (digitalRead(lampPin) == HIGH){
    digitalWrite(lampPin, LOW);
  }
  else {digitalWrite(lampPin, HIGH);
  }
}
void sign (){
  if (digitalRead(signPin) == HIGH){
    digitalWrite(signPin, LOW);
  }
  else {digitalWrite(signPin, HIGH);
  }
}

void allSet (){
  if (digitalRead(signPin) == HIGH || digitalRead(lampPin) == HIGH || digitalRead(boxPin) == HIGH){
    digitalWrite(boxPin, LOW);
    digitalWrite(lampPin, LOW);
    digitalWrite(signPin, LOW);
  }
  else {
    digitalWrite(boxPin, HIGH);
    digitalWrite(lampPin, HIGH);
    digitalWrite(signPin, HIGH);
  }
  
}

