#define COLA_IMP_DINAMICA
#include "..\Cola\Cola.h"
#include <stdlib.h>
#include <string.h>

void crearCola(Cola* pc){

    pc->fondo=pc->frente=NULL;

}

booleano encolar(Cola* pc,const void* elem,size_t tamElem){

    Nodo* nuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    void* dirDimElem=malloc(tamElem);

    if(!nuevoNodo || !dirDimElem){
        free(nuevoNodo);
        free(dirDimElem);
        return FALSO;
    }

    memcpy(dirDimElem,elem,tamElem);

    nuevoNodo->elem=dirDimElem;
    nuevoNodo->tamElem=tamElem;

    nuevoNodo->sig=NULL;
    if(pc->fondo){
        pc->fondo->sig = nuevoNodo; //Si hay un fondo, ese fondo ahora apunta al nuevo, y no a NULL
    }
    else{
        pc->frente=nuevoNodo;   //Si esta vacia, debemos cambiar el frente
    }
    pc->fondo = nuevoNodo;  //Siempre el que entra nuevo apunta hacia NULL ya que es el ultimo de la cola

    return VERDADERO;
}

booleano desencolar(Cola* pc,void* elem,size_t tamElem){

    if(!pc->frente){
        return FALSO;
    }

    Nodo* nae = pc->frente;

    pc->frente=nae->sig;

    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));

    free(nae->elem);
    free(nae);

    return VERDADERO;


}

booleano verFrenteDeCola(const Cola* pc,void* elem,size_t tamElem){

    if(!pc->frente){
        return FALSO;
    }

    memcpy(elem,pc->frente->elem,MIN(tamElem,pc->frente->tamElem));

    return VERDADERO;


}

booleano colaLLena(const Cola* pc,size_t tamElem){

    Nodo* nuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    void* dirDinElem=malloc(tamElem);

    if(!nuevoNodo || !dirDinElem){
        free(nuevoNodo);
        free(dirDinElem);
        return VERDADERO;
    }
    else{
        free(nuevoNodo);
        free(dirDinElem);
        return FALSO; 
    }


}

booleano colaVacia(const Cola* pc){

    return pc->frente==pc->fondo && pc->frente==NULL;

}

void vaciarCola(Cola* pc){

    Nodo* nae=pc->frente;

    while(nae){
        pc->frente=nae->sig;

        free(nae->elem);
        free(nae);

        nae=pc->frente; 
    }

    pc->fondo=NULL;
}