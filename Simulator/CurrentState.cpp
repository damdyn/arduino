#include <iostream>
#include<CurrentState.h>
using namespace std;
bool CurrentState::MotorIsRuning() {
    return MotorIsGoingDown || MotorIsGoingUp;
}
void CurrentState::SetHomePosition() {
    impulsCount = 0;
}
void CurrentState::GoUP() {
    MotorIsGoingUp = true;
    cout << "Motor: Go up";
    cout << "\n";
};
void CurrentState::GoDown() {
    MotorIsGoingDown = true;
    cout << "Motor: Go down";
    cout << "\n";
};
void CurrentState::Stop() {
    MotorIsGoingDown = false;
    MotorIsGoingUp = false;
    cout << "Motor: Stop";
    cout << "\n";
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


