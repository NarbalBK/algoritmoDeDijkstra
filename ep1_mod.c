/*          Exercicio Programa
 Implementação do algoritmo de Dijkstra em C
 Alunos: Álvaro, Ângelo, Péricles e Suzane
 Data de entrega: 11/04/2019              */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200
#define INFINITO 99999


// Prototipos de funções
FILE *abreArquivo (char diretorio[100], FILE *arquivo);
int *alocaLista (int *vertices, int *listaDeAdjacencias);
void leArquivo (FILE *arquivo, int *vertices, int *arcos, int *origem, int *destino);
int *preencheLista (FILE *arquivo, int *listaDeAdjacencias, int *vertices, int *arcos, int *destino);
void dijkstra(int Vert, int Orig, int Dest, int *Valor);

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
    
    dijkstra(vertices, origem, destino, listaDeAdjacencias);
    
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
    //aloca o espa√ßo necess√°rio na memoria
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
}
//Fim de preencheLista


//Inicio dijkstra
void dijkstra(int Vert, int Orig, int Dest, int *Valor){
    int i = 0;            // contador
    int v = 0;         // auxiliar vÈrtice v
    int ant[MAX];     // vetor dos predecessores
    int z[MAX];       // vÈrtices para os quais se conhece o caminho mÌnimo
    double min;        // auxiliar
    double dist[MAX]; // custos dos caminhos
    
    for(i = 0; i < Vert; i++){
        if(Valor[i] != -1){
            ant[i] = Orig-1;
            dist[i] = Valor[i];
        }
        else{
            ant[i] = -1;
            dist[i] = INFINITO;
        }
        z[i] = 0;
    }
    z[Orig-1] = 1;
    dist[Orig-1] = 0;
    
    //Insere o novo vÈrtice em z
    while(v != Dest-1 && min != INFINITO){
        min = INFINITO;
        
        for(i = 0; i < Vert; i++){
            if(z[i] == 0){
                if(dist[i] >= 0 && dist[i] < min){
                    min = dist[i];
                    v = i;
                }
            }
        }
        
        //Dist‚ncias dos novos vizinhos de z
        if(min != INFINITO && v != Dest-1){
            z[v] = 1;
            for(i = 0; i < Vert; i++)
                if(z[i] == 0){
                    if(Valor[v*Vert+i] != -1 && dist[v]+Valor[v*Vert+i] < dist[i]){
                        dist[i] = dist[v]+Valor[v*Vert+i];
                        ant[i] = v;
                    }
                }
        }
    }//Fim de while(v != destino-1 && min != INFINITO)
    
    //Imprime caminho mÌnimo de origem a destino
    if(min == INFINITO)
        printf("\nNão existe caminho do vertive %d para %d.\n", Orig, Dest);
    else{
        printf("\nO Caminho mínimo de %d para o vértice %d é \n",
               Orig, Dest);
        
        i = Dest;
        printf("%d", i);
        i = ant[i-1];
        
        while(i !=-1) {
            printf(" <- %d", i+1);
            i = ant[i];
        }
        printf("\nCusto = %d\n", (int)dist[Dest-1]);
    }
}//dijkstra
