#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>
#include <conio.h>

typedef struct nodo{
    int cantApariciones;
    char palabra[10];   //s1=00000; s2=00001
    struct nodo * sig;
}nodo;

typedef struct nodo* TLista;

typedef struct nodoSF{// nodo ShannonFano
    float probabilidad;
    char simbolo[10];
    char codificacion[20];
    struct nodoSF * sig;
} nodoSF;

typedef nodoSF * TListaSF;

void CargaLista(TLista *L, int cantCaracteres,int *cantPalabras);
void AgregaPalabra(TLista *L, char pal[]);
void MuestraLista(TLista L);
void MuestraCantidadInformacion(TLista L,int total);

void CargaMatriz(float mat[][4]);
int Valor(char simbolo[10]);
void IncisoA();
void IncisoB();
void IncisoD();
void OrdenaPorProbabilidad(TLista *L,int cantTotalApariciones,TListaSF *LSF);
void MuestraListaSF(TListaSF L);
void ShannonFano(TListaSF L, int i);

int main()
{
    char opcion;
    //Menu
    do{
        system("cls");
        printf("\nIngrese letra de inciso a ejecutar (a, b, c) o f para salir: ");
        scanf("%c",&opcion);
        switch (opcion){
        case 'a':
            IncisoA();
        break;
        case 'b':
            IncisoB();
        break;
        case 'c':
            //IncisoA();
        break;
        case 'd':
            IncisoD();
        break;
        }
    }while(opcion!='f');






    return 0;
}

void IncisoD(){

    TLista Palabras5=NULL,Palabras7=NULL,Palabras9=NULL;
    TListaSF ShannonFano5=NULL;//,ShannonFano7=NULL,ShannonFano9=NULL;
    int cantPal5,cantPal7,cantPal9;
    int escenario;

    printf("\nInciso D\nIngrese el escenario (1, 2 o 3): ");
    scanf("%d",&escenario);

    switch(escenario){
    case 1:
        CargaLista(&Palabras5,5,&cantPal5);
        OrdenaPorProbabilidad(&Palabras5,cantPal5,&ShannonFano5);
        //OrdenaPorApariciones(&Palabras5);
        MuestraListaSF(ShannonFano5);
        //ShannonFano();
        printf("\nEscenario 1: Palabras codigo de 5 digitos");
    break;
    case 2:
        CargaLista(&Palabras7,7,&cantPal7);
        //OrdenaPorApariciones(&Palabras7);
        printf("\nEscenario 2: Palabras codigo de 7 digitos");
    break;
    case 3:
        CargaLista(&Palabras9,9,&cantPal9);
        //OrdenaPorApariciones(&Palabras9);
        printf("\nEscenario 3: Palabras codigo de 9 digitos");
    break;
    }
    getch();

}

                            //int i=0;
void ShannonFano(TListaSF L, int i){
    //L->codificacion[i]='1';
    TListaSF act=L;
    float acum=0;
    while(act!=NULL){
        acum+=act->probabilidad;


    }
    if(i==0){
    }

}
void MuestraListaSF(TListaSF L){

    while(L!=NULL){
        printf("\n[%s]=%6.4f",L->simbolo, L->probabilidad);
        L=L->sig;
    }
}


void OrdenaPorProbabilidad(TLista *L,int cantTotalApariciones,TListaSF *LSF){
    //de mayor a menor
    TLista act=(*L);
    int n=0;
    nodo vector[1000];
    while(act!=NULL){
        vector[n]= (*act);
        n++;
        act=act->sig;
    }

    nodo aux;
    for(int i=0; i<n;i++){//Ordena vector por burbujeo
        for(int j=0; j<n-1; j++){
            if(vector[j].cantApariciones<vector[j+1].cantApariciones){
                aux=vector[j];
                vector[j]=vector[j+1];
                vector[j+1]=aux;
            }
        }
    }

    TListaSF nuevo,ultimo=NULL;
    for(int i=0; i<n; i++){
        nuevo=(TListaSF)malloc(sizeof(nodoSF));
        nuevo->probabilidad= (float)(vector[i].cantApariciones) / (float)cantTotalApariciones;
        nuevo->sig=NULL;
        strcpy(nuevo->simbolo,vector[i].palabra);
        if(ultimo==NULL){
            (*LSF)=nuevo;
        }
        else{
            ultimo->sig=nuevo;
        }
        ultimo=nuevo;
    }


}

void IncisoB(){
    //---Inciso B------
    printf("\nInciso B");
    float mat [4][4]={{0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0}};

    CargaMatriz(mat);
    printf("\nMatriz de probabilidades condicionales:");
    printf("\n\n\t00\t\t01\t\t10\t\t11");
    printf("\n\t--------------------------------------------------------");

    for(int i=0; i<4; i++){
        printf("\n");
        if(i<2)
            printf("0");
        else
            printf("1");
        if(i%2==0)
            printf("0  |");
        else
            printf("1  |");
        for(int j=0; j<4; j++){
            printf("\t%8.6f",mat[i][j]);
        }
    }
    getch();
}

void IncisoA(){
    TLista Palabras5=NULL,Palabras7=NULL,Palabras9=NULL;
    int cantPal5,cantPal7,cantPal9;
    int escenario;

    printf("\nInciso A\nIngrese el escenario (1, 2 o 3): ");
    scanf("%d",&escenario);

    switch(escenario){
    case 1:
        CargaLista(&Palabras5,5,&cantPal5);
        printf("\nEscenario 1: Palabras codigo de 5 digitos");
        MuestraCantidadInformacion(Palabras5,cantPal5);
    break;
    case 2:
        CargaLista(&Palabras7,7,&cantPal7);
        printf("\nEscenario 2: Palabras codigo de 7 digitos");
        MuestraCantidadInformacion(Palabras7,cantPal7);
    break;
    case 3:
        CargaLista(&Palabras9,9,&cantPal9);
        printf("\nEscenario 3: Palabras codigo de 9 digitos");
        MuestraCantidadInformacion(Palabras9,cantPal9);
    break;
    }
    getch();
}

int Valor(char simbolo[10]){
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
        ant=Valor(simbolo);

        while(fscanf(archt,"%c",&aux)==1){
            i++;
            //printf("\n%c",aux);
            if(i==(cantCaracteres)){
                simbolo[cantCaracteres]='\0';
                act=Valor(simbolo);
                mat[act][ant]++;            //ant es j
                cantidadesTotales[ant]++;   //act es i
                ant=act;
                i=0;
            }
            simbolo[i]=aux;
        }

        simbolo[cantCaracteres]='\0';
        act=Valor(simbolo);
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
    float prob,entropia=0,inf;
    printf("\n\tSimbolo\t\tInformacion");
    while(L!=NULL){
        prob=(float)(L->cantApariciones)/(float)total;
        //printf("\n\nP(%s)=%f",L->palabra,prob);
        //printf("\n%d",L->cantApariciones);
        inf=(-log(prob)/log(2));
        printf("\n\t%s\t\t%f",L->palabra, inf );
        entropia+= (prob * inf);
        L=L->sig;
    }
    printf("\n\nEntropia=%f\n",entropia);
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

