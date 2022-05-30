#define COLA_IMP_CIRCULAR_DINAMICA

#include "..\..\Nodo\Nodo.h"
#include "..\Cola\Cola.h"


void crearCola(Cola* pc){
    *pc=NULL;
}
booleano encolar(Cola* pc,const void* elem,size_t tamElem){ //Completar 
    Nodo* nue = crearNodo(elem,tamElem);
    if(!nue){
        return FALSO;
    }
    if(*pc){
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
    }
    else{
        nue->sig=nue;
        
    }

    *pc=nue;


}
booleano desencolar(Cola* pc,void* elem,size_t tamElem);
booleano verFrenteDeCola(const Cola* pc,void* elem, size_t tamElem);
booleano colaLLena(const Cola* pc,size_t tamElem);
booleano colaVacia(const Cola* pc);
void vaciarCola(Cola* pc);