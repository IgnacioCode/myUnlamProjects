#ifndef PILA_H
#define PILA_H

#ifdef PILA_IMP_ESTATICA
    #include "..\Pila_Imp_Estatica\Pila_Estatica.h"
#endif

#ifdef PILA_IMP_DINAMICA
    #include "..\Pila_Imp_Dinamica\Pila_Dinamica.h"
#endif

#ifdef PILA_IMP_CIRCULAR_DINAMICA
    #include "..\Pila_Imp_Circular_Dinamica\Pila_Circular_Dinamica.h"
#endif

void crearPila(Pila* pp);
booleano apilar(Pila* pp,const void* elem,size_t tamElem);
booleano desapilar(Pila* pp,void* elem,size_t tamElem);
booleano verTopePila(Pila* pp,void* elem, size_t tamElem);
booleano pilaLLena(Pila* pp,size_t tamElem);
booleano pilaVacia(Pila* pp);
void vaciarPila(Pila* pp);

/*
    Deberia haber una funcion "hayEspacio que verifique segun un elemento asignado
    Y pilaLLena solo actuar si esta completamente llena o devolver los bytes restantes"
*/

#endif //PILA_H
