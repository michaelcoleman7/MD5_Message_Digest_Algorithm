#include<stdio.h>

#define F(x, y, z)((x & y) | (~x & z)) 
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32-n)))

// Section 2
#define WORD uint32_t

int main(int argc, char *argv[]) {

}