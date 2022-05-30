#ifndef COLA_IMP_DINAMICA_H_INCLUDED
#define COLA_IMP_DINAMICA_H_INCLUDED

#include <stddef.h>
#define COLA_IMPL_DINAMICA
#include "..\..\Comun\Comun.h"

#include "..\..\Nodo\Nodo.h"

typedef struct {
    Nodo* frente;
    Nodo* fondo;
}Cola;

#endif // COLA_IMP_DINAMICA_H_INCLUDED
