#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Comun/Comun.h"
#include "../Nodo/Nodo.h"
#include "../TDALista/TDALista.h"
#include "../Fecha/Fecha.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES	1
#define ARG_MEDICIONES	2
#define ARG_FACTURAS	3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define MAX_MESES 10

int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar);
int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar);
int comparaFecha(Fecha* f1, Fecha* f2);
int comparaMediciones(const void* m1, const void* m2);
Mes fechaAMes(Fecha f1);

int main(int argc, char* argv[])
{
	int ret = generarArchivos();

	if(ret != TODO_OK)
	{
		printf("Error al generar archivos\n");
		return ret;
	}

	printf("Archivos generados correctamente\n");

	puts("\nAntes de Actualizar:\n");

	mostrarClientes(argv[ARG_CLIENTES]);

	mostrarMediciones(argv[ARG_MEDICIONES]);

	Mes mesesAFacturar[MAX_MESES];

	int cantMesesAFacturar = extraerMesesAFacturar(argv, mesesAFacturar);

	//ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
	/// Descomente esta línea y comente la de arriba, para ejecutar su código
    ret = generarFacturas_ALU(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);

	if(ret != TODO_OK)
	{
		printf("Error al generar facturas\n");
		return ret;
	}

	puts("\nDespues de Actualizar:\n");

	mostrarFacturas(argv[ARG_FACTURAS]);

	mostrarClientes(argv[ARG_CLIENTES]);

	return ret;
}


int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar)
{
	int cantMesesAFacturar = atoi(argv[ARG_CANT_MESES_A_FACTURAR]);

	for(int i = 0; i < cantMesesAFacturar; i++)
		mesesAFacturar[i] = strToMes(argv[ARG_CANT_MESES_A_FACTURAR + 1 + i]);

	return cantMesesAFacturar;
}


int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar){

	int i,DM,DD;
	double CDE;
	double CM;
	FILE* pfMed = fopen(nombreArchivoMediciones,"rt");
	FILE* pfCli = fopen(nombreArchivoClientes,"rb");
	FILE* pfFac = fopen(nombreArchivoFacturas,"wb");

	Lista listaMediciones;
	Lista listaFacturasCliente;
	crearLista(&listaFacturasCliente);
	crearLista(&listaMediciones);

	Medicion medicionLeida;
	Cliente clienteLeido;
	Factura facturaAnterior;
	Factura facturaAux;

	fread(&medicionLeida,sizeof(Medicion),1,pfMed);
	while(!feof(pfMed)){
		insertarEnListaOrd(&listaMediciones,&medicionLeida,sizeof(Medicion),comparaMediciones);
		fread(&medicionLeida,sizeof(Medicion),1,pfMed);
	}


	fread(&clienteLeido,sizeof(Cliente),1,pfCli);
	while(!feof(pfCli)){

		for(i=0;i<cantMesesAFacturar;i++){
			eliminarDeListaPrimero(&listaMediciones,&medicionLeida,sizeof(Medicion));
			insertarEnListaOrd(&listaFacturasCliente,&medicionLeida,sizeof(Medicion),comparaMediciones);
		}

		for(i=0;i<cantMesesAFacturar;i++){

			eliminarDeListaPrimero(&listaFacturasCliente,&medicionLeida,sizeof(Medicion));

			facturaAux.nroFactura=proximoNroFactura;
			facturaAux.nroCliente=clienteLeido.nroCliente;

			if(comparaFecha(&clienteLeido.fechaUltMedicion,&medicionLeida.fechaMedicion)){
				facturaAux.fechaUltMedicion=clienteLeido.fechaUltMedicion;
			}
			else{
				facturaAux.fechaUltMedicion=medicionLeida.fechaMedicion;

			}

			facturaAux.valorMedidor=medicionLeida.valorMedidor;
			facturaAux.mesFacturado=fechaAMes(medicionLeida.fechaMedicion);

			if(i==0){
				DM = clienteLeido.valorMedidor;
				DD = difEnDiasEntreFechas(&facturaAux.fechaUltMedicion,&clienteLeido.fechaUltMedicion);
				CDE = ((float)DM)/((float)DD);
				CM = CDE * cantDiasMes(facturaAux.mesFacturado.mes,facturaAux.mesFacturado.anio);
			}
			else{
				DM = facturaAnterior.valorMedidor;
				DD = difEnDiasEntreFechas(&facturaAux.fechaUltMedicion,&facturaAnterior.fechaUltMedicion);
				CDE = ((float)DM)/((float)DD);
				CM = CDE * cantDiasMes(facturaAux.mesFacturado.mes,facturaAux.mesFacturado.anio);
			}

			facturaAux.consumoMes=CM;
			facturaAnterior=facturaAux;
			fwrite(&facturaAux,sizeof(Factura),1,pfFac);


		}

		fread(&clienteLeido,sizeof(Cliente),1,pfCli);

	}

    fclose(pfMed);
    fclose(pfCli);
    fclose(pfFac);

    return 0;
}

int comparaMediciones(const void* m1, const void* m2){

	Medicion* med1 = (Medicion*)m1;
	Medicion* med2 = (Medicion*)m2;

	int res = med1->nroCliente>med2->nroCliente;
	if(res>0){
		return 1;
	}
	else if(res==0){
		return comparaFecha(&med1->fechaMedicion,&med2->fechaMedicion);
	}
	else{
		return -1;
	}
}

int comparaFecha(Fecha* f1, Fecha* f2){
	if(f1->anio>f2->anio){
		return 1;
	}
	else if(f1->anio==f2->anio){
		if(f1->mes>f2->mes){
			return 1;
		}
		else if(f1->mes==f2->mes){
			if(f1->dia>f2->dia){
				return 1;
			}
			else if(f1->dia==f2->dia){
				return 0;
			}
			else{
				return -1;
			}
		}
		else{
			return -1;
		}
	}
	else{
		return -1;
	}
}

Mes fechaAMes(Fecha f1){
	Mes mAux;

	mAux.anio=f1.anio;
	mAux.mes=f1.mes;

	return mAux;
}

