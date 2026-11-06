# pragma once
#include <cstdint>
using namespace std;
class ALU{
    public:
    uint8_t addTwoComplement(uint8_t a, uint8_t b);
    uint8_t addFloatingPoint(uint8_t a, uint8_t b);
    uint8_t bitewiseXOR(uint8_t a, uint8_t b);
    uint8_t bitewiseAND(uint8_t a, uint8_t b);
    uint8_t bitewiseOR(uint8_t a, uint8_t b);
    uint8_t rotateRight(uint8_t value, int steps);



  };