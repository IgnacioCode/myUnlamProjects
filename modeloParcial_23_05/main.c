#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "ListaModelo\Lista_Dinamica.h"

#define aMayus(X) (X+32)
#define aMinus(X) (X-32)
#define esMinus(X) (X>=97 && X<=122? (1):(0))
#define esMayus(X) (X>=65 && X<=90? (1):(0))



typedef struct Producto{

    unsigned codigo;
    char nombre[31];
    int stock;

}Producto;

typedef struct{

    unsigned codigo;
    int saldo;

}Transaccion;

typedef void (*Norm)(char*);
void normalizaCadena(char* cad,char[],Norm norm,FILE* pf);
void primerasMayusculas(char* cad);
void creaProductos1();
void creaProductos2();
void creaProductos3();
void fusionArchivos(char archivo1[],char archivo2[],char archivoRes[]);
void imprimeStock(char[]);
void cargaArchivoEnLista(char archivo[],Lista* pl);
void creaTransaccion();
void actualizaStock(char archivo1[],char archivo2[]);

int comparaCodigosProductos(const void* c1, const void* c2){
    Producto* p1 = (Producto*)c1;
    Producto* p2 = (Producto*)c2;

    return p1->codigo-p2->codigo;
}

void sumaProductos(void* c1,void* c2){

    Producto* p1 = (Producto*)c1;
    Producto* p2 = (Producto*)c2;

    p1->stock+=p2->stock;

}

int imprimeProducto(const void* d1,const void* datos){

    Producto* p1 = (Producto*)d1;
    printf("%-10s | %d : %d\n",p1->nombre,p1->codigo,p1->stock);
    return 0;
}


int main(){

    Lista listaDeProductos;
    crearLista(&listaDeProductos);

    creaProductos1();
    creaProductos2();
    creaProductos3();
    creaTransaccion();

    //char miCadena[35]="pEDazO dE tROLiTA MaLA";
    //normalizaCadena(miCadena,"primerasMayusculas.txt",primerasMayusculas,pf);

    fusionArchivos("stockLocal1.dat","stockLocal2.dat","fusionStocks.dat");

    //cargaArchivoEnLista("fusionStocks.dat",&listaDeProductos);

    imprimeStock("fusionStocks.dat");

    actualizaStock("fusionStocks.dat","transacciones.dat");

    printf("---------------------------------------\n");
    imprimeStock("fusionStocks.dat");

    cargaArchivoEnLista("stockLocal3.dat",&listaDeProductos);
    sumarDuplicadosListaOrdenada(&listaDeProductos,sumaProductos,comparaCodigosProductos);

    recorrerLista(&listaDeProductos,imprimeProducto,NULL);

}

void normalizaCadena(char* cad,char nombreFunc[],Norm norm,FILE* pf){

    pf=fopen(nombreFunc,"at");

    norm(cad);

    fprintf(pf,"%s\n",cad);

    fclose(pf);
}

void primerasMayusculas(char* cad){

    char* act=cad;


    while(*act!='\0'){
        *act = toupper(*act);
        act++;
        while(*act!=' ' && *act!='\0'){
            if(esMayus(*act)){
                *act = tolower(*act);
            }
            act++;
        }
        if(*act){
            act++;
        }

    }


}

void fusionArchivos(char archivo1[],char archivo2[],char archivoRes[]){

    int comparacion;
    FILE* pf1 = fopen(archivo1,"rb");
    FILE* pf2 = fopen(archivo2,"rb");
    FILE* pfR = fopen(archivoRes,"wb");

    Producto leido1,leido2,resultante;
    fread(&leido1,sizeof(Producto),1,pf1);
    fread(&leido2,sizeof(Producto),1,pf2);

    while(!feof(pf1) && !feof(pf2)){
        comparacion=leido1.codigo-leido2.codigo;
        if(comparacion==0){ //Actualizo sumando
            resultante=leido1;
            resultante.stock+=leido2.stock;
            fwrite(&resultante,sizeof(Producto),1,pfR);
            fread(&leido1,sizeof(Producto),1,pf1);
            fread(&leido2,sizeof(Producto),1,pf2);
        }
        else if(comparacion>0){  //Añado producto del archivo 2
            resultante=leido2;
            fwrite(&resultante,sizeof(Producto),1,pfR);
            fread(&leido2,sizeof(Producto),1,pf2);
        }
        else{   //Añado producto del archivo 1
            resultante=leido1;
            fwrite(&resultante,sizeof(Producto),1,pfR);
            fread(&leido1,sizeof(Producto),1,pf1);
        }

    }
    resultante=leido1;
    while(!feof(pf1)){

        fwrite(&resultante,sizeof(Producto),1,pfR);
        fread(&resultante,sizeof(Producto),1,pf1);
    }
    resultante=leido2;
    while(!feof(pf2)){
        fwrite(&resultante,sizeof(Producto),1,pfR);
        fread(&resultante,sizeof(Producto),1,pf2);
    }

    fclose(pf1);
    fclose(pf2);
    fclose(pfR);

}

void creaProductos1(){

    Producto misProductos[9]={
        {1001,"Leche",5},
        {1002,"Chocolate",3},
        {1003,"Arroz",2},
        {1004,"Coca",11},
        {1006,"Galletitas",9},
        {1007,"Yogurt",2},
        {1008,"Metal",1},
        {1009,"Vinagre",1},
        {1010,"Aceite",5},
    };

    FILE* pf = fopen("stockLocal1.dat","wb");

    fwrite(misProductos,sizeof(Producto),9,pf);

    fclose(pf);
}

void creaProductos2(){

    Producto misProductos[6]={
        {1001,"Leche",8},
        {1002,"Chocolate",1},
        {1003,"Arroz",9},
        {1004,"Coca",3},
        {1005,"Tutuca",4},
        {1008,"Metal",2},
    };

    FILE* pf = fopen("stockLocal2.dat","wb");

    fwrite(misProductos,sizeof(Producto),6,pf);

    fclose(pf);
}

void creaProductos3(){

    Producto misProductos[6]={
        {1001,"Leche",8},
        {1001,"Leche",4},
        {1003,"Arroz",9},
        {1004,"Coca",3},
        {1004,"Coca",6},
        {1008,"Metal",2},
    };

    FILE* pf = fopen("stockLocal3.dat","wb");

    fwrite(misProductos,sizeof(Producto),6,pf);

    fclose(pf);
}

void imprimeStock(char archivo[]){

    FILE* pf=fopen(archivo,"rb");
    Producto aux;
    fread(&aux,sizeof(Producto),1,pf);
    while(!feof(pf)){
        printf("%d | %-11s | %d\n",aux.codigo,aux.nombre,aux.stock);
        fread(&aux,sizeof(Producto),1,pf);

    }

    fclose(pf);

}

void cargaArchivoEnLista(char archivo[],Lista* pl){

    FILE* pf=fopen(archivo,"rb");

    Producto leido;

    fread(&leido,sizeof(Producto),1,pf);
    while(!feof(pf)){
        insertarEnListaFondo(pl,&leido,sizeof(Producto));
        fread(&leido,sizeof(Producto),1,pf);
    }

}

void creaTransaccion(){

    Transaccion misProductos[6]={
        {1001,8},
        {1002,-1},
        {1001,9},
        {1004,3},
        {1005,-4},
        {1027,2}
    };

    FILE* pf = fopen("transacciones.dat","wb");

    fwrite(misProductos,sizeof(Transaccion),6,pf);

    fclose(pf);

}

void actualizaStock(char archivo1[],char archivo2[]){

    FILE* pfS=fopen(archivo1,"r+");
    FILE* pfT=fopen(archivo2,"rb");
    FILE* pfE=fopen("ERRORES_ACTUALIZACIONES.txt","wt");

    Producto productoLeido;
    Transaccion transacLeida;

    fread(&transacLeida,sizeof(Transaccion),1,pfT);

    while(!feof(pfT)){
        fread(&productoLeido,sizeof(Producto),1,pfS);
        while(productoLeido.codigo!=transacLeida.codigo && !feof(pfS)){
            fread(&productoLeido,sizeof(Producto),1,pfS);
        }
        if(!feof(pfS)){
            productoLeido.stock+=transacLeida.saldo;
            fseek(pfS,-(1*sizeof(Producto)),SEEK_CUR);
            fwrite(&productoLeido,sizeof(Producto),1,pfS);
        }
        else{
            fprintf(pfE,"No existe el producto %d\n",transacLeida.codigo);
        }
        fseek(pfS,0,SEEK_SET);
        fread(&transacLeida,sizeof(Transaccion),1,pfT);
    }

    fclose(pfS);
    fclose(pfT);
    fclose(pfE);

}
