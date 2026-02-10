#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // // nova biblioteca, coloquei ela para manipular a entrada do usuário, para não ter diferença entre letras maiúsculas e minúsculas (ex: bra, Bra, BRA, bRA, etc, tudo vai ser convertido para BRA)

// Avisa para o main que essa função existe la na questao3.c
void resolver_questao_3(char* pais_alvo);

int main() {
    char pais_escolhido[100]; 

    printf("=== SISTEMA DE ANALISE DE MEDALHAS (QUESTAO 3) ===\n");
    printf("Digite a sigla do pais (ex: BRA, USA, FRA): ");
    
    // Le o que o usuario digitou
    scanf("%s", pais_escolhido);

    // Converte para maiusculo a entrada
    for(int i = 0; pais_escolhido[i]; i++){
        pais_escolhido[i] = toupper(pais_escolhido[i]);
    }

    // Chama a função da lógica que está no questao3.c
    resolver_questao_3(pais_escolhido);

    return 0; 
}