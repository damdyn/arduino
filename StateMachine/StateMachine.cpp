#include <LiquidCrystal.h>
class Context;

class State {
  /**
   * @var Context
   */
 protected:
  Context *context_;

 public:
  virtual ~State() {
  }

  void set_context(Context *context) {
    this->context_ = context;
  }

  virtual void ButtonUp() = 0;
  virtual void ButtonDown() = 0;
  virtual void ButtonA() = 0;
  virtual void ButtonB() = 0;
  virtual void UpdateLcd(LiquidCrystal *lcd) = 0;
};

class Context {
  /**
   * @var State A reference to the current state of the Context.
   */
 private:
  State *state_;
  LiquidCrystal *lcd_;

 public:
  Context(State *state, LiquidCrystal *lcd) : state_(nullptr) {
    this->lcd_ = lcd;
    this->TransitionTo(state);
  }
  ~Context() {
    delete state_;
    delete lcd_;
  }
  /**
   * The Context allows changing the State object at runtime.
   */
  void TransitionTo(State *state) {
    if (this->state_ != nullptr)
      delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
  }
  /**
   * The Context delegates part of its behavior to the current State object.
   */
  void ButtonUp() {
    this->state_->ButtonUp();
    this->state_->UpdateLcd(this->lcd_);
  }
  void ButtonDown() {
    this->state_->ButtonDown();
    this->state_->UpdateLcd(this->lcd_);
  }
  void ButtonA(){
    this->state_->ButtonA();
    this->state_->UpdateLcd(this->lcd_);
  };
   void ButtonB(){
     this->state_->ButtonB();
     this->state_->UpdateLcd(this->lcd_);
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
  void ButtonUp() override {
    this->context_->TransitionTo(new WorkMenu);
  }
  void ButtonDown() override {
    this->context_->TransitionTo(new SettingsMenu);
  }
  void ButtonB() override {
    
  }
  void ButtonA() override {
    this->context_->TransitionTo(new BoardSelection);
  }
  void UpdateLcd(LiquidCrystal *lcd) override
  {
    lcd->setCursor(0,0);
    lcd->print("-> Wybór deski");
  }
};
class WorkMenu : public State {
 public:
  void ButtonUp() override {
    this->context_->TransitionTo(new SettingsMenu);
  }
  void ButtonDown() override {
    this->context_->TransitionTo(new SelectedBoardMenu);
  }
    void ButtonB() override {

  }
  void ButtonA() override {
    this->context_->TransitionTo(new Work);
  }
    void UpdateLcd(LiquidCrystal *lcd) override
  {
    lcd->setCursor(0,0);
    lcd->print("-> Praca");
  }
  
};

class SettingsMenu : public State {
 public:
  void ButtonUp() override {
    this->context_->TransitionTo(new SelectedBoardMenu);
  }
  void ButtonDown() override {
    Work work;
    this->context_->TransitionTo(&work);
  }
    void ButtonB() override {

  }
  void ButtonA() override {
    this->context_->TransitionTo(new Settings);
  }
    void UpdateLcd(LiquidCrystal *lcd) override
  {
    lcd->setCursor(0,0);
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
    void UpdateLcd(LiquidCrystal *lcd) override
  {
    lcd->setCursor(0,0);
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
    void UpdateLcd(LiquidCrystal *lcd) override
  {
    lcd->setCursor(0,0);
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
    void UpdateLcd(LiquidCrystal *lcd) override
  {
    lcd->setCursor(0,0);
    lcd->print("Praca");
  }
  
};
