#ifndef STRUCTS_H
#define STRUCTS_H


// esse arquivo de struct serve de auxiliar para as questões, diminuindo as linhas de código que seriam repetidas de forma desnecessária

typedef struct {
    int id;           
    char name[150];    
    char noc[10];      
} Atleta;

typedef struct {
    int year;                   
    char event[300];  
    int athlete_id;    
    char noc[10];      
    char medal[15];
} Resultado;

typedef struct {
    char noc[10];  
    int qtd_ouros;          
    int qtd_pratas;
    int qtd_bronzes;
    int total_medalhas;     
    int pontuacao_total;    
} PaisStats;

typedef struct {
    int athlete_id;
    char gender;            
    int count_gold;
    int participated;       
} AtletaStats;

#endif