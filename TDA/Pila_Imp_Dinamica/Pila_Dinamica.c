#define PILA_IMP_DINAMICA
#include "..\Pila\Pila.h"

#define MIN(X,Y) ((X)>(Y)? (Y):(X))

void crearPila(Pila* pp){

    *pp = NULL;

}

booleano apilar(Pila* pp, const void* elem, size_t tamElem){

    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* nueElem = malloc(tamElem);

    if(!nue || !nueElem){
        free(nue);
        free(nueElem);
        return FALSO;
    }

    nue->elem = nueElem;
    nue->tamElem = tamElem;
    nue->sig = *pp;

    memcpy(nueElem,elem,tamElem);

    *pp = nue;

    return VERDADERO;

}

booleano desapilar(Pila* pp, void* elem, size_t tamElem){

    if(!*pp){
        return FALSO;
    }

    Nodo* nae = *pp;
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    *pp = nae->sig;

    free(nae->elem);
    free(nae);

    return VERDADERO;

}

booleano verTopePila(Pila* pp, void* elem, size_t tamElem){

    if(!*pp){
        return FALSO;
    }

    Nodo* tope = *pp;
    memcpy(elem,tope->elem,MIN(tamElem,tope->tamElem));

    return VERDADERO;

}

booleano pilaLLena(Pila* pp,size_t tamElem){

    Nodo* nodo=malloc(sizeof(Nodo));
    void* elem=malloc(tamElem);

    free(nodo);
    free(elem);

    return !nodo || !elem;

}

booleano pilaVacia(Pila* pp){
    return *pp==NULL? VERDADERO:FALSO;
}

void vaciarPila(Pila* pp){

    Nodo* nae = *pp;

    while(nae){
        *pp = nae->sig;
        free(nae->elem);
        free(nae);
        nae = *pp;
    }

}
