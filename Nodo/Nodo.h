#ifndef NODO_H
#define NODO_H

#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
#include "..\Comun\Comun.h"

typedef struct SNodo{

    void* elem;
    size_t tamElem;
    struct SNodo* sig;

}Nodo;

Nodo* crearNodo(const void* elem, size_t tamElem);
void destruirNodo(Nodo* nae,void* elem,size_t tamElem);

#endif
