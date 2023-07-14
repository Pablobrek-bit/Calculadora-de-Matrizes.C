/*
# Copyright (c) 2023 [Pablo Henrique da Silva Andrade]

# Este código é livre para uso sob os termos da Licença MIT.

# Veja o arquivo LICENSE para mais informações.
*/


//BIBLIOTECAS NECESSARIAS
#include <stdio.h>
#include <stdlib.h>
#include "visual.h"
#include "operacoes.h"

void retornar();

void menu(){
    Mats *matrizes; // Criação de um vetor da struct Mats

    float multiplicador;
    nome(); // Aparecer o nome MATRIZ
    int opcao = menuOpcoes(); // Definindo a variável que receberá o valor retornado de menuOpcoes
    
    switch (opcao)
    {

    //SOMA DE MATRIZ
    case 0:
        matrizes = calloc(2, sizeof(Mats));

        processarMatriz(&matrizes[0]);
        processarMatriz(&matrizes[1]);
        somar(matrizes);
        liberarMemoria(*matrizes);
        
        //Liberação de memoria das matrizes
        
        retornar();

        break;

    //MULTIPLICAR MATRIZ POR NUMERO
    case 1:
        matrizes = calloc(1, sizeof(Mats)); // Alocar memoria para o vetor da Struct para poder usar seus recursos

        entrada_dados_mult(&matrizes->linhas, &matrizes->colunas,&multiplicador); // Primeiro a entrada de dados para o uso;
        alocarMemoria(&(*matrizes)); // Alocar memoria para a matriz 
        setMatriz(&(matrizes[0].matriz), matrizes[0].linhas, matrizes[0].colunas); // Crição da matriz
        num_mult_matriz(*matrizes, multiplicador); // Chamada da função para multiplicar
        liberarMemoria(*matrizes);
        
        retornar();

        break;
    
    //SUBTRAIR MATRIZES
    case 2:
        matrizes = calloc(2, sizeof(Mats));

        processarMatriz(&matrizes[0]);
        processarMatriz(&matrizes[1]);

        subtracao(matrizes);
        //Imprimir o resultado da subtração das matrizes

        liberarMemoria(*matrizes);
        
        //Liberação de memoria das matrizes

        retornar();
        
        break;

    //TRANSPOSTA DE MATRIZ
    case 3:
        matrizes = calloc(1, sizeof(Mats));
        
        processarMatriz(matrizes);
        transposta(matrizes);
        //Imprimir o resultado da matriz com as colunas e linhas inventidas com a função transposta
        liberarMemoria(*matrizes);

        retornar();

        break;

    //MULTIPLICAR MATRIZES
    case 4:
        matrizes = calloc(2, sizeof(Mats));

        processarMatriz(&matrizes[0]);
        processarMatriz(&matrizes[1]);

        multiplicar(matrizes);
        
        liberarMemoria(*matrizes);
        
            
        retornar();

        break;

    //DETERMINANTE DE MATRIZ
    case 5:
        matrizes = calloc(1, sizeof(Mats));

        processarMatriz(matrizes);
        getDeterminante(calcularDeterminante(matrizes[0].matriz, matrizes[0].linhas));
        liberarMemoria(*matrizes);

        retornar();

        break;
        
    //INVERSA DE UMA MATRIZ
    case 6:
        matrizes = calloc(1, sizeof(Mats));

        processarMatriz(matrizes);
        inversoMatriz(matrizes[0].matriz, matrizes[0].linhas);
        liberarMemoria(*matrizes);

        retornar();

        break;
    }
}

//FUNÇÃO PARA RETORNAR AO MENU
void retornar(){
    contorno();
    gotoxy(39,9);
    printf("Digite 1 para voltar ao menu:");
    gotoxy(39,10);
    printf("Digite 2 para sair do programa:");
    gotoxy(60, 100);

    switch(getch()){
        case 49:{ //Quando clicado 1 ele vai para esse caso
            system("cls");
            menu();
        }
        case 50:{ //Quando clicado 2 ele vai para esse caso
            system("cls");
            exit(1);
        }
    }
}

int main(){
    menu();
}

