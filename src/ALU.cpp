#include "ALU.h"
uint8_t ALU:: bitewiseAND(uint8_t a, uint8_t b){
return a&b;
}
uint8_t ALU:: bitewiseOR(uint8_t a, uint8_t b){
return a|b;
}
 uint8_t ALU:: bitewiseXOR(uint8_t a, uint8_t b){
return a^b;
 }
uint8_t ALU:: addTwoComplement(uint8_t a, uint8_t b){
return a+b;
}
uint8_t ALU:: rotateRight(uint8_t value, int steps){
    if (steps ==0){
return value;
}
else{steps = steps%8;
        value =(value>>steps)|(value<<(8-steps));
return value;    }

}
uint8_t ALU:: addFloatingPoint(uint8_t a, uint8_t b){
uint8_t a_sign=  a >> 7;
uint8_t b_sign= b >> 7;
uint8_t a_Exponent=(a>>4)&0x07;
uint8_t b_Exponent=(b>>4)&0x07;
uint8_t a_Mantissa=a&0x0F;
uint8_t b_Mantissa=b&0x0F;
uint8_t diff;
int result;
int final_Exponent;
uint8_t final_sign;
if(a_Exponent>b_Exponent){
 diff=  a_Exponent  - b_Exponent  ;
 b_Mantissa=b_Mantissa>>diff;
 final_Exponent =a_Exponent;
}
else{diff= b_Exponent - a_Exponent ; 
a_Mantissa=a_Mantissa>>diff;
final_Exponent=b_Exponent;
}

if (a_sign==b_sign){
result = a_Mantissa + b_Mantissa;
final_sign=a_sign;
}
else{
if (a_Mantissa>b_Mantissa){
result = a_Mantissa - b_Mantissa;
final_sign=a_sign;
}
 else if(a_Mantissa<b_Mantissa){
result = b_Mantissa - a_Mantissa;
final_sign=b_sign;
}
else{
return 0x00;
}
}

if (result>=16){
result = result >>1;
final_Exponent=final_Exponent +1;

}

while(result<8){
result = result <<1;
final_Exponent=final_Exponent -1;

}
if (final_Exponent>7){final_Exponent=7;}
if (final_Exponent<0){return 0x00;}

uint8_t final_result= (final_sign << 7) | (final_Exponent << 4) | (result & 0x0F);

return final_result;
}

