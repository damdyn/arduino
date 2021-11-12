#include <LiquidCrystal.h>
const int MOTOR_UP = 10;
const int MOTOR_DOWN = 11;

struct Data {
    int selectedBordSizeMM;
    int selectedBoardNumber;
    float converter;
    int setPosition;   

};

class CurrentState {
    public:
        bool lowerLimitSwitch;
        bool upperLimitSwitch;
        int impulsCount ;
        bool MotorIsRuning = false;
        void SetHomePosition() {
            impulsCount = 0;
        }
        void GoUP() {
            MotorIsRuning = true;
            digitalWrite(MOTOR_UP, HIGH);
        };
        void GoDown() {
            MotorIsRuning = true;
            digitalWrite(MOTOR_DOWN, HIGH);
        };
        void Stop() {
            MotorIsRuning = false;
             digitalWrite(MOTOR_DOWN, LOW);
             digitalWrite(MOTOR_UP, LOW);
        }
        int GetBoard(int boradNumber) 
        {
            return boards[boradNumber];
        }
        void SaveBorad(int boradNumber, int value) 
        {
            boards[boradNumber] = value;
        }
        void SaveGain(float newGain) {
            gain = newGain;
        }
        float GetGain() {
            return gain;
        }
    private:
        int boards[10] = { 10,20,30,50,50,60,70,80,90,99 };
        float gain = 1;

};
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
    virtual void ExecuteTask(CurrentState* data) {};
};

class Context {
    /**
     * @var State A reference to the current state of the Context.
     */
private:
    State* state_;
    
  
public:
    Context(State* state, LiquidCrystal* lcd, CurrentState* data) : state_(nullptr) {
        this->lcd_ = lcd;
        this->data_ = data;
        this->configData_.selectedBordSizeMM = data->GetBoard(0);
        this->configData_.selectedBoardNumber = 0;

        this->TransitionTo(state);
        this->configData_.converter = data_->GetGain();
   
    }
    LiquidCrystal* lcd_;
    Data configData_;
    CurrentState* data_;
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
        this->lcd_->clear();
        this->state_ = state;
        this->state_->set_context(this);
        this->state_->UpdateLcd(this->lcd_);
        if (this->data_->MotorIsRuning)
            this->data_->Stop();
    }
    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void ButtonUp() {
        this->state_->ButtonUp(); 
    }
    void ButtonDown() {
        this->state_->ButtonDown();
    }
    void ButtonA() {
        this->state_->ButtonA();
    };
    void ButtonB() {
        this->state_->ButtonB();
    };
    void ExecuteTask(CurrentState* data) {
        this->state_->ExecuteTask(data);
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
        lcd->print("-> Wybor deski");
        lcd->setCursor(0, 1);
        int data = this->context_->configData_.selectedBoardNumber;
        lcd->print(context_->configData_.selectedBoardNumber);
        lcd->print(":");
        lcd->print(context_->configData_.selectedBordSizeMM);
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
        lcd->print("-> Praca ");
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
        this->context_->configData_.converter += 0.1;
        if (this->context_->configData_.converter == 0)
            this->context_->configData_.converter = 1;
        UpdateLcd(context_->lcd_);
    }
    void ButtonDown() override {
        this->context_->configData_.converter -= 0.01;
        UpdateLcd(context_->lcd_);
    }
    void ButtonB() override {
        context_->data_->SaveGain(context_->configData_.converter);
        this->context_->TransitionTo(new SettingsMenu);
    }
    void ButtonA() override {

    }
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("1 impuls to");
        lcd->setCursor(0, 1);
        lcd->print("            ");
        lcd->setCursor(0, 1);
        lcd->print(this->context_->configData_.converter);
        lcd->print(" mm");
    }

};
class BoardSelection : public State {
private:
    int _boardNumber;
    int _boardValue;
public:
    BoardSelection(int boradNumber, int boardValue)
    {
        _boardNumber = boradNumber;
        _boardValue = boardValue;
    }
    void ButtonUp() override {
        _boardNumber--;
        if (_boardNumber < 0)
            _boardNumber = 9;
        _boardValue = this->context_->data_->GetBoard(_boardNumber);
        this->UpdateLcd(this->context_->lcd_);
    }
    void ButtonDown() override {
        
        _boardNumber++;
        if (_boardNumber > 9)
            _boardNumber = 0;
        _boardValue = this->context_->data_->GetBoard(_boardNumber);
        this->UpdateLcd(this->context_->lcd_);

    }
    void ButtonB() override {
        this->context_->configData_.selectedBordSizeMM = _boardValue;
        this->context_->configData_.selectedBoardNumber = _boardNumber;
        this->context_->TransitionTo(new SelectedBoardMenu);
        
    }
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("Wybrana deska:");
        lcd->setCursor(14, 0);
        lcd->print(" ");
        lcd->setCursor(14, 0);
        lcd->print(_boardNumber);
        lcd->setCursor(0, 1);
        lcd->print(_boardValue);
    }

};
class BoardSettings : public State {
private:
    int _boardNumber = 0;
    int _boardValue = 0;
public:
    BoardSettings(int boardNumber, int boardValue)
    {
        _boardValue = boardValue;
        _boardNumber = boardNumber;
    }
    void ButtonUp() override {
        _boardValue++;
        this->UpdateLcd(this->context_->lcd_);
    }
    void ButtonDown() override {
        _boardValue--;
        this->UpdateLcd(this->context_->lcd_);

    }
    void ButtonB() override {
        this->context_->data_->SaveBorad(_boardNumber, _boardValue);
        this->context_->TransitionTo(new BoardSelection(_boardNumber,_boardValue));

    }
    void ButtonA() override {

    }
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("Zmien deske:");
        lcd->setCursor(14, 0);
        lcd->print(" ");
        lcd->setCursor(14, 0);
        lcd->print(_boardNumber);
        lcd->setCursor(0, 1);
        lcd->print(_boardValue);
    }

};
class Work : public State {
public:
    void ButtonUp() override {

    }
    void ButtonDown() override {
        int currentPos = this->context_->data_->impulsCount * this->context_->configData_.converter;
        this->context_->configData_.setPosition = this->context_->configData_.selectedBordSizeMM * this->context_->configData_.converter + currentPos;
        if (this->context_->configData_.setPosition > currentPos)
        {
            this->context_->data_->GoDown();
            this->context_->lcd_->setCursor(14, 0);
            this->context_->lcd_->print("*");

        }
            

    }
    void ButtonB() override {
        this->context_->TransitionTo(new WorkMenu);
    }
    void ButtonA() override {
        this->context_->data_->SetHomePosition();
    }
    void UpdateLcd(LiquidCrystal* lcd) override
    {
        lcd->setCursor(0, 0);
        lcd->print("Wybrana deska: ");
        this->context_->lcd_->setCursor(13, 1);
        this->context_->lcd_->print(this->context_->configData_.selectedBordSizeMM);
        

    }
    void ExecuteTask(CurrentState* data) {
        //if (!data->MotorIsRuning)
        //    if(this->context_->configData_.setPosition < data->impulsCount * this->context_->configData_.converter)
        //        data->GoDown();
        if (data->MotorIsRuning)
            if (this->context_->configData_.setPosition <= data->impulsCount * this->context_->configData_.converter)
            {
                data->Stop();
                this->context_->lcd_->setCursor(14, 0);
                this->context_->lcd_->print(" ");
            }
                
        int toGoal = (this->context_->data_->impulsCount - this->context_->configData_.setPosition);
        this->context_->lcd_->setCursor(0, 1);
        this->context_->lcd_->print("       ");
        this->context_->lcd_->setCursor(0, 1);
        this->context_->lcd_->print(toGoal);
    }

};
void SelectedBoardMenu::ButtonUp() {
    this->context_->TransitionTo(new WorkMenu);
};
void SelectedBoardMenu::ButtonDown() {
    this->context_->TransitionTo(new SettingsMenu);
};
void BoardSelection::ButtonA() {
    this->context_->TransitionTo(new BoardSettings(_boardNumber, _boardValue));
};
void SelectedBoardMenu::ButtonA() {
    int boardValue = context_->configData_.selectedBordSizeMM;
    int boardNumber = context_->configData_.selectedBoardNumber;

    this->context_->TransitionTo(new BoardSelection(boardNumber, boardValue));
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
CurrentState currentState;
Context cx(&work, &lcd, &currentState);
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
