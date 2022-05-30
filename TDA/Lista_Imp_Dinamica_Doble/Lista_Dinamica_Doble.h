#ifndef LISTA_DINAMICA_DOBLE_H_INCLUDED
#define LISTA_DINAMICA_DOBLE_H_INCLUDED

#include "..\..\Nodo\NodoD.h"
#include "..\..\Comun\Comun.h"

typedef NodoD* Lista;

typedef struct{
    Nodo* inicio;
    Nodo* actual;
}Iterador;

#endif // LISTA_DINAMICA_DOBLE_H_INCLUDED
