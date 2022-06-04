#include <stdio.h>
#include <stdlib.h>
#include "libros.h"

void sumarDatos(int a);

int main(){

    creaArchivoStock();

    //printf("-------ISBN-------|Stock");

    actualizarStock


}

void actualizarStock(char* archivoStock,char* archivoActualizacion){

    FILE* pfStock = fopen(archivoStock,"rb");
    FILE* pfActu = fopen(archivoStock,"rt");
    FILE* pfNue = fopen("temporalStock.temp","wb");
    FILE* pfE = fopen("archivoErrores.txt","wt");

    int comp;
    Libro stockLeido,actualizacionLeida;


    comp = comparaISBN(stockLeido.ISBN,actualizacionLeida.ISBN);
    if(comp==0){
        stockLeido.cantidad+=actualizacionLeida.cantidad;
        fwrite(&stockLeido,sizeof(Libro),1,pfNue);

        fscanf(pfActu,"%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
        fread(&stockLeido,sizeof(Libro),1,pfStock);
    }
    else if(comp >0){
        fprintf(pfE,"%s|%d",actualizacionLeida.ISBN,actualizacionLeida.cantidad);
        fscanf(pfActu,"%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
    }
    else{
        fwrite(&stockLeido,sizeof(Libro),1,pfNue);
        fread(&stockLeido,sizeof(Libro),1,pfStock);
    }




}

