//https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue1 = analogRead(A2);
  int sensorValue2 = analogRead(A3);
  int sensorValue3 = analogRead(A4);
  int sensorValue4 = analogRead(A5);
  // print out the value you read:
  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  Serial.println(sensorValue3);
  Serial.println(sensorValue4);
  delay(1);  // delay in between reads for stability
}
