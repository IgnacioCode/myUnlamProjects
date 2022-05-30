#ifndef COLA_ESTATICA_H_INCLUDED
#define COLA_ESTATICA_H_INCLUDED

#include <stddef.h>
#define COLA_IMPL_ESTATICA
#include "..\..\Comun\Comun.h"
#define TAM_COLA 500

typedef struct{

    char vec[TAM_COLA];
    unsigned frente;
    unsigned fondo;
    size_t tamDisponible;

}Cola;


#endif // COLA_ESTATICA_H_INCLUDED
