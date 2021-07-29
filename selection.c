#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>  
#include <sys/resource.h>
#define MAX 25000//valor máximo de n
#define MIN 1000//valor mínimo de n
#define PASSO 100//tamanho do passo
#define RMAX 2000//valor máximo que pode ser sorteado
#define MED 5//o tempo de ordenacao do vetor eh contado 5 vezes
//lista encadeada
typedef struct no{
        int n;
        struct no* prox;
}No;
No* insereNo(No* l,int x){
    No* aux=(No*)malloc(sizeof(No));
    aux->n=x;
    aux->prox=l;
    return aux;
}
void libera(No *l){
    if (l)
    {   No* temp=l->prox;
        free(l);
        libera(temp);
    }   
}
No* criaLista(No* l,int tam,int seed){
    srand(seed);
    for(int i=0;i<tam;i++){
      l=insereNo(l,rand()%(RMAX+1)); 
    }
    return l;
}
No* criaListaTipo2(No* l,int tam,int seed){  
    srand(seed);
    for(int i=0;i<tam;i++){
      l=insereNo(l,rand()%((tam*tam)+1)); 
    }
    return l;
}
//contador cpu
void Tempo_CPU_Sistema(double *seg_CPU_total, double *seg_sistema_total)
{
  long seg_CPU, seg_sistema, mseg_CPU, mseg_sistema;
  struct rusage ptempo;

  getrusage(0,&ptempo);

  seg_CPU = ptempo.ru_utime.tv_sec;
  mseg_CPU = ptempo.ru_utime.tv_usec;
  seg_sistema = ptempo.ru_stime.tv_sec;
  mseg_sistema = ptempo.ru_stime.tv_usec;

 *seg_CPU_total     = (seg_CPU + 0.000001 * mseg_CPU);
 *seg_sistema_total = (seg_sistema + 0.000001 * mseg_sistema);
}
//algoritmo analisado
void selection(No* l, int tam) { 
  No* aux,*aux2,*min;
  int temp;
  aux=l;
  for (int i = 0; i < (tam-1); i++) 
  { 
    aux2=aux->prox;
    min=aux;
    for (int j = (i+1); j < tam; j++) {
        if (aux2->n<min->n)
        {
            min=aux2;
        }
        aux2=aux2->prox;
    }
    temp=aux->n;
    aux->n=min->n;
    min->n=temp;
    aux=aux->prox;
  }
}
//medicao do tempo
double guardaTempo(No *l,int tam){
    double s_CPU_inicial,s_CPU_final,s_total_inicial,s_total_final;
    Tempo_CPU_Sistema(&s_CPU_inicial, &s_total_inicial);
    selection(l,tam);
    Tempo_CPU_Sistema(&s_CPU_final, &s_total_final);
    return s_CPU_final - s_CPU_inicial;
}
//arquivo
void imprimeTxt(No *l,FILE *f){//gera o registro das listas
    if (l)
    {   No* temp=l->prox;
        fprintf(f,"%d\n",l->n);
        imprimeTxt(temp,f);
    }   
}
void imprimeTxtaux(No *l,char *nome, int tam){
    FILE *f;
    f = fopen(nome, "w");
    fprintf(f,"#N=%d\n",tam);
    imprimeTxt(l,f);
    fclose(f);   
}
void geraArq(char*nome,char*aux,char* parte,char* graf,char* graf2){
    No* lista=NULL;
    double total=0;
    int tam;
    FILE *f;
    int cont=0;
    int arraySeeds[] = {2000, 566, 30610, 134, 2001};
    for (int z = 0; z < 2; z++)
    {
        for (int j = 0; j <= (MAX-MIN)/PASSO; j++)
        {
            for (int i = 0; i < MED; i++)
            {   tam=MIN+j*PASSO;
                if(z==0)lista=criaLista(lista,tam,arraySeeds[i]);
                else lista=criaListaTipo2(lista,tam,arraySeeds[i]);
                strcpy(aux,nome);
                sprintf(parte,"%d",cont);
                imprimeTxtaux(lista,strcat(aux,parte),tam);
                total+=guardaTempo(lista,tam);
                libera(lista);
                lista=NULL;
                printf ("%d\n",cont);
                cont++;
            }
            //gera o registro dos tempos 
            if(z==0){
                f = fopen(graf, "a");
                fprintf (f,"%d  %f\n",tam,total/MED);
                fclose(f);
            }
            else{
                f = fopen(graf2, "a");
                fprintf (f,"%d  %f\n",tam,total/MED);
                fclose(f);
            }
            total=0;
        }
    }
    
}
int main (){
    char nomealg[15]="selection";
    char nomegraf[20]="selectionTime";
    char nomegraf2[20]="selectionTime2";
    char parte[50];
    char aux[50];
    geraArq(nomealg,aux,parte,nomegraf,nomegraf2);
    return 0;
}