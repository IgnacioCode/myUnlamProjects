#include <stdio.h>
#include <stdlib.h>

#include "misPruebas.h"


int main(){

    Lista miLista;
    crearLista(&miLista);
    Producto miProducto;

    cargaProductosEnLista(&miLista,"stockProductos.txt");

    while(!listaVacia(&miLista)){
        eliminarDeListaFrente(&miLista,&miProducto,sizeof(Producto));
        imprimeProducto(&miProducto);
    }


    return 0;
}





