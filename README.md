# Olimpiadas-PI

Seja bem-vindo ao Sistema Olímpico
Nosso Sistema aqui está funcionando para responder quatro questões advindas do projeto de trabalho do professor Kalil Bispo 
Nossos códigos respondem às seguintes questões:
1) Considere 10 países a sua escolha. Crie um ranking dos países com base no número total de medalhas conquistadas. Ordene os países pelo total de medalhas
2) Para um determinado país, determine a quantidade de atletas do sexo masculino e feminino que já participaram das Olimpíadas
3) Para um determinado país, determine o número de atletas do sexo masculino e feminino que conquistaram mais de uma medalha de ouro
4) Considere 10 países. Crie um ranking ordenado pela pontuação de medalhas, em que Ouro vale 3 pontos, Prata vale 2 pontos e Bronze vale 1 ponto

Além das respostas, oferecemos criação de gráficos de torre para cada questão.

Para conseguir acessar nosso Menu personalizado, basta ter os abri-lo no visual code studio e ter os arquivos csv necessários para resposta (results.csv e bios.csv) na mesma pasta de menu.c
Com isso, basta a você digitar no terminal:
gcc menu.c src/leitura.c src/questao1.c src/questao2.c src/questao3.c src/questao4.c -I include -o programa_final.exe
.\'programa_final.exe'

À sua opção, caso queira abrir o sistema em uma aba totalmente separada, recomendo seguir este método:
Com o menu aberto, aperte Ctrl + Shift + B
Em seguida, acesse a área de Executar e Depurar do VSCode (Ctrl + Shift + D) e dê play no Rodar Menu Olimpico
