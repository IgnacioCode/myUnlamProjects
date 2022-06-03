#ifndef LISTA_H
#define LISTA_H

#ifdef LISTA_IMP_ESTATICA
    #include "..\Lista_Imp_Estatica\Lista_Imp_Estatica.h"
#endif
#ifdef LISTA_IMP_DINAMICA
    #include "..\Lista_Imp_Dinamica\Lista_Dinamica.h"
#endif
#ifdef LISTA_IMP_DINAMICA_DOBLE
    #include "..\Lista_Imp_Dinamica_Doble\Lista_Dinamica_Doble.h"
#endif


void crearLista(Lista* pl);
int insertarEnListaOrdenada(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarEnListaEnPos(Lista* pl, const void* elem, size_t tamElem,int pos);
int insertarEnListaFrentre(Lista* pl, const void* elem, size_t tamElem);
int insertarEnListaFondo(Lista* pl, const void* elem, size_t tamElem);
booleano eliminarDeListaOrdenada(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
booleano eliminarDeListaEnPos(Lista* pl, void* elem, size_t tamElem,int pos);
booleano eliminarDeListaFrente(Lista* pl, void* elem, size_t tamElem);
booleano eliminarDeListaFondo(Lista* pl, void* elem, size_t tamElem);
booleano buscarEnListaOrdenada(const Lista* pl, void* elem, size_t tamElem, Cmp cmp);
booleano listaVacia(const Lista* pl);
booleano listaLlena(const Lista* pl,size_t tamElem);
void ordenarLista(Lista* pl, Cmp cmp);
int eliminarDuplicados(Lista* pl, Cmp cmp);
int eliminarDuplicadosOrdenada(Lista* pl, Cmp cmp);
void vaciarLista(Lista* pl);
void recorrerLista(Lista* pl,Accion accion,void* datosAccion);  //Recorrida Interna

/// Iterador (Recorrida externa)
booleano crearIterador(Iterador* it,const Lista* pl);
booleano primeroDeLista(Iterador* it, void* elem, size_t tamElem);
booleano haySiguienteDeLista(Iterador* it);
booleano siguienteDeLista(Iterador* it, void* elem, size_t tamElem);
booleano finLista(Iterador* it);

#endif
