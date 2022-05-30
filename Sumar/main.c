#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ABS(X) ((X>=0)? (X):(-X))
#define charToInt(X) (X - '0')
#define intToChar(X) (X + '0')

#include "..\TDA\Pila\Pila.h"

int main(int argc, const char* argv[]){

    const char* num1=argv[1];
    const char* num2=argv[2];
    const char* i;
    int j;
    int res1,res2,resFinal,ac=0;
    char aux1,aux2,auxFinal;
    Pila p1,p2,pf;

    crearPila(&p1),crearPila(&p2),crearPila(&pf);

    int difLargos = strlen(num1)-strlen(num2);

    if(difLargos>0){
        //Apilo en la pila 2
        for(j=0;j< (ABS(difLargos));j++){
            aux1='0';
            apilar(&p2,&aux1,sizeof(char));
        }

    }
    else{
        //Apilo en la pila 1
        for(j=0;j< (ABS(difLargos));j++){
            aux1='0';
            apilar(&p1,&aux1,sizeof(char));
        }
    }

    for(i=num1;*i!='\0';i++){
        apilar(&p1,i,sizeof(char));
    }

    for(i=num2;*i!='\0';i++){
        apilar(&p2,i,sizeof(char));
    }

    while(!pilaVacia(&p1) && !pilaVacia(&p2)){

        desapilar(&p1,&aux1,sizeof(char));
        desapilar(&p2,&aux2,sizeof(char));

        res1 = charToInt(aux1);
        res2 = charToInt(aux2);

        resFinal=res1+res2+ac;

        ac=resFinal/10;

        resFinal-=10*ac;

        auxFinal = intToChar(resFinal);

        apilar(&pf,&auxFinal,sizeof(char));
    }

    printf("El resultado de la suma es: ");

    while(!pilaVacia(&pf)){
        desapilar(&pf,&auxFinal,sizeof(char));
        printf("%c",auxFinal);

    }

    return 0;
}


