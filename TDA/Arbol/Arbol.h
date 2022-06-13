#ifndef ARBOL_H
#define ARBOL_H

#include "..\..\Comun\Comun.h"



#ifdef TDA_ARBOL_IMP_DINAMICA
    #include "..\Arbol_Imp_Dinamica\Arbol_Dinamico.h"
#endif

typedef enum{
    COMPLETO,BALANCEADO,AVL,DESBALANCEADO
}TipoArbol;

typedef void (*ImprimirElemArbol)(void* elem,void* datos, int nivel);

/// -------------------- PRIMITIVAS --------------------

void crearArbol(Arbol* pa);

int insertarEnArbol(Arbol* pa, const void* elem, size_t tamElem,Cmp cmp,Actualizar actualizar);
booleano eliminarDeArbol(Arbol* pa, void* elem, size_t tamElem,Cmp cmp);
booleano buscarEnArbol(Arbol* pa, void* elem, size_t tamElem,Cmp cmp);
booleano arbolVacio(Arbol* pa);
void vaciarArbol(Arbol* pa);

void recorrerArbolPre(Arbol* pa,Accion acc,void* datosAccion);  // Raiz - hIzq - hDer
void recorrerArbolEn(Arbol* pa,Accion acc,void* datosAccion);   // hIzq - Raiz - hDer
void recorrerArbolPost(Arbol* pa,Accion acc,void* datosAccion); // hIzq - hDer - Raiz

int alturaArbol(const Arbol* pa);
int contarNodos(const Arbol* pa);
int contarNodosHasta(const Arbol* pa,int nivel);

booleano esArbolCompleto(const Arbol* pa);      //Arbol que tiene todos los hijos completos
booleano esArbolBalanceado(const Arbol* pa);    
booleano esArbolAVL(const Arbol* pa);
TipoArbol tipoArbol(const Arbol* pa);
void imprimirArbol(const Arbol* pa,ImprimirElemArbol imprimir,void* datosImprimir);

/// -------------------- PRIMITIVAS --------------------

#endif