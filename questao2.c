//Para um determinado país, determine a quantidade de atletas do sexo masculino e feminino que já participaram das Olimpíadas
//testando a leitura 1

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main(){
    int Masculino, Feminino;
    Masculino = 0;
    Feminino = 0;
    int contador = 0;

    char str[100];
    FILE*output = fopen("output\\bios.csv", "r");
    while (fgets(str, sizeof(str), output) != NULL && contador < 5){
      printf("%d: %s", contador + 1, str);
    contador++;
    }
    fclose(output);
    return 0;
}
