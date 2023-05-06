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

//testes big_sum
//caso a variavel a seja 0, resultado deve ser b
//caso a variavel b seja 0, resultado deve ser a
//caso a variavel a e b sejam 0, resultado deve ser 0
//caso a variavel a e b sejam numeros diferentes de 0, resultado deve ser a + b
void testes_big_sum() {
    printf("\nTestando função big_sum:\n");
        
    BigInt a;
    BigInt b;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser b
    big_val(a, 0x0);
    big_val(b, 0x8FFFFFFFFFFFFFFF);
    
    big_sum(res, a, b);
    
    printf("\tTeste 1: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\x8f\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
    //caso a variavel b seja 0, resultado deve ser a
    big_val(a, 0x8FFFFFFFFFFFFFFF);
    big_val(b, 0x0);
    
    big_sum(res, a, b);
    
    printf("\tTeste 2: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\x8f\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
    
    //caso a variavel a e b sejam 0, resultado deve ser 0
    big_val(a, 0x0);
    big_val(b, 0x0);
    
    big_sum(res, a, b);

    printf("\tTeste 3: %s\n", memcmp(res, "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    //caso a variavel a e b sejam numeros diferentes de 0, resultado deve ser a + b
    big_val(a, 0x8FFFFFFFFFFFFFFF);
    big_val(b, 0x8FFFFFFFFFFFFFFF);

}

//testes big_sub
//caso a variavel a seja 0, resultado deve ser b
//caso a variavel b seja 0, resultado deve ser a
//caso a variavel a e b sejam 0, resultado deve ser 0
//caso a variavel a e b sejam numeros diferentes de 0, resultado deve ser a - b
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

//testes big_mul
//caso a variavel a seja 0, resultado deve ser 0
//caso a variavel b seja 0, resultado deve ser 0
//caso a variavel a e b sejam 0, resultado deve ser 0
//caso a variavel a e b sejam numeros diferentes de 0, resultado deve ser a * b
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

    // big_print(a);

    // big_shl_1(a);

    big_shl(res,a,0);
    // big_print(a);
    // // big_print(res);// 
    // big_print("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");
    

    printf("\tTeste 1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    big_val(a, 123456789);
    
    // Teste 2 (a!=0, n==0):
    
    big_shl(res, a, 0);

    // big_print(a);
    // big_print(res);
    // big_print("\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");
    
    printf("\tTeste 2: %s\n", memcmp(res, "\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    // Teste 3 (a!=0, n=>0):
    big_val(a, 0x0FFFFFFFFFFFFFFF);
    
    big_shl(res, a, 4);

    // big_print(a);
    // big_print(res);
    // big_print("\xf0\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00");

    printf("\tTeste 3: %s\n", memcmp(res, "\xf0\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
}

// testes big_shr: caso a variavel a seja 0, resultado deve ser 0
// caso a variavel n seja 0, resultado deve ser a
// caso a variavel n seja um numero diferente de 0 e a seja um numero diferente de 0, resultado deve ser a << n
void testes_big_shr() {
    printf("\nTestando função big_shr:\n");
        
    BigInt a;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser 0
    big_val(a, 0x0);
    
      // Teste 1 (a == 0, n>0):

    // big_print(a);

    // big_shr_1(a);

    big_shr(res,a,0);

    // big_print(a);
    // big_print(res);
    // big_print("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");
    

    printf("\tTeste 1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    big_val(a, 123456789);
    
    // Teste 2 (a!=0, n==0):
    
    big_shr(res, a, 0);

    // big_print(a);
    // big_print(res);
    // big_print("\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");
    //
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

// testes big_sar: caso a variavel a seja 0, resultado deve ser 0
// caso a variavel n seja 0, resultado deve ser a
// caso a variavel n seja um numero diferente de 0 e a seja um numero diferente de 0, resultado deve ser a << n
void testes_big_sar() {
    printf("\nTestando função big_sar:\n");
        
    BigInt a;
    BigInt res;
    
    //caso a variavel a seja 0, resultado deve ser 0
    big_val(a, 0x0);
    
      // Teste 1 (a == 0, n>0):

    // big_print(a);

    // big_shr_1(a);

    big_sar(res,a,0);

    // big_print(a);
    // big_print(res);
    // big_print("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");
    

    printf("\tTeste 1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
    big_val(a, 123456789);
    
    // Teste 2 (a!=0, n==0):
    
    big_sar(res, a, 0);

    // big_print(a);
    // big_print(res);
    // big_print("\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");
    
    printf("\tTeste 2: %s\n", memcmp(res, "\x15\xcd\x5b\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");

    // Teste 3 (a!=0, n=>0):
    big_val(a, 0x0FFFFFFFFFFFFFFF);
    
    big_sar(res, a, 4);

    // big_print(a);
    // big_print(res);
    // big_print("\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00");

    printf("\tTeste 3: %s\n", memcmp(res, "\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
      
    // Teste 4 (a==valor max, n=>0):
    big_val(a, 0xFFFFFFFFFFFFFFFF);
    
    big_sar(res, a, 4);

    // big_print(a);
    // big_print(res);
    // big_print("\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff");

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
