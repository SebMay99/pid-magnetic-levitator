
// Define variables
int anaPin = A0;   // Arduino Analogic Pin 0
int digPin = 8;   // Arduino Digital  Pin 5
int subPin = 9;   // Arduino Digital  Pin 7
int addPin = 10;   // Arduino Digital  Pin 8
int outputValue = 0;

int StartPin = 2;   // Arduino Pin 9
int ModePin1 = 3;   // Arduino Analogic Pin 10
int ModePin2 = 4;   // Arduino Analogic Pin 11
int ModePin3 = 5;   // Arduino Analogic Pin 12

int Mode1 = 0;
int Mode2 = 0;
int Mode3 = 0;
int Start = 0;

//
int anaVal = 0;   // Analogic Valie
int digVal = 0;   // Digital Value

//

int levVal1 = 649; // Levitation Value 1
int levVal2 = 700; // Levitation Value 2
int levVal3 = 730; // Levitation Value 3

int dlyVal = 5;  // Delay Value
float timVal = 0; // Time Value

  //---------------------------------------------------------|
  // PID Values
  float setpoint = 0;
  float measured_value = 0;
  float output = 0;
  float integral = 0;
  float derivative = 0;
  float error = 0;
  float previous_error = 0;
  float dt = 0.1;
  float Kp = 1.0;
  float Ki = 0.3;
  float Kd = 0.65;
  //---------------------------------------------------------|
  


void setup()
{
   // Levitator initialization Begin; 
   Serial.begin(57600);
   // Digital Pins Work Mode Setup;
   pinMode(digPin, OUTPUT);
   pinMode(addPin, INPUT_PULLUP);
   pinMode(subPin, INPUT_PULLUP);
   pinMode(StartPin, INPUT);   // Arduino Pin 9
   pinMode(ModePin1, INPUT);   // Arduino Pin 9
   pinMode(ModePin2, INPUT);   // Arduino Pin 9
   pinMode(ModePin3, INPUT);   // Arduino Pin 9
   //
   setpoint = levVal1;
   Serial.println("Setting up!");
}
//---------------------------------------------------------|
void loop() // PID
{

  if (Start == 1)
  {
    // Hall Sensor Read (Magnetic Field Intensity);
   anaVal = analogRead(anaPin);
   Serial.println(anaVal);
   
   // map it to the range of the analog out:
   outputValue = map(anaVal, 0, 1023, 0, 255);
   
   // PID calculations
   measured_value = anaVal;
   error = setpoint - measured_value;
   integral = integral + error * dt;
   derivative = (error - previous_error) / dt;
   output = (-Kp * error) + (-Ki * integral) + (-Kd * derivative);
   previous_error = error;
   
   // Final value setup
   digVal += output;
   // Check the value for levitation point;
   if (digVal < 0) digVal=0;
   if (digVal > 255) digVal=255;
   // Increase/Decrease the value for Electromagnet;
   // With Base on Sensor Value and the Levitation Point;
   analogWrite(digPin, digVal);

   // Change the mode;
   if (digitalRead(ModePin1) == HIGH && Mode1 == 0) 
   {
      Mode1 = 1;
      Mode2 = 0;
      Mode3 = 0;
      setpoint = levVal1;
      resetPID();
      Serial.println("Mode 1!");
      delay(1000);
   }
   if (digitalRead(ModePin2) == HIGH && Mode2 == 0) 
   {
      Mode1 = 0;
      Mode2 = 1;
      Mode3 = 0;
      setpoint = levVal2;
      resetPID();
      Serial.println("Mode 2!");
      delay(1000);
   }
   if (digitalRead(ModePin3) == HIGH && Mode3 == 0) 
   {
      Mode1 = 0;
      Mode2 = 0;
      Mode3 = 1;
      setpoint = levVal3;
      resetPID();
      Serial.println("Mode 3!");
      delay(1000);
   }

   //Stop the system
   if (digitalRead(StartPin) == LOW) 
   {
      Start = 0;//Turn of the flag
      resetPID();
      Serial.println("Stopping!");
      delay(1000);
   }

   // Increase The Value Of Levitation Point;
   if (digitalRead(addPin) == LOW) 
   {
      setpoint++;
      value_log();
      delay(100);
   }
   if (digitalRead(subPin) == LOW) 
   {
      setpoint--;
      value_log();
      delay(100);
   }
   // Time between electromagnet state changes;
   delayMicroseconds(dlyVal);
  
  }
  else if(digitalRead(StartPin) == HIGH) 
  {
      Start = 1;//Turn ON the flag
      resetPID();
      Serial.println("Starting!");
      delay(1000);
  }
 
}

void value_log()
// Analogic/Digital/Levitation Values Print;
{
   // Show the Hall Sensor Value;
   Serial.print("anaVal=[");
   Serial.print(anaVal); 
   Serial.print("]-");
   // Show the Electromagnet state On=1/Off=0;
   Serial.print("digVal=[");
   Serial.print(digVal);
   Serial.print("]-");
   // Show the Levitation Point Value;
   Serial.print("setpoint=[");
   Serial.print(setpoint);
   Serial.println("];");
}
//=========================================================|

void resetPID()
{
  // PID Values
  measured_value = 0;
  output = 0;
  integral = 0;
  derivative = 0;
  error = 0;
  previous_error = 0;
  dt = 0.1;
  Kp = 1.0;
  Ki = 0.3;
  Kd = 0.65;
  //---------------------------------------------------------|
  
  
}
