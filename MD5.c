#include<stdio.h>
#include <inttypes.h>

//F,G,H,I functions - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define F(x, y, z)((x & y) | (~x & z)) 
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

//ROTATE_LEFT function - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32-n)))

//FF,GG,HH,II - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define FF(a,b,c,d,x,s,ac) { a += F(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;}
#define GG(a,b,c,d,x,s,ac) { a += G(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;}
#define HH(a,b,c,d,x,s,ac) { a += H(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;} 
#define II(a,b,c,d,x,s,ac) { a += I(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;} 

/* MD5 context. */
typedef struct {
  uint32_t  state[4];//state (ABCD)
  uint32_t  count[2];//number of bits, modulo 2^64 (lsb first) 
  unsigned char buffer[64];//input buffer
} MD5_CTX;

// Section 2
#define WORD uint32_t

int main(int argc, char *argv[]) {

}