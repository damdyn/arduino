#include <LiquidCrystal.h>
#include "StateMachine/StateMachine.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Context *cx = new Context(new Work(),&lcd);
void setup()
{
    lcd.begin(16, 2);
    String a ;
    lcd.print("hello, world!");
    
}

void loop()
{
	lcd.setCursor(0, 1);
    cx->ButtonDown();
    // cx->ButtonUp();
    // cx->ButtonA();
    // cx->ButtonB();
}
