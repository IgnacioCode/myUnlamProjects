#include <stdio.h>
#include <stdlib.h>
#include "..\Cadenas\Cadenas.h"

void imprimeDir(int* pi);

int main(){

    char cadena1[41]="!%hoLA $$mundo(!$como va";
    char cadena2[41];

    int a=2,b=3;
    int* pi = &a;

    normalizar(cadena1,cadena1);

    miStrcpy(cadena2,cadena1);

    printf("%s\n%s\n",cadena2,cadena1);

    imprimeDir(pi);
    imprimeDir(&b);
    printf("%p\n",&pi);

}

void imprimeDir(int* pi){

    printf("%p\n",&pi);

}
