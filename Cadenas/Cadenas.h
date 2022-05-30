#ifndef CADENAS_H_INCLUDED
#define CADENAS_H_INCLUDED
#include "..\Comun\Comun.h"

typedef struct{

    char* inicio;
    char* fin;

}Palabra;

typedef struct{

    char* cursor;
    char* iniCad;
    booleano finSec;

}SecPal;

void normalizar(const char* origen,const char* destino);
void creaSecPal(SecPal* sl,char* origen);
void leerPal(SecPal* sl,Palabra* pal);
int finSecPal(SecPal* secuencia);
void escribePal(SecPal* se,Palabra* pal);
void escribeCaracter(SecPal* se,char caracter);
void mueveCursor(SecPal* se,int movimiento);
void rebobinarSecPal(SecPal* secuencia);
void formateoMayusyMin(Palabra* pal);
int esLetra(char letra);
char aMayuscula(char caracter);
char aMinuscula(char caracter);

#endif // CADENAS_H_INCLUDED
