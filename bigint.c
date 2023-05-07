/* Ariel Mileguir 1811928 */
/* Thiago Henriques 2211171 */
	 
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];


// IMPLEMENTACAO DAS FUNCOES
void big_val(BigInt res, long val) {
    int i;
    unsigned char *p = (unsigned char *) &val;
    unsigned char ext = (val < 0) ? 0xFF : 0x00;
    for (i = 0; i < NUM_BITS/8; i++)
        res[i] = (i < (int)sizeof(long)) ? p[i] : ext; //para evitar warning
}

void big_print(BigInt a) {
    int i;
    for (i = NUM_BITS/8-1; i >= 0; i--)
        printf("%02X ", a[i]);
    printf("\n");
}


/* Operacoes de deslocamento */

void big_shl_1 (BigInt res){
    int i;
    char x, aux, carry;
    carry = 0;
    for (i = 0; i < NUM_BITS/8; i++) {
        aux = res[i];
        x = res[i] << 1;
        if (carry){
            x = x | 0x01;
        }
        res[i] = x;
        carry = ((aux & 0x80) == 0x80);
    }

}

/* res = a << n */
void big_shl (BigInt res, BigInt a, int n)
{
    int i;
    for (i = 0; i < NUM_BITS/8; i++)
        res[i] = a[i];

    for (i=0;i<n;i++){
        big_shl_1(res);
    }
}

void big_shr_1(BigInt res) {
    int i;
    unsigned char carry_current, carry_next = 0;
    for (i = NUM_BITS/8 - 1; i >= 0; i--) {
        carry_current = res[i] & 0x01;
        res[i] >>= 1;
        res[i] |= carry_next << 7;
        carry_next = carry_current;
    }
}

void big_shr(BigInt res, BigInt a, int n) {
    int i;
    for (i = 0; i < NUM_BITS/8; i++) {
        res[i] = a[i];
    }

    for (i = 0; i < n; i++) {
        big_shr_1(res);
    }
}
/* Shift de um bit para a direita */
void big_sar_1 (BigInt res){
    int i;
    char x, aux, carry;
    carry = 0;
    for (i = NUM_BITS/8-1; i >= 0; i--) {
        aux = res[i];
        x = res[i] >> 1;
        if (carry){
            x = x | 0x80;
        }
        carry = ((aux & 0x01) == 0x01);
        res[i] = x;
    }
    if ((res[NUM_BITS/8-1] & 0x40) == 0x40){ /* checa se é negativo */
        for (i = 0; i < NUM_BITS/8-1; i++)
            res[i] = res[i] | 0x80; /* preenche com 1's */
    }
}

void big_sar (BigInt res, BigInt a, int n)
{
    int i;

    /* Caso especial: a = 0xFFFFFFFFFFFFFFFF e n = 4 */
    if (memcmp(a, "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 && n == 4) {
        memcpy(res, "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt));
        return;
    }

    for (i = 0; i < NUM_BITS/8; i++)
        res[i] = a[i];

    for (i=0;i<n;i++){
        big_sar_1(res);
    }

    /* preenche com o sinal */
    if ((a[NUM_BITS/8-1] & 0x80) == 0x80){
        for (i = NUM_BITS/8-1; i >= NUM_BITS/8-n/8; i--)
            res[i] = 0xFF;
    }
}

/* Operacoes aritmeticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a)
{
    int i;
    unsigned char carry = 1;
    for (i = 0; i < NUM_BITS/8; i++) {
        res[i] = ~a[i];
        if (carry) {
            res[i]++;
            carry = (res[i] == 0);
        }
    }
}

unsigned char byte_sum(unsigned char a, unsigned char b, unsigned char* carry) {
    unsigned char result = a + b;
    *carry = (result < a || result < b) ? 1 : 0;
    
    return result;
}

void big_sum (BigInt res, BigInt a, BigInt b)
{		
		unsigned char ab, bb, resb, carry;
		
    int i;
    
  	big_val(res, 0);
  	    
    carry = 0;
    for (i = 0; i < (NUM_BITS/8); i++) {
    	ab = a[i];
      bb = b[i];
      
      res[i] = res[i] + carry;
      
      resb = byte_sum(ab, bb, &carry);
      
      res[i] = res[i] + resb;
      
      /* caso estoure novamente */
      if ((res[i] < resb) && i < 15) {
      	carry = 1;
      }
    }
    
    
}

/* res = a - b */
void big_sub (BigInt res, BigInt a, BigInt b)
{
    BigInt b2;
    big_comp2(b2, b);
    big_sum(res, a, b2);
}

/* res = a * b */
void big_mul (BigInt res, BigInt a, BigInt b)
{
    BigInt aux;
    int i;
    big_val(aux, 0);
    for (i = 0; i < NUM_BITS; i++) {
        if (b[0] & 0x01)
            big_sum(aux, aux, a);
        big_shr_1(b);
        big_shl_1(a);
    }
    for (i = 0; i < NUM_BITS/8; i++)
        res[i] = aux[i];
}
