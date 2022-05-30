#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "..\Comun\Comun.h"

typedef struct{

    unsigned int codigo;
    char descripcion[101];
    int cantidad;
    float precio;

}Producto;

typedef struct{
    unsigned int dni;
    char nombre[20];
    char apellido[20];
    double sueldo;
}Empleado;

typedef struct{
    unsigned int dni;
    char nombre[20];
    char apellido[20];
    float promedio;
}Estudiante;



int MostrarMenu();
int LlenarVector(float*,int);
int Minimo(float*,int);
float promedioPosPares(float*,int);
void mostrarInverso(float*,int);
void GuardarEnArchivo(FILE*,float*,int);

///Clase del 21/4 MERGE

void mergeArchivoProductos(char* archivoBase,const char* archivoCambios);
void cambiaExtension(char* archivo,char* cadena, const char* nuevaExtension);
void creaProductos(const char* nombreArchivo);
void creaMovimientos(const char* nombreArchivo);
void muestraProductos(const char* nombreArchivo);
void muestraMovimientos(const char* nombreArchivo);

///Funcion INTERSECCION

void interseccionArchivosProductos(char* archivo1,char* archivo2,char* archivoResultante);

///Funcion Punto 12

int ingresoAlumnos(char[][101][31],float[][101]);
void imprimeResultados(FILE* archivo,char nombresApellidos[][101][31],float notas[][101],int cantAlum);
void calculaPromedioGenerales(float notas[][101],int cantAlumnos);
void calculaPromedio(float array[][101],int alumno);

///Funcion Punto 13

void actualizaSueldos(FILE* archivoEstudiantes,FILE* archivoEmpleados,float porAumento);
int datosIguales(Empleado empleado,Estudiante estudiante);

///Trabajo Practico 3
///Funcion Punto 3

int mostrarMenuPila();
void cargarRegEnPila(Pila* pp,FILE* archivo);
void cargarEnPila(Pila* pp);
void devolverTopePila(Pila* pp);
void sacarTopePila(Pila* pp);
void cargarRestoPila(Pila* pp,FILE* archivo);

#endif // ARCHIVOS_H_INCLUDED
