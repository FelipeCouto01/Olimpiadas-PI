//Para um determinado país, determine a quantidade de atletas do sexo masculino e feminino que já participaram das Olimpíadas
//testando a leitura 1

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main() {
    
    // Declarando as variáveis:
    char [300]
    int Masculino, Feminino;
    Masculino = 0;
    Feminino = 0;
    int contador = 0;
    
// recebendo o país escolhido e testando a abertura do arquivo:
    
    printf("Digite o NOC do país: ");
    scanf("%s", &país);
    FILE*output = fopen("output/bios.csv", "r");
    if (output == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    while (fgets(linha, sizeof(linha), output)) {
int coluna = 0;
char *token = strtok(linha, ",");

        while (token != NULL) {
            if (coluna == 6) {
                if (strcmp(token, busca) == 0) {
                    printf ("País encontrado\n");
                }
            }    
        }  
     } 
    }   
    return 0;
}
