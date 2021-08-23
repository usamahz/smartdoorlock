/*
* Implemented the unlocking and locking action of a door controlled by an Android application,
* developed using Arduino UNO board and Bluetooth module as an efficient embedded system. 

* Designed in C++ based on embedded libraries and I2C protocols.

* Servo motor pulls or pushes the latch attached to it when the application in the mobile phone sends
* requests to the device.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,20,4);
#include <Servo.h>
#include <Keypad.h>

//Defining the variables
int mot_min = 90;   //Min servo angle 
int mot_max = 180; //Max servo angle
int character = 0;
int activated =0;
char Received = 'c';
char Str[16] = {' ', ' ', ' ', ' ', ' ', ' ', '-', '*', '*', '*', ' ', ' ', ' ', ' ', ' ', ' '};  

//Defining the Pins
Servo myservo;
int buzzer=11;     //Pin for the buzzer beep
int external = 12; //Pin to inside open
int internal = 13; //Pin to inside close

//Configuring Keypad
const byte ROWS = 4; //Four rows
const byte COLS = 4; //Four columns

//Defining the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //Connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //Connect to the column pinouts of the keypad

//Initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  myservo.attach(10); //Initializing the servo to pin D10
  pinMode(buzzer,OUTPUT); 
  pinMode(external,INPUT);
  pinMode(internal,INPUT); 
  //Initialize the screen and print the first text
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("    PASSWORD");
  lcd.setCursor(0,1);
  lcd.print("      -***     ");
  //Put the servo in the close position first
  myservo.write(mot_min);  
  
}
  
void loop()
{

//Bluetooth Control Setup 
  if(Serial.available()>0)
 { 
    
    char Received = Serial.read();

    if (Received == 'c')
    {
      myservo.write(mot_min);
      activated = 0;
      character=0;
      Str[6]= '-';
      Str[7]= '*'; 
      Str[8]= '*'; 
      Str[9]= '*';
      Str[10]= ' ';   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    PASSWORD");    
      lcd.setCursor(0,1);
      lcd.print(Str);  
    }
    if (Received == 'o')
    {
      myservo.write(mot_max);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Bluetooth OPEN");
      activated = 2;
      analogWrite(buzzer,240);
      delay(250);
      analogWrite(buzzer,200);
      delay(250);
      analogWrite(buzzer,180);
      delay(250);
      analogWrite(buzzer,250);
      delay(250);
      analogWrite(buzzer,LOW);
     
      
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("WELCOME");
      
      lcd.setCursor(2,1);
      lcd.print("USAMAH'S ROOM");
      

      lcd.clear();    
      lcd.setCursor(3,0);
      lcd.print("DOOR  OPEN");
      lcd.setCursor(2,1);
      lcd.print("USAMAH'S ROOM");
      delay(500);
    }
    
    
    
 }

//Room's internal buttons control
  if (digitalRead(external))
  {
      myservo.write(mot_max);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("INSIDE  OPEN");
      activated = 2;
      analogWrite(buzzer,240);
      delay(250);
      analogWrite(buzzer,200);
      delay(250);
      analogWrite(buzzer,180);
      delay(250);
      analogWrite(buzzer,250);
      delay(250);
      analogWrite(buzzer,LOW);
     
      
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("WELCOME");
      
      lcd.setCursor(2,1);
      lcd.print("USAMAH'S ROOM");
      

      lcd.clear();    
      lcd.setCursor(3,0);
      lcd.print("DOOR  OPEN");
      lcd.setCursor(2,1);
      lcd.print("USAMAH'S ROOM");
      delay(500);
    
  }

  if (digitalRead(internal))
  {
    myservo.write(mot_min);
    activated = 0;
    character=0;
    Str[6]= '-';
    Str[7]= '*'; 
    Str[8]= '*'; 
    Str[9]= '*';
    Str[10]= ' ';   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    PASSWORD");    
    lcd.setCursor(0,1);
    lcd.print(Str);
  }
    
//Setup Keypad Control  
  char customKey = customKeypad.getKey(); //this function reads the presed key
  
  if (customKey){
  analogWrite(buzzer,200);
    if (character ==0)
    {  
    Serial.println(customKey);
    Str[6]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    PASSWORD");    
    lcd.setCursor(0,1);
    lcd.print(Str);
   
    }

    if (character ==1)
    {  
    Serial.println(customKey);
    Str[7]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    PASSWORD");    
    lcd.setCursor(0,1);
    lcd.print(Str);
   
    }

    if (character ==2)
    {  
    Serial.println(customKey);
    Str[8]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    PASSWORD");    
    lcd.setCursor(0,1);
    lcd.print(Str);
   
    }

    if (character ==3)
    {  
    Serial.println(customKey);
    Str[9]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    PASSWORD");    
    lcd.setCursor(0,1);
    lcd.print(Str);
   
    }

    if (character ==4)
    {  
    Serial.println(customKey);
    Str[10]= customKey;
    activated=1;
   
    }
    character=character+1;
    delay(100);
    analogWrite(buzzer,LOW);
  }

  if (activated == 1)
    {
    if(Str[10]='A' && character==5 && Str[6]=='2' && Str[7]=='7' && Str[8]=='6' && Str[9]=='3' )
    {
      myservo.write(mot_max);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("ACCEPTED");
      activated = 2;
      analogWrite(buzzer,240);
      delay(250);
      analogWrite(buzzer,200);
      delay(250);
      analogWrite(buzzer,180);
      delay(250);
      analogWrite(buzzer,250);
      delay(250);
      analogWrite(buzzer,LOW);
      delay(1000);
      
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("WELCOME");
      delay(500);
      lcd.setCursor(2,1);
      lcd.print("USAMAH'S ROOM");
      delay(1000);

      lcd.clear();    
      lcd.setCursor(3,0);
      lcd.print("DOOR  OPEN");
      lcd.setCursor(2,1);
      lcd.print("USAMAH'S ROOM");
      
    }
    else
    {
      lcd.clear();    
      lcd.setCursor(1,0);
      lcd.print("WRONG PASSWORD");
      lcd.setCursor(3,1);
      lcd.print("TRY  AGAIN");
      analogWrite(buzzer,150);
      delay(3000);
      analogWrite(buzzer,LOW);
      character=0;
      Str[6]= '-';
      Str[7]= '*'; 
      Str[8]= '*'; 
      Str[9]= '*';
      Str[10]= ' ';
      activated = 0;
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("PASSWORD");
      lcd.setCursor(0,1);
      lcd.print(Str);   
    }
  }
  if (activated == 2)
    {
    if(customKey == 'B' )
    {
      myservo.write(mot_min);
      activated = 0;
      character=0;
      Str[6]= '-';
      Str[7]= '*'; 
      Str[8]= '*'; 
      Str[9]= '*';
      Str[10]= ' ';   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    PASSWORD");    
      lcd.setCursor(0,1);
      lcd.print(Str);
     
    }
  }  
}
