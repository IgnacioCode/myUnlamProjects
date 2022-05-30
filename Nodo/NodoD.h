#ifndef NODOD_H_INCLUDED
#define NODOD_H_INCLUDED

#include <stddef.h>

typedef struct SnodoD{

    struct SnodoD* ant;
    void* elem;
    size_t tamElem;
    struct SnodoD* sig;

}NodoD;

NodoD* crearNodoD(const void* elem, size_t tamElem);
void destruirNodoD(NodoD* nae,void* elem,size_t tamElem);

#endif // NODOD_H_INCLUDED
