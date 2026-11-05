# pragma once
#include <string>
#include <cstdint>
using namespace std;
  class Screen{
    private:
    string outputbuffer;
    public:
    void write(uint8_t value);
    void display();




  };