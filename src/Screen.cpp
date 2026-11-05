#include "Screen.h"
#include <iostream>
using namespace std;
void Screen::write(uint8_t value){
outputbuffer +=(char) value;
}

void Screen ::display(){

cout<<outputbuffer;


}
