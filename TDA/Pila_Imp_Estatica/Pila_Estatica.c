//#include "Pila_Estatica.h"


#ifndef PILA_IMPL_ESTATICA
    #define PILA_IMPL_ESTATICA
#endif
#define DESTINO_PILA pp->vPila+pp->tope


#include "..\Pila\Pila.h"

void crearPila(Pila* pp){
    pp->tope=0;
}

void vaciarPila(Pila* pp){
    pp->tope=0;
}

booleano apilar(Pila* pp,const void* elem,size_t tamElem){

    if(tamElem+sizeof(size_t) > TAM_PILA-pp->tope){
        return FALSO;
    }

    memcpy(DESTINO_PILA,elem,tamElem);
    pp->tope+=tamElem;

    *(size_t*)(DESTINO_PILA)=tamElem;

    pp->tope+=sizeof(size_t);

    return VERDADERO;

}

booleano desapilar(Pila* pp,void* elem,size_t tamElem){

    if(pp->tope==0){
        return FALSO;
    }

    pp->tope-=sizeof(size_t);

    size_t tamElemAp=*(size_t*)(DESTINO_PILA);

    pp->tope-=tamElemAp;

    memcpy(elem,DESTINO_PILA,MIN(tamElemAp,tamElem));

    return VERDADERO;

}

booleano verTopePila(Pila* pp,void* elem,size_t tamElem){

    if(pp->tope==0){
        return FALSO;
    }

    unsigned int tope=pp->tope;

    tope-=sizeof(size_t);

    size_t tamElemAp=*(size_t*)(pp->vPila+tope);

    tope-=tamElemAp;

    memcpy(elem,pp->vPila+tope,MIN(tamElemAp,tamElem));

    return VERDADERO;

}

booleano pilaLLena(Pila* pp,size_t tamElem){
    return tamElem+sizeof(size_t)>TAM_PILA-pp->tope? VERDADERO:FALSO;
}

booleano pilaVacia(Pila* pp){
    return !pp->tope? VERDADERO:FALSO;
}
