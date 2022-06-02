#include <stdio.h>
#include <stdlib.h>
#define TDA_ARBOL_IMP_DINAMICA
#include "..\TDA\Arbol\Arbol.h"

int comparaEnteros(const void* d1,const void* d2){
    return *(int*)d1 - *(int*)d2;
}

void imprimeEnteroArbol(void* d1,void* datos,int nivel);

int main(){

    Arbol miArbol;
    crearArbol(&miArbol);
    int i;
    int elems[] = {50,20,10,5,7,15,13,70,60,55,85,73,90};
    //int elems[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    //int elems[] = {7,4,2,1,3,5,6,11,12,13,9,8,10};
    for(i=0;i<13;i++){
        insertarEnArbol(&miArbol,&elems[i],sizeof(int),comparaEnteros,NULL);
    }

    imprimirArbol(&miArbol,imprimeEnteroArbol,NULL);

    return 0;
}

void imprimeEnteroArbol(void* d1,void* datos,int nivel){
    int i;

    for(i=0;i<nivel;i++){
        printf("\t");
    }

    printf("%d\n",*(int*)d1);
}
