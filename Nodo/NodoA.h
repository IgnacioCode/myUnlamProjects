#ifndef NODOA_H_INCLUDED
#define NODOA_H_INCLUDED

#include <stddef.h>

typedef struct SnodoA{

    struct SnodoA* hIzq;
    void* elem;
    size_t tamElem;
    struct SnodoA* hDer;

}NodoA;

NodoA* crearNodoA(const void* elem, size_t tamElem);
void destruirNodoA(NodoA* nae,void* elem,size_t tamElem);

#endif // NODOA_H_INCLUDED