#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SolucionPatentes/SolucionPatentes.h"

#define ARG_ARCH_FACTURAS 1
#define ARG_ARCH_PARCHE	2
#define ARG_ARCH_FACT_INEX 3

#define MIN(X,Y) (X>Y? Y:X)
#define MAX(X,Y) (X>Y? X:Y)

void eliminarDeListaPrimero_ALU(Lista* pl,void* elem, size_t tamElem);
int alturaArbol_ALU(Arbol* pa);
void eliminarRaizDeArbol_ALU(Arbol* pae);
Arbol* buscarRaizDeArbol_ALU(Arbol* pa, void* elem,size_t tamElem,Cmp cmp);
void eliminarDeArbol_ALU(Arbol* pa,void* elem,size_t tamElem,Cmp cmp);
booleano insertarEnListaAlFinal_ALU(Lista* pl,void* elem, size_t tamElem);
booleano buscarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp);
booleano insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp);
void cargarRegistroMedio_ALU(Arbol* pa,int ini, int fin, size_t tamElem,FILE* pf,Cmp cmp);
void cargarArbolDeArchivoOrdenado_ALU(Arbol* pa,size_t tamElem,const char* archivo,Cmp cmp);
void crearLista_ALU(Lista* pl);
void crearArbol_ALU(Arbol* pa);
void destruirNodoD_ALU(NodoD* nae,void* elem,size_t tamElem);
NodoD* crearNodoD_ALU(void* elem,size_t tamElem);
void destruirNodoA_ALU(NodoA* nae,void* elem,size_t tamElem);
NodoA* crearNodoA_ALU(void* elem,size_t tamElem);
Arbol* menorDeArbol_ALU(Arbol* pa);
Arbol* mayorDeArbol_ALU(Arbol* pa);
booleano listaVacia_ALU(Lista* pl);
void vaciarArbol_ALU(Arbol* pa);


int comparaIndices(const void* i1,const void* i2){

	IndFactura* indice1 = (IndFactura*)i1;
	IndFactura* indice2 = (IndFactura*)i2;

	int compPatente = strcmp(indice1->patente,indice2->patente);
	if(compPatente==0){
		int compCuota = indice1->cuota-indice2->cuota;
		if(compCuota==0){
			return 0;
		}
		return compCuota;
	}
	else{
		return compPatente;
	}

}

int main(int argc, char* argv[])
{
	generarArchivoFacturas();
	generarArchivoPatentesParche();

	puts("Archivo Facturas Automotor");
	mostrarFacturasAuto(argv[ARG_ARCH_FACTURAS]);

	puts("\nArchivo Parche");
	mostrarParche(argv[ARG_ARCH_PARCHE]);

	actualizarFacturas(argv[ARG_ARCH_FACTURAS], argv[ARG_ARCH_PARCHE], argv[ARG_ARCH_FACT_INEX]);
    ///actualizarFacturas_ALU(argv[ARG_ARCH_FACTURAS], argv[ARG_ARCH_PARCHE], argv[ARG_ARCH_FACT_INEX]);

	puts("\nArchivo Facturas Automotor actualizado");
	mostrarFacturasAuto(argv[ARG_ARCH_FACTURAS]);

	puts("\nFacturas Inexistentes");
	mostrarParche(argv[ARG_ARCH_FACT_INEX]);

	return 0;
}


void actualizarFacturas_ALU(const char* nombreArchFactAuto, const char* nombreArchParche, const char* nombreArchFactInex){

	int elemEncontrado;
	char nombreArchIndices[21];
	strcpy(nombreArchIndices,nombreArchFactAuto);
	nombreArchIndices[17]='\0';
	strcat(nombreArchIndices,".idx");

	FILE* pfFacturas = fopen(nombreArchFactAuto,"r+b");
	FILE* pfParche = fopen(nombreArchParche,"rb");
	FILE* pfInexistentes = fopen(nombreArchFactInex,"rb");

	if(!pfFacturas || !pfParche || !pfInexistentes){
		return;
	}

	Arbol arbolIndices;
	crearArbol_ALU(&arbolIndices);

	Lista listaErrores;
	crearLista_ALU(&listaErrores);

	cargarArbolDeArchivoOrdenado_ALU(&arbolIndices,sizeof(IndFactura),nombreArchIndices,comparaIndices);

	FacturaAutomotor facturaLeida;
	ParcheFacturaAutomotor parcheLeido;
	IndFactura indiceAux;
	fread(&parcheLeido,sizeof(ParcheFacturaAutomotor),1,pfParche);
	while(!feof(pfParche)){

		strcpy(indiceAux.patente,parcheLeido.patente);
		indiceAux.cuota=parcheLeido.cuota;
		elemEncontrado = buscarEnArbol_ALU(&arbolIndices,&indiceAux,sizeof(IndFactura),comparaIndices);


		if(elemEncontrado && indiceAux.nroRegistro!=-1){
			fseek(pfFacturas,indiceAux.nroRegistro*sizeof(FacturaAutomotor),SEEK_SET);
			fread(&facturaLeida,sizeof(FacturaAutomotor),1,pfFacturas);
			facturaLeida.importeAPagar+=parcheLeido.importeAdicionalAPagar;
			fseek(pfFacturas,-1L*(long)sizeof(FacturaAutomotor),SEEK_CUR);
			fwrite(&facturaLeida,sizeof(FacturaAutomotor),1,pfFacturas);
		}
		else{
			if(indiceAux.nroRegistro==-1){
				eliminarDeArbol_ALU(&arbolIndices,&indiceAux,sizeof(IndFactura),comparaIndices);
			}
			insertarEnListaAlFinal_ALU(&listaErrores,&parcheLeido,sizeof(ParcheFacturaAutomotor));
		}

		fread(&parcheLeido,sizeof(ParcheFacturaAutomotor),1,pfParche);
	}

	do{
		eliminarDeListaPrimero_ALU(&listaErrores,&parcheLeido,sizeof(ParcheFacturaAutomotor));
		fwrite(&parcheLeido,sizeof(ParcheFacturaAutomotor),1,pfInexistentes);
	}while(!listaVacia_ALU(&listaErrores));

	fclose(pfInexistentes);
	fclose(pfParche);
	fclose(pfFacturas);

	vaciarArbol_ALU(&arbolIndices);

}

void vaciarArbol_ALU(Arbol* pa){

	if(!*pa){
		return;
	}
	vaciarArbol_ALU(&(*pa)->hIzq);
	vaciarArbol_ALU(&(*pa)->hDer);
	destruirNodoA_ALU(*pa,NULL,0);

}

booleano listaVacia_ALU(Lista* pl){
	return *pl? falso:verdadero;
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
	nue->hDer = NULL;
	nue->hIzq = NULL;

	return nue;
}
void destruirNodoA_ALU(NodoA* nae,void* elem,size_t tamElem){
	memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
	free(nae->elem);
	free(nae);
}

NodoD* crearNodoD_ALU(void* elem,size_t tamElem){
	NodoD* nue = (NodoD*)malloc(sizeof(NodoD));
	void* nueElem = malloc(tamElem);

	if(!nue || !nueElem){
		free(nue);
		free(nueElem);
		return NULL;
	}

	memcpy(nueElem,elem,tamElem);

	nue->elem = nueElem;
	nue->tamElem = tamElem;
	nue->ant = NULL;
	nue->sig = NULL;

	return nue;
}
void destruirNodoD_ALU(NodoD* nae,void* elem,size_t tamElem){
	memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
	free(nae->elem);
	free(nae);
}

void crearArbol_ALU(Arbol* pa){
	*pa = NULL;
}
void crearLista_ALU(Lista* pl){
	*pl = NULL;
}

void cargarArbolDeArchivoOrdenado_ALU(Arbol* pa,size_t tamElem,const char* archivo,Cmp cmp){

	FILE* pf = fopen(archivo,"rb");
	if(!pf){
		return;
	}
	int ini = 0,fin;
	fseek(pf,0,SEEK_END);
	fin = (ftell(pf)/tamElem) - 1;
	cargarRegistroMedio_ALU(pa,ini,fin,tamElem,pf,cmp);
	fclose(pf);

}

void cargarRegistroMedio_ALU(Arbol* pa,int ini, int fin, size_t tamElem,FILE* pf,Cmp cmp){

	if(ini > fin){
		return;
	}

	char buffer[tamElem];
	int medio = (ini+fin)/2;
	fseek(pf,medio*tamElem,SEEK_SET);
	fread(buffer,tamElem,1,pf);
	insertarEnArbol_ALU(pa,buffer,tamElem,cmp);
	cargarRegistroMedio_ALU(pa,ini,medio-1,tamElem,pf,cmp);
	cargarRegistroMedio_ALU(pa,medio+1,fin,tamElem,pf,cmp);
}

booleano insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp){

	if(!*pa){
		NodoA* nue = crearNodoA_ALU(elem,tamElem);
		if(!nue){
			return falso;
		}
		*pa = nue;
		return verdadero;
	}

	int comp = cmp(elem,(*pa)->elem);

	return insertarEnArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
}

booleano buscarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp){

	if(!*pa){
		return falso;
	}

	int comp = cmp(elem,(*pa)->elem);
	if(comp == 0){
		memcpy(elem,(*pa)->elem,MIN(tamElem,(*pa)->tamElem));
		return verdadero;
	}

	return buscarEnArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);

}

booleano insertarEnListaAlFinal_ALU(Lista* pl,void* elem, size_t tamElem){

	NodoD* act = *pl;
	NodoD* nue = crearNodoD_ALU(elem,tamElem);
	if(!nue){
		return falso;
	}
	if(!act){
        act = nue;
        return verdadero;
	}
	while(act->sig){
		act = act->sig;
	}
	act->sig = nue;
	nue->ant = act;
	return verdadero;

}
void eliminarDeArbol_ALU(Arbol* pa,void* elem,size_t tamElem,Cmp cmp){

	Arbol* pae = buscarRaizDeArbol_ALU(pa,elem,tamElem,cmp);

	if(!pae){
		return;
	}

	memcpy(elem,(*pae)->elem,MIN(tamElem,(*pae)->tamElem));
	free((*pae)->elem);

	eliminarRaizDeArbol_ALU(pae);

}

Arbol* buscarRaizDeArbol_ALU(Arbol* pa, void* elem,size_t tamElem,Cmp cmp){

	if(!*pa){
		return NULL;
	}

	int comp = cmp(elem,(*pa)->elem);

	if(comp == 0){
		return pa;
	}

	return buscarRaizDeArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
}

void eliminarRaizDeArbol_ALU(Arbol* pae){

	if(!(*pae)->hDer && !(*pae)->hIzq){
		free(*pae);
		*pae=NULL;
		return;
	}

	int hIzq = alturaArbol_ALU(&(*pae)->hIzq);
	int hDer = alturaArbol_ALU(&(*pae)->hDer);

	Arbol* par = hIzq>hDer? mayorDeArbol_ALU(&(*pae)->hIzq):menorDeArbol_ALU(&(*pae)->hDer);
	(*pae)->elem = (*par)->elem;
	(*pae)->tamElem = (*par)->tamElem;

	eliminarRaizDeArbol_ALU(par);
}

Arbol* mayorDeArbol_ALU(Arbol* pa){
	if(!(*pa)->hDer){
		return pa;
	}
	return mayorDeArbol_ALU(&(*pa)->hDer);
}

Arbol* menorDeArbol_ALU(Arbol* pa){
	if(!(*pa)->hIzq){
		return pa;
	}
	return menorDeArbol_ALU(&(*pa)->hIzq);
}

int alturaArbol_ALU(Arbol* pa){

	if(!*pa){
		return 0;
	}

	return MAX(alturaArbol(&(*pa)->hIzq), alturaArbol(&(*pa)->hDer)) + 1;
}

void eliminarDeListaPrimero_ALU(Lista* pl,void* elem, size_t tamElem){

	NodoD* nae = *pl;

	if(!*pl){
		return;
	}

	while(nae->ant){
		nae = nae->ant;
	}

	if(nae->sig){
		*pl = nae->sig;
		nae->sig->ant = NULL;
	}
	else{
		*pl = NULL;
	}

	destruirNodoD_ALU(nae,elem,tamElem);

}
