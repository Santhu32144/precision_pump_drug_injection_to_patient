#include <stdio.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Stepper.h>


////////////////////////////////////////////
//define lcd pins
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//defining the 4x4 keypad
const byte ROWS = 4;
const byte COLS = 4;
const int stepPin = 3; 
const int dirPin = 4;


byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
char keys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},

};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//defining the stepper motor
const int stepsPerRevolution = 200; 
Stepper stepper(stepsPerRevolution, 10, 11, 12, 13);


void showSpalshScreen() {
  lcd.print("   WELCOME TO   ");
  lcd.setCursor(3, 1);
  String message = "SYRINGE PUMP";
  for (byte i = 0; i < message.length(); i++) {
    lcd.print(message[i]);
    delay(200);
  }
  delay(500);
}


void updateCursor() {
  if (millis() / 250 % 2 == 0 ) {
    lcd.cursor();
  } else {
    lcd.noCursor();
  }
}


int hrs = 0;
int min = 0;
int sec = 0;
char op;
bool num1Entered = false;
bool num2Entered = false;
bool num3Entered = false;
char buffer[40];
int i,hrs1,min1,sec1,total;
float steps_per_sec,steps_per_sec1;
int time_for_each_steps,time_for_each_steps1,time_for_each_steps2;
float remaining;
float percentage;


void setup()
{
  lcd.init();
  Serial.begin(9600);
  stepper.setSpeed(160);
    showSpalshScreen();
    loop();
    while(1){
      char key = customKeypad.getKey();
      if (key == '1') {stepper.step(100);}
    else if (key == '2') {stepper.step(-100);}
    else if (key == '3') {stepper.step(300);}
    else if (key == '4') {stepper.step(-300);}
    else if (key == '0') {break;}
    }
}

void processInput(char key)
{
      char volume[20];
      long parseInt(char ignore);
      char A,B,C,D;
      char value;
      char a[10];
      int i;
      a[0] = 0;a[1] = 0;a[2] = 0;a[3] = 0;
      char n[40];
      char buffer[40];

    while(1)
    {
      lcd.setCursor(0,0);
      lcd.println("A= 100ml,B= 50ml");
      lcd.setCursor(0,1);
      lcd.println("C= 20ml, D= 10ml");

        char keypressed = key;
        if(keypressed != 0)
        {
          char key = customKeypad.getKey();
            if(key == '0')
            {
              setup();
            }
          if(keypressed == 'A')
        {
            tone(A3,200);
            delay(200);
            noTone(A3);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" 100ml Selected ");
            delay(600);
            lcd.setCursor(0,0);
            lcd.print("set time :H:M   ");
            delay(1200);
            lcd.clear();
            settime();

          }
           else if(keypressed == 'B')
          {
            tone(A3,200);
            delay(200);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("50ml Selected"); 
            delay(600);
            lcd.setCursor(0,0);
            lcd.print("set time :H:M   ");
            delay(1200);
            lcd.clear();
            settime();
          }
          else if(keypressed == 'C')
          {
            tone(A3,200);
            delay(200);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("20ml Selected");  
            delay(600);
            lcd.setCursor(0,0);
            lcd.print("set time :H:M   ");
            delay(1200);
            lcd.clear();
            settime();
          }
           else if(keypressed == 'D')
          {
            tone(A3,200);
            delay(200);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("10ml Selected"); 
            delay(600);
            lcd.setCursor(0,0);
            lcd.print("set time :H:M   ");
            delay(1200);
            lcd.clear();
            settime();
          }
        else
          {
            tone(A3,200);
            delay(200);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Please Press"); 
            delay(500);
            lcd.setCursor(0,1);
            lcd.print("A, B, C, D");
            delay(3000);
            lcd.clear();
            key = 0;
            loop();
          }
          break;
      }
    }
}


void loop()
{
  updateCursor();
      lcd.setCursor(0,0);
      lcd.println("A= 100ml,B= 50ml");
      lcd.setCursor(0,1);
      lcd.println("C= 20ml, D= 10ml");
          char key = customKeypad.getKey();
          if(key){updateCursor();processInput(key);}
        }
          
void loop1(int hrs, int min) {
  while(1)
  {
  char key = customKeypad.getKey();
  char buffer1[40];
  sprintf(buffer1,"Time: %02d:%02d",hrs,min);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(buffer1);
    hrs1 = hrs*60*60;
    min1 = min*60;
    total = hrs1 + min1;
    total = total - 250;
    steps_per_sec = (9600.0/(total + 0.0));
    time_for_each_steps = (1.0/steps_per_sec)*1000;

      for(i=0;i<=9600;i++)
      {
        stepper.step(1);
      percentage = ((i + 0.0)/9600.0)*100;
      lcd.setCursor(0,1);
      lcd.print("Running...");
      lcd.print(percentage);
      lcd.print("%");
      delay(time_for_each_steps);
      char key = customKeypad.getKey();
        if (key == '5') {intermediate();}
        if(i == 9600){refilling();} 
      }
}
}

void settime()
{
 while(1)  
 {
  char key = customKeypad.getKey();
    if (key != NO_KEY)
   {
     if(key == 'D')
     {
       setup();
     }
             if (key == 'C') 
        {
          hrs = 0;
          min = 0;
          sec = 0;        
          op = '\0';
          num1Entered = false;
          num2Entered = false;
          num3Entered = false;
          lcd.clear();
          lcd.print("set time:H:M");
          delay(2000);
          lcd.clear();
        }
        if(key == 'D'){
          setup();
        }
          else if (key >= '0' && key <= '9')
         {
              tone(A3,200);
              delay(200);
              noTone(A3);
            if (!num1Entered)
            {
              hrs = hrs * 10 + (key - '0');
              updateCursor();
              lcd.print(key);
            }
            else if (num1Entered && !num2Entered)
            {
              tone(A3,200);
              delay(200);
              noTone(A3);
              min = min * 10 + (key - '0');
              updateCursor();
              lcd.print(key);
            }
          }

    else if(key == 'A')
    {
        tone(A3,200);
        delay(200);
        noTone(A3);
      op = key;
      updateCursor();
      num1Entered = true;
      num2Entered = false;
      num3Entered = false;
      lcd.setCursor(0, 0);
      lcd.print("HH:MM");
      lcd.setCursor(0, 1);
      lcd.print(hrs);
      lcd.print(":");
    }
      
    else if (key == 'B')
       {
       op = key;
      num1Entered = true;
      num2Entered = true;
      num3Entered = false;
      updateCursor();
      lcd.setCursor(0, 0);
      lcd.print("HH:MM");
      lcd.setCursor(0, 1);
      lcd.print(hrs);
      lcd.print(":");
      lcd.print(min);
      }
     else if (key == '*')
      {
          tone(A3,200);
          delay(200);
          noTone(A3);
          sprintf(buffer, "%02d:%02d         " ,hrs,min); 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("set time is");
          lcd.setCursor(0,1);
          lcd.print(buffer);
      }
      else if (key == '#')
      {
        tone(A3,200);
        delay(200);
        noTone(A3);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Starts in....   ");
        lcd.setCursor(0,1);
        lcd.print("3");
        updateCursor();
        delay(1000);  

        tone(A3,200);
        delay(200);
        noTone(A3);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Starts in....   ");
        lcd.setCursor(0,1);
        lcd.print("2");
        updateCursor();
        delay(1000);  

        tone(A3,200);
        delay(200);
        noTone(A3);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Starts in....   ");
        lcd.setCursor(0,1);
        lcd.print("1");
        updateCursor();
        tone(A3,200);
        delay(1000);
        noTone(A3);
       loop1(hrs,min);   
      }
    }
  }
}

void intermediate()
{
  while(1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("press 0");
    while(1)
    {
    char key = customKeypad.getKey();
    if(key == '0'){stepper.step(-i);}
    if(key == 'D'){setup();}
    }
  }
}

void refilling()
{
tone(A3,200);delay(300);noTone(A3);
tone(A3,200);delay(300);noTone(A3);
tone(A3,200);delay(300);noTone(A3);
tone(A3,200);delay(300);noTone(A3);
tone(A3,200);delay(300);noTone(A3);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("    Press 0");
            lcd.setCursor(0,1);
            lcd.print("To refill it");
          while(1)
          {
            char key = customKeypad.getKey();
            if(key == '0')
            {
              lcd.clear();
              lcd.setCursor(0,1);
              lcd.print("Thank you");
            stepper.step(-9600);
            delay(-200);
           }
            else if(key == 'D'){setup();}
          }
}