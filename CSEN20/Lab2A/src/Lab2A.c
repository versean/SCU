// Sean Cajigal 2026-09-30 Implementation of binary functions stuff

#include <stdint.h>

uint32_t Bits2Unsigned(int8_t bits[8])
{
    // To be implemented by student
    // Input: bits[0] = Least significant bit
    // bits[7] = Most significant bit
    // Output: 0 <= return value < 255
    uint32_t value = 0;
    int bit ;

    //Implementation
    for (bit = 7; bit >= 0; bit--) {
        value = 2 * value + bits[bit];
    }
    return value ;
}
int32_t Bits2Signed(int8_t bits[8])
{
    // To be implemented by student
    // Input: bits[0] = Least significant bit
    // bits[7] = Most significant bit
    // Output: -128 <= return value <= +127
    int32_t value ;

    //Implementation
    value = Bits2Unsigned(bits);
    if (bits[7] == 1) {
        value -= 256;
    }
    return value ;
}
void Increment(int8_t bits[8])
{
    // To be implemented by student
    // Adds 1 to the number represented by bits
    // Where: bits[0] = Least significant bit
    // bits[7] = Most significant bit
    int32_t bit, carry, sum ;
    carry = 1 ;

    //Implementation
    for (bit = 0; bits[bit] > 0; bit++) {
        bits[bit] = 0;
    }
    bits[bit] = 1;
    // 01101011
    // 01101100
}
void Unsigned2Bits(uint32_t n, int8_t bits[8])
{
    // To be implemented by student
    // Input: 0 <= n <= 255
    // Output: Converts n to an array of bits
    // Where: bits[0] = Least significant bit
    // bits[7] = Most significant bit
    int32_t bit ;

    //Implementation
    for (int i = 0; i < 8; i++) {
        bits[i] = n % 2;
        n/=2;
    }
}
