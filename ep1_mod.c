/*          Exercicio Programa
 Implementação do algoritmo de Dijkstra em C
 Alunos: Álvaro, Ângelo, Péricles e Suzane
 Data de entrega: 11/04/2019              */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 150        //tem que mudar esse negocio
#define INFINITO 10000  //tem que mudar esse negocio


// Prototipos de funções
//void dijkstra(int vertices, int origem, int destino, int *custos);
FILE *abreArquivo (char diretorio[100], FILE *arquivo);
int *alocaLista (int *vertices, int *listaDeAdjacencias);
void leArquivo (FILE *arquivo, int *vertices, int *arcos, int *origem, int *destino);
int *preencheLista (FILE *arquivo, int *listaDeAdjacencias, int *vertices, int *arcos, int *destino);

// Inicio da main
int main(void){
    
    int arcos = 0;                  //qtd de arcos do grafo
    int vertices = 0;               //qtd de vertices do grafo
    int origem = 0;                 //vertice origem do caminho
    int destino = 0;                //vertice destino do caminho
    int *listaDeAdjacencias = NULL; //grafo no formato de L.A
    
    FILE *arquivo = NULL;
    char diretorio[100] = "";
    
    arquivo = abreArquivo(diretorio, arquivo);
    leArquivo(arquivo, &vertices, &arcos, &origem, &destino);
    listaDeAdjacencias = alocaLista(&vertices, listaDeAdjacencias);
    listaDeAdjacencias = preencheLista(arquivo, listaDeAdjacencias, &vertices, &arcos, &destino);
    
    //dijkstra(vertices, origem, destino, custos);
    
    return 0;
}
// Fim da main


// Inicio de abreArquivo
FILE *abreArquivo (char diretorio[100], FILE *arquivo){
    while(arquivo == NULL){
        puts("Insira o diretorio do arquivo");
        fgets(diretorio, (sizeof(char)*(100)), stdin);
        //remove o caracter \n da string
        char *remove = strchr(diretorio, '\n');
        if (remove != NULL){
            *remove = '\0';
        };
        arquivo = fopen(diretorio, "r");
    }
    return arquivo;
}
//Fim de abreArquivo


//Inicio de leArquivo
void leArquivo (FILE *arquivo, int *vertices, int *arcos, int *origem, int *destino){
    //ler o arquivo e atribui os valores
    fscanf(arquivo, "%d %d %d %d", vertices, arcos, origem, destino);
}
//Fim de leArquivo


//Inicio de alocaLista
int *alocaLista (int *vertices, int *listaDeAdjacencias){
    free(listaDeAdjacencias);
    //aloca o espaço necessário na memoria
    listaDeAdjacencias = malloc(sizeof(int)*(*vertices)*(*vertices));
    for(int i = 0; i <= ((*vertices)*(*vertices)); i++){
        listaDeAdjacencias[i] = -1;
    }
    return listaDeAdjacencias;
}
// Fim de alocaLista


//Inicio de preencheLista
int *preencheLista (FILE *arquivo, int *listaDeAdjacencias, int *vertices, int *arcos, int *destino){
    for(int j = 0; j < *arcos; j++){
        int u = 0, v = 0;
        fscanf(arquivo, "%d %d", &u, &v);
        //preenche a lista de adjacencias
        fscanf(arquivo, "%d", &listaDeAdjacencias[(u-1)*(*vertices)+v-1]);
    }
    fclose(arquivo);
    return listaDeAdjacencias;
} //Fim de preencheLista






