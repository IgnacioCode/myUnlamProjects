#ifndef PILA_ESTATICA_H_INCLUDED
#define PILA_ESTATICA_H_INCLUDED

#include <stdio.h>
#include <memory.h>
#include "..\..\Comun\Comun.h"

#define TAM_PILA 1000

typedef struct{

    char vPila[TAM_PILA];
    unsigned int tope;

}Pila;


#endif // PILA_ESTATICA_H_INCLUDED
