//Para um determinado país, determine a quantidade de atletas do sexo masculino e feminino que já participaram das Olimpíadas
//testando a leitura 1

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main(){
    // Declarando as variáveis:
    char País[10];
    int Masculino, Feminino;
    int país_representante = 1;
    Masculino = 0;
    Feminino = 0;
    int contador = 0;
// recebendo o país escolhido e testando a abertura do arquivo:
    printf("Digite o NOC do país: ");
    scanf("%s", &país);
    FILE*output = fopen("output/bios.csv", "r");
    if (output == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 1;

        while (país_representante == 1)
    }
    fclose(output);
    return 0;
}
