#ifndef MISPRUEBAS_H_INCLUDED
#define MISPRUEBAS_H_INCLUDED

#define LISTA_IMP_DINAMICA
#include "..\TDA\Lista\Lista.h"
#define TAM_NOMBRE 30
typedef struct{

    unsigned int codigo;
    char descripcion[TAM_NOMBRE];
    int cantidad;
    float precio;

}Producto;

void cargaProductosEnLista(Lista* pl,char* archivoProductos);
void imprimeProducto(Producto* prod);

#endif
