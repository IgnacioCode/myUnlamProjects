#include <stdio.h>
#include <stdlib.h>
#define PILA_IMPL_ESTATICA
#include "..\TDA\Pila\Pila.h"
#include "..\Archivos\Archivos.h"

int main()
{
    /*int opcion=0;
    float vec[10];
    int cantElem = 10;
    FILE* archivo;

    archivo=fopen("vector.txt", "wt");

    cantElem=LlenarVector(vec, cantElem);

    while(opcion!=4)
    {
        fflush(stdin);

        opcion = MostrarMenu();

        switch (opcion)
        {
        case 1:
            printf("El minimo numero es: %.2f",vec[Minimo(vec, cantElem)]);
            printf("\n Pulse ENTER para continuar...");
            fflush(stdin);
            getchar();
            break;

        case 2:
            printf("El promedio de las posiciones pares es: %.2f",promedioPosPares(vec, cantElem));
            printf("\n Pulse ENTER para continuar...");
            fflush(stdin);
            getchar();
            break;

        case 3:
            mostrarInverso(vec, cantElem);
            printf("\n Pulse ENTER para continuar...");
            fflush(stdin);
            getchar();
            break;
        }
    }
    GuardarEnArchivo(archivo, vec, cantElem);
    fclose(archivo);

    return 0;*/

    ///Prueba algoritmo Merge

    /*creaProductos("misProductos.dat");
    creaMovimientos("misMovimientos.dat");

    printf("---------Productos---------\n");
    muestraProductos("misProductos.dat");
    printf("--------Movimientos--------\n");
    muestraProductos("misMovimientos.dat");

    printf("---------Resultado---------\n");
    mergeArchivoProductos("misProductos.dat","misMovimientos.dat");

    muestraProductos("misProductos.dat");*/

    /*creaProductos("misProductos.dat");
    creaMovimientos("misMovimientos.dat");

    printf("---------Productos---------\n");
    muestraProductos("misProductos.dat");
    printf("--------Movimientos--------\n");
    muestraProductos("misMovimientos.dat");

    printf("---------Resultado---------\n");
    interseccionArchivosProductos("misProductos.dat","misMovimientos.dat","miInterseccion.dat");
    muestraProductos("miInterseccion.dat");*/

    ///Ejercicio 12

    /* FILE* pf = fopen("notasAlumnos.txt","wt");

    char nombresApellidos[2][101][31];
    float notas[7][101];
    int cantAlumnos;

    cantAlumnos=ingresoAlumnos(nombresApellidos,notas);

    imprimeResultados(pf,nombresApellidos,notas,cantAlumnos);

    fclose(pf);*/

    ///Ejercicio 13

    /*FILE* pfEmp=fopen("Empleados.dat","r+b");
    FILE* pfEst=fopen("Estudiantes.dat","r+b");

    actualizaSueldos(pfEmp,pfEst,7.28);

    fclose(pfEmp);
    fclose(pfEst);
    */

    FILE* pf=fopen("registros.dat","rb");

    Pila miPila;
    crearPila(&miPila);

    cargarRegEnPila(&miPila,pf); 

    switch(mostrarMenuPila()){
    case 1:
        cargarEnPila();
        break;
    case 2:
        devolverTopePila();
        break;
    case 3:
        sacarTopePila();
        break;
    case 4:
        pf=fopen("registros.dat","ab");
        cargarRestoPila();
        break;
    }


    return 0;

}
