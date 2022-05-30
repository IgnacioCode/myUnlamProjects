#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define ABS(x) x>0? (x):(-x)

int main(){

    /*float x;

    printf("Ingrese un numero: ");

    scanf("%f",&x);*/

    /*while(x!=0){

        printf("Su factorial es: %d\n",factorial(x));

        printf("Ingrese un numero: ");

        scanf("%d",&x);
    }*/

    //printf("e^% d es aproximadamente: %f",x,calculoE(x,0.01));

   // printf("La raiz cuadrada de %f es: %f",x,raizCuadrada(x,0.0001));

    /*if(esFibonnaci(15)){
        printf("si es");
    }
    else{
        printf("No es");

    }*/

    //printf("%d",clasificaNatural(10));

    printf("%d",sumatoriaMultiplos(4,3));
}

int sumarNumeros(int a, int b){
    return a+b;
    
}

