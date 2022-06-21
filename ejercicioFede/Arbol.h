#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUD

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "Comun.h"

typedef struct SNodoA{

    struct SNodoA* hIzq;
    void* elem;
    size_t tamElem;
    struct SNodoA* hDer;

}NodoA;


/// Primitivas de NodoA

NodoA* crearNodoA(void* elem,size_t tamElem);
void destruirNodoA(NodoA* nae,void* elem,size_t tamElem);

/// Primitivas de Arbol

typedef NodoA* Arbol;

void crearArbol(Arbol* pa);
booleano insertarEnArbolOrdenado(Arbol* pa,void* elem,size_t tamElem,Cmp cmp);
booleano eliminarDeArbol(Arbol* pa,void* elem,size_t tamElem, Cmp cmp);
void imprimeArbolEnPantalla(const Arbol* pa,ImpFunc imprimir,const void* datosImprimir);
void vaciarArbol(Arbol* pa);

#endif // ARBOL_H_INCLUDED
