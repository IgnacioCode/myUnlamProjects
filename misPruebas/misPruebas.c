#include "misPruebas.h"

void cargaProductosEnLista(Lista* pl,char* archivoProductos){

    FILE* pfProd = fopen(archivoProductos,"rt");

    Producto productoLeido;

    fscanf(pfProd,"%d|%[^|]|%d|%f",&productoLeido.codigo,productoLeido.descripcion,&productoLeido.cantidad,&productoLeido.precio);
    while(!feof(pfProd)){
        insertarEnListaFondo(pl,&productoLeido,sizeof(Producto));

        fscanf(pfProd,"%d|%[^|]|%d|%f",&productoLeido.codigo,productoLeido.descripcion,&productoLeido.cantidad,&productoLeido.precio);
    }

    fclose(pfProd);


}

void imprimeProducto(Producto* prod){
    printf("%d|%-30s|%d|%.2f\n",prod->codigo,prod->descripcion,prod->cantidad,prod->precio);
}
