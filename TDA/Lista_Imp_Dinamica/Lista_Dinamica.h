#ifndef LISTA_IMP_DINAMICA_H_INCLUDED
#define LISTA_IMP_DINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "..\..\Nodo\Nodo.h"
#include "..\..\Comun\Comun.h"

typedef struct{
    Nodo* inicio;
    Nodo* actual;
}Iterador;

typedef Nodo* Lista;

#endif // LISTA_IMP_DINAMICA_H_INCLUDED
