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

    return 0;
}

void MuestraCantidadInformacion(TLista L,int total){
    double prob;
    int aux;
    while(L!=NULL){
        //prob=(L->cantApariciones)/total;.
        aux=L->cantApariciones;
        printf("\n%d / %d",(aux),total);
        prob=(aux/total);
        printf("\n%10.8lf",prob);
        //printf("\n I(%s)=%f",L->palabra, L->cantApariciones);

        L=L->sig;
    }

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

