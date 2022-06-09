#define TDA_ARBOL_IMP_DINAMICA

#include "..\Arbol\Arbol.h"

void imprimirArbolRec(const Arbol* pa,ImprimirElemArbol imprimir,void* datosImprimir,int nivel);
const Arbol* buscarRaizArbol(const Arbol* pa, void* elem,Cmp cmp);
void eliminarRaizDeArbol(Arbol* pae);

void crearArbol(Arbol* pa){
    *pa=NULL;
}

int insertarEnArbol(Arbol* pa, const void* elem, size_t tamElem,Cmp cmp,Actualizar actualizar){

    //Version Iterativa
    /*
    int comp;
    while(*pa){

        comp = cmp(elem,(*pa)->elem);
        if(comp==0){    //Duplicado

            if(actualizar){ //Si se paso una funcion de actualizar, se utiliza para cambiar a los duplicados
                return actualizar((*pa)->elem,elem);
            }
            return DUPLICADO;
        }
        else if(comp < 1){  //elem es mas chico que el del arbol
            pa = &(*pa)->hIzq;
        }
        else{   //elem es mas grande que el del arbol
            pa = &(*pa)->hDer;
        }

    }

    *pa = crearNodoA(elem,tamElem);

    if(!*pa){
        return NO_MEMORY;
    }

    return TODO_OK;
    */

    //Version Recursiva

    if(!*pa){
        *pa = crearNodoA(elem,tamElem);
        return !*pa? NO_MEMORY:TODO_OK;
    }

    int comp=cmp(elem,(*pa)->elem);

    if(comp==0){    //Duplicado

            if(actualizar){ //Si se paso una funcion de actualizar, se utiliza para cambiar a los duplicados
                return actualizar((*pa)->elem,elem);
            }
            return DUPLICADO;
    }

    return insertarEnArbol(comp <0? &(*pa)->hIzq:&(*pa)->hDer, elem, tamElem, cmp, actualizar);

}

booleano eliminarDeArbol(Arbol* pa, void* elem, size_t tamElem,Cmp cmp){
    
    Arbol* pae = (Arbol*)buscarRaizArbol(pa,elem,cmp);  //funciones privadas
    //busca el nodo que tenga a el elemento "elem"
    if(!pae){
        return FALSO;
    }

    memcpy(elem,(*pae)->elem,MIN(tamElem,(*pae)->tamElem)); //lo copiamos
    free((*pae)->elem); //borramos el elemento

    eliminarRaizDeArbol(pae);  //funciones privadas

    return VERDADERO;
}

const Arbol* buscarRaizArbol(const Arbol* pa, void* elem,Cmp cmp){

    if(!*pa){
        return NULL;
    }

    int comp = cmp(elem,(*pa)->elem);

    if(comp==0){
        return pa;
    }

    return buscarRaizArbol(comp<0?(*pa)->hIzq:(*pa)->hDer,elem,cmp);
}

void eliminarRaizDeArbol(Arbol* pae){

    if(!(*pae)->hDer && !(*pae)->hIzq){
        free(*pae);
        *pae=NULL;
        return;
    }

    int hI = alturaArbol(&(*pae)->hIzq);
    int hD = alturaArbol(&(*pae)->hDer);

    Arbol* par = hI>hD? mayorDeArbol(&(*pae)->hIzq) : menorDeArbol(&(*pae)->hDer);
    (*pae)->elem = (*par)->elem;
    (*pae)->tamElem = (*par)->tamElem;

    eliminarRaizDeArbol(par);
}

int alturaArbol(const Arbol* pa){
    if(!*pa){
        return 0;
    }

    int aHi = alturaArbol(&(*pa)->hIzq); 
    int aHd = alturaArbol(&(*pa)->hDer);

    return MAX(aHi,aHd)+1;

}

Arbol* mayorDeArbol(Arbol* pa){
    
    if(!(*pa)->hDer){
        return pa;
    }

    return mayorDeArbol(&(*pa)->hDer);
}

Arbol* menorDeArbol(Arbol* pa){
    
    if(!(*pa)->hIzq){
        return pa;
    }

    return menorDeArbol(&(*pa)->hIzq);
}

void recorrerArbolPre(Arbol* pa,Accion acc,void* datosAccion){

    if(!*pa){
        return;
    }
    acc((*pa)->elem,datosAccion);
    recorrerArbolPre(&(*pa)->hIzq,acc,datosAccion);
    recorrerArbolPre(&(*pa)->hDer,acc,datosAccion);

}

void recorrerArbolEn(Arbol* pa,Accion acc,void* datosAccion){

    if(!*pa){
        return;
    }
    recorrerArbolPre(&(*pa)->hIzq,acc,datosAccion);
    acc((*pa)->elem,datosAccion);
    recorrerArbolPre(&(*pa)->hDer,acc,datosAccion);

}

void recorrerArbolPost(Arbol* pa,Accion acc,void* datosAccion){

    if(!*pa){
        return;
    }
    recorrerArbolPre(&(*pa)->hIzq,acc,datosAccion);
    recorrerArbolPre(&(*pa)->hDer,acc,datosAccion);
    acc((*pa)->elem,datosAccion);

}

void imprimirArbol(const Arbol* pa,ImprimirElemArbol imprimir,void* datosImprimir){

    imprimirArbolRec(pa,imprimir,datosImprimir,0);

}

void imprimirArbolRec(const Arbol* pa,ImprimirElemArbol imprimir,void* datosImprimir,int nivel){

    if(!*pa){
        return;
    }

    imprimirArbolRec(&(*pa)->hDer,imprimir,datosImprimir,nivel+1);
    imprimir((*pa)->elem,datosImprimir,nivel);
    imprimirArbolRec(&(*pa)->hIzq,imprimir,datosImprimir,nivel+1);


}
