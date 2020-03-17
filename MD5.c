//Coded by Michael Coleman
//RFC Document used in implementation - https://tools.ietf.org/html/rfc1321

#include<stdio.h>
#include <inttypes.h>

//F,G,H,I functions, RFC Document  - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define F(x, y, z)((x & y) | (~x & z)) 
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

//ROTATE_LEFT function, RFC Document - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32-n)))

//FF,GG,HH,II , RFC Document - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define FF(a,b,c,d,x,s,ac) { a += F(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;}
#define GG(a,b,c,d,x,s,ac) { a += G(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;}
#define HH(a,b,c,d,x,s,ac) { a += H(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;} 
#define II(a,b,c,d,x,s,ac) { a += I(b,c,d) + x + ac; a = b + ROTLEFT(a,s); a += b;} 

// Section 2 of RTF Document
#define WORD uint32_t

// Constants used transform rounds 1-4, pages 12-13 of RTF Document
const WORD K[] = {
  0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
  0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
  0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
  0x6b901122,0xfd987193,0xa679438e,0x49b40821,
  0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
  0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
  0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
  0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
  0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
  0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
  0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
  0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
  0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
  0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
  0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
  0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

// Constants for MD5Transform routine,page 9 of RTF Document
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// MD5 context.
typedef struct {
  uint32_t  state[4]; //state (ABCD)
  uint32_t  count[2]; //number of bits, modulo 2^64 (lsb first) 
  unsigned char buffer[64]; //input buffer
} MD5_CTX;

void md5_transform(MD5_CTX *context, char buffer[]) 
{  
   int a,b,c,d;
   int message[16];
   
   // MD5 specifies big endian byte order, but this implementation assumes a little 
   // endian byte order CPU. Reverse all the bytes upon input, and re-reverse them 
   // on output (in md5_final()). 
   int i,j;
   for (i=0, j=0; i < 16; ++i, j += 4) {
     message[i] = (buffer[j]) + (buffer[j+1] << 8) + (buffer[j+2] << 16) + (buffer[j+3] << 24); 
   }
   
   //set initial values for states
   a = context->state[0]; 
   b = context->state[1]; 
   c = context->state[2]; 
   d = context->state[3]; 
   
   FF(a,b,c,d,message[0], S11,K[0]); 
   FF(d,a,b,c,message[1], S12,K[1]); 
   FF(c,d,a,b,message[2], S13,K[2]); 
   FF(b,c,d,a,message[3], S14,K[3]); 
   FF(a,b,c,d,message[4], S11,K[4]); 
   FF(d,a,b,c,message[5], S12,K[5]); 
   FF(c,d,a,b,message[6], S13,K[6]); 
   FF(b,c,d,a,message[7], S14,K[7]); 
   FF(a,b,c,d,message[8], S11,K[8]); 
   FF(d,a,b,c,message[9], S12,K[9]); 
   FF(c,d,a,b,message[10],S13,K[10]); 
   FF(b,c,d,a,message[11],S14,K[11]); 
   FF(a,b,c,d,message[12],S11,K[12]);
   FF(d,a,b,c,message[13],S12,K[13]); 
   FF(c,d,a,b,message[14],S13,K[14]); 
   FF(b,c,d,a,message[15],S14,K[15]); 
   
   GG(a,b,c,d,message[1], S21,K[16]); 
   GG(d,a,b,c,message[6], S22,K[17]); 
   GG(c,d,a,b,message[11],S23,K[18]); 
   GG(b,c,d,a,message[0], S24,K[19]);
   GG(a,b,c,d,message[5], S21,K[20]); 
   GG(d,a,b,c,message[10],S22,K[21]); 
   GG(c,d,a,b,message[15],S23,K[22]); 
   GG(b,c,d,a,message[4], S24,K[23]);
   GG(a,b,c,d,message[9], S21,K[24]); 
   GG(d,a,b,c,message[14],S22,K[25]); 
   GG(c,d,a,b,message[3], S23,K[26]); 
   GG(b,c,d,a,message[8], S24,K[27]);
   GG(a,b,c,d,message[13],S21,K[28]); 
   GG(d,a,b,c,message[2], S22,K[29]); 
   GG(c,d,a,b,message[7], S23,K[30]); 
   GG(b,c,d,a,message[12],S24,K[31]);
   
   HH(a,b,c,d,message[5], S31,K[32]); 
   HH(d,a,b,c,message[8], S32,K[33]); 
   HH(c,d,a,b,message[11],S33,K[34]); 
   HH(b,c,d,a,message[14],S34,K[35]); 
   HH(a,b,c,d,message[1], S31,K[36]); 
   HH(d,a,b,c,message[4], S32,K[37]); 
   HH(c,d,a,b,message[7], S33,K[38]); 
   HH(b,c,d,a,message[10],S34,K[39]); 
   HH(a,b,c,d,message[13],S31,K[40]); 
   HH(d,a,b,c,message[0], S32,K[41]); 
   HH(c,d,a,b,message[3], S33,K[42]); 
   HH(b,c,d,a,message[6], S34,K[43]); 
   HH(a,b,c,d,message[9], S31,K[44]); 
   HH(d,a,b,c,message[12],S32,K[45]); 
   HH(c,d,a,b,message[15],S33,K[46]); 
   HH(b,c,d,a,message[2], S34,K[47]); 
      
   II(a,b,c,d,message[0], S41,K[48]); 
   II(d,a,b,c,message[7], S42,K[49]); 
   II(c,d,a,b,message[14],S43,K[50]); 
   II(b,c,d,a,message[5], S44,K[51]); 
   II(a,b,c,d,message[12],S41,K[52]); 
   II(d,a,b,c,message[3], S42,K[53]); 
   II(c,d,a,b,message[10],S43,K[54]); 
   II(b,c,d,a,message[1], S44,K[55]); 
   II(a,b,c,d,message[8], S41,K[56]); 
   II(d,a,b,c,message[15],S42,K[57]); 
   II(c,d,a,b,message[6], S43,K[58]); 
   II(b,c,d,a,message[13],S44,K[59]); 
   II(a,b,c,d,message[4], S41,K[60]); 
   II(d,a,b,c,message[11],S42,K[61]); 
   II(c,d,a,b,message[2], S43,K[62]); 
   II(b,c,d,a,message[9], S44,K[63]); 
   
   // add the hash value onto each state
   context->state[0] += a; 
   context->state[1] += b; 
   context->state[2] += c; 
   context->state[3] += d; 
}  







int main(int argc, char *argv[]) {

}