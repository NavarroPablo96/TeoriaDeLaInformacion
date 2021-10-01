#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>
#include <conio.h>

typedef struct nodo{
    int cantApariciones;
    char palabra[10];
    struct nodo * sig;
}nodo;

typedef struct nodo* TLista;

typedef struct nodoSF{
    float probabilidad;
    char simbolo[10];
    char codificacion[20];
} nodoSF;



void CargaLista(TLista *L, int cantCaracteres,int *cantPalabras);
void AgregaPalabra(TLista *L, char pal[]);
void MuestraLista(TLista L);
void MuestraCantidadInformacion(TLista L,int total,FILE *archt);

void CargaMatriz(float mat[][4]);
int Valor(char simbolo[10]);
void IncisoA();
void IncisoB();
void IncisoD();
void OrdenaPorProbabilidad(TLista *L,int cantTotalApariciones,nodoSF vector[],int *n);
void MuestraSF(nodoSF vec[],int n);
void ImprimeSF(nodoSF vec[],int n, FILE *archt);
void ShannonFano(nodoSF vector[], int limInf, int limSup);
void ReconstruyeArch(nodoSF vector[], int n, int cantCaracteres,char nombre_Arch[20]);

int main()
{
    char opcion;
    //Menu
    do{
        system("cls");
        printf("\nIngrese letra de inciso a ejecutar (a, b, d) o f para salir: ");
        scanf("%c",&opcion);
        switch (opcion){
        case 'a':
            IncisoA();
        break;
        case 'b':
            IncisoB();
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
    nodoSF ShannonFano5[1000],ShannonFano7[1000],ShannonFano9[1000];
    int cantPal5,cantPal7,cantPal9;
    int escenario;

    printf("\nInciso D\nIngrese el escenario (1, 2 o 3): ");
    scanf("%d",&escenario);

    FILE *archt;
    switch(escenario){
    case 1:
        archt=fopen("Inciso_D_Escenario1.txt","wt");

        printf("\nEscenario 1: Palabras codigo de 5 digitos");
        fprintf(archt,"Escenario 1: Palabras codigo de 5 digitos");
        CargaLista(&Palabras5,5,&cantPal5);
        int n5;
        OrdenaPorProbabilidad(&Palabras5,cantPal5,ShannonFano5,&n5);
        ShannonFano(ShannonFano5,0,n5);
        printf("\nLa codificacion resultante de Shannon-Fano es:");
        fprintf(archt,"\nLa codificacion resultante de Shannon-Fano es:");
        ImprimeSF(ShannonFano5,n5,archt);
        MuestraSF(ShannonFano5,n5);
        ReconstruyeArch(ShannonFano5,n5,5,"reconstruccion_caso1.txt");

        fclose(archt);
    break;
    case 2:
        archt=fopen("Inciso_D_Escenario2.txt","wt");

        printf("\nEscenario 2: Palabras codigo de 7 digitos");
        fprintf(archt,"Escenario 2: Palabras codigo de 7 digitos");
        CargaLista(&Palabras7,7,&cantPal7);
        int n7;
        OrdenaPorProbabilidad(&Palabras7,cantPal7,ShannonFano7,&n7);
        ShannonFano(ShannonFano7,0,n7);
        printf("\nLa codificacion resultante de Shannon-Fano es:");
        fprintf(archt,"\nLa codificacion resultante de Shannon-Fano es:");
        MuestraSF(ShannonFano7,n7);
        ImprimeSF(ShannonFano7,n7,archt);
        ReconstruyeArch(ShannonFano7,n7,7,"reconstruccion_caso2.txt");
        fclose(archt);
    break;
    case 3:
        archt=fopen("Inciso_D_Escenario3.txt","wt");
        printf("\nEscenario 3: Palabras codigo de 9 digitos");
        fprintf(archt,"Escenario 3: Palabras codigo de 9 digitos");
        CargaLista(&Palabras9,9,&cantPal9);
        int n9;
        OrdenaPorProbabilidad(&Palabras9,cantPal9,ShannonFano9,&n9);
        ShannonFano(ShannonFano9,0,n9);
        printf("\nLa codificacion resultante de Shannon-Fano es:");
        fprintf(archt,"\nLa codificacion resultante de Shannon-Fano es:");
        MuestraSF(ShannonFano9,n9);
        ImprimeSF(ShannonFano9,n9,archt);
        ReconstruyeArch(ShannonFano9,n9,9,"reconstruccion_caso3.txt");
        fclose(archt);
    break;
    }
    getch();
}

int posSimbolo(char simbolo[10],nodoSF vector[],int n){
    int i=0;
    while(i<n && strcmp(simbolo,vector[i].simbolo)!=0){
        i++;
    }
    return i;
}

void ReconstruyeArch(nodoSF vector[], int n, int cantCaracteres,char nombre_Arch[20]){
    FILE *archt,*archtnuevo;
    archt=fopen("datos para tp1.txt","rt");
    char aux,palabra[20]="";
    int i=-1,pos;
    if(archt==NULL){
        printf("No existe el archivo");
    }
    else{
        archtnuevo=fopen(nombre_Arch,"wt");
        while(fscanf(archt,"%c",&aux)==1){
            i++;
            if(i==(cantCaracteres)){
                palabra[cantCaracteres]='\0';
                pos=posSimbolo(palabra,vector,n);
                fprintf(archtnuevo,"%s",vector[pos].codificacion);
                i=0;
            }
            palabra[i]=aux;
        }
        palabra[cantCaracteres]='\0';
        pos=posSimbolo(palabra,vector,n);
        fprintf(archtnuevo,"%s",vector[pos].codificacion);
        fclose(archtnuevo);
    }

    fclose(archt);
}


void ShannonFano(nodoSF vector[], int limInf, int limSup){
    int i;
    float totProb = 0, probAcum = 0;

    if(limInf != (limSup-1)){
        for(i=limInf; i<limSup; i++)
            totProb+= vector[i].probabilidad;
        i = limInf;
        while(probAcum < (totProb/2)){
            probAcum+= vector[i].probabilidad;
            strcat((vector[i].codificacion),"1");
            i++;
        }
        ShannonFano(vector,limInf,i);
        int j = i;
        while(probAcum < totProb){
            probAcum += vector[j].probabilidad;
            strcat(vector[j].codificacion,"0");
            j++;
        }
        ShannonFano(vector,i,limSup);
    }
}


void MuestraSF(nodoSF vec[],int n){
    printf("\n\n\tsimbolo\t\tprobabilidad\tcodificacionSF");
    for(int i=0; i<n; i++){
        printf("\n\t%s\t\t%6.4f\t\t%10s",vec[i].simbolo, vec[i].probabilidad,vec[i].codificacion);
    }
}
void ImprimeSF(nodoSF vec[],int n, FILE *archt){
    fprintf(archt,"\n\n\t   simbolo\t\tprobabilidad\tcodificacionSF");
    for(int i=0; i<n; i++){
        fprintf(archt,"\n\t%10s\t\t\t%6.4f\t\t%10s",vec[i].simbolo, vec[i].probabilidad,vec[i].codificacion);
    }
}


void OrdenaPorProbabilidad(TLista *L,int cantTotalApariciones,nodoSF vector[],int *n){
    //de mayor a menor
    TLista act=(*L);
    (*n)=0;

    while(act!=NULL){
        vector[(*n)].probabilidad= (float)(act->cantApariciones)/ (float)cantTotalApariciones;
        strcpy(vector[(*n)].simbolo,act->palabra);
        strcpy(vector[(*n)].codificacion,"");
        (*n)++;
        act=act->sig;
    }

    nodoSF aux;
    for(int i=0; i<(*n);i++){//Ordena vector por burbujeo
        for(int j=0; j<(*n)-1; j++){
            if(vector[j].probabilidad<vector[j+1].probabilidad){
                aux=vector[j];
                vector[j]=vector[j+1];
                vector[j+1]=aux;
            }
        }
    }
}

void IncisoB(){
    FILE *archt;
    archt=fopen("Inciso_B.txt","wt");

    printf("\nInciso B");
    fprintf(archt,"Inciso B");
    float mat [4][4]={{0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0}};

    CargaMatriz(mat);
    printf("\nMatriz de probabilidades condicionales:");
    printf("\n\n\t00\t\t01\t\t10\t\t11");
    printf("\n\t--------------------------------------------------------");

    fprintf(archt,"\nMatriz de probabilidades condicionales:");
    fprintf(archt,"\n\n\t00\t\t01\t\t10\t\t11");
    fprintf(archt,"\n\t--------------------------------------------------------");
    for(int i=0; i<4; i++){
        printf("\n");
        fprintf(archt,"\n");
        if(i<2){
            printf("0");
            fprintf(archt,"0");
        }
        else{
            printf("1");
            fprintf(archt,"1");
        }
        if(i%2==0){
            printf("0  |");
            fprintf(archt,"0    |");
        }
        else{
            printf("1  |");
            fprintf(archt,"1    |");
        }
        for(int j=0; j<4; j++){
            printf("\t%8.6f",mat[i][j]);
            fprintf(archt,"\t%8.6f",mat[i][j]);
        }
    }
    fclose(archt);
    getch();
}

void IncisoA(){
    TLista Palabras5=NULL,Palabras7=NULL,Palabras9=NULL;
    int cantPal5,cantPal7,cantPal9;
    int escenario;

    printf("\nInciso A\nIngrese el escenario (1, 2 o 3): ");
    scanf("%d",&escenario);

    FILE *archt;
    switch(escenario){
    case 1:
        archt=fopen("Inciso_A_Escenario1.txt","wt");
        CargaLista(&Palabras5,5,&cantPal5);
        printf("\nEscenario 1: Palabras codigo de 5 digitos");
        fprintf(archt,"Escenario 1: Palabras codigo de 5 digitos");
        MuestraCantidadInformacion(Palabras5,cantPal5,archt);
        fclose(archt);
    break;
    case 2:
        archt=fopen("Inciso_A_Escenario2.txt","wt");
        CargaLista(&Palabras7,7,&cantPal7);
        printf("\nEscenario 2: Palabras codigo de 7 digitos");
        fprintf(archt,"Escenario 1: Palabras codigo de 7 digitos");
        MuestraCantidadInformacion(Palabras7,cantPal7,archt);
        fclose(archt);
    break;
    case 3:
        archt=fopen("Inciso_A_Escenario3.txt","wt");
        CargaLista(&Palabras9,9,&cantPal9);
        printf("\nEscenario 3: Palabras codigo de 9 digitos");
        fprintf(archt,"Escenario 1: Palabras codigo de 9 digitos");
        MuestraCantidadInformacion(Palabras9,cantPal9,archt);
        fclose(archt);
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

void MuestraCantidadInformacion(TLista L,int total,FILE *archt){
    float prob,entropia=0,inf;
    printf("\n\tSimbolo\t\tInformacion");
    fprintf(archt,"\n\n\tSimbolo\t\tInformacion");
    while(L!=NULL){
        prob=(float)(L->cantApariciones)/(float)total;
        inf=(-log(prob)/log(2));
        printf("\n\t%s\t\t%f",L->palabra, inf );
        fprintf(archt,"\n\t%s\t\t%f",L->palabra, inf);
        entropia+= (prob * inf);
        L=L->sig;
    }
    printf("\n\nEntropia=%f\n",entropia);
    fprintf(archt,"\n\nEntropia=%f\n",entropia);
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
            if(i==(cantCaracteres)){
                palabra[cantCaracteres]='\0';
                AgregaPalabra(L,palabra);
                i=0;
                (*cantPalabras)++;
            }
            palabra[i]=aux;
        }
        (*cantPalabras)++;
        palabra[cantCaracteres]='\0';
        AgregaPalabra(L,palabra);
    }
    fclose(archt);
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
        act=*L;
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



