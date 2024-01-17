
/*=================================================================================================

 Program Name:   TARDIS Control
   
 Author:         Chuck Badger

 Description:    Software is written for controling the electronics of a TARDIS. Hardware
                 includes a prototyping board with 3 digital outputs wired to mosfets to drive 3
                 LED arrays and a remote receiver with a global signal line and 4 discrete
                 signal lines (one for each button on the remote).
         
                 The 3 LED arrays are the lantern at the top of the TARDIS, the lighting for the
                 inside of the TARDIS, and the lighting for the 4 POLICE BOX signs.
         
                 The discrete signal lines from the remote receiver are wired to individual
                 inputs on the prototyping board. The global signal line from the remote
                 receiver is wired a hardware inturrupt circuit.
         
                 The 4 buttons on the remote will activate the following 4 light sequences:
                   1. Lantern pulsing with all other lights off
                   2. All lights on solid
                   3. All lights on soild with lantern pulsing
                   4. All lights on solid with lantern off
           
 Note:           Software was designed using an Arduino UNO. Software should be
                 compatible with similar hardware.
         
                 Wiring diagram can be found at:
                 http://tardisbuilders.com/index.php/index.php?topic=9572.msg120021#msg120021

===================================================================================================

 CHANGE LOG

 1.0.2   2019-09-27    BUG FIX
 
	- Corrected a bug found in 1.0.1 where attempting to change a pulsing sequences didn't
          always succeed unless the sequence was canceled first
       - Removed invalidation of lighting sequences when the sequence is triggered
       - Added invalidation of lighting sequences to the sequence activation status
 
 1.0.1   2019-09-26    MAINTENENCE BUILD
       
       - Changed evaluations to compare number to variable (10 == x rather than x == 10)
       - Added OR conditions to the pulsing light sequences so that any button press will
         exit and reevaluate instead of staying stuck depending on when you press a
         button
       - Updated lighting sequences to be discrete sequences calling out all 3 arrays
 
 1.0.0   2019-07-10    INITIAL BUILD
 
=================================================================================================*/

/*  RF Transmitter button-to-circuit is as follows:
     Button A = Circuit D2
     Button B = Circuit D0
     Button C = Circuit D3
     Button D = Circuit D1
*/

//Declare lighting sequence activation status variables
int value_a = 0;
int value_b = 0;
int value_c = 0;
int value_d = 0;

//Declare change flags
volatile bool changeA = false;
volatile bool changeB = false;
volatile bool changeC = false;
volatile bool changeD = false;
 
//Attach labels to pin designations for easier code comprehension
#define boxPin 10
#define lampPin 11
#define signPin 9

//=================================================================================================

void setup(){
Serial.begin(115200);
//Identify the output pins
pinMode(boxPin, OUTPUT);
pinMode(lampPin, OUTPUT);
pinMode(signPin, OUTPUT);

//Identify the input pins
pinMode(A5, INPUT);
pinMode(A4, INPUT);
pinMode(A3, INPUT);
pinMode(A2, INPUT);
pinMode(2, INPUT);

//Identify the interrupt pin and what function will be called when triggered
attachInterrupt(digitalPinToInterrupt(2), ButtonPressed, RISING);

}

//=================================================================================================

void loop() {

/*  TOGGLES FOR THE 4 SEQUENCES ===================================================================
   
     When a button is pressed, the corresponding toggle will force a change in the lighting
     sequence activation status variable
*/
 
//  Button A Pressed  
 if (changeA) {  
   if (0 == value_a) {
     value_a = 1;
     value_b = 0;
     value_c = 0;
     value_d = 0;
   }
   else {
     value_a = 0;
   }
   changeA = false;
 }
   
// Button B Pressed
 if (changeB) {  
   if (0 == value_b) {
     value_b = 1;
     value_a = 0;
     value_c = 0;
     value_d = 0;
   }
   else {
     value_b = 0;
   }
   changeB = false;
 }
 
//  Button C Pressed  
 if (changeC) {  
   if (0 == value_c) {
     value_c = 1;
     value_a = 0;
     value_b = 0;
     value_d = 0;
   }
   else {
     value_c = 0;
   }
   changeC = false;
 }
 
//  Button D Pressed
 if (changeD) {  
   if (0 == value_d) {
     value_d = 1;
     value_a = 0;
     value_b = 0;
     value_c = 0;
   }
   else {
     value_d = 0;
   }
   changeD = false;
 }

/*  LIGHT SEQUENCES  ==============================================================================
     When a light sequence is activated, the controller will drive the appropriate LED arrays
*/
 
//  Default, No Flag State
 if(0 == value_a && 0 == value_b && 0 == value_c && 0 == value_d) {
   analogWrite (boxPin, 0);
   analogWrite (lampPin, 0);
   analogWrite (signPin, 0);
   }

//  Flag A Turned On - All Off With Pulse
 if (1 == value_a) {
   analogWrite (boxPin, 0);
   analogWrite (signPin, 0);
   
   for(int i = 0; i<3600; i++){
     //convert 0-360 angle to radian (needed for sin function)
     float rad = DEG_TO_RAD * i;
     
     //calculate sin of angle as number between 0 and 255
     int sinOut = constrain((sin(rad)*128)+128, 0, 255);
     
     analogWrite(lampPin, sinOut);
     delay(5);
     if (changeA || changeB || changeC || changeD){
       break;
     }
   }
   
 }

//  Flag B Turned On - All On Solid
 if (1 == value_c) {    
   analogWrite (boxPin, 255);
   analogWrite (lampPin, 255);
   analogWrite (signPin, 255);
 }

//  Flag C Turned On - All On With Pulse
 if (1 == value_b) {    
   analogWrite (boxPin, 255);
   analogWrite (signPin, 255);

   for(int i = 0; i<3600; i++){
     //convert 0-360 angle to radian (needed for sin function)
     float rad = DEG_TO_RAD * i;
     
     //calculate sin of angle as number between 0 and 255
     int sinOut = constrain((sin(rad)*128)+128, 0, 255);
     
     analogWrite(lampPin, sinOut);
     delay(5);
     if (changeA || changeB || changeC || changeD){
       break;
     }
   }
 }

//  Flag D Turned On - Lights On No Lamp
	if (1 == value_d) {  
		analogWrite (boxPin, 255);
		analogWrite (lampPin, 0);
		analogWrite (signPin, 255);
   }
}

//  BUTTON PRESS INTURRUPT ========================================================================

void ButtonPressed(){
 
	if (digitalRead (A5) == HIGH) {
		changeA = true;
	}
   else if (digitalRead (A4) == HIGH) {
		changeB = true;
   }
   else if (digitalRead (A3) == HIGH) {
		changeC = true;
   }
   else if (digitalRead (A2) == HIGH) {
		changeD = true;
   }
}