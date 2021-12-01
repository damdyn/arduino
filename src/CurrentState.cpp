#include "CurrentState.h"
#include <Arduino.h>

using namespace std;
CurrentState::CurrentState(int motorUp, int motorDown){
    motorUp_ =motorUp;
    motorDown = motorDown;
}
bool CurrentState::MotorIsRuning() {
    return MotorIsGoingDown || MotorIsGoingUp;s
}
void CurrentState::SetHomePosition() {
    impulsCount = 0;
}
void CurrentState::GoUP() {
    MotorIsGoingUp = true;
    digitalWrite(motorUp_, HIGH);
};
void CurrentState::GoDown() {
    MotorIsGoingDown = true;
    digitalWrite(motoDown_, HIGH);
};
void CurrentState::Stop() {
    MotorIsGoingDown = false;
    MotorIsGoingUp = false;
    digitalWrite(motorUp_, LOW);
    digitalWrite(motoDown_, LOW);
}
int CurrentState::GetBoard(int boradNumber)
{
    return boards[boradNumber];
}
void CurrentState::SaveBorad(int boradNumber, int value)
{
    boards[boradNumber] = value;
}
void CurrentState::SaveGain(float newGain) {
    gain = newGain;
}
float CurrentState::GetGain() {
    return gain;
}


