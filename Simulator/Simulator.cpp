#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
//#include <LiquidCrystal.h>
//#include <CurrentState.h>
#include <LumbMil.h>

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
using namespace std;


//class CurrentState {
//    public:
//        bool lowerLimitSwitch = false;
//        bool upperLimitSwitch = false;
//        int impulsCount = 0 ;
//        bool MotorIsRuning() {
//            return MotorIsGoingDown || MotorIsGoingUp;
//        }
//        bool MotorIsGoingUp = false;
//        bool MotorIsGoingDown = false;
//        void SetHomePosition() {
//            impulsCount = 0;
//        }
//        void GoUP() {
//            MotorIsGoingUp = true;
//            cout << "Motor: Go up";
//            cout << "\n";
//        };
//        void GoDown() {
//            MotorIsGoingDown = true;
//            cout << "Motor: Go down";
//            cout << "\n";
//        };
//        void Stop() {
//            MotorIsGoingDown = false;
//            MotorIsGoingUp = false;
//            cout << "Motor: Stop";
//            cout << "\n";
//        }
//        int GetBoard(int boradNumber) 
//        {
//            return boards[boradNumber];
//        }
//        void SaveBorad(int boradNumber, int value) 
//        {
//            boards[boradNumber] = value;
//        }
//        void SaveGain(float newGain) {
//            gain = newGain;
//        }
//        float GetGain() {
//            return gain;
//        }
//    private:
//        int boards[10] = { 10,20,30,50,50,60,70,80,90,99 };
//        float gain = 1;
//
//};
//class LiquidCrystal {
//private:
//    uint8_t col;
//    uint8_t row;
//public:
//    char Row0[16] = {' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', };
//    char Row1[16] = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', };
//
//    void setCursor(uint8_t col, uint8_t row)
//    {
//        this->col = col;
//        this->row = row;
//    };
//    void print(const char str[]) {
//        uint8_t i = 0;
//        for (i; i < strlen(str); i++)
//        {
//            if (row == 0) {
//                Row0[i + col] = str[i];
//            }
//            else if (row == 1) {
//                Row1[i + col] = str[i];
//            }
//        }
//        if (row == 0)
//        {
//            col += i;
//        }
//        else if (row == 1) {
//            col += i;
//        }
//
//    };
//    void print(float a) {
//        char array[10];
//        sprintf_s(array, "%f", a);
//        for (size_t i = 0; i < 4; i++)
//        {
//            Row1[i + col] = array[i];
//        }
//        if (row == 0)
//        {
//            col += 4;
//        }
//        else if (row == 1) {
//            col += 4;
//        }
//    }
//    void clear() {
//        for (size_t i = 0; i < 15; i++)
//        {
//            Row0[i] = ' ';
//            Row1[i] = ' ';
//        }
//    }
//    void print(int a) {
//        std::string tmp = std::to_string(a);
//        char const* num_char = tmp.c_str();
//        int i = 0;
//        while (*num_char != '\0') {
//            //process the current char
//
//
//            if (row == 0) {
//                Row0[i + col] = *num_char;
//            }
//            else if (row == 1) {
//                Row1[i + col] = *num_char;
//            }
//            ++num_char;
//            i++;//you can increment pointers without assigning an address to them
//        };
//        if (row == 0)
//        {
//            col += i;
//        }
//        else if (row == 1) {
//            col += i;
//        }
//
//    }
//    void printHelper() {
//        system("CLS");
//        cout << "---------------------";
//        cout << "\n";
//        cout << this->Row0;
//        cout << "\n";
//        cout << this->Row1;
//        cout << "\n";
//        cout << "---------------------";
//        cout << "\n";
//        cout << "Pruszaj sie po menu strzlkami !\n";
//    }
//};

//struct Data {
//    int selectedBordSizeMM;
//    int selectedBoardNumber;
//    float converter;
//    int setPosition;
//
//};
//class Context;
//
//class State {
//    /**
//     * @var Context
//     */
//    
//protected:
//    Context* context_ = nullptr;
//
//
//public:
//    virtual ~State() {
//    }
//
//    void set_context(Context* context) {
//        this->context_ = context;
//    }
//
//    virtual void ButtonUp() = 0;
//    virtual void ButtonDown() = 0;
//    virtual void ButtonA() = 0;
//    virtual void ButtonB() = 0;
//    virtual void UpdateLcd(LiquidCrystal* lcd) = 0;
//    virtual void ExecuteTask(CurrentState* data) {};
//};
//
//class Context {
//    /**
//     * @var State A reference to the current state of the Context.
//     */
//private:
//    State* state_;
//    
//  
//public:
//    Context(State* state, LiquidCrystal* lcd, CurrentState* data) : state_(nullptr) {
//        this->lcd_ = lcd;
//        this->data_ = data;
//        this->configData_.selectedBordSizeMM = data->GetBoard(0);
//        this->configData_.selectedBoardNumber = 0;
//
//        this->TransitionTo(state);
//        this->configData_.converter = data_->GetGain();
//   
//    }
//    LiquidCrystal* lcd_;
//    Data configData_;
//    CurrentState* data_;
//    ~Context() {
//        //delete state_;
//        //delete lcd_;
//    }
//    /**
//     * The Context allows changing the State object at runtime.
//     */
//    void TransitionTo(State* state) {
//        //if (this->state_ != nullptr)
//            //delete this->state_;
//        delete state_;
//        this->lcd_->clear();
//        this->state_ = state;
//        this->state_->set_context(this);
//        this->state_->UpdateLcd(this->lcd_);
//        if (this->data_->MotorIsRuning())
//            this->data_->Stop();
//    }
//    /**
//     * The Context delegates part of its behavior to the current State object.
//     */
//    void ButtonUp() {
//        this->state_->ButtonUp(); 
//    }
//    void ButtonDown() {
//        this->state_->ButtonDown();
//    }
//    void ButtonA() {
//        this->state_->ButtonA();
//    };
//    void ButtonB() {
//        this->state_->ButtonB();
//    };
//    void ExecuteTask(CurrentState* data) {
//        this->state_->ExecuteTask(data);
//    };
//    
//};
//class WorkMenu;
//class SettingsMenu;
//class BoardSelection;
//
//class SelectedBoardMenu : public State {
//public:
//    void ButtonUp() override;
//
//    void ButtonDown() override;
//    void ButtonB() override {
//
//    }
//    void ButtonA() override;
//    void UpdateLcd(LiquidCrystal* lcd) override
//    {
//        lcd->setCursor(0, 0);
//        lcd->print("-> Wybor deski");
//        lcd->setCursor(0, 1);
//        int data = this->context_->configData_.selectedBoardNumber;
//        lcd->print(context_->configData_.selectedBoardNumber);
//        lcd->print(":");
//        lcd->print(context_->configData_.selectedBordSizeMM);
//    }
//
//};
//class WorkMenu : public State {
//public:
//    void ButtonUp() override;
//    void ButtonDown() override {
//        this->context_->TransitionTo(new SelectedBoardMenu);
//    }
//    void ButtonB() override {
//
//    }
//    void ButtonA() override;
//    void UpdateLcd(LiquidCrystal* lcd) override
//    {
//        lcd->setCursor(0, 0);
//        lcd->print("-> Praca ");
//    }
//
//};
//
//class SettingsMenu : public State {
//public:
//    void ButtonUp() override {
//        this->context_->TransitionTo(new SelectedBoardMenu);
//    }
//    void ButtonDown() override {
//        this->context_->TransitionTo(new WorkMenu);
//    }
//    void ButtonB() override {
//
//    }
//    void ButtonA() override;
//    void UpdateLcd(LiquidCrystal* lcd) override
//    {
//        lcd->setCursor(0, 0);
//        lcd->print("-> Ustawienia");
//    }
//
//};
//class Settings : public State {
//public:
//    void ButtonUp() override {
//        this->context_->configData_.converter +=(float)0.01;
//        if (this->context_->configData_.converter >= 1)
//            this->context_->configData_.converter = 1;
//        UpdateLcd(context_->lcd_);
//    }
//    void ButtonDown() override {
//        this->context_->configData_.converter -= (float)0.01;
//        if (this->context_->configData_.converter <= 0)
//            this->context_->configData_.converter = 0;
//        UpdateLcd(context_->lcd_);
//    }
//    void ButtonB() override {
//        context_->data_->SaveGain(context_->configData_.converter);
//        this->context_->TransitionTo(new SettingsMenu);
//    }
//    void ButtonA() override {
//
//    }
//    void UpdateLcd(LiquidCrystal* lcd) override
//    {
//        lcd->setCursor(0, 0);
//        lcd->print("1 impuls to");
//        lcd->setCursor(0, 1);
//        lcd->print("            ");
//        lcd->setCursor(0, 1);
//        lcd->print(this->context_->configData_.converter);
//        lcd->print(" mm");
//    }
//
//};
//class BoardSelection : public State {
//private:
//    int _boardNumber;
//    int _boardValue;
//public:
//    BoardSelection(int boradNumber, int boardValue)
//    {
//        _boardNumber = boradNumber;
//        _boardValue = boardValue;
//    }
//    void ButtonUp() override {
//        _boardNumber--;
//        if (_boardNumber < 0)
//            _boardNumber = 9;
//        _boardValue = this->context_->data_->GetBoard(_boardNumber);
//        this->UpdateLcd(this->context_->lcd_);
//    }
//    void ButtonDown() override {
//        
//        _boardNumber++;
//        if (_boardNumber > 9)
//            _boardNumber = 0;
//        _boardValue = this->context_->data_->GetBoard(_boardNumber);
//        this->UpdateLcd(this->context_->lcd_);
//
//    }
//    void ButtonB() override {
//        this->context_->configData_.selectedBordSizeMM = _boardValue;
//        this->context_->configData_.selectedBoardNumber = _boardNumber;
//        this->context_->TransitionTo(new SelectedBoardMenu);
//        
//    }
//    void ButtonA() override;
//    void UpdateLcd(LiquidCrystal* lcd) override
//    {
//        lcd->setCursor(0, 0);
//        lcd->print("Wybrana deska:");
//        lcd->setCursor(14, 0);
//        lcd->print(" ");
//        lcd->setCursor(14, 0);
//        lcd->print(_boardNumber);
//        lcd->setCursor(0, 1);
//        lcd->print(_boardValue);
//    }
//
//};
//class BoardSettings : public State {
//private:
//    int _boardNumber = 0;
//    int _boardValue = 0;
//public:
//    BoardSettings(int boardNumber, int boardValue)
//    {
//        _boardValue = boardValue;
//        _boardNumber = boardNumber;
//    }
//    void ButtonUp() override {
//        if (_boardValue >= 200)
//            return;
//        _boardValue++;
//        this->UpdateLcd(this->context_->lcd_);
//    }
//    void ButtonDown() override {
//        if (_boardValue <= 5)
//            return;
//        _boardValue--;
//        this->UpdateLcd(this->context_->lcd_);
//
//    }
//    void ButtonB() override {
//        this->context_->data_->SaveBorad(_boardNumber, _boardValue);
//        this->context_->TransitionTo(new BoardSelection(_boardNumber,_boardValue));
//
//    }
//    void ButtonA() override {
//
//    }
//    void UpdateLcd(LiquidCrystal* lcd) override
//    {
//        lcd->setCursor(0, 0);
//        lcd->print("Zmien deske:");
//        lcd->setCursor(14, 0);
//        lcd->print(" ");
//        lcd->setCursor(14, 0);
//        lcd->print(_boardNumber);
//        lcd->setCursor(0, 1);
//        lcd->print("       ");
//        lcd->setCursor(0, 1);
//        lcd->print(_boardValue);
//    }
//
//};
//class Work : public State {
//
//public:
//    void ButtonUp() override {
//        //Home possition
//        if (context_->data_->MotorIsRuning())
//            return;
//        int currentPos = (int)(this->context_->data_->impulsCount * this->context_->configData_.converter);
//        this->context_->configData_.setPosition = 0;
//        if (this->context_->configData_.setPosition < currentPos)
//        {
//            this->context_->data_->GoUP();
//            this->context_->lcd_->setCursor(14, 0);
//            this->context_->lcd_->print("*");
//        }
//    }
//    void ButtonDown() override {
//        if (context_->data_->MotorIsRuning())
//            return;
//        int currentPos = (int)(this->context_->data_->impulsCount * this->context_->configData_.converter);
//        this->context_->configData_.setPosition = (int)(this->context_->configData_.selectedBordSizeMM * this->context_->configData_.converter) + currentPos;
//        if (this->context_->configData_.setPosition > currentPos)
//        {
//            this->context_->data_->GoDown();
//            this->context_->lcd_->setCursor(14, 0);
//            this->context_->lcd_->print("*");
//        }          
//    }
//    
//    void ButtonB() override {
//        this->context_->TransitionTo(new WorkMenu);
//    }
//    void ButtonA() override {
//        if (this->context_->data_->MotorIsRuning())
//            return;
//        this->context_->data_->SetHomePosition();
//        context_->configData_.setPosition = 0;
//    }
//    void UpdateLcd(LiquidCrystal* lcd) override
//    {
//        lcd->setCursor(0, 0);
//        lcd->print("Wybrana deska: ");
//        this->context_->lcd_->setCursor(13, 1);
//        this->context_->lcd_->print(this->context_->configData_.selectedBordSizeMM);
//        
//
//    }
//    void ExecuteTask(CurrentState* data) {
//        //if (!data->MotorIsRuning)
//        //    if(this->context_->configData_.setPosition < data->impulsCount * this->context_->configData_.converter)
//        //        data->GoDown();
//        if (data->MotorIsRuning())
//        {
//            if(data->MotorIsGoingDown)
//                if (this->context_->configData_.setPosition <= data->impulsCount * this->context_->configData_.converter)
//                {
//                    data->Stop();
//                    this->context_->lcd_->setCursor(14, 0);
//                    this->context_->lcd_->print(" ");
//                }
//            if (data->MotorIsGoingUp)
//                if (this->context_->configData_.setPosition >= data->impulsCount * this->context_->configData_.converter)
//                {
//                    data->Stop();
//                    this->context_->lcd_->setCursor(14, 0);
//                    this->context_->lcd_->print(" ");
//                }
//            //if (data->MotorIsGoingUp)
//            //    if (this->context_->configData_.setPosition >= data->impulsCount * this->context_->configData_.converter)
//            //    {
//            //        data->Stop();
//            //        this->context_->lcd_->setCursor(14, 0);
//            //        this->context_->lcd_->print(" ");
//            //    }
//
//
//            int toGoal = (this->context_->data_->impulsCount - this->context_->configData_.setPosition);
//            this->context_->lcd_->setCursor(0, 1);
//            this->context_->lcd_->print("       ");
//            this->context_->lcd_->setCursor(0, 1);
//            this->context_->lcd_->print(toGoal);
//        }
//    }
//
//};
//void SelectedBoardMenu::ButtonUp() {
//    this->context_->TransitionTo(new WorkMenu);
//};
//void SelectedBoardMenu::ButtonDown() {
//    this->context_->TransitionTo(new SettingsMenu);
//};
//void BoardSelection::ButtonA() {
//    this->context_->TransitionTo(new BoardSettings(_boardNumber, _boardValue));
//};
//void SelectedBoardMenu::ButtonA() {
//    int boardValue = context_->configData_.selectedBordSizeMM;
//    int boardNumber = context_->configData_.selectedBoardNumber;
//
//    this->context_->TransitionTo(new BoardSelection(boardNumber, boardValue));
//};
//void WorkMenu::ButtonUp() {
//    this->context_->TransitionTo(new SettingsMenu);
//};
//void WorkMenu::ButtonA() {
//    this->context_->TransitionTo(new Work);
//};
//void SettingsMenu::ButtonA() {
//    this->context_->TransitionTo(new Settings);
//}
int main()
{
   // Work work;
    LiquidCrystal lcd;
    CurrentState currentState;
    
    Context cx(new Work(), &lcd, &currentState);
    currentState.impulsCount = 0;
    while (true)
    { 
        lcd.printHelper();
        if (currentState.MotorIsGoingDown)
        {

            currentState.impulsCount += 1;
        }
        else if(currentState.MotorIsGoingUp)
        {
            currentState.impulsCount -= 1;
        }
           
        //cin >> value;
        unsigned char ch2 = _getch();
        switch (ch2) {
        case KEY_UP:
            cx.ButtonUp();
            break;
        case KEY_DOWN:
            cx.ButtonDown();
            break;
        case KEY_RIGHT:
            cx.ButtonA();
            
            break;
        case KEY_LEFT:
            cx.ButtonB();
            break;
        case 1:
            return 0;
            break;
        }
        cx.ExecuteTask(&currentState);
    }
    
    
    return 0;
}