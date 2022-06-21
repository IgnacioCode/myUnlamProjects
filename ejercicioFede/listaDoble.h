#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include "Comun.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct SNodoD{

    struct SNodoD* ant;
    void* elem;
    size_t tamElem;
    struct SNodoD* sig;
}NodoD;

typedef NodoD* Lista;
/// Primitivas NodoD

NodoD* crearNodoD(const void* elem, size_t tamElem);
void destruirNodoD(NodoD* nae,void* elem, size_t tamElem);

/// Primitivas Lista

void crearLista(Lista* pl);
booleano insertarEnListaOrdenada(Lista* pl, const void* elem,size_t tamElem, Cmp cmp);
booleano eliminarDeListaOrdenada(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
void vaciarLista(Lista* pl);

#endif // LISTADOBLE_H_INCLUDED
