#pragma once

class Memory {
private:
    int cells[256];
public:
    Memory();
    int getCell(int cellNumber) const;
    void setCell(int cellNumber, int Newvalue);
    void display();
    void clear();
};
