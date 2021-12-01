#pragma once
#include <cstdint>
#pragma once
class LiquidCrystal {
private:
    uint8_t col;
    uint8_t row;
public:
    char Row0[16] = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', };
    char Row1[16] = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', };

    void setCursor(uint8_t col, uint8_t row);
    void print(const char str[]);
    void print(float a);
    void clear();
    void print(int a);
    void printHelper();
};