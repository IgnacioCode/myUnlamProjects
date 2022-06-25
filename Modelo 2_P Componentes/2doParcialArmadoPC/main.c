#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"
#include <string.h>

/**/
#define ERROR_ALU 404
/**/


#include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#include "../TDAArbol/TDAArbol.h"
#include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include "../TDALista/TDALista.h"
#include "../TDA/TDA.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep);

/***/


#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para m�quinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para m�quinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para m�quinas Windows

    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

	puts("Componentes antes de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
	puts("");

	puts("Armados/Reparaciones:");
	mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
	puts("");
    int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************
	/** Descomente esta l�nea y comente la de arriba para probar su c�digo              **/
	//int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************

	if(resp != TODO_OK){
		puts("Error actualizando los componentes.");
		return resp;
	}


	puts("\nComponentes despues de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}


int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep){
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

	if(!pfComponentes || !pfArmados || !|pfIndices){
		printf("No se pudo abrir alguno de los archivos...");
		getch();
		return 1;
	}

	Arbol arbolIndices;
	crearArbol_ALU(&arbolIndices);

	Lista listaArmados;
	crearLista_ALU(&listaArmados);

	cargarArchivoEnLista_ALU(&listaArmados,pfArmados);
	eliminaDuplicados_ALU(&listaArmados,comparaArmados,sumaArmados);

	ArmadoYRep armadoLeido;
	eliminaDeListaFrente_ALU(&listaArmados,&armadoLeido,sizeof(ArmadoYRep));
	while(!listaVacia_ALU(&listaArmados)){
		buscarElementoEnArbol_ALU(&arbolIndices,&indiceAux,sizeof(IndComponente));
		fseek(pfComponentes,indiceAux.nroReg*sizeof(Componente),SEEK_SET);
		fread(&componenteAux,sizeof(Componente),1,pfComponentes);

		componenteAux.stock-=armadoLeido.cantidad;
		fseek(pfComponentes,-1*sizeof(Componente),SEEK_CUR);
		fwrite(&componenteAux,sizeof(Componente),1,pfComponentes);
		eliminaDeListaFrente_ALU(&listaArmados,&armadoLeido,sizeof(ArmadoYRep));
	}

	fclose(pfComponentes);
	fclose(pfArmados);
	fclose(pfIndices);


}




