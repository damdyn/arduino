#ifndef StateMachine_h
#define StateMachine_h
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
class SelectedBoardMenu : public State {
 public:
  void ButtonUp() override {
  }
  void ButtonDown() override {
  }
  void ButtonB() override {
  }
  void ButtonA() override {
  }
  void UpdateLcd(LiquidCrystal *lcd) override
  {
    
  }
};
class WorkMenu : public State {
 public:
  void ButtonUp() override {
  }
  void ButtonDown() override {
  }
    void ButtonB() override {

  }
  void ButtonA() override {
  }
    void UpdateLcd(LiquidCrystal *lcd) override
  {
  }
  
};

class SettingsMenu : public State {
 public:
  void ButtonUp() override {
  }
  void ButtonDown() override {
  }
    void ButtonB() override {

  }
  void ButtonA() override {
  }
    void UpdateLcd(LiquidCrystal *lcd) override
  {
  }
  
};
class Settings : public State {
 public:
  void ButtonUp() override {
  }
  void ButtonDown() override {
  }
    void ButtonB() override {

  }
  void ButtonA() override {

  }
    void UpdateLcd(LiquidCrystal *lcd) override
  {
  }
  
};
class BoardSelection : public State {
 public:
  void ButtonUp() override {
  }
  void ButtonDown() override {
  }
    void ButtonB() override {

  }
  void ButtonA() override {

  }
    void UpdateLcd(LiquidCrystal *lcd) override
  {
  }
  
};
class Work : public State {
 public:
  void ButtonUp() override {
  }
  void ButtonDown() override {
  }
    void ButtonB() override {

  }
  void ButtonA() override {

  }
    void UpdateLcd(LiquidCrystal *lcd) override
  {
  }
  
};

#endif