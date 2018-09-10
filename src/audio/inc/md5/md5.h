

#ifndef _MD5_H
#define _MD5_H
#include <string.h>

#ifndef _BYTE
#define _BYTE
#define BYTE unsigned char
#endif
typedef struct {
  unsigned int state[4];                                   /* state (ABCD) */
  unsigned int count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

void MD5_Init(MD5_CTX *context) ;
int MD5_enc(BYTE id, BYTE *pwd, BYTE pwdlen, BYTE *hash);
void MD5_Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen);
void MD5_Final (unsigned char* digest, MD5_CTX *context);

#endif


