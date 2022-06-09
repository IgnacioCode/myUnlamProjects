#include "Nodo.h"
#include "NodoD.h"
#include "NodoA.h"

Nodo* crearNodo(const void* elem, size_t tamElem){

    Nodo* nuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    void* dirDimElem=malloc(tamElem);

    if(!nuevoNodo || !dirDimElem){
        free(nuevoNodo);
        free(dirDimElem);
        return NULL;
    }

    memcpy(dirDimElem,elem,tamElem);

    nuevoNodo->elem=dirDimElem;
    nuevoNodo->tamElem=tamElem;
    nuevoNodo->sig=NULL;

    return nuevoNodo;
}

void destruirNodo(Nodo* nae,void* elem,size_t tamElem){
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}

NodoD* crearNodoD(const void* elem, size_t tamElem){

    NodoD* nuevoNodo=(NodoD*)malloc(sizeof(NodoD));
    void* dirDimElem=malloc(tamElem);

    if(!nuevoNodo || !dirDimElem){
        free(nuevoNodo);
        free(dirDimElem);
        return NULL;
    }

    memcpy(dirDimElem,elem,tamElem);

    nuevoNodo->elem=dirDimElem;
    nuevoNodo->tamElem=tamElem;
    nuevoNodo->sig=NULL;
    nuevoNodo->ant=NULL;

    return nuevoNodo;
}

void destruirNodoD(NodoD* nae,void* elem,size_t tamElem){
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}

NodoA* crearNodoA(const void* elem, size_t tamElem){

    NodoA* nuevoNodo=(NodoA*)malloc(sizeof(NodoA));
    void* dirDimElem=malloc(tamElem);

    if(!nuevoNodo || !dirDimElem){
        free(nuevoNodo);
        free(dirDimElem);
        return NULL;
    }

    memcpy(dirDimElem,elem,tamElem);

    nuevoNodo->elem=dirDimElem;
    nuevoNodo->tamElem=tamElem;
    nuevoNodo->hDer=NULL;
    nuevoNodo->hIzq=NULL;

    return nuevoNodo;
}

void destruirNodoA(NodoA* nae,void* elem,size_t tamElem){
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}

