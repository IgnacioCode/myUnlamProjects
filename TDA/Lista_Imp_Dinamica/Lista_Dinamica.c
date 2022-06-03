#define LISTA_IMP_DINAMICA
#include "..\Lista\Lista.h"

Lista* buscarMinimoDeLista(Lista* pl,Cmp cmp);

void crearLista(Lista* pl){
    *pl = NULL;
}

int insertarEnListaOrdenada(Lista* pl, const void* elem, size_t tamElem, Cmp cmp){

    while(*pl && cmp(elem,(*pl)->elem) > 0){
        pl = &(*pl)->sig;
    }
    if(*pl && cmp(elem,(*pl)->elem) == 0){
        return DUPLICADO;
    }

    Nodo* nue = crearNodo(elem,tamElem);

    if(!nue){
        return NO_MEMORY;
    }

    nue->sig =*pl;
    *pl = nue;

    return TODO_OK;
}

int insertarEnListaEnPos(Lista* pl, const void* elem, size_t tamElem,int pos){

    Nodo* nae;

    int posActual=1;

    while(posActual!=pos){
        pl=&(*pl)->sig;
        posActual++;
    }

    nae = crearNodo(elem,tamElem);
    if(!nae){
        return NO_MEMORY;
    }

    nae->sig=(*pl);
    (*pl)=nae;

    return TODO_OK;
}

int insertarEnListaFrente(Lista* pl, const void* elem, size_t tamElem){

    Nodo* nae;

    nae = crearNodo(elem,tamElem);
    if(!nae){
        return NO_MEMORY;
    }

    nae->sig=(*pl);
    (*pl)=nae;

    return TODO_OK;

}

int insertarEnListaFondo(Lista* pl, const void* elem, size_t tamElem){

    Nodo* nae;

    while(*pl){
        pl=&(*pl)->sig;
    }

    nae = crearNodo(elem,tamElem);
    if(!nae){
        return NO_MEMORY;
    }

    nae->sig=(*pl);
    (*pl)=nae;

    return TODO_OK;

}

booleano eliminarDeListaOrdenada(Lista* pl, void* elem, size_t tamElem, Cmp cmp){

    while(*pl && cmp(elem,(*pl)->elem) > 0){
        pl = &(*pl)->sig;
    }
    if(!*pl || cmp(elem,(*pl)->elem) < 0){
        return FALSO;
    }

    Nodo* nae = *pl;

    *pl = nae->sig;

    destruirNodo(nae,elem,tamElem);

    return VERDADERO;
}

booleano eliminarDeListaFrente(Lista* pl, void* elem, size_t tamElem){

    Nodo* nae=*pl;

    if(!nae){
        return VACIA;
    }

    *pl=nae->sig;
    destruirNodo(nae,elem,tamElem);

    return TODO_OK;

}

booleano listaVacia(const Lista* pl){
    return !*pl? VERDADERO:FALSO;
}

void recorrerLista(Lista* pl,Accion accion,void* datosAccion){

    while(*pl){
        accion((*pl)->elem,datosAccion);
        pl = &(*pl)->sig;
    }

}

/// ----------------- FUNCIONES ITERADOR -----------------

booleano crearIterador(Iterador* it, const Lista* pl){

    it->inicio=*pl;
    it->actual=NULL;

    if(*pl){
        return VERDADERO;
    }
    return FALSO;

}

booleano primeroDeLista(Iterador* it, void* elem, size_t tamElem){

    if(!it->inicio){
        return FALSO;
    }

    it->actual = it->inicio;

    memcpy(elem,it->actual->elem,MIN(tamElem,it->actual->tamElem));

    return VERDADERO;

}

booleano siguienteDeLista(Iterador* it,void* elem, size_t tamElem){

    if(!it->actual){
        return FALSO;
    }
    it->actual = it->actual->sig;
    if(!it->actual){
        return FALSO;
    }

    memcpy(elem,it->actual->elem,MIN(tamElem,it->actual->tamElem));

    return VERDADERO;
}

booleano haySiguienteDeLista(Iterador* it){
    if(!it->actual){
        return FALSO;
    }

    return (it->actual->sig != NULL);
}

booleano finLista(Iterador* it){
    return !it->actual;
}

/// --------------- FIN FUNCIONES ITERADOR ---------------

int eliminarDuplicados(Lista* pl,Cmp cmp){

    Lista* plAct = pl;
    void* elemAnterior;
    Nodo* nae;

    while(*pl){

        elemAnterior = (*pl)->elem;
        plAct = &(*plAct)->sig;
        while(*plAct){
            if(cmp(elemAnterior,(*plAct)->elem)==0){
                nae = *plAct;
                *plAct = (*plAct)->sig;
                destruirNodo(nae,elemAnterior,nae->tamElem);
            }
            else{
                plAct = &(*plAct)->sig;
            }

        }
        pl = &(*pl)->sig;
        plAct = pl;
    }

    return TODO_OK;

}

void ordenarLista(Lista* pl, Cmp cmp){

    Lista listaOrdenada;
    Lista* plMinimo;
    Lista* plOrdenada=&listaOrdenada;

    while(*pl){
        plMinimo=buscarMinimoDeLista(pl,cmp);
        *plOrdenada=*plMinimo;
        *plMinimo=(*plMinimo)->sig;
        plOrdenada=&(*plOrdenada)->sig;
    }

    *pl=listaOrdenada;

}

Lista* buscarMinimoDeLista(Lista* pl,Cmp cmp){

    Lista* plMinimo = pl;
    Lista* plAct = pl;

    while(*plAct){

        if(cmp((*plAct)->elem,(*plMinimo)->elem)<0){
            plMinimo=plAct;
        }
        plAct = &(*plAct)->sig;

    }

    return plMinimo;

}
