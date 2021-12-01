#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <LiquidCrystal.h>
using namespace std;

void LiquidCrystal::setCursor(uint8_t col, uint8_t row)
{
    this->col = col;
    this->row = row;
};
void LiquidCrystal::print(const char str[]) {
    uint8_t i = 0;
    for (i; i < strlen(str); i++)
    {
        if (row == 0) {
            Row0[i + col] = str[i];
        }
        else if (row == 1) {
            Row1[i + col] = str[i];
        }
    }
    if (row == 0)
    {
        col += i;
    }
    else if (row == 1) {
        col += i;
    }

};
void LiquidCrystal::print(float a) {
    char array[10];
    sprintf_s(array, "%f", a);
    for (size_t i = 0; i < 4; i++)
    {
        Row1[i + col] = array[i];
    }
    if (row == 0)
    {
        col += 4;
    }
    else if (row == 1) {
        col += 4;
    }
};
void LiquidCrystal::clear() {
    for (size_t i = 0; i < 15; i++)
    {
        Row0[i] = ' ';
        Row1[i] = ' ';
    }
};
void LiquidCrystal::print(int a) {
    std::string tmp = std::to_string(a);
    char const* num_char = tmp.c_str();
    int i = 0;
    while (*num_char != '\0') {
        //process the current char


        if (row == 0) {
            Row0[i + col] = *num_char;
        }
        else if (row == 1) {
            Row1[i + col] = *num_char;
        }
        ++num_char;
        i++;//you can increment pointers without assigning an address to them
    };
    if (row == 0)
    {
        col += i;
    }
    else if (row == 1) {
        col += i;
    }

};
void LiquidCrystal::printHelper() {
    system("CLS");
    cout << "---------------------";
    cout << "\n";
    cout << this->Row0;
    cout << "\n";
    cout << this->Row1;
    cout << "\n";
    cout << "---------------------";
    cout << "\n";
    cout << "Pruszaj sie po menu strzlkami !\n";
};
