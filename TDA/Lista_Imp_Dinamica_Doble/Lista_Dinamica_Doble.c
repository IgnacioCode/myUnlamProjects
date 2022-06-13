#define LISTA_IMP_DINAMICA_DOBLE

#include "..\Lista\Lista.h"

void recorrerListaIzquierda(Lista* pl,Accion accion,void* datosAccion);
void recorrerListaDerecha(Lista* pl,Accion accion,void* datosAccion);

void crearLista(Lista* pl){
    *pl=NULL;
}

int insertarEnListaOrdenada(Lista* pl, const void* elem, size_t tamElem, Cmp cmp){

    NodoD* act = *pl;
    NodoD* ant=NULL;
    NodoD* sig=NULL;

    if(act){

        while(act->ant && cmp(elem,act->elem)<0){   //Avanza para la izquierda hasta encontrar el correcto
           act = act->ant;
        }

        while(act->sig && cmp(elem,act->sig)>0){    //Avanza para la derecha hasta encontrar el correcto
            act = act->sig;
        }

        int comp=cmp(elem,act->elem);

        if(comp==0){
            return DUPLICADO;
        }

        if(comp<0){
            sig = act;
            ant = act->ant;
        }
        else{
            ant = act;
            sig= act->sig;
        }
   
    }

    NodoD* nue =crearNodoD(elem,tamElem);
    if(!nue){
        return NO_MEMORY;
    }

    nue->ant=ant;
    nue->sig=sig;
    if(ant){
        ant->sig = nue;
    }
    if(sig){
        sig->ant = nue;
    }

    *pl=nue;

    return TODO_OK;

}

booleano eliminarDeListaOrdenada(Lista* pl, void* elem, size_t tamElem, Cmp cmp){

    if(!*pl){
        return FALSO;
    }

    NodoD* nae = *pl;

    while(nae->ant && cmp(elem,nae->elem)<0){   //Avanza para la izquierda hasta encontrar el correcto
       nae = nae->ant;
    }

    while(nae->sig && cmp(elem,nae->sig)>0){    //Avanza para la derecha hasta encontrar el correcto
        nae = nae->sig;
    }

    if(cmp(elem,nae->elem)!=0){
        return FALSO;
    }

    if(nae->ant){       //Casos de Borde inicio
        nae->ant->sig = nae->sig;
    }
    if(nae->sig){       //Casos de Borde final
        nae->sig->ant = nae->ant;
    }
    if(nae == *pl){
        if(nae->sig){
            *pl = nae->sig;
        }
        else{
            *pl = nae->ant;
        }
    }

    destruirNodoD(nae,elem,tamElem);

    return TODO_OK;

}

booleano buscarEnListaOrdenada(const Lista* pl,void* elem,size_t tamElem, Cmp cmp){

    if(!*pl){
        return FALSO;
    }

    NodoD* nae = *pl;

    while(nae->ant && cmp(elem,nae->elem) < 0){
        nae = nae->ant;
    }

    while(nae->sig && cmp(elem,nae->elem) > 0 ){
        nae = nae->sig;
    }

    if(cmp(elem,nae->elem)!=0){
        return FALSO;
    }
    
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    return VERDADERO;

}

void recorrerLista(Lista* pl,Accion accion,void* datosAccion){

    NodoD* pIzq = *pl;
    NodoD* pDer = (*pl)->sig;

    accion(*pl,datosAccion);

    recorrerListaIzquierda(&pIzq,accion,datosAccion);
    recorrerListaDerecha(&pDer,accion,datosAccion);

}

void recorrerListaIzquierda(Lista* pl,Accion accion, void* datosAccion){

    accion(*pl,datosAccion);

    if(!(*pl)->ant){
        return;
    }

    recorrerListaIzquierda((*pl)->ant,accion,datosAccion);

}

void recorrerListaDerecha(Lista* pl,Accion accion, void* datosAccion){

    accion(*pl,datosAccion);

    if(!(*pl)->sig){
        return;
    }

    recorrerListaDerecha((*pl)->sig,accion,datosAccion);
}

