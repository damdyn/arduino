#pragma once
#include <LiquidCrystal.h>
#include <CurrentState.h>

struct Data {
    int selectedBordSizeMM;
    int selectedBoardNumber;
    float converter;
    int setPosition;

};
class Context;

class State {
    /**
     * @var Context
     */

protected:
    Context* context_ = nullptr;


public:
    virtual ~State() {};

    void set_context(Context* context);
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
    Context(State* state, LiquidCrystal* lcd, CurrentState* data);
    LiquidCrystal* lcd_;
    Data configData_;
    CurrentState* data_;
    ~Context();
    /**
     * The Context allows changing the State object at runtime.
     */
    void TransitionTo(State* state);
    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void ButtonUp();
    void ButtonDown();
    void ButtonA();
    void ButtonB();
    void ExecuteTask(CurrentState* data);

};
class WorkMenu;
class SettingsMenu;
class BoardSelection;

class SelectedBoardMenu : public State {
public:
    void ButtonUp() override;

    void ButtonDown() override;
    void ButtonB() override;
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override;

};
class WorkMenu : public State {
public:
    void ButtonUp() override;
    void ButtonDown() override;
    void ButtonB() override;
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override;

};

class SettingsMenu : public State {
public:
    void ButtonUp() override;
    void ButtonDown() override;
    void ButtonB() override;
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override;

};
class Settings : public State {
public:
    void ButtonUp() override;
    void ButtonDown() override;
    void ButtonB() override;
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override;

};
class BoardSelection : public State {
private:
    int _boardNumber;
    int _boardValue;
public:
    BoardSelection(int boradNumber, int boardValue);
    void ButtonUp() override;
    void ButtonDown() override;
    void ButtonB() override;
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override;

};
class BoardSettings : public State {
private:
    int _boardNumber = 0;
    int _boardValue = 0;
public:
    BoardSettings(int boardNumber, int boardValue);
    void ButtonUp() override;
    void ButtonDown() override;
    void ButtonB() override;
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override;

};
class Work : public State {

public:
    void ButtonUp() override;
    void ButtonDown() override;

    void ButtonB() override;
    void ButtonA() override;
    void UpdateLcd(LiquidCrystal* lcd) override;
    void ExecuteTask(CurrentState* data);

};
