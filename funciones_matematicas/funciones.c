#include <stdio.h>
#include <stdlib.h>
#define ABS(x) x>0? (x):(-x)

int potencia(int base,int exponente){

    int i;
    int resultado=base;
    for(i=0;i<exponente-1;i++){
        resultado*=base;

    }
    return resultado;
}

int factorial(int numero){

    if(numero==0 || numero==1){
        return 1;
    }
    else{
        return numero*factorial(numero-1);
    }

}

int redondeo(int x){

    return 0;
}

float calculoE(int x, float Tol){

    float valorCalculado=1;
    float nuevoTermino=0;
    int i=1;

    do{
        nuevoTermino=pow(x,i)/(float)factorial(i);

        valorCalculado+=nuevoTermino;
        i++;
    }while(nuevoTermino>Tol);

    return valorCalculado;
}

float raizCuadrada(float numero,float TOL){

    float nuevoTermino;
    float terminoAnterior=1;

    nuevoTermino=(0.5)*(terminoAnterior+(numero/terminoAnterior));

    while(ABS((nuevoTermino-terminoAnterior))>TOL){

        terminoAnterior=nuevoTermino;
        nuevoTermino=(0.5)*(terminoAnterior+(numero/terminoAnterior));

    }

    return nuevoTermino;

}

int esFibonnaci(int numero){

    int termino1=0,termino2=1,nuevoTermino;

    nuevoTermino=termino1+termino2;

    while(nuevoTermino<numero){
        termino1=termino2;
        termino2=nuevoTermino;
        nuevoTermino=termino1+termino2;
    }

    return nuevoTermino==numero? 1:0;

}

int clasificaNatural(int numero){
    ///  0-->  Perfecto
    ///  1-->  Abundante
    /// -1-->  Deficiente

    int i;
    int sumaDivisores=0;

    for(i=1;i<numero;i++){

        if(numero%i==0){
            sumaDivisores+=i;
        }

    }

    if(sumaDivisores>=numero){
        if(sumaDivisores==numero){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        return -1;
    }

}

int sumatoriaNaturales(int tope){

    return (tope)*(tope+1)/(2);

}

int sumatoriaMultiplos(int terminos, int divisor){

    return (divisor*terminos*(terminos+1))/(2);

}
