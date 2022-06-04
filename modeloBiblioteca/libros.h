#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define charToInt(X) (X - '0')
#define intToChar(X) (X + '0')
#define MIN(X,Y) (X>Y? Y:X)

// ISBN ==> 978 - codigo Pais (2d) - editor (3d) - nro Articulo (4d) - verificador (1d)
// Ej : 978-84-253-4025-3 --> 978842534025

typedef enum{
    FALSO,VERDADERO
}booleano;

typedef struct{
    char ISBN[18];
    int cantidad;
}Libro;

// ----------- Primitivas Nodo -----------

typedef struct SNodo{

    void* elem;
    size_t tamElem;
    struct SNodo* sig;

}Nodo;

Nodo* crearNodo(void* elem,size_t tamElem);
void destruirNodo(Nodo* nae,void* elem,size_t tamElem);

// ----------- Primitivas Lista -----------

typedef Nodo* Lista;
typedef int (*Cmp)(const void*,const void*);

void crearLista(Lista* pl);
booleano insertarEnListaOrdenada(Lista* pl,void*elem,size_t tamElem,Cmp cmp);
void eliminarDeListaFondo(Lista* pl,void* elem,size_t tamElem);
void eliminarDeListaFrente(Lista* pl,void* elem,size_t tamElem);
int cantElementosDeLista(Lista* pl);

// --------- Primitivas Biblioteca ---------



void creaArchivoStock();
int comparaISBN(const char* c1,const char* c2);
booleano verificaISBN(char* codigo);
booleano esNumero(char c);
booleano esLetra(char c);

#endif // LIBROS_H_INCLUDED
