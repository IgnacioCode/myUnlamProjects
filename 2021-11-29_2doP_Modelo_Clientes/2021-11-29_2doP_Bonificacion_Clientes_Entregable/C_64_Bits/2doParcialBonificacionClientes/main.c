#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "..\Solucion2doParcialBonificacionClientes\Utilitarias2doParcialBonificacionClientes.h"
#include "..\Solucion2doParcialBonificacionClientes\Solucion2doParcialBonificacionClientes.h"
#include "..\Solucion2doParcialBonificacionClientes\TiposArchivos.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "..\TDAArbol\TDAArbol.h"
#define MIN(X,Y) (X>Y? Y:X)

void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas);
void cargarArchivoPreEnArbol_ALU(FILE* pf,Arbol* pa,size_t tamElem,Cmp cmp);
booleano buscarEnArbol_ALU(Arbol* pa,void* elem, size_t tamElem, Cmp cmp);
booleano insertarEnArbol_ALU(Arbol* pa,void* elem, size_t tamElem, Cmp cmp);
void crearArbol_ALU(Arbol* pa);
NodoA* crearNodoA_ALU(void* elem,size_t tamElem);

int comparaIndicesOrden_ALU(const void* i1,const void* i2){
	Indice* indice1 = (Indice*)i1;
	Indice* indice2 = (Indice*)i2;

	return indice1->nroReg - indice2->nroReg;
}

int comparaIndicesCliente_ALU(const void* i1,const void* i2){
	Indice* indice1 = (Indice*)i1;
	Indice* indice2 = (Indice*)i2;

	return strcmp(indice1->codCliente,indice2->codCliente);
}

int main()
{
	generarArchivoClientes();
	generarIndiceArchivoClientes();
	generarArchivoVentas();

	mostrarArchivoClientes();
	puts("\n");

	mostrarArchivoVentas();
	puts("\n");

	bonificarClientes_ALU("Clientes.dat", "Clientes.idx", "Ventas.dat");
	///bonificarClientes("Clientes.dat", "Clientes.idx", "Ventas.dat");

	puts("Clientes Bonificados");
	mostrarArchivoClientes();
	puts("\n");

	return 0;
}


void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas){
/// Resuelva esta funci�n y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ning�n otro.
/// main.c es el �nico archivo que deber� entregar del proyecto C.

	FILE* pfClientes = fopen(clientes,"r+b");
	FILE* pfIndices = fopen(clientesInd,"rb");
	FILE* pfVentas = fopen(ventas,"rb");

	Arbol arbolIndices;
	Venta ventaLeida;
	Cliente clienteLeido;
	Indice indiceAux;

	float sumaCompras = 0;
	char cdoClienteAnt[16];
	float precioVentaTotal;

	float porDescuento;

	crearArbol_ALU(&arbolIndices);
	cargarArchivoPreEnArbol_ALU(pfIndices,&arbolIndices,sizeof(Indice),comparaIndicesCliente_ALU);

	fread(&ventaLeida,sizeof(Venta),1,pfVentas);
	while(!feof(pfVentas)){

		sumaCompras = 0;
		strcpy(cdoClienteAnt,ventaLeida.codCliente);

		while(strcmp(ventaLeida.codCliente,cdoClienteAnt)==0 && !feof(pfVentas)){
			precioVentaTotal = ventaLeida.cantidad * ventaLeida.precioUnit;
			sumaCompras+=precioVentaTotal;
			fread(&ventaLeida,sizeof(Venta),1,pfVentas);
		}

		if(sumaCompras>100000){
			if(sumaCompras > 300000){
				porDescuento = 20;
			}
			else if(sumaCompras >200000){
				porDescuento = 10;
			}
			else{
				porDescuento = 5;
			}

			strcpy(indiceAux.codCliente,cdoClienteAnt);


			buscarEnArbol_ALU(&arbolIndices,&indiceAux,sizeof(Indice),comparaIndicesCliente_ALU); //Buscar indice del cliente
			fseek(pfClientes,indiceAux.nroReg*sizeof(Cliente),SEEK_SET);	//mover cursor hasta el indice encontrado
			fread(&clienteLeido,sizeof(Cliente),1,pfClientes);

			clienteLeido.porcBonif = porDescuento;
			fseek(pfClientes,-sizeof(Cliente),SEEK_CUR);
			fwrite(&clienteLeido,sizeof(Cliente),1,pfClientes);
		}



	}

	fclose(pfClientes);
	fclose(pfVentas);
	fclose(pfIndices);

}

void crearArbol_ALU(Arbol* pa){
	*pa=NULL;
}

booleano insertarEnArbol_ALU(Arbol* pa,void* elem, size_t tamElem, Cmp cmp){

	if(!*pa){
		NodoA* nue = crearNodoA_ALU(elem,tamElem);
		if(!nue){
			return falso;
		}
		*pa = nue;
		return verdadero;
	}

	int comp = cmp(elem,(*pa)->elem);

	if(comp == 0){
		return falso; // duplicado
	}
	else if(comp < 0){
		insertarEnArbol_ALU(&(*pa)->hIzq,elem,tamElem,cmp);
	}
	else if(comp > 0){
		insertarEnArbol_ALU(&(*pa)->hDer,elem,tamElem,cmp);
	}

	return verdadero;

}

booleano buscarEnArbol_ALU(Arbol* pa,void* elem, size_t tamElem, Cmp cmp){

	if(!*pa){
		return falso;
	}

	int comp = cmp(elem,(*pa)->elem);

	if(comp == 0){
		memcpy(elem,(*pa)->elem,MIN(tamElem,(*pa)->tamElem));
		return verdadero;
	}
	/*else if(comp < 0){
		buscarEnArbol_ALU(&(*pa)->hIzq,elem,tamElem,cmp);
	}
	else if(comp > 0){
		buscarEnArbol_ALU(&(*pa)->hDer,elem,tamElem,cmp);
	}*/

    return buscarEnArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
}

void cargarArchivoPreEnArbol_ALU(FILE* pf,Arbol* pa,size_t tamElem,Cmp cmp){

	char regLeido[tamElem];

	fread(regLeido,tamElem,1,pf);
	while(!feof(pf)){
		insertarEnArbol_ALU(pa,regLeido,tamElem,cmp);
		fread(regLeido,tamElem,1,pf);
	}


}

NodoA* crearNodoA_ALU(void* elem,size_t tamElem){

	NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
	void* nueElem = malloc(tamElem);

	if(!nue || !nueElem){
		free(nue);
		free(nueElem);
		return NULL;
	}

	memcpy(nueElem,elem,tamElem);

	nue->elem = nueElem;
	nue->tamElem = tamElem;
	nue->hIzq=NULL;
	nue->hDer=NULL;
	return nue;
}
