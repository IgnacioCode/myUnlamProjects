#include <stdio.h>
#include <stdlib.h>
//#include "..\Vectores\Vectores.h"
#include "C:\Users\nacho\Desktop\Programas\Vectores\Vectores.h"
int cmpInt(const void* a,const void* b);

int main(){

    /*int vec[CAPACIDAD_VECTOR] = {12,7,-6};
    int cantEle= 3;*/

    /*Vector miVector;
    crearVector(&miVector);

    insertarElemento(&miVector,2);
    insertarElemento(&miVector,3);
    insertarElemento(&miVector,2);
    insertarElemento(&miVector,7);
    insertarElemento(&miVector,2);
    insertarElemento(&miVector,9);
    insertarElemento(&miVector,15);
    insertarElemento(&miVector,15);


    mostrarVector(&miVector);

    borraRepetidos(&miVector);

    mostrarVector(&miVector);*/

    ///Clase 28/4 Ordenamiento

    int vector[30]={2,6,8,4,1,3,9,5,7,10,14,29,34,5,18,92,70,58,39,41,38,41,90,73,57,83,81,20,75,27};

    ordenarGenSeleccion(vector,30,sizeof(int),cmpInt);

    for(int i=0;i<30;i++){
        printf("-%d- ",vector[i]);
    }

}

int cmpInt(const void* a,const void* b){

    int* ai = (int*)a;  //Aca casteamos los punteros void para facilitar
    int* bi = (int*)b;  //la asignacion a una variable puntero del tipo que buscamos

    return *ai - *bi;
}
