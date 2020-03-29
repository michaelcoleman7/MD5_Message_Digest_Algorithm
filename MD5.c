//Coded by Michael Coleman
//RFC Document used in implementation - https://tools.ietf.org/html/rfc1321

#include<stdio.h>

//F,G,H,I functions, RFC Document  - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z))) 

//ROTATE_LEFT function, RFC Document - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32-n)))

//FF,GG,HH,II , RFC Document - APPENDIX A - Reference Implementation - section: A.3 md5c.c
#define FF(a, b, c, d, x, s, ac) \
  {(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) \
  {(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) \
  {(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) \
  {(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }

// UINT4 defines a four byte word
typedef unsigned long int UINT4;

// Constants used transform rounds 1-4, pages 12-13 of RTF Document
const UINT4 K[] = {
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

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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
  UINT4  state[4]; //state (ABCD)
  UINT4  count[2]; //number of bits, modulo 2^64
  unsigned char buffer[64]; //input buffer
  unsigned char finalDigest[16]; // final digest value after MD5Final has been called
} MD5_CTX;

//MD5 initialization method, Begins an MD5 operation, writing a new context
void MD5Init(MD5_CTX *context) 
{  
  //initials counts to zero
  context->count[0] = context->count[1] = 0;
  // Load magic initialization constants to set state values
  context->state[0] = 0x67452301; 
  context->state[1] = 0xEFCDAB89; 
  context->state[2] = 0x98BADCFE; 
  context->state[3] = 0x10325476; 
}  

// MD5 basic transformation. Transforms state based on block.
static void MD5Transform (UINT4 *state, UINT4 *message)
{
  UINT4 a,b,c,d;
  a = state[0];
  b = state[1];
  c = state[2];
  d = state[3];

  // RFC document pages 13 and 14 for round values - 4 rounds
  //round 1 - FF Function
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
  
  //round 2 - GG Function
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
  
  //round 3 - HH Function
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
    
  //round 4 - II Function
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

  //update states after rounds
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
}

//MD5 block update operation. Continues an MD5 message-digest operation, processing another message block, and updating the context, Note: input and input length both refer to same input block
void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
  UINT4 block[16];
  unsigned int i, j, index;

  // compute the number of bytes mod 64
  index = ((context->count[0] >> 3) & 0x3F);

  // update the number of bits
  if ((context->count[0] + ((UINT4)inputLen << 3)) < context->count[0])
    context->count[1]++;
  context->count[0] += ((UINT4)inputLen << 3);
  context->count[1] += ((UINT4)inputLen >> 29);

  //decrement though length until 0
  while (inputLen--) {
    // add new character to buffer, increment the index
    context->buffer[index++] = *input++;
    // Transform as many times as possible.
    if (index == 64) {
      for (i = 0, j = 0; i < 16; i++, j += 4)
        block[i] = (context->buffer[j]) | ((context->buffer[j+1]) << 8) | ((context->buffer[j+2]) << 16) | ((context->buffer[j+3]) << 24);
      MD5Transform (context->state, block);
      index = 0;
    }
  }
}

//MD5 finalization. calculates final digest and ends an MD5 message-digest operation
void MD5Final (MD5_CTX *context)
{
  UINT4 block[16];
  unsigned int i, j, index, padLen;

  // save the number of bits to blocks last 2 bits
  block[14] = context->count[0];
  block[15] = context->count[1];

  // pad out to 56 mod 64
  index = ((context->count[0] >> 3) & 0x3F);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD5Update (context, PADDING, padLen);

  // append length in bits and transform (run to 14 as last 2 blocks already filled)
  for (i = 0, j = 0; i < 14; i++, j += 4) 
    block[i] = (context->buffer[j]) | ((context->buffer[j+1]) << 8)  | ((context->buffer[j+2]) << 16) | ((context->buffer[j+3]) << 24);
  MD5Transform (context->state, block);

  // update final digest value digest
  for (i = 0, j = 0; i < 4; i++, j += 4) {
    context->finalDigest[j] = (context->state[i] & 0xFF);
    context->finalDigest[j+1] =((context->state[i] >> 8) & 0xFF);
    context->finalDigest[j+2] =((context->state[i] >> 16) & 0xFF);
    context->finalDigest[j+3] =((context->state[i] >> 24) & 0xFF);
  }
}

int main() {
  MD5_CTX context;
  char testString[50] = "abc";
  unsigned int len = strlen (testString);
  int i;

  MD5Init (&context);
  MD5Update (&context, testString, len);
  MD5Final (&context);
  printf ("(\"%s\") = ", testString);
    for (i = 0; i < 16; i++)
    printf ("%02x", context.finalDigest[i]);
  printf ("\n\n");
}