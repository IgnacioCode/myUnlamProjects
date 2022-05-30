#ifndef LISTA_DINAMICA_H_INCLUDED
#define LISTA_DINAMICA_H_INCLUDED

#include <stddef.h>
#include <memory.h>
#include <stdlib.h>
#define MIN(X,Y) ((X)>(Y)? (Y):(X))

typedef struct Snodo{
    void* elem;
    size_t tamElem;
    struct Snodo* sig;
}Nodo;

typedef Nodo* Lista;

typedef enum booleano{
    FALSO,VERDADERO
}booleano;

typedef int (*Cmp)(const void*,const void*);
typedef void (*Suma)( void*, void*);
typedef int (*Accion)(const void*,const void*);

#define TODO_OK 0
#define NO_MEMORY 1
#define DUPLICADOS 2

//Primitivas de Nodo
Nodo* crearNodo(void* elem,size_t tamElem);
void destruirNodo(Nodo* nae,void* elem,size_t tamElem);

//Primitivas de Lista
void crearLista(Lista* pl);
booleano insertarEnListaFondo(Lista* pl,void* elem,size_t tamElem);
void sumarDuplicadosListaOrdenada(Lista* pl,Suma sum,Cmp cmp);
void recorrerLista(Lista* pl,Accion accion,void* datosAccion);

#endif // LISTA_DINAMICA_H_INCLUDED
