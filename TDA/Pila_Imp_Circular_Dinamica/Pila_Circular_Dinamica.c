#define PILA_IMP_CIRCULAR_DINAMICA

#include "..\Pila\Pila.h"

void crearPila(Pila* pp){
    *pp=NULL;
}
booleano apilar(Pila* pp,const void* elem,size_t tamElem){
    
    Nodo* nue = crearNodo(elem,tamElem);

    if(!nue){
        return FALSO;
    }
    if(*pp){
        nue->sig = (*pp)->sig;
        (*pp)->sig = nue;
    }
    else{
        nue->sig =nue;
    }
    

}
booleano desapilar(Pila* pp,void* elem,size_t tamElem);
booleano verTopePila(Pila* pp,void* elem, size_t tamElem);
booleano pilaLLena(Pila* pp,size_t tamElem);
booleano pilaVacia(Pila* pp);
void vaciarPila(Pila* pp);
