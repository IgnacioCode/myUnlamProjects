#include <stdio.h>
#include <stdlib.h>
#include "libros.h"

void sumarDatos(int a);
void actualizarStock(const char* archivoStock,const char* archivoActualizacion);
void insertaHasta5Ordenada(Lista* pl,void* elem,size_t tamElem,Cmp cmp);

int comparaVentasMayor(const void* l1,const void* l2){

    Libro* libro1= (Libro*)l1;
    Libro* libro2= (Libro*)l2;

    return libro1->cantidad-libro2->cantidad;
}

int main(){

    creaArchivoStock();

    actualizarStock("archivoStockLibros.dat","nuevoStock.txt");


}

void actualizarStock(const char* archivoStock,const char* archivoActualizacion){

    Lista listaTop5;
    crearLista(&listaTop5);
    FILE* pfStock = fopen(archivoStock,"rb");
    FILE* pfActu = fopen(archivoActualizacion,"rt");
    FILE* pfNue = fopen("temporalStock.temp","wb");
    FILE* pfE = fopen("archivoErrores.txt","wt");

    int comp,codigoValido,i;
    Libro stockLeido,actualizacionLeida;

    fscanf(pfActu,"%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
    fread(&stockLeido,sizeof(Libro),1,pfStock);

    while(!feof(pfStock) && !feof(pfActu)){
        comp = comparaISBN(stockLeido.ISBN,actualizacionLeida.ISBN);
        codigoValido = verificaISBN(actualizacionLeida.ISBN);
        if(!codigoValido){
            fprintf(pfE,"%s|%d\n",actualizacionLeida.ISBN,actualizacionLeida.cantidad);
            fscanf(pfActu,"\n%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
        }
        else{
            if(comp==0){
                stockLeido.cantidad+=actualizacionLeida.cantidad;
                fwrite(&stockLeido,sizeof(Libro),1,pfNue);
                insertaHasta5Ordenada(&listaTop5,&stockLeido,sizeof(Libro),comparaVentasMayor);

                fscanf(pfActu,"\n%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
                fread(&stockLeido,sizeof(Libro),1,pfStock);
            }
            else if(comp >0){
                fprintf(pfE,"%s|%d\n",actualizacionLeida.ISBN,actualizacionLeida.cantidad);
                fscanf(pfActu,"\n%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
            }
            else{
                fwrite(&stockLeido,sizeof(Libro),1,pfNue);
                insertaHasta5Ordenada(&listaTop5,&stockLeido,sizeof(Libro),comparaVentasMayor);
                fread(&stockLeido,sizeof(Libro),1,pfStock);
            }
        }

    }

    while(!feof(pfStock)){
        fwrite(&stockLeido,sizeof(Libro),1,pfNue);
        insertaHasta5Ordenada(&listaTop5,&stockLeido,sizeof(Libro),comparaVentasMayor);
        fread(&stockLeido,sizeof(Libro),1,pfStock);
    }

    while(!feof(pfActu)){
        fprintf(pfE,"%s|%d\n",actualizacionLeida.ISBN,actualizacionLeida.cantidad);
        fscanf(pfActu,"\n%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
    }

    fclose(pfStock);
    fclose(pfNue);
    fclose(pfActu);
    fclose(pfE);

    remove(archivoStock);
    rename("temporalStock.temp",archivoStock);

    printf("5 libros mas vendidos\n\n");    //printf("------------------------\n");
    printf("-------ISBN------|Ventas\n");
    int cantElem = cantElementosDeLista(&listaTop5);
    for(i=0;i<cantElem;i++){
        eliminarDeListaFrente(&listaTop5,&stockLeido,sizeof(Libro));
        printf("%s|%d\n",stockLeido.ISBN,stockLeido.cantidad);
    }


}

void insertaHasta5Ordenada(Lista* pl,void* elem,size_t tamElem,Cmp cmp){

    if(cantElementosDeLista(pl)<5){
        insertarEnListaOrdenada(pl,elem,tamElem,cmp);
    }
    else{
        insertarEnListaOrdenada(pl,elem,tamElem,cmp);
        eliminarDeListaFondo(pl,NULL,0);
    }

}
