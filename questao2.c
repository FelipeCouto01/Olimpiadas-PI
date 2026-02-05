//Para um determinado país, determine a quantidade de atletas do sexo masculino e feminino que já participaram das Olimpíadas
//testando a leitura 1

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main(){
    char País[10];
    int Masculino, Feminino;
    Masculino = 0;
    Feminino = 0;
    int contador = 0;

    printf("Digite o NOC do país: ");
    scanf("%s", &País);
    FILE*output = fopen("output\\bios.csv", "r");
    if (output == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    
    while ( ){
      printf("%d: %s", contador + 1, str);
    contador++;
    }
    fclose(output);
    return 0;
}
