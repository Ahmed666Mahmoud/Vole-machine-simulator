#pragma once
class Memory{
	private:
		int cells[256];
        public:
	  int getCell(int cellNumber);
	  void setCell(int cellNumyber,int Newvalue);
          void display();
};

