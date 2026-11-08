#include "Memory.h"
#include <iostream>
using namespace std;

Memory::Memory() {
    clear();
}

int Memory::getCell(int CellNumber) const {
    if (CellNumber < 0 || CellNumber >= 256) return 0;
    return cells[CellNumber];
}

void Memory::setCell(int CellNumber, int Newvalue) {
    if (CellNumber >= 0 && CellNumber < 256) {
        cells[CellNumber] = Newvalue & 0xFF;
    }
}

void Memory::display() {
    for (int i = 0; i < 256; i++) {
        cout << cells[i] << endl;
    }
}

void Memory::clear() {
    for (int i = 0; i < 256; i++) {
        cells[i] = 0;
    }
}
