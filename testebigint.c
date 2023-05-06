/* Ariel Mileguir 1811928 */
/* Thiago Henriques 2211171*/

#include "bigint.h"
#include <stdio.h>

/* big_val */
void testes_big_val() {
	printf("\nTestando função big_val:\n");
		
	BigInt res;
	 	
	  // Teste 1 (valor negativo):
    big_val(res, 0x8FFFFFFFFFFFFFFF);
    
    printf("\tTeste 1: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\x8f\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    // Teste 2 (valor positivo):
    big_val(res, 123456789);
    printf("\tTeste 2: %s\n", memcmp(res, "\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    // Teste 3 (valor == 0):
    big_val(res, 0);
    printf("\tTeste 3: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
}

/* big_comp_2 */
void testes_big_comp2() {
	printf("\nTestando função big_comp2:\n");
		
	BigInt a;
    BigInt res;
    
    /* extende 0x8FFFFFFFFFFFFFFF para 128 bits gerando o big_int a*/
    big_val(a, 0x8FFFFFFFFFFFFFFF);
    
	  // Teste 1 (valor negativo):
	  
    big_comp2(res, a);
    // 7000000000000001
    // 0700000000000001

    // big_print(a);
    // big_print(res);
    // big_print("\x01\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x00\x00\x00\x00\x00");
    

    printf("\tTeste 1: %s\n", memcmp(res, "\x01\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    big_val(a, 123456789);
    
    // Teste 2 (valor positivo):
    
    big_comp2(res, a);
    
    printf("\tTeste 2: %s\n", memcmp(res, "\xeb\x32\xa4\xf8\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
					
    big_val(a, 0);
		
    // Teste 3 (valor == 0):
    
    big_comp2(res, a);
    
    printf("\tTeste 3: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
}

/* big_sum */
void testes_big_sum() {
	printf("\nTestando função big_sum:\n");
	
	BigInt a;
	BigInt b;
	BigInt res;
		
	// Teste 1 (a e b são negativos e a soma não da overflow):
	
	//a   = FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
	//b   = FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
	//res = FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FE
	
	big_val(a, 0xFFFFFFFFFFFFFFFF);
	big_val(b, 0xFFFFFFFFFFFFFFFF);
	
	big_sum(res, a, b);
	
	printf("\tTeste 1:  %s\n", memcmp(res, "\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 2 (a e b são negativos e a soma da overflow):
	
	//a   = 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//b   = 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
	//res = FF FF FF FF FF FF FF FF 00 00 00 00 00 00 00 01
	
	
	big_val(a, 0x8000000000000000);
	big_val(b, 0x8000000000000001);
	
	big_sum(res, a, b);
	
	printf("\t\nTeste 2: %s\n", memcmp(res, "\x01\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 3 (a é 0):
	
	//a   = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//b   = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	//res = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	
	big_val(a, 0x7987654321fedcba);
	big_val(b, 0x0000000000000000);
	
	big_sum(res, a, b);
	
	printf("\tTeste 3: %s\n", memcmp(res, "\xba\xdc\xfe\x21\x43\x65\x87\x79\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 3.1 (b é 0):
	
	//a   = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	//b   = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//res = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	
	big_val(a, 0x803453efab456541);
	big_val(b, 0x0000000000000000);
	
	big_sum(res, a, b);
	
	printf("\tTeste 3.1: %s\n", memcmp(res, "\x41\x65\x45\xab\xef\x53\x34\x80\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 4 (a é negativo):
	
	//a   = FF FF FF FF FF FF FF FF 80 34 53 EF AB 45 65 41
	//b   = 00 00 00 00 00 00 00 00 70 34 53 EF AB 45 65 41
	//res = FF FF FF FF FF FF FF FF F0 68 A7 DF 56 8A CA 82
	
	big_val(a, 0x803453efab456541);
	big_val(b, 0x703453efab456541);
	
	big_sum(res, a, b);
	
	printf("\tTeste 4: %s\n", memcmp(res, "\x82\xca\x8a\x56\xdf\xa7\x68\xf0\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
		
	// Teste 4.1 (b é negativo):
	
	//a   = 03 34 53 EF AB 45 65 41 00 00 00 00 00 00 00 00
	//b   = FF FF FF FF FF FF FF FF 80 34 53 EF AB 45 65 41
	//res = 03 34 53 EF AB 45 65 40 80 34 53 EF AB 45 65 41
	

	big_val(a, 0x033453efab456541);
	big_val(b, 0x803453efab456541);
	
	printf("\nprintando a:\n");
	big_print(a);
	
	printf("\nprintando b:\n");
	big_print(b);
	
	printf("\nprintando res:\n");
	big_print(res);
	
	printf("\nprintando resultado esperado:\n");
	big_print("\x41\x65\x45\xab\xef\x53\x34\x80\x40\x65\x45\xab\xef\x53\x34\x03");
	
	big_sum(res, a, b);
	
	printf("\tTeste 4.1: %s\n", memcmp(res, "\x41\x65\x45\xab\xef\x53\x34\x80\x40\x65\x45\xab\xef\x53\x34\x03", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 5 (a e b são positivos e a soma não da overflow):
	
	//a   = 04 34 53 EF AB 45 65 41 00 00 00 00 00 00 00 00
	//b   = 03 34 53 EF AB 45 65 41 00 00 00 00 00 00 00 00
	//res = 07 68 A7 DF 56 8A CA 82 00 00 00 00 00 00 00 00
	
  a[15] = 0X04, b[15] = 0X03;
  a[14] = 0X34, b[14] = 0X34;
  a[13] = 0X53, b[13] = 0X53;
  a[12] = 0XEF, b[12] = 0XEF;
  a[11] = 0XAB, b[11] = 0XAB;
  a[10] = 0X45, b[10] = 0X45;
  a[9] = 0X65,  b[9] = 0X65;
  a[8] = 0X41,  b[8] = 0X41;
  a[7] = 0X00,  b[7] = 0X00;
  a[6] = 0X00,  b[6] = 0X00;
  a[5] = 0X00,  b[5] = 0X00;
  a[4] = 0X00,  b[4] = 0X00;
  a[3] = 0X00,  b[3] = 0X00;
  a[2] = 0X00,  b[2] = 0X00;
  a[1] = 0X00,  b[1] = 0X00;
  a[0] = 0X00,  b[0] = 0X00;

	big_sum(res, a, b);
	
	printf("\tTeste 5: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x82\xca\x8a\x56\xdf\xa7\x68\x07", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 5.1 (a e b são positivos e a soma da overflow):
		
	//a   = 04 34 53 EF AB 45 65 41 00 00 00 00 00 00 00 00
	//b   = 04 43 AC D9 AC 15 65 48 00 00 00 00 00 00 00 00
	//res = 08 78 00 C9 57 5A CA 89 00 00 00 00 00 00 00 00
	
  a[15] = 0X04, b[15] = 0X04;
  a[14] = 0X34, b[14] = 0X43;
  a[13] = 0X53, b[13] = 0XAC;
  a[12] = 0XEF, b[12] = 0XD9;
  a[11] = 0XAB, b[11] = 0XAC;
  a[10] = 0X45, b[10] = 0X15;
  a[9] = 0X65,  b[9] = 0X65;
  a[8] = 0X41,  b[8] = 0X48;
  a[7] = 0X00,  b[7] = 0X00;
  a[6] = 0X00,  b[6] = 0X00;
  a[5] = 0X00,  b[5] = 0X00;
  a[4] = 0X00,  b[4] = 0X00;
  a[3] = 0X00,  b[3] = 0X00;
  a[2] = 0X00,  b[2] = 0X00;
  a[1] = 0X00,  b[1] = 0X00;
  a[0] = 0X00,  b[0] = 0X00;

	big_sum(res, a, b);
	
	printf("\tTeste 5.1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x89\xca\x5a\x57\xc9\x00\x78\x08", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
  // Teste 6 (a (positivo) + b (negativo) = 0):
		
	//a   = 04 34 53 EF AB 45 65 41 00 00 00 00 00 00 00 00
	//b   = FB CB AC 10 54 BA 9A BF 00 00 00 00 00 00 00 00
	//res = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	
  a[15] = 0X04, b[15] = 0XFB;
  a[14] = 0X34, b[14] = 0XCB;
  a[13] = 0X53, b[13] = 0XAC;
  a[12] = 0XEF, b[12] = 0X10;
  a[11] = 0XAB, b[11] = 0X54;
  a[10] = 0X45, b[10] = 0XBA;
  a[9] = 0X65,  b[9] = 0X9A;
  a[8] = 0X41,  b[8] = 0XBF;
  a[7] = 0X00,  b[7] = 0X00;
  a[6] = 0X00,  b[6] = 0X00;
  a[5] = 0X00,  b[5] = 0X00;
  a[4] = 0X00,  b[4] = 0X00;
  a[3] = 0X00,  b[3] = 0X00;
  a[2] = 0X00,  b[2] = 0X00;
  a[1] = 0X00,  b[1] = 0X00;
  a[0] = 0X00,  b[0] = 0X00;

	big_sum(res, a, b);
	
	printf("\tTeste 6: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
  
  // Teste 6.1 (a (negativo) + b (positivo) = 0):
		
	//a   = FB CB AC 10 54 BA 9A BF 00 00 00 00 00 00 00 00
	//b   = 04 34 53 EF AB 45 65 41 00 00 00 00 00 00 00 00
	//res = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	
  b[15] = 0X04, a[15] = 0XFB;
  b[14] = 0X34, a[14] = 0XCB;
  b[13] = 0X53, a[13] = 0XAC;
  b[12] = 0XEF, a[12] = 0X10;
  b[11] = 0XAB, a[11] = 0X54;
  b[10] = 0X45, a[10] = 0XBA;
  b[9] = 0X65,  a[9] = 0X9A;
  b[8] = 0X41,  a[8] = 0XBF;
  b[7] = 0X00,  a[7] = 0X00;
  b[6] = 0X00,  a[6] = 0X00;
  b[5] = 0X00,  a[5] = 0X00;
  b[4] = 0X00,  a[4] = 0X00;
  b[3] = 0X00,  a[3] = 0X00;
  b[2] = 0X00,  a[2] = 0X00;
  b[1] = 0X00,  a[1] = 0X00;
  b[0] = 0X00,  a[0] = 0X00;

	big_sum(res, a, b);
	
	printf("\tTeste 6.1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
}

void testes_big_sub() {
    printf("\nTestando função big_sub:\n");
        
    BigInt a;
    BigInt b;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser b
    big_val(a, 0x0);
    big_val(b, 0x8FFFFFFFFFFFFFFF);
    
    big_sub(res, a, b);
    
    printf("\tTeste 1: %s\n", memcmp(res, "\x01\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
    //caso a variavel b seja 0, resultado deve ser a
    big_val(a, 0x8FFFFFFFFFFFFFFF);
    big_val(b, 0x0);
    
    big_sub(res, a, b);
    
    printf("\tTeste 2: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\x8f\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
    //caso a variavel a e b sejam 0, resultado deve ser 0
    big_val(a, 0x0);
    big_val(b, 0x0);

    big_sub(res, a, b);
    printf("\tTeste 3: %s\n", memcmp(res, "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    //caso a variavel a e b sejam numeros diferentes de 0, resultado deve ser a - b
    big_val(a, 0x8FFFFFFFFFFFFFFF);
    big_val(b, 0x8FFFFFFFFFFFFFFF);
    
    big_sub(res, a, b);

    printf("\tTeste 4: %s\n", memcmp(res, "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
}

void testes_big_mul() {
    printf("\nTestando função big_mul:\n");
        
    BigInt a;
    BigInt b;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser 0
    big_val(a, 0x0);
    big_val(b, 0x8FFFFFFFFFFFFFFF);

    big_mul(res, a, b);

    printf("\tTeste 1: %s\n", memcmp(res, "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
    //caso a variavel b seja 0, resultado deve ser 0
    big_val(a, 0x8FFFFFFFFFFFFFFF);
    big_val(b, 0x0);

    big_mul(res, a, b);

    printf("\tTeste 2: %s\n", memcmp(res, "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
    //caso a variavel a e b sejam 0, resultado deve ser 0
    big_val(a, 0x0);
    big_val(b, 0x0);

    big_mul(res, a, b);

    printf("\tTeste 3: %s\n", memcmp(res, "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    //caso a variavel a e b sejam numeros diferentes de 0, resultado deve ser a * b
    big_val(a, 0x8FFFFFFFFFFFFFFF);
    big_val(b, 0x8FFFFFFFFFFFFFFF);

    big_mul(res, a, b);

    printf("\tTeste 4: %s\n", memcmp(res, "\x01\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
}

// testes big_shl: caso a variavel a seja 0, resultado deve ser 0
// caso a variavel n seja 0, resultado deve ser a
// caso a variavel n seja um numero diferente de 0 e a seja um numero diferente de 0, resultado deve ser a << n
void testes_big_shl() {
    printf("\nTestando função big_shl:\n");
        
    BigInt a;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser 0
    big_val(a, 0x0);
    
      // Teste 1 (a == 0, n>0):

    big_shl(res,a,0);
    
    printf("\tTeste 1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    big_val(a, 123456789);
    
    // Teste 2 (a!=0, n==0):
    
    big_shl(res, a, 0);

 
    printf("\tTeste 2: %s\n", memcmp(res, "\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    // Teste 3 (a!=0, n=>0):
    big_val(a, 0x0FFFFFFFFFFFFFFF);
    
    big_shl(res, a, 4);
    
    printf("\tTeste 3: %s\n", memcmp(res, "\xf0\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
}

void testes_big_shr() {
    printf("\nTestando função big_shr:\n");
        
    BigInt a;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser 0
    big_val(a, 0x0);
    
     // Teste 1 (a == 0, n>0):


    big_shr(res,a,0);

    printf("\tTeste 1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    big_val(a, 123456789);
    
    // Teste 2 (a!=0, n==0):
    
    big_shr(res, a, 0);

    printf("\tTeste 2: %s\n", memcmp(res, "\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    // Teste 3 (a!=0, n=>0):
    big_val(a, 0x0FFFFFFFFFFFFFFF);
    
    big_shr(res, a, 4);
  
    printf("\tTeste 3: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
    // Teste 4 (a==valor max, n=>0):
    big_val(a, 0xFFFFFFFFFFFFFFFF);
    
    big_shr(res, a, 4);

    printf("\tTeste 4: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x0f", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
}

void testes_big_sar() {
    printf("\nTestando função big_sar:\n");
        
    BigInt a;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser 0
    big_val(a, 0x0);
    
      // Teste 1 (a == 0, n>0):

    big_sar(res,a,0);

    printf("\tTeste 1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    big_val(a, 123456789);
    
    // Teste 2 (a!=0, n==0):
    
    big_sar(res, a, 0);

    printf("\tTeste 2: %s\n", memcmp(res, "\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    // Teste 3 (a!=0, n=>0):
    big_val(a, 0x0FFFFFFFFFFFFFFF);
    
    big_sar(res, a, 4);

    printf("\tTeste 3: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
      
    // Teste 4 (a==valor max, n=>0):
    big_val(a, 0xFFFFFFFFFFFFFFFF);
    
    big_sar(res, a, 4);

    printf("\tTeste 4: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    

}


int main() {
    printf("Testes da biblioteca bigint:\n");
    
    testes_big_val();
    
    testes_big_comp2();
    
    testes_big_sum();
    
    testes_big_sub();

    testes_big_mul();

    testes_big_shl();

    testes_big_shr();

    testes_big_sar();
    
    return 0;
}
