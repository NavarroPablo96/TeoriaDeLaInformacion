#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>

typedef struct nodo{
    int cantApariciones;
    char palabra[10];
    struct nodo * sig;
}nodo;

typedef struct nodo* TLista;

void CargaLista(TLista *L, int cantCaracteres,int *cantPalabras);
void AgregaPalabra(TLista *L, char pal[]);
void MuestraLista(TLista L);
void MuestraCantidadInformacion(TLista L,int total);

void CargaMatriz(float mat[][4]);
int valor(char simbolo[10]);
int main()
{
    TLista Palabras5=NULL,Palabras7=NULL,Palabras9=NULL;
    int cantPal5,cantPal7,cantPal9;

    CargaLista(&Palabras5,5,&cantPal5);
    printf("\nTotal5=%d",cantPal5);
    //MuestraLista(Palabras5);

    CargaLista(&Palabras7,7,&cantPal7);
    printf("\nTotal7=%d",cantPal7);
    //MuestraLista(Palabras7);

    CargaLista(&Palabras9,9,&cantPal9);
    printf("\nTotal9=%d",cantPal9);
    //MuestraLista(Palabras9);

    MuestraCantidadInformacion(Palabras5,cantPal5);

    //---Inciso B------
    printf("\n---Inciso B------");
    float mat [4][4]={{0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0}};



    CargaMatriz(mat);
    int cantidadTotal=0;
    for(int i=0; i<4; i++){
        printf("\n");
        for(int j=0; j<4; j++){
            cantidadTotal+=mat[i][j];
            printf("\t%8.6f",mat[i][j]);
        }
    }
    printf("total= %d",cantidadTotal);

    return 0;
}

int valor(char simbolo[10]){
    if(strcmp(simbolo,"00")==0)
        return 0;
    else if(strcmp(simbolo,"01")==0)
        return 1;
    else if(strcmp(simbolo,"10")==0)
        return 2;
    else if(strcmp(simbolo,"11")==0)
        return 3;

    return 45;
}



void CargaMatriz(float mat[][4]){
    char aux;
    char simbolo[10];
    strcpy(simbolo,"");
    int i=-1,ant,act;
    int cantCaracteres=2;
    float cantidadesTotales[4]={0,0,0,0};

    FILE *archt;
    archt=fopen("datos para tp1.txt","rt");

    if(archt==NULL){
        printf("No existe el archivo");
    }
    else{
        fscanf(archt,"%c",&aux);
        simbolo[0]=aux;
        fscanf(archt,"%c",&aux);
        simbolo[1]=aux;
        simbolo[2]='\0';
        ant=valor(simbolo);

        while(fscanf(archt,"%c",&aux)==1){
            i++;
            //printf("\n%c",aux);
            if(i==(cantCaracteres)){
                simbolo[cantCaracteres]='\0';
                act=valor(simbolo);
                mat[act][ant]++;            //ant es j
                cantidadesTotales[ant]++;   //act es i
                ant=act;
                i=0;
            }
            simbolo[i]=aux;
        }

        simbolo[cantCaracteres]='\0';
        act=valor(simbolo);
        mat[act][ant]++;
        cantidadesTotales[ant]++;

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                mat[j][i] /= cantidadesTotales[i];
            }
        }
    }
}

void MuestraCantidadInformacion(TLista L,int total){
    float prob,entropia=0;
    while(L!=NULL){
        prob=(float)(L->cantApariciones)/(float)total;
        printf("\n\nP(%s)=%f",L->palabra,prob);
        //printf("\n%d",L->cantApariciones);
        printf("\nI(%s)=%f",L->palabra, (-log(prob)/log(2)) );
        entropia+= (prob * (-log(prob)/log(2)));
        L=L->sig;
    }
    printf("\nentropia=%f",entropia);
}

void MuestraLista(TLista L){
    int total=0;
    while(L!=NULL){
        printf("\n[%s]=%d",L->palabra, L->cantApariciones);
        total+=L->cantApariciones;
        L=L->sig;
    }
}

void CargaLista(TLista *L, int cantCaracteres,int *cantPalabras){
    char aux;
    char palabra[10];
    strcpy(palabra,"");
    int i=-1;
    (*cantPalabras)=0;

    FILE *archt;
    archt=fopen("datos para tp1.txt","rt");

    if(archt==NULL){
        printf("No existe el archivo");
    }
    else{
        while(fscanf(archt,"%c",&aux)==1){
            i++;
            //printf("\n%c",aux);
            if(i==(cantCaracteres)){
                palabra[cantCaracteres]='\0';
                AgregaPalabra(L,palabra);
                i=0;
                palabra[i]=aux;
                (*cantPalabras)++;
            }
            else{
                palabra[i]=aux;

            }
        }
        (*cantPalabras)++;
        palabra[cantCaracteres]='\0';
        AgregaPalabra(L,palabra);
    }
}

void AgregaPalabra(TLista *L, char pal[]){
    TLista nuevo,ant,act;
    nuevo= (TLista)malloc(sizeof(nodo));
    nuevo->cantApariciones=1;
    nuevo->sig=NULL;
    strcpy(nuevo->palabra,pal);
    if((*L==NULL)  || strcmp(pal,(*L)->palabra)<0 ){
        nuevo->sig=*L;
        *L=nuevo;
    }
    else{
        ant=NULL;
        act=*L;             //strcmp("aaa","bbb")==-1
        while(act!=NULL && strcmp(act->palabra,pal)<0 ){
            ant=act;
            act=act->sig;
        }
        if(act!=NULL && strcmp(act->palabra,pal)==0){
            free(nuevo);
            act->cantApariciones++;
        }
        else{
            nuevo->sig=act;
            ant->sig=nuevo;
        }
    }
}



//31500 = 5 * 7 * 9 * 100

//32 simbolos para el escenario 1
//128 símbolos para el escenario 2
//512 símbolos para el escenario 3

