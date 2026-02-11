//Para um determinado país, determine o número de atletas do sexo masculino e feminino que conquistaram mais de uma medalha de ouro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#include "../include/structs.h"
#include "../include/leitura.h"

// Define o tamanho do Mapa de IDs
// Coloquei 200.000 para ter uma margem de segurança e evitar erros de memória (ACONTECEU)
#define MAX_MAPA_ID 200000

// -------------------------------------------------------------------
// Gera o gráfico usando Gnuplot
// -------------------------------------------------------------------

void gerar_grafico_gnuplot(char* pais, int homens, int mulheres) {
    
    // Abre o caminho para enviar comandos pro gnuplot
    FILE *gnuplotPipe = popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");

    if (gnuplotPipe == NULL) {
        printf("Gnuplot nao encontrado\n");
        return;
    }

    // Configurações visuais do gráfico
    // "set terminal pngcairo": Avisa ao Gnuplot para não abrir uma janela, mas sim
    //  renderizar uma imagem PNG (usando a lib 'cairo')
    // "size 800,600": Define o tamanho da imagem gerada (Largura x Altura) em pixels
    // "font": Escolhe a fonte (Verdana) e o tamanho (10) para os textos do gráfico
    fprintf(gnuplotPipe, "set terminal pngcairo size 800,600 enhanced font 'Verdana,10'\n");
    fprintf(gnuplotPipe, "set output 'grafico_%s.png'\n", pais); // Nome do arquivo gerado
    
    // Títulos e Eixos ----- O fprintf envia comandos para o gnuplot, como se estivesse digitando na linha de comando do gnuplot
    // Esses comandos estão configurando o gráfico
    fprintf(gnuplotPipe, "set title 'Atletas do %s com >1 Medalha de Ouro'\n", pais); // titulo do grafico
    fprintf(gnuplotPipe, "set ylabel 'Quantidade de Atletas'\n"); // titulo do eixo y
    fprintf(gnuplotPipe, "set style fill solid 1.0 border -1\n"); // configura o estilo das barras, o solid 1.0 deixa as barras completamente preenchidas, e border -1 desenha uma borda preta ao redor das barras
    fprintf(gnuplotPipe, "set boxwidth 0.5\n"); // é a largura da barra, ta deixando elas mais finas
    fprintf(gnuplotPipe, "set grid y\n"); // faz aquelas linhas de grade no eixo Y
    
    // Eu pego o maior valor entre homens e mulheres (max_val) e digo para o eixo Y ir de 0 até max_val + 2
    // Isso cria aquele espacinho em branco no topo do gráfico
    int max_val = (homens > mulheres ? homens : mulheres);
    fprintf(gnuplotPipe, "set yrange [0:%d]\n", max_val + 2); 

    // "plot '-'":    Avisa "Não procure um arquivo. Os dados virão digitados abaixo"
    // "using 2":     Use a 2ª coluna (os números) para definir a altura da barra
    // ":xtic(1)":    Use a 1ª coluna (os nomes "Masculino/Feminino") como rótulos no eixo X
    // "with boxes":  O formato do desenho deve ser Caixas (Barras)
    // "notitle":     Remove a legenda automática para limpar o visual
    // "linecolor":   Define a cor da barra, azul :D
    fprintf(gnuplotPipe, "plot '-' using 2:xtic(1) with boxes notitle linecolor rgb '#4682B4'\n");

    // Enviando o valor dos homens e mulheres para o gnuplot
    fprintf(gnuplotPipe, "\"Masculino\" %d\n", homens);
    fprintf(gnuplotPipe, "\"Feminino\" %d\n", mulheres);
    
    // Finaliza o envio dos dados
    fprintf(gnuplotPipe, "e\n");

    fflush(gnuplotPipe); // Garante que todos os comandos foram enviados para o gnuplot, ele meio que empurra tudo que possa ter ficado preso no buffer para o gnuplot processar
    pclose(gnuplotPipe); // Fecha o pipe, o gnuplot processa os comandos e gera o gráfico

    printf("\nGrafico gerado: 'grafico_%s.png'\n", pais); // so para deixar mais organizado no menu visual do terminal

}

void resolver_questao_3(char* pais_alvo) {
    printf("\n=== INICIANDO ANALISE PARA O PAIS: %s ===\n", pais_alvo);

    // Guardando a quantidade de linhas/atletas carregados para usar nos loops depois
    int qtd_resultados = 0;
    int qtd_atletas = 0;

    // ---------------------------------------------------------
    // Carregar os dados do arquivo de Resultados (as medalhas)
    // ---------------------------------------------------------
    
    // A função carregar_resultados (que está no leitura.c)
    Resultado* vetor_resultados = carregar_resultados("results.csv", &qtd_resultados); // tirei aq tbm
    
    // Me previnindo de um possível erro na leitura do arquivo, caso de erro eu vou saber mais facilmente e vou evitar que o código trave ou de merda
    if (vetor_resultados == NULL) {
        printf("Falha ao ler results.csv\n");
        return;
    }

    // ---------------------------------------------------------
    // Carregar os dados do arquivo bios.csv(Atletas)
    // ---------------------------------------------------------
    Atleta* vetor_atletas = carregar_atletas("bios.csv", &qtd_atletas); // tirei o .. pq POR ALGUM MOTIVO A LOGICA DO #INCLUDE É DIFERENTE, ent tava dando erro na leitura :/

    // Verificação de segurança para o segundo arquivo
    if (vetor_atletas == NULL) {

        // Me previnindo de um possível erro na leitura do arquivo, caso de erro eu vou saber mais facilmente e vou evitar que o código trave ou de merda
        printf("Falha ao ler bios.csv.\n"); 
        free(vetor_resultados); // Libera o que já tínhamos carregado antes de sair
        return;

    }

    // ---------------------------------------------------------
    // Criar o Mapa para contagem
    // ---------------------------------------------------------

    // Usei calloc em vez de malloc
    // Diferença: O calloc já deixa tudo com zeros, enquanto o malloc deixa lixo de memória (valores aleatórios) que podem causar erros se não forem inicializados
    // A lógica aqui é: O índice do vetor será o ID do atleta
    // Ex: mapa_ouros[10] guarda quantas medalhas o atleta de ID 10 tem
    int* mapa_ouros = (int*) calloc(MAX_MAPA_ID, sizeof(int));

    if (mapa_ouros == NULL) {
        printf("Memoria RAM insuficiente para criar o mapa\n");
        free(vetor_resultados);
        free(vetor_atletas);
        return;
    }

    // ---------------------------------------------------------
    // Contar Medalhas de Ouro
    // ---------------------------------------------------------
    printf("--> Processando medalhas de ouro...\n");
    int ouros_encontrados = 0;

    // Loop que passa por todas as linhas do arquivo de resultados
    for (int acumulado = 0; acumulado < qtd_resultados; acumulado++) {
        
        // Verifica se os campos NOC (País) e Medal não estão vazios ou corrompidos
        if (vetor_resultados[acumulado].noc[0] != '\0' && vetor_resultados[acumulado].medal[0] != '\0') {
            
            // Compara se o país é o que queremos (ex: BRA) e se a medalha é de ouro
            // strcmp retorna 0 se as strings forem iguais
            if (strcmp(vetor_resultados[acumulado].noc, pais_alvo) == 0 && 
                strcmp(vetor_resultados[acumulado].medal, "Gold") == 0) {
                
                // Pega o ID do atleta que ganhou essa medalha
                int id = vetor_resultados[acumulado].athlete_id;

                // Proteção: Só acessa o vetor se o ID for válido
                if (id >= 0 && id < MAX_MAPA_ID) {
                    mapa_ouros[id]++; // Adiciona +1 medalha para esse ID
                    ouros_encontrados++;
                }
            }
        }
    }
    printf("--> Total de medalhas de ouro do %s encontradas: %d\n", pais_alvo, ouros_encontrados);

    // ---------------------------------------------------------
    // Verificar Sexo
    // ---------------------------------------------------------
    printf("--> Verificando generos dos multi-medalhistas...\n");
    
    int homens_multi = 0;   // Contador final de homens
    int mulheres_multi = 0; // Contador final de mulheres

    // Agora percorre a lista de atletas (bios.csv)
    for (int acumulador = 0; acumulador < qtd_atletas; acumulador++) {
        
        int id = vetor_atletas[acumulador].id; // Pega o ID do atleta atual

        // Checa o mapa, se esse ID acumulou MAIS DE 1 medalha de ouro
        if (id >= 0 && id < MAX_MAPA_ID && mapa_ouros[id] > 1) {
            
            // Se sim, pega o sexo dele
            char* sexo = vetor_atletas[acumulador].sex;

            // Verifica se é Homem 
            if (strcmp(sexo, "Male") == 0) {
                homens_multi++;
            } 
            // Verifica se é Mulher
            else if (strcmp(sexo, "Female") == 0) {
                mulheres_multi++;
            }

            // IMPORTANTE:
            // Zero o contador desse atleta no mapa
            // Motivo: Se o atleta aparecer duplicado no arquivo bios.csv (acontece KK),
            // ele não contara duas vezes, pois na segunda vez o valor sera 0.
            mapa_ouros[id] = 0; 
        }
    }

    // ---------------------------------------------------------
    // Exibir Resultados e Limpar Memoria (menu q sera usado dps)
    // ---------------------------------------------------------
    printf("\n#######################################\n");
    printf("RESULTADO FINAL - %s\n", pais_alvo);
    printf("Homens com mais de 1 Ouro:   %d\n", homens_multi);
    printf("Mulheres com mais de 1 Ouro: %d\n", mulheres_multi);
    printf("#######################################\n");

    // Gera o gráfico usando Gnuplot
    if (homens_multi > 0 || mulheres_multi > 0) {
        gerar_grafico_gnuplot(pais_alvo, homens_multi, mulheres_multi);
    } else {
        printf("Nenhum atleta do %s conquistou mais de uma medalha de ouro.\n", pais_alvo);
    }

    // Free libera a memória RAM que o calloc pegou
    // É boa prática sempre limpar a memoria antes de sair. (Evitar vazamentos de memória para não dar merda)
    free(vetor_resultados);
    free(vetor_atletas);
    free(mapa_ouros);
}

