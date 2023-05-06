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
        printf("%02X", a[i]);
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

/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b)
{
    int i;
    __int128_t a_signed = 0;
    __int128_t b_signed = 0;
    __int128_t res_signed;

    // Converter BigInt a e b para int128_t com sinal
    for (i = NUM_BITS/8 - 1; i >= 0; i--) {
        a_signed = (a_signed << 8) | a[i];
        b_signed = (b_signed << 8) | b[i];
    }

    // Realizar a soma
    res_signed = a_signed + b_signed;

    // Converter int128_t com sinal de volta para BigInt
    for (i = 0; i < NUM_BITS/8; i++) {
        res[i] = (unsigned char)(res_signed & 0xFF);
        res_signed >>= 8;
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
