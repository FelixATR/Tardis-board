

//input from receiver
//int data_0 = A2;
//int data_1 = A3;
//int data_2 = A4;
//int data_3 = A5;

//int boxPin = 9;
//int lampPin = 10;
//int signPin = 11;


int sensorValue1 = digitalRead(2);

Serial.println(sensorValue);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("testing serial");
Serial.println(sensorValue1);
delay(1000);
}
