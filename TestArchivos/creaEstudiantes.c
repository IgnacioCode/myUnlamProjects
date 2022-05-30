#include <stdio.h>

typedef struct{
    unsigned int dni;
    char nombre[20];
    char apellido[20];
    float promedio;
}Estudiante;

int main(){

    Estudiante estudiantes[8]={
        {44209416,"Ignacio","Romero",8.5}, //X
        {42516984,"Maria","Romero",7},//X
        {32651498,"Pablo","Perez",5.3},
        {40156239,"Jose","Juanes",4.5},
        {26536889,"Matias","Loquero",10},//X
        {41256365,"Matias","Tarrico",2.6},
        {35489652,"Ignacio","Pan",4},
    };

    FILE* pf=fopen("Estudiantes.dat","wb");

    //fwrite(estudiantes,sizeof(Estudiante),8,pf);
    for(Estudiante* i=estudiantes;i-estudiantes<7;i++){
        fwrite(i,sizeof(Estudiante),1,pf);
        printf("%d\n",i->dni);
    }
    fclose(pf);
}

