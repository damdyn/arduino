#pragma once
class CurrentState {
public:
    CurrentState(int motorUp, int motorDown);
    bool lowerLimitSwitch = false;
    bool upperLimitSwitch = false;
    int impulsCount = 0;
    bool MotorIsRuning();
    bool MotorIsGoingUp = false;
    bool MotorIsGoingDown = false;
    void SetHomePosition();
    void GoUP();
    void GoDown();
    void Stop();
    int GetBoard(int boradNumber);
    void SaveBorad(int boradNumber, int value);
    void SaveGain(float newGain);
    float GetGain();
private:
    int boards[10] = { 10,20,30,50,50,60,70,80,90,99 };
    float gain = 1;
    int motorUp_;
    int motoDown_;
};


