#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define charToInt(X) (X - '0')
#define intToChar(X) (X + '0')

// ISBN ==> 978 - codigo Pais (2d) - editor (3d) - nro Articulo (4d) - verificador (1d)
// Ej : 978-84-253-4025-3 --> 978842534025

typedef struct{
    char ISBN[18];
    int cantidad;
}Libro;

typedef enum{
    FALSO,VERDADERO
}booleano;

void creaArchivoStock();
Libro lineaALibro(char* linea);
int comparaISBN(const char* c1,const char* c2);

booleano verificaISBN(char* codigo);
booleano esLetra(char c);

#endif // LIBROS_H_INCLUDED
