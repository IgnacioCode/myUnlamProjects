#include <stdio.h>
#include <stdlib.h>
#define COLA_IMP_DINAMICA
#include "..\TDA\Cola\Cola.h"

int main(){

    Cola miCola;
    int a,b,c;
    a=1;
    b=2;

    crearCola(&miCola);

    encolar(&miCola,&a,sizeof(int));
    encolar(&miCola,&b,sizeof(int));

    desencolar(&miCola,&c,sizeof(int));
    printf("%d ",c);
    encolar(&miCola,&a,sizeof(int));
    desencolar(&miCola,&c,sizeof(int));
    printf("%d ",c);

    vaciarCola(&miCola);

    encolar(&miCola,&b,sizeof(int));

    desencolar(&miCola,&c,sizeof(int));
    printf("%d ",c);

    return 0;

}
