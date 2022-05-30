#ifndef VECTORES_H_INCLUDED
#define VECTORES_H_INCLUDED

#include "..\Comun\Comun.h"
#include <stdio.h>

#define CAPACIDAD_VECTOR 10

typedef struct{

    int vec[CAPACIDAD_VECTOR];
    int cantEle;

}Vector;

typedef int (*Cmp)(const void*,const void*);

booleano insertarElemento(Vector* vector, int valor);
void mostrarVector(Vector* vector);
void crearVector(Vector* vector);
int insertarEnPos(Vector* vector,int pos, int valor); //Inserta en la posicion corriendo los demas elementos
void borraEleRepetido(Vector* vector,int valor);
void correAtras(Vector* vector,int pos);
void borraRepetidos(Vector* vector);

///Clase 28/4 Ordenamiento generico

void ordenarGenSeleccion(void* vector, int ce,size_t tamElem, Cmp cmp);
void ordenarGenBurbujeo(void* vector, int ce,size_t tamElem, Cmp cmp);
void ordenarGenInsercion(void* vector, int ce,size_t tamElem, Cmp cmp);

void intercambiar(void* destino, void* origen,size_t tamElem);







#endif // VECTORES_H_INCLUDED
