#ifndef COLA_H
#define COLA_H

#include <stddef.h>

#ifdef COLA_IMP_ESTATICA
    #include "..\Cola_Imp_Estatica\Cola_Estatica.h"
#endif

#ifdef COLA_IMP_DINAMICA
    #include "..\Cola_Imp_Dinamica\Cola_Dinamica.h"
#endif

#ifdef COLA_IMP_CIRCULAR_DINAMICA
    #include "..\Cola_Imp_Circular_Dinamica\Cola_Circular_Dinamica.h"
#endif

void crearCola(Cola* pc);
booleano encolar(Cola* pc,const void* elem,size_t tamElem);
booleano desencolar(Cola* pc,void* elem,size_t tamElem);
booleano verFrenteDeCola(const Cola* pc,void* elem, size_t tamElem);
booleano colaLLena(const Cola* pc,size_t tamElem);
booleano colaVacia(const Cola* pc);
void vaciarCola(Cola* pc);

/*
    Deberia haber una funcion "hayEspacio que verifique segun un elemento asignado
    Y ColaLLena solo actuar si esta completamente llena o devolver los bytes restantes"
*/

#endif //Cola_H
