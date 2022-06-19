#include <stdio.h>
#include <stdlib.h>
#include "Arbol.h"

int comparaLetras(const void* l1,const void* l2){
    return *(char*)l1-*(char*)l2;
}
void imprimeCaracteres(const void* l1,const void* datosImprimir, const int nivel){
    int i;
    for(i=0;i<nivel;i++){
        printf("\t");
    }
    printf("%c\n",*(char*)l1);
}

int main(){

    FILE* pfLetras = fopen("letras.txt","rt");
    char lineaLetras[25];
    Arbol arbolLetras;
    crearArbol(&arbolLetras);


    fgets(lineaLetras,25,pfLetras);
    int i=0;
    while(lineaLetras[i]!='\0' && lineaLetras[i]!='\n'){
        insertarEnArbolOrdenado(&arbolLetras,&lineaLetras[i],sizeof(char),comparaLetras);
        i++;
    }

    imprimeArbolEnPantalla(&arbolLetras,imprimeCaracteres,NULL);
    char aux = 'l';
    eliminarDeArbol(&arbolLetras,&aux,sizeof(char),comparaLetras);
    printf("--------------------------------------------\n");
    imprimeArbolEnPantalla(&arbolLetras,imprimeCaracteres,NULL);

    aux = 'a';
    eliminarDeArbol(&arbolLetras,&aux,sizeof(char),comparaLetras);
    printf("--------------------------------------------\n");
    imprimeArbolEnPantalla(&arbolLetras,imprimeCaracteres,NULL);

    aux = 'd';
    eliminarDeArbol(&arbolLetras,&aux,sizeof(char),comparaLetras);
    printf("--------------------------------------------\n");
    imprimeArbolEnPantalla(&arbolLetras,imprimeCaracteres,NULL);

    aux = 'h';
    eliminarDeArbol(&arbolLetras,&aux,sizeof(char),comparaLetras);
    printf("--------------------------------------------\n");
    imprimeArbolEnPantalla(&arbolLetras,imprimeCaracteres,NULL);
}
