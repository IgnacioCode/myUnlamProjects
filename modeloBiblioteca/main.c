#include <stdio.h>
#include <stdlib.h>
#include "libros.h"

void sumarDatos(int a);
void actualizarStock(const char* archivoStock,const char* archivoActualizacion);

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

    int cantElemLista=0,comp,codigoValido;
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
                
                fscanf(pfActu,"\n%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
                fread(&stockLeido,sizeof(Libro),1,pfStock);
            }
            else if(comp >0){
                fprintf(pfE,"%s|%d\n",actualizacionLeida.ISBN,actualizacionLeida.cantidad);
                fscanf(pfActu,"\n%[^|]|%d",actualizacionLeida.ISBN,&actualizacionLeida.cantidad);
            }
            else{
                fwrite(&stockLeido,sizeof(Libro),1,pfNue);
                fread(&stockLeido,sizeof(Libro),1,pfStock);
            }
        }

    }

    while(!feof(pfStock)){
        fwrite(&stockLeido,sizeof(Libro),1,pfNue);
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


}

