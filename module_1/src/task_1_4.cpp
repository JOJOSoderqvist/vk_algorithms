#include <iostream>
#include <cassert>

bool isBitNumberValid(int value, int bit_number){
    int a = 1;
    a <<= bit_number;
    return value >= a;
}

int invertBit(int value, int bit_number){
    if (value == 1)
        return 0;

    assert(isBitNumberValid(value, bit_number));
    int inverted_bit;
    inverted_bit = value >> bit_number;
    inverted_bit ^= 1;

    if (inverted_bit & 1){
        inverted_bit <<= bit_number;
        return value | inverted_bit;
    } else {
        inverted_bit <<= bit_number;
        inverted_bit |= 1;
        return inverted_bit & value;
    }
}
