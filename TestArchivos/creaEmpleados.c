#include <stdio.h>

typedef struct{
    unsigned int dni;
    char nombre[20];
    char apellido[20];
    double sueldo;
}Empleado;

int main(){

    Empleado empleados[8]={
        {44209416,"Ignacio","Romero",10000}, //X
        {41236594,"Maria","Romero",10000},//X
        {32651498,"Pablo","Perez",10000},
        {40156239,"Locura","Juanes",10000},
        {26536889,"Matias","Loquero",10000},//X
        {41256365,"Matias","Tarrico",10000},
        {35489652,"Nestor","Pan",10000},
    };

    FILE* pf=fopen("Empleados.dat","wb");

    //fwrite(empleados,sizeof(Empleado),8,pf);
    for(Empleado* i=empleados;i-empleados<7;i++){
       fwrite(i,sizeof(Empleado),1,pf);
       printf("%d\n",i->dni);
    }
    fclose(pf);
}
