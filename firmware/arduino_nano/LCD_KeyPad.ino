#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define variables
int anaPin = 0;   // Arduino Analogic Pin 0
int StartPin = 9;   // Arduino Pin 9
int ModePin1 = 10;   // Arduino Analogic Pin 10
int ModePin2 = 11;   // Arduino Analogic Pin 11
int ModePin3 = 12;   // Arduino Analogic Pin 12
int outputValue = 0;
unsigned long currentTime = 0;
unsigned long previousTime = 0;

const byte Rows= 4; //number of rows on the keypad 
const byte Cols= 3; //number of columns on the keypad 

//we will definne the key map as on the key pad:

char keymap[Rows][Cols]=
{
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'},
{'*', '0', '#'}
};


//keypad connections to the arduino terminals is given as:

byte rPins[Rows]= {8,7,6,5}; //Rows 0 to 3
byte cPins[Cols]= {4,3,2}; //Columns 0 to 2

//initializes an instance of the Keypad class
Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);

int anaVal = 0;   // Analogic Valie


LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
   // Levitator initialization Begin; 
   Serial.begin(9600);
   
   //Start LCD
   lcd.init();
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("Press 1 to Start");

  pinMode(StartPin, OUTPUT);   // Arduino Pin 9
   pinMode(ModePin1, OUTPUT);   // Arduino Pin 10
   pinMode(ModePin2, OUTPUT);   // Arduino Pin 11
   pinMode(ModePin3, OUTPUT);   // Arduino Pin 12
  
   delay(1500);
}
//---------------------------------------------------------|
void loop() // PID
{ 
   char keypressed = kpd.getKey();
   if (keypressed == '1' && digitalRead(StartPin == LOW))
   {  
      Serial.println("Starting!");
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      lcd.clear();
      lcd.print("Starting!");
      delay(1000);
   }
   else if (keypressed == '5' && digitalRead(StartPin == HIGH))
   {  
      Serial.println("Stopping!");
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      lcd.clear();
      lcd.print("Stopping!");
      delay(1000);
   }
   else if (keypressed == '2' && digitalRead(StartPin == HIGH))
   {  
      Serial.println("Mode 1");
       digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      lcd.clear();
      lcd.print("Mode 1!");
      delay(1000);
   }
   else if (keypressed == '3' && digitalRead(StartPin == HIGH))
   {  
      Serial.println("Mode 2");
       digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      lcd.clear();
      lcd.print("Mode 2!");
      delay(1000);
   }
   else if (keypressed == '4' && digitalRead(StartPin == HIGH))
   {  
      Serial.println("Mode 3");
       digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      lcd.clear();
      lcd.print("Mode 3!");
      delay(1000);
   }

   if( digitalRead(StartPin) == HIGH)
   {
      // Hall Sensor Read (Magnetic Field Intensity);
     anaVal = analogRead(anaPin);
     Serial.println(anaVal);
     
     // map it to the range of the analog out:
     //outputValue = map(anaVal, 0, 1023, 0, 255);
  
     currentTime = millis();
  
     if(currentTime - previousTime >= 1000)
     {
        // Show the Hall Sensor Value;
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Sensor=");
       lcd.setCursor(0,1);
       lcd.print("Value");
       lcd.setCursor(8,0);
       lcd.print(anaVal-36);
       previousTime = currentTime;
       
     } 
     delayMicroseconds(5);
   }
   
}
