#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>//NECESSARIO PARA USAR A FUNÇÃO GOTOXY
#include <conio.h>
#include <ctype.h>


int i, j;

void retornar();
void error();

int ehLetra(const char valor) {
    // Verifica se cada caractere é uma letra
    if (isalpha(valor)) {
        error(3);
    }

    return 1; // São apenas letras
}

void gotoxy(int x, int y) {
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

//FUNÇÃO PARA RETORNAR PARA MENU
void contorno() {
    int altura = 29;   // Altura da tela
    int largura = 119;  // Largura da tela

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            if (i == 0 || i == altura - 1 || j == 0 || j == largura - 1) {
                printf("%c", 219);  // Preenchimento das bordas
            } else {
                printf(" ");       // Para poder deixar os espaços do meio da tela
            }
        }
        printf("\n");
    }
}

//ENUMERAÇÃO PARA AS OPÇÕES
enum Opcoes{
    ADICAO_MATRIZES,
    PRODUTO_NUM_MATRIZ,
    SUBTRACAO_MATRIZES,
    MATRIZ_TRANSPOSTA,
    PRODUTO_MATRIZES,
    CALCULO_DETERMINANTE,
    MATRIZ_INVERSA,
};

//FUNÇÃO PARA AMOSTRAR AS OPÇÕES DE CALCULO
int menuOpcoes(){
    int item = ADICAO_MATRIZES; //Primeira seleção
    int tecla, b = 1;//Variavel para armazenar o valor da tecla digitada e variavel booleana

    while(b){
        system("cls");
        contorno();
        gotoxy(39,9);
        printf("SELECIONE O CALCULO QUE DESEJA FAZER(use UP, DOWN e Enter): \n");
        gotoxy(39,10);
        printf("%s 1- Adicao de Matrizes\n", item == ADICAO_MATRIZES ? "->" : " "); //Quando item for igual a linha ele coloca a seta
        gotoxy(39,11);
        printf("%s 2- Multiplicar por um numero\n", item == PRODUTO_NUM_MATRIZ ? "->" : " ");
        gotoxy(39,12);
        printf("%s 3- Subtracao de Matrizes\n", item == SUBTRACAO_MATRIZES ? "->" : " ");
        gotoxy(39,13);
        printf("%s 4- Matriz Transposta\n", item == MATRIZ_TRANSPOSTA ? "->" : " ");
        gotoxy(39,14);
        printf("%s 5- Produto de Matrizes\n", item == PRODUTO_MATRIZES ? "->" : " ");
        gotoxy(39,15);
        printf("%s 6- Calculo de Determinate\n", item == CALCULO_DETERMINANTE ? "->" : " ");
        gotoxy(39,16);
        printf("%s 7- Matriz Inversa\n", item == MATRIZ_INVERSA ? "->" : " ");

        tecla = getch();
        if(tecla == 224){
            tecla = getch();
            switch (tecla)
            {
            case 72: //Quando a seta UP for clicada
                item = (item + 6) % 7; //Quando ele estiver em uma posição ele vai somar mais 6 posições e tirar o modulo com 7 para poder ter
                //o efeito que subiu 1 e quando estive no topo e para baixo

                break;
            case 80: // Quando a seta down for clicada
                item = (item + 1) % 7; 
                break;
            }
        } else if(tecla == 13){ // Quando Enter for clicado
            system("cls");
            return item;
            b = 0;
            
        }
    }
    return -1;
}

//FUNÇÃO PARA PODER FAZER APARECER A MATRIZ
void getMatriz(float **matriz, int linhas, int colunas){
    int y = 9;
    contorno();
    gotoxy(50, 7);
    printf("RESULTADO:");
    for(i = 0; i < linhas; i++){
        gotoxy(50, y += 1);
        for(j = 0; j < colunas; j++){
            printf("%.2f\t", *(*(matriz + i) + j)); 
        }
    }
    gotoxy(50, y+2);
    printf("APERTE ENTER PARA PROXIMA ETAPA!");
    int tecla = getch();

    if(tecla == 13){
        system("cls");
    }
}

//FUN��O PARA FAZER A MATRIZ
void setMatriz(float ***mat, int lin, int col){

    contorno();
    int y = 1;
	//Ler matriz
    gotoxy(3, 2);
	printf("Agora digite os numeros para preencher as matrizes\n");
	for(i = 0; i < lin; i++){
		for(j = 0; j < col; j++){
            gotoxy(3, 2 + y);
			printf("Digite um numero para a posicao (%d,%d) da matriz: ", i, j);
			scanf("%f", &(*mat)[i][j]); //Feito desta maneira porque o parametro é um ponteiro
            ehLetra((*mat)[i][j]);
			getchar();
            y++;
		}
	}
    system("cls");
}

//FUNÇÃO PARA APARECER MATRIZ
void nome() {
    contorno();
    // letra M
    gotoxy(20, 10);
    printf("###     ###");
    gotoxy(20, 11);
    printf("####   ####");
    gotoxy(20, 12);
    printf("###########");
    gotoxy(20, 13);
    printf("### ### ###");
    gotoxy(20, 14);
    printf("###  #  ###");
    gotoxy(20, 15);
    printf("###     ###");
    gotoxy(20, 16);
    printf("###     ###");
    gotoxy(20, 17);
    printf("###     ###");
    gotoxy(20, 18);
    printf("###     ###");

    // letra A
    gotoxy(33, 10);
    printf("    #####   ");
    gotoxy(33, 11);
    printf("   ##   ##  ");
    gotoxy(33, 12);
    printf("  ##     ## ");
    gotoxy(33, 13);
    printf("  ##     ## ");
    gotoxy(33, 14);
    printf(" ###########");
    gotoxy(33, 15);
    printf(" ##       ##");
    gotoxy(33, 16);
    printf("##         ##");
    gotoxy(33, 17);
    printf("##         ##");
    gotoxy(33, 18);
    printf("##         ##");

    // letra T
    gotoxy(46, 10);
    printf("###########");
    gotoxy(46, 11);
    printf("###########");
    gotoxy(46, 12);
    printf("    ###    ");
    gotoxy(46, 13);
    printf("    ###    ");
    gotoxy(46, 14);
    printf("    ###    ");
    gotoxy(46, 15);
    printf("    ###    ");
    gotoxy(46, 16);
    printf("    ###    ");
    gotoxy(46, 17);
    printf("    ###    ");
    gotoxy(46, 18);
    printf("    ###    ");

    // letra R
    gotoxy(59, 10);
    printf("#########  ");
    gotoxy(59, 11);
    printf("########## ");
    gotoxy(59, 12);
    printf("###    ####");
    gotoxy(59, 13);
    printf("###    ####");
    gotoxy(59, 14);
    printf("########## ");
    gotoxy(59, 15);
    printf("#########  ");
    gotoxy(59, 16);
    printf("###  ###   ");
    gotoxy(59, 17);
    printf("###   ###  ");
    gotoxy(59, 18);
    printf("###    ### ");

    // letra I
    gotoxy(72, 10);
    printf("###########");
    gotoxy(72, 11);
    printf("###########");
    gotoxy(72, 12);
    printf("     ###   ");
    gotoxy(72, 13);
    printf("     ###   ");
    gotoxy(72, 14);
    printf("     ###   ");
    gotoxy(72, 15);
    printf("     ###   ");
    gotoxy(72, 16);
    printf("     ###   ");
    gotoxy(72, 17);
    printf("###########");
    gotoxy(72, 18);
    printf("###########");

    // letra Z
    gotoxy(85, 10);
    printf("###########");
    gotoxy(85, 11);
    printf("###########");
    gotoxy(85, 12);
    printf("       ### ");
    gotoxy(85, 13);
    printf("      ###  ");
    gotoxy(85, 14);
    printf("     ###   ");
    gotoxy(85, 15);
    printf("    ###    ");
    gotoxy(85, 16);
    printf("   ###     ");
    gotoxy(85, 17);
    printf("###########");
    gotoxy(85, 18);
    printf("###########");
    
    
    sleep(3);
    system("cls");
    
}

void entrada_dados_mult(int *linhas, int *colunas, float *multiplicador){
    contorno();
    gotoxy(5,4);
    printf("Digite o numero que voce deseja multiplicar sua matriz: ");
    scanf("%f", multiplicador);
    fflush(stdin);
    ehLetra(*multiplicador);
    gotoxy(5,5);
    printf("Digite o numero de linhas da sua matriz: ");
    scanf("%d", linhas);
    fflush(stdin);
    ehLetra(*linhas);
    gotoxy(5,6);
    printf("Digite o numero de colunas da sua matriz: ");
    scanf("%d", colunas);
    fflush(stdin);
    ehLetra(*colunas);
    getchar();
    system("cls");

}

void entrada_dados(int *linhas, int *colunas){
    contorno();
    gotoxy(5,4);
    printf("Digite o numero de linhas da sua matriz: ");
    scanf("%d", linhas);
    ehLetra(*linhas);
    gotoxy(5,5);
    printf("Digite o numero de colunas da sua matriz: ");
    scanf("%d", colunas);
    ehLetra(*colunas);
    system("cls");
}

void msm_erros(int opcao){
    switch (opcao)
    {
    case 1:
        gotoxy(3, 13);
        printf("DETERMINANTE = 0, IMPOSSIVEL INVERTER!!!");
        break;
    case 2:
        gotoxy(3, 13);
        printf("DIMENSOES INCORRETAS!!!");
        break;
    case 3:
        gotoxy(3, 13);
        printf("DIGITO INCORRETO:");
        break;
    default:
        break;
    }
}

void error(int opcao){
    system("cls");
    contorno();
     // Letra E
    gotoxy(3, 3);
    printf("###########");
    gotoxy(3, 4);
    printf("###########");
    gotoxy(3, 5);
    printf("###        ");
    gotoxy(3, 6);
    printf("###        ");
    gotoxy(3, 7);
    printf("###########");
    gotoxy(3, 8);
    printf("###########");
    gotoxy(3, 9);
    printf("###        ");
    gotoxy(3, 10);
    printf("###        ");
    gotoxy(3, 11);
    printf("###########");

    // Letra R
    gotoxy(16, 3);
    printf("########## ");
    gotoxy(16, 4);
    printf("###########");
    gotoxy(16, 5);
    printf("###     ###");
    gotoxy(16, 6);
    printf("###     ###");
    gotoxy(16, 7);
    printf("########## ");
    gotoxy(16, 8);
    printf("########   ");
    gotoxy(16, 9);
    printf("###   ###  ");
    gotoxy(16, 10);
    printf("###    ### ");
    gotoxy(16, 11);
    printf("###     ###");

    // Letra R
    gotoxy(30, 3);
    printf("########## ");
    gotoxy(30, 4);
    printf("###########");
    gotoxy(30, 5);
    printf("###     ###");
    gotoxy(30, 6);
    printf("###     ###");
    gotoxy(30, 7);
    printf("########## ");
    gotoxy(30, 8);
    printf("########   ");
    gotoxy(30, 9);
    printf("###   ###  ");
    gotoxy(30, 10);
    printf("###    ### ");
    gotoxy(30, 11);
    printf("###     ###");

    // Letra O
    gotoxy(44, 3);
    printf("###########");
    gotoxy(44, 4);
    printf("###########");
    gotoxy(44, 5);
    printf("###     ###");
    gotoxy(44, 6);
    printf("###     ###");
    gotoxy(44, 7);
    printf("###     ###");
    gotoxy(44, 8);
    printf("###     ###");
    gotoxy(44, 9);
    printf("###     ###");
    gotoxy(44, 10);
    printf("###########");
    gotoxy(44, 11);
    printf("###########");

    // Letra !
    gotoxy(57, 3);
    printf("   ###  ");
    gotoxy(57, 4);
    printf("   ###  ");
    gotoxy(57, 5);
    printf("   ###  ");
    gotoxy(57, 6);
    printf("   ###  ");
    gotoxy(57, 7);
    printf("   ###  ");
    gotoxy(57, 8);
    printf("   ###  ");
    gotoxy(57, 9);
    printf("        ");
    gotoxy(57, 10);
    printf("   ###  ");
    gotoxy(57, 11);
    printf("   ###  ");
    gotoxy(3, 13);
    msm_erros(opcao);

    sleep(4);
    system("cls");

    retornar();


}

//FUNÇÃO PARA PODER AMOSTRAR O VALOR UNITARIO DO DETERMINANTE
void getDeterminante(float dado){
    contorno();
    gotoxy(50, 10);
    printf("Determinante: %.2f", dado);
    sleep(5);
    system("cls");
}
