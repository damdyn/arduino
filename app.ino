#include <LiquidCrystal.h>
class Context;

class State {
    /**
     * @var Context
     */
protected:
    Context* context_;

public:
    virtual ~State() {
    }

    void set_context(Context* context) {
        this->context_ = context;
    }

    virtual void ButtonUp() = 0;
    virtual void ButtonDown() = 0;
    virtual void ButtonA() = 0;
    virtual void ButtonB() = 0;
    virtual void UpdateLcd(LiquidCrystal* lcd) = 0;
};

class Context {
    /**
     * @var State A reference to the current state of the Context.
     */
private:
    State* state_;
    LiquidCrystal* lcd_;

public:
    Context(State* state, LiquidCrystal* lcd) : state_(nullptr) {
        this->lcd_ = lcd;
        this->TransitionTo(state);
    }
    ~Context() {
        //delete state_;
        //delete lcd_;
    }
    /**
     * The Context allows changing the State object at runtime.
     */
    void TransitionTo(State* state) {
        //if (this->state_ != nullptr)
            //delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
        this->state_->UpdateLcd(this->lcd_);
    }
    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void ButtonUp() {
        system("CLS");
        this->state_->ButtonUp(); 
    }
    void ButtonDown() {
        system("CLS");
        this->state_->ButtonDown();
    }
    void ButtonA() {
        system("CLS");
        this->state_->ButtonA();
    };
    void ButtonB() {
        system("CLS");
        this->state_->ButtonB();
    };
    
};
class WorkMenu;
class SettingsMenu;
class BoardSelection;
class StateMachine
{
private:
    /* data */
public:
    StateMachine(/* args */);
    ~StateMachine();
};

StateMachine::StateMachine(/* args */)
{
}

StateMachine::~StateMachine()
{
}

class SelectedBoardMenu : public State {
public:
    void ButtonUp() override;

    void ButtonDown() override;
    void ButtonB() override {

    }
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("-> Wybór deski");
    }
};
class WorkMenu : public State {
public:
    void ButtonUp() override;
    void ButtonDown() override {
        this->context_->TransitionTo(new SelectedBoardMenu);
    }
    void ButtonB() override {

    }
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("-> PracaMenu");
    }

};

class SettingsMenu : public State {
public:
    void ButtonUp() override {
        this->context_->TransitionTo(new SelectedBoardMenu);
    }
    void ButtonDown() override {
        this->context_->TransitionTo(new WorkMenu);
    }
    void ButtonB() override {

    }
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("-> Ustawienia");
    }

};
class Settings : public State {
public:
    void ButtonUp() override {

    }
    void ButtonDown() override {

    }
    void ButtonB() override {
        this->context_->TransitionTo(new SettingsMenu);
    }
    void ButtonA() override {

    }
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("Ustawienia ustwa");
    }

};
class BoardSelection : public State {
public:
    void ButtonUp() override {

    }
    void ButtonDown() override {

    }
    void ButtonB() override {
        this->context_->TransitionTo(new SelectedBoardMenu);
    }
    void ButtonA() override {

    }
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("-> Tutaj wybiorę deskę");
    }

};
class Work : public State {
public:
    void ButtonUp() override {

    }
    void ButtonDown() override {

    }
    void ButtonB() override {
        this->context_->TransitionTo(new WorkMenu);
    }
    void ButtonA() override {

    }
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("Wybrana deska: ");
        lcd->setCursor(0, 1);
    }

};
void SelectedBoardMenu::ButtonUp() {
    this->context_->TransitionTo(new WorkMenu);
};
void SelectedBoardMenu::ButtonDown() {
    this->context_->TransitionTo(new SettingsMenu);
};
void SelectedBoardMenu::ButtonA() {
    this->context_->TransitionTo(new BoardSelection);
};
void WorkMenu::ButtonUp() {
    this->context_->TransitionTo(new SettingsMenu);
};
void WorkMenu::ButtonA() {
    this->context_->TransitionTo(new Work);
};
void SettingsMenu::ButtonA() {
    this->context_->TransitionTo(new Settings);
}

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int BUTTON_UP_PIN = 6;
const int BUTTON_DOWN_PIN = 7;
const int BUTTON_A_PIN = 8;
const int BUTTON_B_PIN = 9;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Work work;
Context cx(&work, &lcd);
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
