#include "Arbol.h"

///Funciones de Nodo

NodoA* crearNodoA(void* elem, size_t tamElem){

    NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
    void* nueElem = malloc(tamElem);

    if(!nue || !nueElem){
        free(nue);
        free(nueElem);
        return NULL;
    }

    memcpy(nueElem,elem,tamElem);

    nue->elem = nueElem;
    nue->tamElem = tamElem;
    nue->hIzq = NULL;
    nue->hDer = NULL;

    return nue;
}

void destruirNodoA(NodoA* nae,void* elem,size_t tamElem){
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}

/// Funciones de Arbol

void imprimeArbolNivel(const Arbol*,int,ImpFunc,const void*);
void eliminarRaizDeArbol(Arbol*);
Arbol* buscarRaizDeArbol(Arbol*, void*,size_t,Cmp);
int alturaArbol(Arbol*);
const Arbol* mayorDeArbol(const Arbol*);
const Arbol* menorDeArbol(const Arbol*);

void crearArbol(Arbol* pa){
    *pa=NULL;
}

booleano insertarEnArbolOrdenado(Arbol* pa,void* elem,size_t tamElem,Cmp cmp){

    if(!*pa){
        NodoA* nue=crearNodoA(elem,tamElem);
        if(!nue)
            return FALSO;
        *pa = nue;
        return VERDADERO;
    }

    return insertarEnArbolOrdenado(cmp(elem,(*pa)->elem)<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
}

booleano eliminarDeArbol(Arbol* pa,void* elem,size_t tamElem, Cmp cmp){

    Arbol* pae = buscarRaizDeArbol(pa,elem,tamElem,cmp);
    if(!*pae){
        return FALSO;
    }

    memcpy(elem,(*pae)->elem,MIN(tamElem,(*pae)->tamElem));
    free((*pae)->elem);
    eliminarRaizDeArbol(pae);

    return VERDADERO;

}

Arbol* buscarRaizDeArbol(Arbol* pa, void* elem,size_t tamElem,Cmp cmp){

    if(!*pa){
        return NULL;
    }

    int comp = cmp(elem,(*pa)->elem);
    if(comp==0){
        return pa;
    }
    return comp<0?buscarRaizDeArbol(&(*pa)->hIzq,elem,tamElem,cmp):buscarRaizDeArbol(&(*pa)->hDer,elem,tamElem,cmp);
}

void eliminarRaizDeArbol(Arbol* pa){

    if(!(*pa)->hIzq && !(*pa)->hDer){
        free(*pa);
        *pa=NULL;
        return;
    }

    int hI = alturaArbol(&(*pa)->hIzq);
    int hD = alturaArbol(&(*pa)->hDer);

    Arbol* arbolReemplazo = (Arbol*)( hI>hD? mayorDeArbol(&(*pa)->hIzq):menorDeArbol(&(*pa)->hDer));
    (*pa)->elem = (*arbolReemplazo)->elem;
    (*pa)->tamElem = (*arbolReemplazo)->tamElem;
    eliminarRaizDeArbol(arbolReemplazo);
}

int alturaArbol(Arbol* pa){
    if(!*pa){
        return 0;
    }

    return alturaArbol(&(*pa)->hIzq) + alturaArbol(&(*pa)->hDer) + 1;
}

const Arbol* mayorDeArbol(const Arbol* pa){
    if(!(*pa)->hDer){
        return pa;
    }

    return mayorDeArbol(&(*pa)->hDer);
}

const Arbol* menorDeArbol(const Arbol* pa){
    if(!(*pa)->hIzq){
        return pa;
    }

    return mayorDeArbol(&(*pa)->hIzq);
}

void imprimeArbolEnPantalla(const Arbol* pa,ImpFunc imprimir,const void* datosImprimir){

    imprimeArbolNivel(pa,0,imprimir,datosImprimir);

}

void imprimeArbolNivel(const Arbol* pa,int nivel,ImpFunc imprimir,const void* datosImprimir){

    if(!*pa){
        return;
    }

    imprimeArbolNivel(&(*pa)->hDer,nivel+1,imprimir,datosImprimir);
    imprimir((*pa)->elem,datosImprimir,nivel);
    imprimeArbolNivel(&(*pa)->hIzq,nivel+1,imprimir,datosImprimir);
}
