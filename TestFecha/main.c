#include <stdio.h>
#include <stdlib.h>

#include "..\Fecha\Fecha.h"

int main(){

    Fecha fecha1={2,4,2036};
    Fecha fecha2={19,4,2036};

    /*printf("Ingrese una fecha (dd/mm/aaaa): ");

    scanf("%d/%d/%d",&fecha1.dia,&fecha1.mes,&fecha1.anio);

    if(esFechaValida(fecha1)){
        printf("Es una fecha valida");
    }
    else{
        printf("No es una fecha valida");
    }*/

    fecha1=sumaDias(&fecha1,365);

    printf("Dia: %d Mes: %d Anio: %d",fecha1.dia,fecha1.mes,fecha1.anio);


}
