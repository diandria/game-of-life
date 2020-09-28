/*
 * Script para executar o jogo da vida de John Conway
 *
 * @link  do código https://repl.it/join/sipypalw-diandria
 * @author Daiane   - TIA: 4199227-1 
 * @author Diandria - TIA: 3190751-2
 * @author Leonardo - TIA: 4194942-0
 * @version 1.0
 */

#include <stdio.h>

//valores globais que são utilizados nas matrizes
int TAM_COLUNA;
int TAM_LINHA;

/**
 * Método que inicializa todas as posições de uma matriz valendo 0
 *
 * @method inicializaMatriz
 * @param {int} a_matriz[][] - Matriz que terá o valores iniciados
 *
 */
void inicializaMatriz(int a_matriz[TAM_LINHA][TAM_COLUNA]) {

    for (int in_linha = 0; in_linha < TAM_LINHA; in_linha++) {
        for (int in_coluna = 0; in_coluna < TAM_COLUNA; in_coluna++) {
            a_matriz[in_linha][in_coluna] = 0;
        }
    }
}

/**
 * Método que exibe no terminal uma matriz formatada, indicando os seus indices ao lado e acima para assim a melhor localização e orientação do usuário
 *
 * @method printMatriz
 * @param {int} a_matriz[][] - Matriz que terá o valores exibidos
 *
 */
void printMatriz(int a_matriz[TAM_LINHA][TAM_COLUNA]) {

    printf("\n\n");
    printf("    ");
    //Laço para mostrar os indices das colunas
    for (int in_coluna = 0; in_coluna < TAM_COLUNA; in_coluna++) {
        //arrumando formatação para que fique alinhado 
        if (in_coluna < 10) {
            printf("%d  ", in_coluna);
        } else {
            printf("%d ", in_coluna);
        }
    }
    printf("\n");
    //Laço para mostrar os valores da matriz
    for (int in_linha = 0; in_linha < TAM_LINHA; in_linha++) {
        printf("\n");

        //Mostrando os indices das linhas
        if (in_linha < 10) {
            printf("%d  ", in_linha);
        } else {
            printf("%d ", in_linha);
        }
        //Laço para mostrar os valores da matriz
        for (int in_coluna = 0; in_coluna < TAM_COLUNA; in_coluna++) {
            //mostrando os valores da matriz
            printf(" %d ", a_matriz[in_linha][in_coluna]);
        }
    }
}

/**
 * Método que analisa os termos vizinhos de uma determinada coordenada e calcula os vizinhos "vivos" de uma célula
 *
 * @method analisaVizinhos
 * @param {int} a_matriz[][] - Matriz de inteiros principal que terá os valores dos vizinhos analisados
 * @param {int} in_cordLinha - O valor da coordenada da linha que será analisada
 * @param {int} in_cordColuna - O valor da coordenada da coluna que será analisada
 * @return {int} in_qtdVizinhos - O valor inteiro da quantidade de vizinhos "vivos" encontrados
 *
 */
int analisaVizinhos(int a_matriz[TAM_LINHA][TAM_COLUNA], int in_cordLinha, int in_cordColuna) {

    int in_qtdVizinhos = 0;
    int in_elemento;

    for (int in_linha = 0; in_linha < 3; in_linha++) {
        for (int in_coluna = 0; in_coluna < 3; in_coluna++) {

            //in_linha + (in_cordLinha - 1): vizinhos considerando o termo anterior de cada linha
            //in_coluna + (in_cordColuna - 1): vizinhos considerando o termo anterior de cada coluna
            //se for uma posição inexiste na matriz ele não considera como vizinho, 
            //se for uma posição -1 é uma posição inexistente, 
            //se for uma posição maior que o numero de linhas ou de colunas tbm é inexistente
            if (!((in_linha + (in_cordLinha - 1) == -1 || in_coluna + (in_cordColuna - 1) == -1) || (in_linha + (in_cordLinha - 1) > TAM_LINHA) || (in_coluna + (in_cordColuna - 1) > TAM_COLUNA))) {

                // Conteudo do vizinho que vai ser analisado
                in_elemento = a_matriz[in_linha + (in_cordLinha - 1)][in_coluna + (in_cordColuna - 1)];

                // Elimina da analise o ponto central
                if (in_linha == 1 && in_coluna == 1) {
                    continue;
                }
                // Se o vizinho estiver vivo será somado na quantidade de vizinhos
                else if (in_elemento == 1) {
                    in_qtdVizinhos++;
                }
            }
        }
    }
    return in_qtdVizinhos;
}

/**
 * Método que define se o ponto central vai ser alterado ou se será mantido na proxima geração
 *
 * @method definePontoCentral
 * @param {int} a_matriz[][] - Matriz de inteiros principal que terá o valores manipulados
 * @param {int} in_qtdVizinhos - O valor inteiro da quantidade de vizinhos "vivos" encontrados para a coordenada
 * @param {int} in_cordLinha - A posição da coordenada da linha que será analisada
 * @param {int} in_cordColuna - A posição da coordenada da coluna que será analisada
 *
 */
void definePontoCentral(int a_matriz[TAM_LINHA][TAM_COLUNA], int in_qtdVizinhos, int in_cordLinha, int in_cordColuna) {

    // se estiver a celula estiver viva, e os vizinhos forem < 2 a celula morre
    if (in_qtdVizinhos < 2 && a_matriz[in_cordLinha][in_cordColuna] == 1) {
        a_matriz[in_cordLinha][in_cordColuna] = 0;
    }

    // se estiver a celula estiver viva, e os vizinhos forem > 3 a celula morre
    else if (in_qtdVizinhos > 3 && a_matriz[in_cordLinha][in_cordColuna] == 1) {
        a_matriz[in_cordLinha][in_cordColuna] = 0;
    }

    // se estiver a celula estiver morta, e os vizinhos forem == 3 a celula vive
    else if (in_qtdVizinhos == 3 && a_matriz[in_cordLinha][in_cordColuna] == 0) {
        a_matriz[in_cordLinha][in_cordColuna] = 1;
    }

    // se estiver a celula estiver viva, e os vizinhos forem == 2 ou == 3 a celula continua
    else if ((in_qtdVizinhos == 2 || in_qtdVizinhos == 3) && a_matriz[in_cordLinha][in_cordColuna] == 1) {
        a_matriz[in_cordLinha][in_cordColuna] = 1;
    }
}

/**
 * Método que realiza a troca na matriz que contem a proxima geração para a matriz que terá a geração atual
 *
 * @method defineGeracaoAtual
 * @param {int} a_matriz[][] - Matriz de inteiros principal que será atualizada para obter a geração atual
 * @param {int} a_proximaGeracao[][] - Matriz de inteiros que contém os valores que da proxima geração que irá atualizar a matriz principal
 *
 */
void defineGeracaoAtual(int a_matriz[TAM_LINHA][TAM_COLUNA], int a_proximaGeracao[TAM_LINHA][TAM_COLUNA]) {

    for (int in_linha = 0; in_linha < TAM_LINHA; in_linha++) {
        for (int in_coluna = 0; in_coluna < TAM_COLUNA; in_coluna++) {
            a_matriz[in_linha][in_coluna] = a_proximaGeracao[in_linha][in_coluna];
        }
    }
}

/**
 * Método que define um padrão inicial para a matriz principal e a matriz que contem os valores da proxima geração
 *
 * @method padraoInicial
 * @param {int} a_matriz[][] - Matriz de inteiros principal que será atualizada para obter a geração atual
 * @param {int} a_proximaGeracao[][] - Matriz de inteiros que contém os valores que da proxima geração que irá atualizar a matriz principal
 *
 */
void padraoInicial(int a_matriz[TAM_LINHA][TAM_COLUNA], int a_proximaGeracao[TAM_LINHA][TAM_COLUNA]) {

    // Formato sendo passado como padrão para as duas matrizes, principal e a que possui a proxima geração 
    a_matriz[3][7] = a_proximaGeracao[3][7] = 1;
    a_matriz[5][5] = a_proximaGeracao[5][5] = 1;
    a_matriz[5][6] = a_proximaGeracao[5][6] = 1;
    a_matriz[5][8] = a_proximaGeracao[5][8] = 1;
    a_matriz[5][9] = a_proximaGeracao[5][9] = 1;
    a_matriz[6][5] = a_proximaGeracao[6][5] = 1;
    a_matriz[6][7] = a_proximaGeracao[6][7] = 1;
    a_matriz[6][9] = a_proximaGeracao[6][9] = 1;
    a_matriz[7][7] = a_proximaGeracao[7][7] = 1;
    a_matriz[8][7] = a_proximaGeracao[8][7] = 1;
    a_matriz[9][5] = a_proximaGeracao[9][5] = 1;
    a_matriz[9][7] = a_proximaGeracao[9][7] = 1;
    a_matriz[9][9] = a_proximaGeracao[9][9] = 1;
    a_matriz[10][5] = a_proximaGeracao[10][5] = 1;
    a_matriz[10][6] = a_proximaGeracao[10][6] = 1;
    a_matriz[10][8] = a_proximaGeracao[10][8] = 1;
    a_matriz[10][9] = a_proximaGeracao[10][9] = 1;
    a_matriz[12][7] = a_proximaGeracao[12][7] = 1;
}

/**
 * Método que insere uma "celula viva" para uma determinada coordenada indicada pelo usuário
 *
 * @method inserePonto
 * @param {int} a_proximaGeracao[][] - Matriz que contem os valores que atualizam a matriz principal
 * @param {int} in_cordLinha - A posição da coordenada da linha que será analisada
 * @param {int} in_cordColuna - A posição da coordenada da coluna que será analisada
 *
 */
void inserePonto(int a_proximaGeracao[TAM_LINHA][TAM_COLUNA], int in_cordLinha, int in_cordColuna) {

    a_proximaGeracao[in_cordLinha][in_cordColuna] = 1;
}

/**
 * Método que realiza a chamada de todas as funções necessárias em um único processamento
 *
 * @method processamento
 * @param {int} a_matriz[][] - Matriz de inteiros principal que será atualizada para obter a geração atual
 * @param {int} a_proximaGeracao[][] - Matriz de inteiros que contém os valores que da proxima geração que irá atualizar a matriz principal
 *
 */
void processamento(int a_matriz[TAM_LINHA][TAM_COLUNA], int a_proximaGeracao[TAM_LINHA][TAM_COLUNA]) {

    for (int in_linha = 0; in_linha < TAM_LINHA; in_linha++) {
        for (int in_coluna = 0; in_coluna < TAM_COLUNA; in_coluna++) {
            definePontoCentral(a_proximaGeracao, analisaVizinhos(a_matriz, in_linha, in_coluna), in_linha, in_coluna);
        }
    }
    defineGeracaoAtual(a_matriz, a_proximaGeracao);
    printMatriz(a_matriz);
    printf("\n\n");
}

/**
 * Método main
 *
 * @method main
 * @return {int} Retorna 0 indicando que o codigo chegou ao fim
 *
 */
int main(void) {

    printf("###### JOGO DA VIDA - CONWAY ######\n\n\n\n");

    // while que valida os valores das entradas de linhas e colunas
    while (1) {
        // Informa ao usuário a faixa permitida na entrada
        printf("\nDigite valores entre 15 e 25 para linhas e colunas.\n\n");

        // Pede um valor de entrada para o usuário para quantidade de linhas que tera a matriz
        printf("Digite o numero de linhas: ");
        scanf("%d", & TAM_LINHA);

        // Pede um valor de entrada para o usuário para quantidade de coluna que tera a matriz
        printf("Digite o numero de coluna: ");
        scanf("%d", & TAM_COLUNA);

        // Se a faixa digitada pelo usuário estiver dentro do esperado finaliza o while, senão roda o while ate que a faixa digitada esteja correta
        if (!(TAM_COLUNA < 15 || TAM_LINHA < 15 || TAM_LINHA > 25 || TAM_COLUNA > 25)) {
            break;
        } else {
            printf("\nValor digitado e' menor que 15 ou maior que 25. Digite novamente:\n\n");
        }
    }

    // Cria as matrizes, principal e a auxiliar que terá a proxima geração
    int a_matriz[TAM_LINHA][TAM_COLUNA];
    int a_proximaGeracao[TAM_LINHA][TAM_COLUNA];

    // Inicia a matriz princial e matriz auxiliar com todas as posições zeradas
    inicializaMatriz(a_matriz);
    inicializaMatriz(a_proximaGeracao);

    // Define uma padrão inicial para as matrizes principal e auxiliar
    padraoInicial(a_matriz, a_proximaGeracao);

    // Exibe para o usuário a primeira geração
    printMatriz(a_matriz);

    // Loop que define as ações tomadas, até que o usuário encerre o programa
    while (1) {
        int in_opc;

        // Exibe para o usuário um menu com um menu com as opções possiveis
        printf("\n\n\nESCOLHA A OPCAO:\n0. Finalizar;\n1. Ver a proxima geracao;\n2. Inserir novo ponto.\n");
        scanf("%d", & in_opc);

        // Se o usuário escolher a opção 1 irá ver a proxima geração de celulas
        if (in_opc == 1) {
            processamento(a_matriz, a_proximaGeracao);
        }

        // Se o usuário escolher a opção 2 irá definir um novo ponto na matriz
        else if (in_opc == 2) {

            int in_cordLinha;
            int in_cordColuna;

            // Pede ao usuário o valor da coordenada da linha
            printf("\nDigite o numero da linha ");
            scanf("%d", & in_cordLinha);

            // Pede ao usuário o valor da coordenada da coluna
            printf("\nDigite o numero da coluna ");
            scanf("%d", & in_cordColuna);

            // O valor será inserido na matriz auxiliar que contem a proxima geração, 
            //será feito o espelhamento para a matriz principal
            //exibido para o usuário a matriz modificada
            inserePonto(a_proximaGeracao, in_cordLinha, in_cordColuna);
            defineGeracaoAtual(a_matriz, a_proximaGeracao);
            printMatriz(a_matriz);
        }

        // Se o usuário escolher a opção 0 o programa será encerrado
        else if (in_opc == 0) {
            break;
        }
    }

    printf("\n\n\n #########################################");

}