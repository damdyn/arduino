#include <LiquidCrystal.h>
#include <CurrentState.h>
#include <LumbMil.h>


Context::Context(State* state, LiquidCrystal* lcd, CurrentState* data) : state_(nullptr) {
    this->lcd_ = lcd;
    this->data_ = data;
    this->configData_.selectedBordSizeMM = data->GetBoard(0);
    this->configData_.selectedBoardNumber = 0;


    this->TransitionTo(state);
    this->configData_.converter = data_->GetGain();

}

Context::~Context() {
        //delete state_;
        //delete lcd_;
}
    /**
     * The Context allows changing the State object at runtime.
     */
void  Context::TransitionTo(State* state) {
    //if (this->state_ != nullptr)
        //delete this->state_;
    delete state_;
    this->lcd_->clear();
    this->state_ = state;
    this->state_->set_context(this);
    this->state_->UpdateLcd(this->lcd_);
    if (this->data_->MotorIsRuning())
        this->data_->Stop();
}
    /**
     * The Context delegates part of its behavior to the current State object.
     */
void  Context::ButtonUp() {
    this->state_->ButtonUp();
}
void  Context::ButtonDown() {
    this->state_->ButtonDown();
}
void  Context::ButtonA() {
    this->state_->ButtonA();
};
void  Context::ButtonB() {
    this->state_->ButtonB();
};
void  Context::ExecuteTask(CurrentState* data) {
    this->state_->ExecuteTask(data);
};
void State::set_context(Context* context) {
    this->context_ = context;
}
void SelectedBoardMenu::UpdateLcd(LiquidCrystal* lcd)
{
    lcd->setCursor(0, 0);
    lcd->print("-> Wybor deski");
    lcd->setCursor(0, 1);
    int data = this->context_->configData_.selectedBoardNumber;
    lcd->print(context_->configData_.selectedBoardNumber);
    lcd->print(":");
    lcd->print(context_->configData_.selectedBordSizeMM);
}


void WorkMenu::ButtonDown() {
    this->context_->TransitionTo(new SelectedBoardMenu);
}
void WorkMenu::ButtonB() {

}
void WorkMenu::UpdateLcd(LiquidCrystal* lcd)
{
    lcd->setCursor(0, 0);
    lcd->print("-> Praca ");
}

void SettingsMenu::ButtonUp() {
    this->context_->TransitionTo(new SelectedBoardMenu);
}
void SettingsMenu::ButtonDown() {
    this->context_->TransitionTo(new WorkMenu);
}
void SettingsMenu::ButtonB() {

}

void SettingsMenu::UpdateLcd(LiquidCrystal* lcd)
{
    lcd->setCursor(0, 0);
    lcd->print("-> Ustawienia");
}


void Settings::ButtonUp() {
    this->context_->configData_.converter += (float)0.01;
    if (this->context_->configData_.converter >= 1)
        this->context_->configData_.converter = 1;
    UpdateLcd(context_->lcd_);
}
void Settings::ButtonDown() {
    this->context_->configData_.converter -= (float)0.01;
    if (this->context_->configData_.converter <= 0)
        this->context_->configData_.converter = 0;
    UpdateLcd(context_->lcd_);
}
void Settings::ButtonB() {
    context_->data_->SaveGain(context_->configData_.converter);
    this->context_->TransitionTo(new SettingsMenu);
}
void Settings::ButtonA() {

}
void Settings::UpdateLcd(LiquidCrystal* lcd)
{
    lcd->setCursor(0, 0);
    lcd->print("1 impuls to");
    lcd->setCursor(0, 1);
    lcd->print("            ");
    lcd->setCursor(0, 1);
    lcd->print(this->context_->configData_.converter);
    lcd->print(" mm");
}

BoardSelection::BoardSelection(int boradNumber, int boardValue)
{
    _boardNumber = boradNumber;
    _boardValue = boardValue;
}
void BoardSelection::ButtonUp() {
    _boardNumber--;
    if (_boardNumber < 0)
        _boardNumber = 9;
    _boardValue = this->context_->data_->GetBoard(_boardNumber);
    this->UpdateLcd(this->context_->lcd_);
}
void BoardSelection::ButtonDown() {

    _boardNumber++;
    if (_boardNumber > 9)
        _boardNumber = 0;
    _boardValue = this->context_->data_->GetBoard(_boardNumber);
    this->UpdateLcd(this->context_->lcd_);

}
void BoardSelection::ButtonB() {
    this->context_->configData_.selectedBordSizeMM = _boardValue;
    this->context_->configData_.selectedBoardNumber = _boardNumber;
    this->context_->TransitionTo(new SelectedBoardMenu);

}
void BoardSelection::UpdateLcd(LiquidCrystal* lcd)
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


BoardSettings::BoardSettings(int boardNumber, int boardValue)
    {
        _boardValue = boardValue;
        _boardNumber = boardNumber;
    }
void BoardSettings::ButtonUp() {
    if (_boardValue >= 200)
        return;
    _boardValue++;
    this->UpdateLcd(this->context_->lcd_);
}
void BoardSettings::ButtonDown() {
    if (_boardValue <= 5)
        return;
    _boardValue--;
    this->UpdateLcd(this->context_->lcd_);

}
void BoardSettings::ButtonB() {
    this->context_->data_->SaveBorad(_boardNumber, _boardValue);
    this->context_->TransitionTo(new BoardSelection(_boardNumber, _boardValue));

}
void BoardSettings::ButtonA() {

}
void BoardSettings::UpdateLcd(LiquidCrystal* lcd)
{
    lcd->setCursor(0, 0);
    lcd->print("Zmien deske:");
    lcd->setCursor(14, 0);
    lcd->print(" ");
    lcd->setCursor(14, 0);
    lcd->print(_boardNumber);
    lcd->setCursor(0, 1);
    lcd->print("       ");
    lcd->setCursor(0, 1);
    lcd->print(_boardValue);
}


void Work::ButtonUp() {
    //Home possition
    if (context_->data_->MotorIsRuning())
        return;
    int currentPos = (int)(this->context_->data_->impulsCount * this->context_->configData_.converter);
    this->context_->configData_.setPosition = 0;
    if (this->context_->configData_.setPosition < currentPos)
    {
        this->context_->data_->GoUP();
        this->context_->lcd_->setCursor(14, 0);
        this->context_->lcd_->print("*");
    }
}
void Work::ButtonDown() {
    if (context_->data_->MotorIsRuning())
        return;
    int currentPos = (int)(this->context_->data_->impulsCount * this->context_->configData_.converter);
    this->context_->configData_.setPosition = (int)(this->context_->configData_.selectedBordSizeMM * this->context_->configData_.converter) + currentPos;
    if (this->context_->configData_.setPosition > currentPos)
    {
        this->context_->data_->GoDown();
        this->context_->lcd_->setCursor(14, 0);
        this->context_->lcd_->print("*");
    }
}

void Work::ButtonB() {
    this->context_->TransitionTo(new WorkMenu);
}
void Work::ButtonA() {
    if (this->context_->data_->MotorIsRuning())
        return;
    this->context_->data_->SetHomePosition();
    context_->configData_.setPosition = 0;
}
void Work::UpdateLcd(LiquidCrystal* lcd)
{
    lcd->setCursor(0, 0);
    lcd->print("Wybrana deska: ");
    this->context_->lcd_->setCursor(13, 1);
    this->context_->lcd_->print(this->context_->configData_.selectedBordSizeMM);


}
void Work::ExecuteTask(CurrentState* data) {
    //if (!data->MotorIsRuning)
    //    if(this->context_->configData_.setPosition < data->impulsCount * this->context_->configData_.converter)
    //        data->GoDown();
    if (data->MotorIsRuning())
    {
        if (data->MotorIsGoingDown)
            if (this->context_->configData_.setPosition <= data->impulsCount * this->context_->configData_.converter)
            {
                data->Stop();
                this->context_->lcd_->setCursor(14, 0);
                this->context_->lcd_->print(" ");
            }
        if (data->MotorIsGoingUp)
            if (this->context_->configData_.setPosition >= data->impulsCount * this->context_->configData_.converter)
            {
                data->Stop();
                this->context_->lcd_->setCursor(14, 0);
                this->context_->lcd_->print(" ");
            }
        //if (data->MotorIsGoingUp)
        //    if (this->context_->configData_.setPosition >= data->impulsCount * this->context_->configData_.converter)
        //    {
        //        data->Stop();
        //        this->context_->lcd_->setCursor(14, 0);
        //        this->context_->lcd_->print(" ");
        //    }


        int toGoal = (this->context_->data_->impulsCount - this->context_->configData_.setPosition);
        this->context_->lcd_->setCursor(0, 1);
        this->context_->lcd_->print("       ");
        this->context_->lcd_->setCursor(0, 1);
        this->context_->lcd_->print(toGoal);
    }
}


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
void SelectedBoardMenu::ButtonB() {
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
