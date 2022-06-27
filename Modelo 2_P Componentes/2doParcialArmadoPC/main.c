#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"
#include <string.h>

/**/
#define ERROR_ALU 404
/**/

#define MIN(X,Y) (X>Y? Y:X)

typedef enum{
	FALSO,VERDADERO
}booleano;

#include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#include "../TDAArbol/TDAArbol.h"
#include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include "../TDALista/TDALista.h"
#include "../TDA/TDA.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

int comparaComponentes(const void* c1,const void* c2){

	Componente* comp1 = (Componente*)c1;
	Componente* comp2 = (Componente*)c2;
	return strcmp(comp1->codigo,comp2->codigo);
}
int comparaArmados(const void* a1,const void* a2){
	ArmadoYRep* comp1 = (ArmadoYRep*)a1;
	ArmadoYRep* comp2 = (ArmadoYRep*)a2;
	return strcmp(comp1->codigo,comp2->codigo);
}
void sumaArmados(void* a1,const void* a2){

}
int comparaIndices(const void* i1,const void* i2){
	IndComponente* comp1 = (IndComponente*)i1;
	IndComponente* comp2 = (IndComponente*)i2;
	return strcmp(comp1->codigo,comp2->codigo);
}


int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);
void destruirNodoD_ALU(NodoD* nae, void* elem, size_t tamElem);
NodoD* crearNodoD_ALU(void* elem,size_t tamElem);
void eliminarDeListaFrente_ALU(Lista* pl,void* elem,size_t tamElem);
booleano insertarEnListaFondo_ALU(Lista* pl,void* elem, size_t tamElem);
void cargaElementoMedio_ALU(int ini, int fin, FILE* pf, Arbol* pa, size_t tamElem, Cmp cmp);
void cargarArchivoEnArbolOrd_ALU(Arbol* pa, FILE* pf,size_t tamElem, Cmp cmp);
void cargarArchivoEnLista_ALU(Lista* pl, FILE* pf);
void crearLista_ALU(Lista* pl);
booleano buscarEnArbol_ALU(Arbol*pa, void* elem,size_t tamElem,Cmp cmp);
booleano insertarEnArbol_ALU(Arbol* pa,void* elem,size_t tamElem,Cmp cmp);
booleano listaVacia_ALU(Lista* pl);
NodoA* crearNodoA_ALU(void* elem,size_t tamElem);
void destruirNodoA_ALU(NodoA* nae, void* elem, size_t tamElem);
void crearArbol_ALU(Arbol* pa);

/***/


#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2


int main(int argc, char* argv[])
{
    /*setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para m�quinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para m�quinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para m�quinas Windows
    */
    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

	puts("Componentes antes de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
	puts("");

	puts("Armados/Reparaciones:");
	mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
	puts("");
    //int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************
	/** Descomente esta l�nea y comente la de arriba para probar su c�digo              **/
	int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************

	if(resp != TODO_OK){
		puts("Error actualizando los componentes.");
		return resp;
	}


	puts("\nComponentes despues de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}


int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep){
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que ser� el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.FILE* bin;
	Componente componenteAux;
	IndComponente indiceAux;

	char pathIndices[16];
	strcpy(pathIndices,pathComponentes);
	pathIndices[11] = '\0';
	strcat(pathIndices,".idx");

	FILE* pfComponentes=fopen(pathComponentes,"r+b");
	FILE* pfArmados=fopen(pathArmadoYRep,"rb");
	FILE* pfIndices=fopen(pathIndices,"rb");

	if(!pfComponentes || !pfArmados || !pfIndices){
		printf("No se pudo abrir alguno de los archivos...");
		return 1;
	}

	Arbol arbolIndices;
	crearArbol_ALU(&arbolIndices);

	Lista listaArmados;
	crearLista_ALU(&listaArmados);

	cargarArchivoEnLista_ALU(&listaArmados,pfArmados);
	cargarArchivoEnArbolOrd_ALU(&arbolIndices,pfIndices,sizeof(IndComponente),comparaIndices);
	//eliminaDuplicados_ALU(&listaArmados,comparaArmados,sumaArmados); //Hacer en casa


	ArmadoYRep armadoLeido;
	//eliminarDeListaFrente_ALU(&listaArmados,&armadoLeido,sizeof(ArmadoYRep));
	do{
        eliminarDeListaFrente_ALU(&listaArmados,&armadoLeido,sizeof(ArmadoYRep));
        strcpy(indiceAux.codigo,armadoLeido.codigo);
		buscarEnArbol_ALU(&arbolIndices,&indiceAux,sizeof(IndComponente),comparaIndices);

		fseek(pfComponentes,indiceAux.nroReg*sizeof(Componente),SEEK_SET);
		fread(&componenteAux,sizeof(Componente),1,pfComponentes);
		//printf("%s <--> ",componenteAux.codigo);
        //printf("%d = %d - %d\n", componenteAux.stock-armadoLeido.cantidad ,componenteAux.stock,armadoLeido.cantidad);
		componenteAux.stock-=armadoLeido.cantidad;

		fseek(pfComponentes,-1L*sizeof(Componente),SEEK_CUR);
		fwrite(&componenteAux,sizeof(Componente),1,pfComponentes);
		//eliminarDeListaFrente_ALU(&listaArmados,&armadoLeido,sizeof(ArmadoYRep));

	}while(!listaVacia_ALU(&listaArmados));

	fclose(pfComponentes);
	fclose(pfArmados);
	fclose(pfIndices);

	return 0;
}

void crearArbol_ALU(Arbol* pa){
	*pa = NULL;
}

booleano listaVacia_ALU(Lista* pl){
	return !*pl? VERDADERO:FALSO;
}

booleano insertarEnArbol_ALU(Arbol* pa,void* elem,size_t tamElem,Cmp cmp){
	if(!*pa){
		NodoA* nue = crearNodoA_ALU(elem,tamElem);
		if(!nue){
			return FALSO;
		}
		*pa = nue;
		return VERDADERO;
	}

	int comp = cmp(elem,(*pa)->elem);
	return insertarEnArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
}

booleano buscarEnArbol_ALU(Arbol*pa, void* elem,size_t tamElem,Cmp cmp){

	if(!*pa){
		return FALSO;
	}

	int comp = cmp(elem,(*pa)->elem);
	if(comp==0){
		memcpy(elem,(*pa)->elem,MIN(tamElem,(*pa)->tamElem));
		return VERDADERO;
	}
	else{
		return buscarEnArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
	}

}

void crearLista_ALU(Lista* pl){
	*pl = NULL;
}

void cargarArchivoEnLista_ALU(Lista* pl, FILE* pf){
	ArmadoYRep armadoLeido;
	fread(&armadoLeido,sizeof(ArmadoYRep),1,pf);
	while(!feof(pf)){
		insertarEnListaFondo_ALU(pl,&armadoLeido,sizeof(ArmadoYRep));
		fread(&armadoLeido,sizeof(ArmadoYRep),1,pf);
	}
}

void cargarArchivoEnArbolOrd_ALU(Arbol* pa, FILE* pf,size_t tamElem, Cmp cmp){

	int ini=0,fin;
	fseek(pf,0,SEEK_END);
	fin = (ftell(pf)/tamElem) - 1;
	cargaElementoMedio_ALU(ini,fin,pf,pa,tamElem,cmp);

}

void cargaElementoMedio_ALU(int ini, int fin, FILE* pf, Arbol* pa, size_t tamElem, Cmp cmp){

	if(ini > fin){
		return;
	}

	char buffer[tamElem];
	int medio = (ini+fin)/2;
	fseek(pf,(medio)*tamElem,SEEK_SET);
	fread(buffer,tamElem,1,pf);
	insertarEnArbol_ALU(pa,buffer,tamElem,cmp);
	cargaElementoMedio_ALU(ini,medio-1,pf,pa,tamElem,cmp);
	cargaElementoMedio_ALU(medio+1,fin,pf,pa,tamElem,cmp);

}

booleano insertarEnListaFondo_ALU(Lista* pl,void* elem, size_t tamElem){

	NodoD* nue = crearNodoD_ALU(elem,tamElem);
	if(!nue){
		return FALSO;
	}
	if(!*pl){
		*pl = nue;
		return VERDADERO;
	}

	while((*pl)->sig){
		*pl = (*pl)->sig;
	}

	(*pl)->sig = nue;
	nue->ant = *pl;
	return VERDADERO;
}

void eliminarDeListaFrente_ALU(Lista* pl,void* elem,size_t tamElem){

	if(!*pl){
		return;
	}

	while((*pl)->ant){
		*pl = (*pl)->ant;
	}

	NodoD* nae = *pl;
	if(nae->sig){
		*pl = (*pl)->sig;
		nae->sig->ant = NULL;
	}
	else{
		*pl = NULL;
	}


	//printf("codigo: %s\n",((ArmadoYRep*)elem)->codigo);
	destruirNodoD_ALU(nae, elem, tamElem);

}

NodoD* crearNodoD_ALU(void* elem,size_t tamElem){
	NodoD* nue = (NodoD*)malloc(sizeof(NodoD));
	void* nueElem = malloc(tamElem);

	memcpy(nueElem,elem,tamElem);

	nue->elem = nueElem;
	nue->ant = NULL;
	nue->sig = NULL;
	nue->tamElem = tamElem;

	return nue;
}

void destruirNodoD_ALU(NodoD* nae, void* elem, size_t tamElem){
	memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
	free(nae->elem);
	free(nae);
}

NodoA* crearNodoA_ALU(void* elem,size_t tamElem){
	NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
	void* nueElem = malloc(tamElem);

	memcpy(nueElem,elem,tamElem);

	nue->elem = nueElem;
	nue->tamElem=tamElem;
	nue->hDer = NULL;
	nue->hIzq = NULL;
	return nue;
}

void destruirNodoA_ALU(NodoA* nae, void* elem, size_t tamElem){
	memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
	free(nae->elem);
	free(nae);
}
