#include "listaDoble.h"

/// Primitivas NodoD

NodoD* crearNodoD(const void* elem, size_t tamElem){
    NodoD* nue = (NodoD*)malloc(sizeof(NodoD));
    void* nueElem = malloc(tamElem);

    if(!nue || !nueElem){
        free(nue);
        free(nueElem);
        return NULL;
    }

    memcpy(nueElem,elem,tamElem);

    nue->ant=NULL;
    nue->sig=NULL;
    nue->elem = nueElem;
    nue->tamElem = tamElem;
    return nue;
}

void destruirNodoD(NodoD* nae,void* elem, size_t tamElem){
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}

/// Primitivas Lista

void crearLista(Lista* pl){
    *pl=NULL;
}

booleano insertarEnListaOrdenada(Lista* pl, const void* elem,size_t tamElem, Cmp cmp){

    if(!*pl){
        NodoD* nue = crearNodoD(elem,tamElem);
        if(!nue){
            return FALSO;
        }
        *pl = nue;
        return VERDADERO;
    }

    int comp = cmp(elem,(*pl)->elem);

    while((*pl)->ant && comp<0){
        *pl = (*pl)->ant;
        comp = cmp(elem,(*pl)->elem);
    }
    while((*pl)->sig && comp>0){
        *pl = (*pl)->sig;
        comp = cmp(elem,(*pl)->elem);
    }

    NodoD* nue = crearNodoD(elem,tamElem);
    if(!nue){
        return FALSO;
    }

    if(!(*pl)->ant){
        if(comp < 0){
            (*pl)->ant = nue;
            nue->sig = *pl;
        }
        else{   // comp > 0
            nue->sig = (*pl)->sig;
            nue->ant = *pl;
            if((*pl)->sig)
                (*pl)->sig->ant = nue;
            (*pl)->sig = nue;

        }
    }
    else if(!(*pl)->sig){
        if(comp > 0){
            (*pl)->sig = nue;
            nue->ant = *pl;
        }
        else{   // comp > 0
            nue->sig = *pl;
            nue->ant = (*pl)->ant;
            if((*pl)->ant)
                (*pl)->ant->sig = nue;
            (*pl)->ant = nue;

        }
    }

    return VERDADERO;
}

booleano eliminarDeListaOrdenada(Lista* pl, void* elem, size_t tamElem, Cmp cmp){

    if(!*pl){
        return FALSO;
    }

    NodoD* act = *pl;


    int comp = cmp(elem,act->elem);

    while(act->ant && comp<0){
        act = act->ant;
        comp = cmp(elem,act->elem);
    }
    while(act->sig && comp>0){
        act = act->sig;
        comp = cmp(elem,act->elem);
    }

    if(comp!=0){
        return FALSO;
    }
    if(act->sig){
        act->sig->ant = act->ant;
    }

    if(act->ant){
        act->ant->sig = act->sig;
    }

    if(act->sig){
        *pl = act->sig;
    }
    else{
        *pl = act->ant;
    }

    destruirNodoD(act,elem,tamElem);

    return VERDADERO;


}

void vaciarLista(Lista* pl){

    if(!*pl){
        return;
    }

    NodoD* pAnt=(*pl)->ant;
    NodoD* pSig=(*pl)->sig;
    NodoD* nae;

    while(!pAnt){
        nae = pAnt;
        pAnt = pAnt->ant;
        destruirNodoD(nae,NULL,0);
    }
    while(!pSig){
        nae = pSig;
        pSig = pSig->sig;
        destruirNodoD(nae,NULL,0);
    }

    destruirNodoD(*pl,NULL,0);
    *pl=NULL;

}

