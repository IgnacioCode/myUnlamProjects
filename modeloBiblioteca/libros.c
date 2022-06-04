#include "libros.h"


booleano verificaISBN(char* codigo){

    int i,leyoImpar=0;
    int sumaImpares=0;
    int sumaPares=0;

    char* charAct = codigo;

    for(i=0;i<17;i++){
        if(!leyoImpar && esNumero(*charAct)){
            sumaImpares+=charToInt(*charAct);
            leyoImpar=1;
        }
        else if(leyoImpar && esNumero(*charAct)){
            sumaPares+=charToInt(*charAct);
            leyoImpar=0;
        }
        charAct++;
    }

    sumaPares*=3;

    return ((sumaImpares+sumaPares)%10) == 0;
}

booleano esLetra(char c){
    return ((c>=65 && c<=90) || (c>=97 && c<=122) )? (VERDADERO):(FALSO);
}

booleano esNumero(char c){
    return (c>=48 && c<=57)? (VERDADERO):(FALSO);
}

void creaArchivoStock(){

    Libro misLibros[3]={
        {"978-11-748-5698-3",7},
        {"978-38-600-5281-5",12},
        {"978-96-684-4030-4",5}
    };

    FILE* pf = fopen("archivoStockLibros.dat","wb");

    fwrite(misLibros,sizeof(Libro),3,pf);

    fclose(pf);

}

int comparaISBN(const char* c1,const char* c2){

    int i,comp;
    for(i=0;i<17;i++){
        comp = charToInt(*(c1+i)) - charToInt(*(c2+i));
        if(comp>0){
            return 1;
        }
        else if(comp < 0){
            return -1;
        }

    }

    return 0;
}

// ----------- Primitivas Nodo -----------

booleano crearNodo(void* elem,size_t tamElem){
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* nueElem = malloc(tamElem);

    if(!nue || !nueElem){
        free(nue);
        free(nueElem);
        return FALSO;
    }

    memcpy(nueElem,elem,tamElem);

    nue->elem=nueElem;
    nue->tamElem=tamElem;
    nue->sig=NULL;

    return VERDADERO;
}

void destruiurNodo(Nodo* nae,void* elem,size_t tamElem){
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}


// --------- Primitivas Lista ---------

void crearLista(Lista* pl){
    *pl=NULL;
}

booleano insertarEnListaOrdenada(Lista* pl,void*elem,size_t tamElem,Cmp cmp){
    
    Nodo* nue =crearNodo(elem,tamElem);

    if(!nue){
        return FALSO;
    }

    while(*pl && cmp(nue->elem,(*pl)->elem)<0){
        pl=&(*pl)->sig;
    }

    nue->sig=*pl;
    *pl = nue;
    return VERDADERO;
}

void eliminarDeListaFondo(Lista* pl,void* elem,size_t tamElem){

    if(!*pl){
        return;
    }

    while((*pl)->sig){
        pl=(*pl)->sig;
    }

    Nodo* nae=*pl;
    *pl=NULL;
    destruirNodo(nae,elem,tamElem);
    

}

int cantElementosDeLista(Lista* pl){
    int cantElem=0;
    while(*pl){
        pl=&(*pl)->sig;
        cantElem++;
    }
    return cantElem;
}
