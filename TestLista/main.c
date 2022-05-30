#include <stdio.h>
#include <stdlib.h>

#define LISTA_IMP_DINAMICA

#include "..\TDA\Lista\Lista.h"

int comparaEntero(const void* d1,const void* d2){

    return *((int*)d1)-*((int*)d2);

}

int imprimeEntero(const void* d1,const void* datos){

    printf("%d ",*(int*)d1);
    return 0;
}

int sumaAElementos(const void* d1,const void* datos){

    *(int*)d1+= *(int*)datos;
    return 0;

}


int main(){

    Lista miLista;

    crearLista(&miLista);
    int a = 2;
    int b = 7;
    int c = 7;
    int d = 7;
    int e = 7;
    int f = 7;
    int aux=0;
    Iterador it;


//    insertarEnListaOrdenada(&miLista,&d,sizeof(int),comparaEntero);
//    insertarEnListaOrdenada(&miLista,&a,sizeof(int),comparaEntero);
//    insertarEnListaOrdenada(&miLista,&c,sizeof(int),comparaEntero);
//    insertarEnListaOrdenada(&miLista,&b,sizeof(int),comparaEntero);

    insertarEnListaFondo(&miLista,&a,sizeof(int));
    insertarEnListaFondo(&miLista,&b,sizeof(int));
    insertarEnListaFondo(&miLista,&c,sizeof(int));
    insertarEnListaFondo(&miLista,&d,sizeof(int));
    insertarEnListaFondo(&miLista,&e,sizeof(int));
    insertarEnListaFondo(&miLista,&f,sizeof(int));

    recorrerLista(&miLista,imprimeEntero,NULL);
    printf("\n");
    //ordenarLista(&miLista,comparaEntero);
    eliminarDuplicados(&miLista,comparaEntero);

    recorrerLista(&miLista,imprimeEntero,NULL);
//    printf("\n");
//    recorrerLista(&miLista,sumaAElementos,&a);
//    recorrerLista(&miLista,imprimeEntero,NULL);

//    crearIterador(&it,&miLista);
//
//    primeroDeLista(&it,&aux,sizeof(int));
//    while(haySiguienteDeLista(&it)){
//        printf("%d ",aux);
//        siguienteDeLista(&it,&aux,sizeof(int));
//    }
//    printf("%d ",aux);


    return 0;

}
