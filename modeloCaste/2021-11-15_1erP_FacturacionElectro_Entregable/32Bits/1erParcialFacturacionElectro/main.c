#include <stdio.h>
#include <stdlib.h>

#include "../Comun/Comun.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES	1
#define ARG_MEDICIONES	2
#define ARG_FACTURAS	3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define MAX_MESES 10

int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar);
int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar);
int CmpMediciones_ALU(const void* e1, const void* e2);

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

	///ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
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


int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar)
{
	/// Desarrolle esta función y todas las que invoque. Puede usar funciones de la biblioteca estándar.
	/// Coloque el sufijo _ALU a todas las funciones que desarrolle.
	/// No use otro archivo que no sea main.c. Será el que deberá entregar.

	int ret;

	Cliente cliAct;
    Medicion medAct;
    Factura facAct;
    Fecha ultFecha;
    int ultMed;

    Lista mediciones;
    crearLista(&mediciones);

    FILE* c = fopen(nombreArchivoClientes, "r+");
    FILE* m = fopen(nombreArchivoMediciones, "r");
    FILE* f = fopen(nombreArchivoFacturas, "w");

    while(!feof(m)) //Inserta Mediciones.txt en una Lista Ordenada por NroCliente
    {
        fscanf(m, "%d|%d/%d/%d|%d", &medAct.nroCliente,&medAct.fechaMedicion.dia,&medAct.fechaMedicion.mes,&medAct.fechaMedicion.anio,&medAct.valorMedidor);
        ret = insertarEnListaOrdCDup(&mediciones, &medAct, sizeof(Medicion), CmpMediciones_ALU);
    }

    if(ret != TODO_OK)
	{
		printf("Error al insertar en lista\n");
		return ret;
	}

    while(!feof(c))
    {
        int i, dm, dd, cde, cm;
        for(i=0; i<cantMesesAFacturar; i++)
        {
            if(!i) //asigna la ultima fecha de medicion y su valor
            {
                ultFecha = cliAct.fechaUltMedicion;
                ultMed = cliAct.valorMedidor;
            }
            else
            {
                ultFecha = medAct.fechaMedicion;
                ultMed = medAct.valorMedidor;
            }

            fread(&cliAct, sizeof(Cliente), 1, c);
            eliminarDeListaPrimero(&mediciones, &medAct, sizeof(Medicion));
            dm = medAct.valorMedidor - ultMed;
            //dd = difEnDiasEntreFechas(&ultFecha, &medAct.fechaMedicion); //error
            //cde = dm/dd;
            cm = cde*cantDiasMes(medAct.fechaMedicion.mes, medAct.fechaMedicion.anio);
            facAct.nroCliente = medAct.nroCliente;
            facAct.nroFactura = proximoNroFactura;
            facAct.mesFacturado.mes = medAct.fechaMedicion.mes;
            facAct.mesFacturado.anio = medAct.fechaMedicion.anio;
            facAct.fechaUltMedicion = medAct.fechaMedicion;
            facAct.valorMedidor = medAct.valorMedidor;
            facAct.consumoMes = cm;
            fwrite(&facAct, sizeof(Factura), 1, f);
            proximoNroFactura++;
        }
        //Actualiza Clientes.dat
        cliAct.fechaUltMedicion = facAct.fechaUltMedicion;
        cliAct.valorMedidor = facAct.valorMedidor;
        cliAct.ultConsumoMes = facAct.consumoMes;
        cliAct.ultMesFacturado = facAct.mesFacturado;
        fwrite(&cliAct, sizeof(Cliente), 1, c);
        printf("hola");
    } //nunca termina el while

    fclose(c);
    fclose(m);
    fclose(f);

	return TODO_OK;
}

int CmpMediciones_ALU(const void* e1, const void* e2)
{
    Medicion* m1 = (Medicion*)e1;
    Medicion* m2 = (Medicion*)e2;

    return m1->nroCliente - m2->nroCliente;
}
