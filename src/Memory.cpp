#include "Memory.h"
#include <iostream>
using namespace std;



 
    int Memory::getCell(int CellNumber){
        return cell[CellNumber];
    }
    void Memory::setCell(int CellNumber,int Newvalue){
        cell[CellNumber] = Newvalue;
        
    }
void Memory::display(){
    for(int i = 0; i < 256;i++){
        cout << cell[i]<<endl;
    }
}

