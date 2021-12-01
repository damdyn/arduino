#include <LiquidCrystal.h>
#include <CurrentState.h>
#include <LumbMil.h>

const int MOTOR_UP = 10;
const int MOTOR_DOWN = 11;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int BUTTON_UP_PIN = 6;
const int BUTTON_DOWN_PIN = 7;
const int BUTTON_A_PIN = 8;
const int BUTTON_B_PIN = 9;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

CurrentState currentState(MOTOR_DOWN, MOTOR_UP);
Context cx(new Work(), &lcd, &currentState);
void setup()
{
    lcd.begin(16, 2);
    String a ;
    lcd.print("hello, world!");
    initButtons();
    
}
void initButtons(){
    pinMode(BUTTON_UP_PIN, INPUT);
    pinMode(BUTTON_DOWN_PIN, INPUT);
    pinMode(BUTTON_A_PIN, INPUT);
    pinMode(BUTTON_B_PIN, INPUT);
    pinMode(MOTOR_DOWN, OUTPUT);
    pinMode(MOTOR_UP, OUTPUT);
}

void loop()
{
    if(digitalRead(BUTTON_UP_PIN) == HIGH)
    {
      cx.ButtonUp();  
    }
        else if(digitalRead(BUTTON_DOWN_PIN) == HIGH)
    {
      cx.ButtonDown();  
    }
        else if(digitalRead(BUTTON_A_PIN) == HIGH)
    {
      cx.ButtonA();  
    }
        else if(digitalRead(BUTTON_B_PIN) == HIGH)
    {
      cx.ButtonB();  
    }
}
