//BIBLIOTECAS NECESSARIAS
#include <stdio.h>
#include <stdlib.h>

int i, j, k; //VARIAVEIS CONTADORAS

//STRUCT PARA A CRIAÇÃO DE MAIS DE UMA MATRIZ
typedef struct {
    float **matriz;
    int linhas;
    int colunas;
} Mats;

//FUNÇÃO PARA A ALOCAÇÃO DE MEMORIA
void alocarMemoria(Mats *matrizes){
	(*matrizes).matriz = calloc(matrizes->linhas, sizeof(float*));
	for(i = 0; i < matrizes->linhas; i++){
		(*matrizes).matriz[i] = calloc(matrizes->colunas, sizeof(float)); 
	}
}

void alocarMemoria_casos(float ***matriz, int linhas, int colunas){
	*matriz = calloc(linhas, sizeof(float*));
	for(i = 0; i < linhas; i++){
		(*matriz)[i] = calloc(colunas, sizeof(float)); 
	}
}

//FUNÇÃO PARA A LIBERAÇÃO DE MEMORIA
void liberarMemoria(Mats matrizes) {
    for (i = 0; i < matrizes.linhas; i++) {
        free(matrizes.matriz[i]);  // Libera a memoria de cada linha da matriz
    }
    free(matrizes.matriz);  // Libera a memoria do ponteiro para a matriz
}

void liberarMemoria_casos(float **matriz, int linha){
	for (i = 0; i < linha; i++) {
        free(matriz[i]);  // Libera a memoria de cada linha da matriz
    }
    free(matriz);  // Libera a memoria do ponteiro para a matriz
}


//FUNÇÃO PARA PROCESSAR UMA MATRIZ
void processarMatriz(Mats *matrizes){
	entrada_dados(&matrizes->linhas, &matrizes->colunas);
	alocarMemoria(matrizes);
	setMatriz(&matrizes->matriz, matrizes->linhas, matrizes->colunas);
}



//FUNÇÃO PARA SOMAR MATRIZ
void somar(Mats *matrizes){
	float **resultado;
	
	if((matrizes[0].linhas != matrizes[1].linhas) || (matrizes[0].colunas != matrizes[1].colunas)){
		error(2);
	} else {
		alocarMemoria_casos(&resultado, matrizes[0].linhas, matrizes[0].colunas);

		//Realização da operação de soma
		for(i = 0; i < matrizes[0].linhas; i++){
			for(j = 0; j < matrizes[0].colunas; j++){
				resultado[i][j] = matrizes[0].matriz[i][j] + matrizes[1].matriz[i][j];
			}
		}
	}
	getMatriz(resultado, matrizes[0].linhas, matrizes[0].colunas);
}

//FUNÇÃO PARA CALCULAR A MULT DE UM NUMERO COM UMA MATRIZ
void num_mult_matriz(Mats matrizes, float multiplicador){
	float **resultado;
	alocarMemoria_casos(&resultado, matrizes.linhas, matrizes.colunas);

	for(i = 0; i < matrizes.linhas; i++){
		for(j = 0; j < matrizes.colunas; j++){
			*(*(resultado + i) + j) = *(*(matrizes.matriz + i) + j) * multiplicador;
		}
	}
	getMatriz(resultado, matrizes.linhas, matrizes.colunas); // Mostrar ao usuario a matriz
}

//FUNÇÃO SUBTRA��O DE MATRIZES
void subtracao(Mats *matrizes){
	float **resultado;
	
	if((matrizes[0].linhas != matrizes[1].linhas) || (matrizes[0].colunas != matrizes[1].colunas)){
		error(2);
	} else {
		alocarMemoria_casos(&resultado, matrizes[0].linhas, matrizes[0].colunas);
	
		for (i = 0; i < matrizes[0].linhas; i++) {
        	for (j = 0; j < matrizes[0].colunas; j++){
				resultado[i][j] = matrizes[0].matriz[i][j] - matrizes[1].matriz[i][j];
			} 
		}
	}
	getMatriz(resultado, matrizes[0].linhas, matrizes[0].colunas);
}

//FUNÇÃO MATRIZ TRANSPOSTA
void transposta(Mats *matrizes){
    float **matrizTransposta; //Nova variavel para receber a transposta da matriz
    alocarMemoria_casos(&matrizTransposta, matrizes->colunas, matrizes->linhas);//Alocar memoria na matriz com as colunas e linhas invertidas
    for (i = 0; i < matrizes->linhas; i++) {
        for (j = 0; j < matrizes->colunas; j++) {
            matrizTransposta[j][i] = matrizes->matriz[i][j]; //Passando os dados da matriz original para a transposta
        }
    }

    getMatriz(matrizTransposta, matrizes[0].colunas, matrizes[0].linhas);
}

//FUNÇÃO PARA MULTIPLICAR MATRIZ
void multiplicar(Mats *matrizes){
	float** resultado;

	//Realização da operação de multiplicação
	alocarMemoria_casos(&resultado, matrizes[0].linhas, matrizes[1].colunas);
	
	if(matrizes[1].colunas == matrizes[0].linhas){
		for(i = 0; i < matrizes[0].linhas; i++){
			for(j = 0; j < matrizes[1].colunas; j++){
				for(k = 0; k < matrizes[0].colunas; k++){
					resultado[i][j] += matrizes[0].matriz[i][k] * matrizes[1].matriz[k][j];
				}
			}
		}
		getMatriz(resultado, matrizes[0].linhas, matrizes[1].colunas);	
	}else{
		error(2);
	}
}

// FUNÇÃO PARA CALCULAR O DETERMINANTE DE MATRIZ QUADRADA
float calcularDeterminante(float **matriz, int tamanho) {
    if (tamanho == 1) {
        return matriz[0][0];
    } else if (tamanho == 2) {
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    } else {
        float determinante = 0.0;
        int sinal = 1;
		int coluna;
        for (coluna = 0; coluna < tamanho; coluna++) { //para a eliminação das colunas dos valores
            // Alocar matriz temporaria para o cofator
            float **cofator;
			alocarMemoria_casos(&cofator, tamanho - 1, tamanho - 1);

            // Calcular o cofator da posi��o (0, coluna)
            int cofatorLinha = 0;
            // Criacao da submatriz cofator
            for (i = 1; i < tamanho; i++) { //Aqui ja elimina a linha 0, a primeira linha dos valores
                int cofatorColuna = 0;
                for (j = 0; j < tamanho; j++) {
                    if (j != coluna) { //eliminacao da coluna do valor escolhido
                        cofator[cofatorLinha][cofatorColuna] = matriz[i][j];
                        cofatorColuna++;
                    }
                }
                cofatorLinha++;
            }

            // Somar o termo do determinante
            determinante += sinal * matriz[0][coluna] * calcularDeterminante(cofator, tamanho - 1);

            // Liberar a memoria alocada para o cofator
            liberarMemoria_casos(cofator, tamanho - 1);

            // Alternar o sinal para o proximo termo
            sinal = -sinal;
        }

        return determinante;
    }
}


//FUNÇÃO PARA CALCULAR O INVERSO DA MATRIZ USANDO ELIMINAÇÃO GAUSSIANA 
void inversoMatriz(float **matriz, int tamanho) {
    if(calcularDeterminante(matriz, tamanho) != 0){
        // Criar uma matriz auxiliar que seraá usada na eliminação gaussiana
        float** auxiliarMatriz = malloc(tamanho * sizeof(float*));
        for (i = 0; i < tamanho; i++) {
            auxiliarMatriz[i] = malloc((2 * tamanho) * sizeof(float));
            //copiando os elementos da matriz para a matriz identidade
            for (j = 0; j < tamanho; j++) {
                auxiliarMatriz[i][j] = matriz[i][j];
            }
            //cria��o da matriz identidade
            for (j = tamanho; j < 2 * tamanho; j++) {
                auxiliarMatriz[i][j] = (j == i + tamanho) ? 1.0 : 0.0;
            }
        }

        // Aplicar a eliminação gaussiana
        for (i = 0; i < tamanho; i++) {
            //escolhe o pivô com o maior valor absoluto
            int pivo = i;
            for (k = i + 1; k < tamanho; k++) {
                if (abs(auxiliarMatriz[k][i]) > abs(auxiliarMatriz[pivo][i])) {
                    pivo = k;
                }
            }

            // Trocar as linhas, caso necessaria o pivo não estiver na linha atual
            if (pivo != i) {
                for (j = 0; j < 2 * tamanho; j++) {
                    float temp = auxiliarMatriz[i][j]; //Valor temporario
                    auxiliarMatriz[i][j] = auxiliarMatriz[pivo][j];
                    auxiliarMatriz[pivo][j] = temp;
                }
            }

            // Reduzir para a forma escalonada
            for (k = i + 1; k < tamanho; k++) {
                float factor = auxiliarMatriz[k][i] / auxiliarMatriz[i][i];
                for (j = i; j < 2 * tamanho; j++) {
                    auxiliarMatriz[k][j] -= factor * auxiliarMatriz[i][j];
                }
            }
        }

        // Aplicar a eliminação inversa
        for (i = tamanho - 1; i >= 0; i--) {
            for (k = i - 1; k >= 0; k--) {
                float factor = auxiliarMatriz[k][i] / auxiliarMatriz[i][i];
                for (j = i; j < 2 * tamanho; j++) {
                    auxiliarMatriz[k][j] -= factor * auxiliarMatriz[i][j];
                }
            }
        }

        // Normalizar as linhas para obter a matriz inversa
        float** inverse = malloc(tamanho * sizeof(float*));
        for (i = 0; i < tamanho; i++) {
            inverse[i] = malloc(tamanho * sizeof(float));
            for (j = 0; j < tamanho; j++) {
                inverse[i][j] = auxiliarMatriz[i][j + tamanho] / auxiliarMatriz[i][i];
            }
        }

        // Liberar a memorio alocada para a matriz auxiliar
        liberarMemoria_casos(auxiliarMatriz, tamanho);

        getMatriz(inverse, tamanho, tamanho);
    } else {
        error(1);
    }
}

