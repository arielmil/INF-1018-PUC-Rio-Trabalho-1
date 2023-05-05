/* Ariel Mileguir 1811928 */
/* Thiago Henriques 2211171*/

//Descrição do trabalho 
/*

INF1018 - Software Básico (2023.1)
Primeiro Trabalho
Inteiros Grandes
O objetivo do trabalho é implementar, na linguagem C, uma biblioteca que permita representar valores inteiros signed de 128 bits, e ofereça algumas operações aritméticas básicas sobre esses valores (soma, subtração, multiplicação, negação) e operações de deslocamento de bits.

Instruções Gerais
Leia com atenção o enunciado do trabalho e as instruções para a entrega. Em caso de dúvidas, não invente. Pergunte!
O trabalho deve ser entregue até as 23h59m do dia 05/05.
Trabalhos entregues após o prazo perderão um ponto por dia de atraso.
Trabalhos que não compilem (i.e., que não produzam um executável) não serão considerados, ou seja, receberão grau zero.
Os trabalhos podem ser feitos em grupos de no máximo dois alunos.
Alguns grupos poderão ser chamados para apresentações orais / demonstrações dos trabalhos entregues.

Representação para Inteiros Grandes
Para representar um valor inteiro de 128 bits, a biblioteca deverá usar a seguinte definição:

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];
Ou seja, um valor do tipo BigInt deve ser representado por um array de bytes, interpretado como um único inteiro de 128 bits, em complemento a 2 e seguindo a ordenação little-endian.
Por exemplo, o array

{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
representa o valor inteiro 1.
O array a seguir

{0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
representa o inteiro 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE, que corresponde ao valor -2 em complemento a 2.

Operações da Biblioteca
A implementação das funções disponibilizadas pela biblioteca deve obedecer os protótipos fornecidos abaixo:
/* Atribuição (com extensão) 
void big_val (BigInt res, long val);

/* Operações Aritméticas 

/* res = -a 
void big_comp2(BigInt res, BigInt a);

/* res = a + b 
void big_sum(BigInt res, BigInt a, BigInt b);

/* res = a - b 
void big_sub(BigInt res, BigInt a, BigInt b);

/* res = a * b 
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operações de Deslocamento */

/* res = a << n 
void big_shl(BigInt res, BigInt a, int n);

/* res = a >> n (lógico)
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmético)
void big_sar(BigInt res, BigInt a, int n);
A função big_val atribui a res o valor fornecido por l (um signed long), corretamente estendido para 128 bits.
A função big_comp2 atribui a res o valor "negado" (complemento a 2) de a.
As funções big_sum, big_sub e big_mul realizam, respectivamente, as operações de soma, subtração e multiplicação de dois inteiros de 128 bits (a e b), armazenando o resultado em res.
A função big_shl realiza um deslocamento para a esquerda (shift left) de um inteiro de 128 bits (a), armazenando em res o resultado da operação. Sua implementação pode assumir que o valor de n é um inteiro no intervalo [0,127].
A função big_shr realiza um deslocamento lógico para a direita (shift right) de um inteiro de 128 bits (a), armazenando em res o resultado da operação. Sua implementação pode assumir que o valor de n é um inteiro no intervalo [0,127].
Implementação e Execução

Você deve criar um arquivo fonte chamado bigint.c, contendo a implementação das funções descritas acima e funções auxiliares, se for o caso. Esse arquivo não deve conter uma função main!
O arquivo bigint.c deverá incluir o arquivo de cabeçalho bigint.h, fornecido aqui. Você não deve alterar este arquivo. Caso necessite de definições auxiliares, faça-as dentro de seu arquivo fonte bigint.c.

Para testar seu programa, use técnica de TDD (Test Driven Design), na qual testes são escritos antes do código. O propósito é garantir ao desenvolvedor (você) ter um bom entendimento dos requisitos do trabalho antes de implementar o programa. Com isto a automação de testes é praticada desde o início do desenvolvimento, permitindo a elaboração e execução contínua de testes de regressão. Desta forma fortalecemos a criação de um código que nasce simples, testável e próximo aos requisitos do trabalho. Os passos gerais para seguir tal técnica:

Escrever/codificar um novo teste
Executar todos os testes criados até o momento para ver se algum falha
Escrever o código responsável por passar no novo teste inserido
Executar todos os testes criados até o momento e atestar execução com sucesso
Refatorar código testado
Para este trabalho, crie um outro arquivo, testebigint.c, contendo uma função main. Este arquivo também deverá incluir o arquivo de cabeçalho bigint.h, além de outras possíveis função para realização dos vários testes que julgar necessário.

Crie seu programa executável testebigint) com a linha:

gcc -Wall -o testebigint bigint.c testebigint.c
Importante! Se, por acaso, você não implementar alguma função, crie uma função dummy para que o programa de teste acima além do usado para a correção do trabalho possa ser gerado sem problemas.

Essa função deverá ter o nome da função não implementada e o corpo

 { return; } 
Esta técnica é denominada de mocking que consiste em criar funções apenas para teste quando as reais ainda não se encontram implementadas. Isto é também prático para o trabalho incremental em equipe, pois permite tornar indepentende o trabalho de cada membro.
Lembre-se que deve haver uma preocupação constante em subtituir as funções dummy ou Mocks pelos códigos corretos quando estes estiverem testados e disponibilizados.
Dicas
Implemente seu trabalho por partes, gerando o teste para cada parte implementada antes de prosseguir.
Por exemplo, você pode implementar primeiro a operação de atribuição, e para testá-la usar alguma função auxiliar que realize um dump do array usado para armazenar o inteiro de 128 bits. Em seguida, vá implementando o teste e correspondente função, um a um, passando para o próximo quando estiver funcionando.

Repare que algumas funções podem ser usadas pela implementação de outras (por exemplo, a operação de subtração pode usar soma e complemento a 2!)
Não se esqueça de ter planejado um roteiro robusto de testes antes de entregar seu trabalho! Para cada operação implementada, pense nos diferentes casos relevantes (números positivos, negativos, muito grandes, zero, etc...).
Algumas operações possuem uma implementação evidente, enquanto outras requerem um pouco mais de investigação. Por exemplo, a multiplicação pode usar somas sucessivas, mas esta seria uma implementação ineficiente e inviável...

Entrega
Devem ser entregues via Moodle três arquivos:

o arquivo fonte bigint.c
Coloque no início do arquivo fonte, como comentário, os nomes dos integrantes do grupo, da seguinte forma:

  /* Nome_do_Aluno1 Matricula Turma */
  /* Nome_do_Aluno2 Matricula Turma 
Lembre-se que este arquivo não deve conter a função main!
o arquivo fonte testebigint.c que deverá conter a função main e demais possíveis funções auciliares que você usou para testar seu trabalho.
Coloque no início do arquivo fonte, como comentário, os nomes dos integrantes do grupo, da seguinte forma:

  /* Nome_do_Aluno1 Matricula Turma */
  /* Nome_do_Aluno2 Matricula Turma 
um arquivo texto, chamado relatorio.txt, relatando o que está funcionando e, eventualmente, o que não está funcionando. Explique sua estratégia geral de teste, como organizou seu roteiro e consequentemente seu arquivo de teste.

Você não deve explicar a sua implementação neste relatório. Seu programa deve ser suficientemente claro e bem comentado.

Coloque também no relatório o nome dos integrantes do grupo.

Coloque na área de texto da tarefa do Moodle os nomes e turmas dos integrantes do grupo.
Para grupos de alunos da mesma turma, apenas uma entrega é necessária (usando o login de um dos integrantes do grupo).

Se o grupo for composto por alunos de turmas diferentes, os dois alunos deverão realizar a entrega, e avisar aos professores!

*/

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "bigint.h"

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
    
    printf("\tTeste 1: %s\n", memcmp(res, "\x01\x00\x00\x00\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
        
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
	//res = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
	
	big_val(a, 0x8000000000000000);
	big_val(b, 0x8000000000000001);
	
	big_sum(res, a, b);
	
	printf("\tTeste 2: %s\n", memcmp(res, "\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
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
}

/* big_sub */
void testes_big_sub() {
	printf("\nTestando função big_sub:\n");
	
	BigInt a;
	BigInt b;
	BigInt res;
		
	// Teste 1 (a e b são negativos (b tem o sinal invertido)):
	
	//a   = FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
	//b   = FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
	//res = FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FE
	
	big_val(a, 0xFFFFFFFFFFFFFFFF);
	big_val(b, 0xFFFFFFFFFFFFFFFF);
	
	big_sub(res, a, b);
	
	/*
	
	OBS: Acredito que esse teste seja desnecessário pois B ∈ [0, BIG_INT_MAX], e A ∈ [BIG_INT_MIN, -1], então A + B ∈ [BIG_INT_MIN, BIG_INT_MAX] (Pois A - B = B - A (já que B é negativo tem o sinal trocado) ).
			 Ou seja, nunca resultaria em um número que não pode ser representado com um BigInt.
			 
	printf("\tTeste 1:  %s\n", memcmp(res, "\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 2 (a e b são negativos e a subtração da overflow):
	
	//a   = 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//b   = 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
	//res = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
	
	big_val(a, 0x8000000000000000);
	big_val(b, 0x8000000000000001);
	
	big_sub(res, a, b);
	

	printf("\tTeste 2: %s\n", memcmp(res, "\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	*/
	
	// Teste 3 (a é 0):
	
	//a   = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//b   = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	//res = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	
	big_val(a, 0x7987654321fedcba);
	big_val(b, 0x0000000000000000);
	
	big_sub(res, a, b);
	
	printf("\tTeste 3: %s\n", memcmp(res, "\xba\xdc\xfe\x21\x43\x65\x87\x79\x00\x00\x00\x00\x00\x00\x00\x00", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 3.1 (b é 0):
	
	//a   = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	//b   = 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//res = 00 00 00 00 00 00 00 00 79 87 65 43 21 FE DC BA
	
	big_val(a, 0x803453efab456541);
	big_val(b, 0x0000000000000000);
	
	big_sub(res, a, b);
	
	printf("\tTeste 3.1: %s\n", memcmp(res, "\x41\x65\x45\xab\xef\x53\x34\x80\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 4 (a é negativo e a subtração da overflow):
	
	//a   = FF FF FF FF FF FF FF FF 80 34 53 EF AB 45 65 41
	//b   = 00 00 00 00 00 00 00 00 70 34 53 EF AB 45 65 41
	//res = FF FF FF FF FF FF FF FF F0 68 A7 DF 56 8A CA 82
	
	big_val(a, 0x803453efab456541);
	big_val(b, 0x703453efab456541);
	
	big_sub(res, a, b);
	
	printf("\tTeste 4: %s\n", memcmp(res, "\x82\xca\x8a\x56\xdf\xa7\x68\xf0\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 4.1 (b é negativo e a subtração da overflow):
	
	//a   = FF FF FF FF FF FF FF FF 80 34 53 EF AB 45 65 41
	//b   = 00 00 00 00 00 00 00 00 70 34 53 EF AB 45 65 41
	//res = FF FF FF FF FF FF FF FF F0 68 A7 DF 56 8A CA 82
	
	big_val(a, 0x803453efab456541);
	big_val(b, 0x703453efab456541);
	
	big_sub(res, a, b);
	
	printf("\tTeste 4.1: %s\n", memcmp(res, "\x82\xca\x8a\x56\xdf\xa7\x68\xf0\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 4.2 (a é negativo e a subtração não da overflow):
	
	//a   = 03 34 53 EF AB 45 65 41 00 00 00 00 00 00 00 00
	//b   = FF FF FF FF FF FF FF FF 80 34 53 EF AB 45 65 41
	//res = 03 34 53 EF AB 45 65 40 80 34 53 EF AB 45 65 41
	

	big_val(a, 0x033453efab456541);
	big_val(b, 0x803453efab456541);
	
	big_sub(res, a, b);
	
	printf("\tTeste 4.2: %s\n", memcmp(res, "\x41\x65\x45\xab\xef\x53\x34\x80\x40\x65\x45\xab\xef\x53\x34\x03", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 4.3 (b é negativo e a subtração não da overflow):
	
	//a   = FF FF FF FF FF FF FF FF 80 34 53 EF AB 45 65 41
	//b   = 00 00 00 00 00 00 00 00 70 34 53 EF AB 45 65 41
	//res = FF FF FF FF FF FF FF FF F0 68 A7 DF 56 8A CA 82
	
	big_val(a, 0x803453efab456541);
	big_val(b, 0x703453efab456541);
	
	big_sub(res, a, b);
	
	printf("\tTeste 4.3: %s\n", memcmp(res, "\x82\xca\x8a\x56\xdf\xa7\x68\xf0\xff\xff\xff\xff\xff\xff\xff\xff", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	// Teste 5 (a e b são positivos):
	
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

	big_sub(res, a, b);
	
	printf("\tTeste 5: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x82\xca\x8a\x56\xdf\xa7\x68\x07", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	/* OBS: Acredito que esse teste também seja desnecessário pelo mesmo motivo do teste 2.
	
	// Teste 5.1 (a e b são positivos e a subtração da overflow):
		
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

	big_sub(res, a, b);
	
	printf("\tTeste 5.1: %s\n", memcmp(res, "\x00\x00\x00\x00\x00\x00\x00\x00\x89\xca\x5a\x57\xc9\x00\x78\x08", sizeof(BigInt)) == 0 ? "sucesso" : "falha");
	
	*/
	
}

/* big_mul */
void testes_big_mul() {
	printf("\nTestando função big_mul:\n");
	
	BigInt a;
	BigInt b;
	BigInt res;
	
	// Teste 1 (a e b são negativos e a soma não da overflow):
	
	// Teste 2 (a e b são negativos e a soma daria overflow):

	// Teste 3 (a é 0):
	
	// Teste 3.1 (b é 0):
	
	// Teste 4 (a é negativo e a multiplicação não da overflow):
	
	// Teste 4.1 (b é negativo e a multiplicação não da overflow):
	
	// Teste 5 (a é negativo e a multiplicação daria overflow):
	
	// Teste 5.1 (b é negativo e a multiplicação daria overflow):
	
	// Teste 6 (a e b são positivos e a multiplicação não da overflow):
	
	// Teste 7 (a e b são positivos e a multiplicação daria overflow):
}

int main() {
    
    testes_big_val();
    
    testes_big_comp2();
    
    testes_big_sum();
    
    testes_big_sub();
    
    return 0;
}


