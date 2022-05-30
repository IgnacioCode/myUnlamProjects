#include "Vectores.h"
#include <stdio.h>
//#include <memory.h>

void* buscaMenorDesde(void* inicio, void* fin,size_t tamElem, Cmp cmp);

booleano insertarElemento(Vector* vector, int valor){

    if(vector->cantEle == CAPACIDAD_VECTOR){
        return FALSO;
    }

    vector->vec[vector->cantEle]=valor;

    (vector->cantEle)++; //Aca la flecha tiene mas precedencia que el ++

    return VERDADERO;
}

void mostrarVector(Vector* vector){
    int i;
    printf("\n{");
    for(i=0;i<vector->cantEle-1;i++){
        printf("%d, ",vector->vec[i]);
    }

    printf("%d}\n",vector->vec[i]);
}

void crearVector(Vector* vector){

    vector->cantEle=0;
}

int insertarEnPos(Vector* vector,int pos, int valor){

    int i;

    if(vector->cantEle == CAPACIDAD_VECTOR){
        return 1;
    }

    for(i= (vector->cantEle) + 1;i>pos;i++){
        vector->vec[i]=vector->vec[i-1];
    }

    vector->vec[pos-1]=valor;

    if(pos>vector->cantEle){
        vector->cantEle += pos-vector->cantEle;
    }
    else{
        vector->cantEle++;
    }


    return 0;

}

void borraEleRepetido(Vector* vector,int elemento){

    int i;
    booleano leyoUno=FALSO;

    for(i=0;i<=vector->cantEle;i++){
        if(vector->vec[i] == elemento){
            if(leyoUno){
                correAtras(vector,i);   //La funcion al "borrar" empuja a la izquierda los elementos pisando el
                vector->cantEle--;      //elemento a borrar y restando la Cantidad de Elementos
            }
            leyoUno=VERDADERO;
        }

    }
}

void correAtras(Vector* vector,int pos){

    int i;

    for(i=pos;i<vector->cantEle-1;i++){

        vector->vec[i]=vector->vec[i+1];

    }

}

void borraRepetidos(Vector* vector){

    int i;
    int busquedaActual;

    for(i=0;i<vector->cantEle;i++){

        busquedaActual=vector->vec[i];

        borraEleRepetido(vector,busquedaActual);

    }

    /*
        Algoritmo que es n^2+n en complejidad mientras que hacerlo bien
        llegaria a x^2/2+3x/2. Siendo entonces que en el infinito seria
        a lo sumo solo el doble de eficiente
    */

}

///Funciones genericas de ordenamiento

void ordenarGenSeleccion(void* vector, int ce,size_t tamElem, Cmp cmp){

    void* i,*menor;
    void* ultimo = vector + (ce - 1) * tamElem;

    for(i=vector;i<ultimo;i+=tamElem){

        menor=buscaMenorDesde(i,ultimo,tamElem,cmp);

        if(menor!=i){
            intercambiar(i,menor,tamElem);
        }

    }

}

void* buscaMenorDesde(void* inicio, void* fin,size_t tamElem, Cmp cmp){

    void* j,*menor;

    menor=inicio;

    for(j=inicio+tamElem;j<=fin;j+=tamElem){

        if( cmp(j,menor) < 0){
            menor = j;
        }
    }

    return menor;
}

void intercambiar(void* destino, void* origen,size_t tamElem){

    char aux[tamElem];    //Ya que tamElem esta definido antes de entrar en la memoria, crea el vector con el tama�o adecuado y lo borra cuando termina
    //void* aux =malloc(tamElem); //Reserva memoria dinamica
    memcpy(aux,origen,tamElem);
    memcpy(origen,destino,tamElem);
    memcpy(destino,aux,tamElem);
    //free(aux);                  //Libera la memoria que se reservo para aux

}
