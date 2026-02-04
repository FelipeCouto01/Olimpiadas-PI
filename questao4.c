//Considere 10 países. Crie um ranking ordenado pela pontuação de medalhas, em que Ouro vale 3 pontos, Prata vale 2 pontos e Bronze vale 1 ponto 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

typedef struct {
    char noc[10];   
    int pontuacao;  
} PaisPontos;

// Função de comparação para o qsort (ordena por pontos, do maior para o menor)
int compararPontos(const void *a, const void *b) {
    PaisStats *ponteiro1 = (PaisStats *)a;
    PaisStats *ponteiro2 = (PaisStats *)b;
    
    PaisStats pais1 = *ponteiro1;
    PaisStats pais2 = *ponteiro2;

    return pais2.pontuacao_total - pais1.pontuacao_total;
}


void ordernarPontuacao(){
    printf("Ranking por Pontuacao Ouro, Prata e Bronze\n");

    //Aqui estou definindo os países que podem ser usados. Mais a frente será necessário organizar, pois pode haver problemas de escolhas
    PaisStats placar[10] = {
        {"USA", 0, 0, 0, 0, 0}, 
        {"CHN", 0, 0, 0, 0, 0}, 
        {"BRA", 0, 0, 0, 0, 0}, 
        {"GBR", 0, 0, 0, 0, 0}, 
        {"FRA", 0, 0, 0, 0, 0},
        {"GER", 0, 0, 0, 0, 0}, 
        {"ITA", 0, 0, 0, 0, 0}, 
        {"JPN", 0, 0, 0, 0, 0}, 
        {"AUS", 0, 0, 0, 0, 0}, 
        {"CAN", 0, 0, 0, 0, 0}
    };
}
