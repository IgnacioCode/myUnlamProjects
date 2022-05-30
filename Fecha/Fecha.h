#ifndef FECHA_H
#define FECHA_H

typedef struct{
    int dia;
    int mes;
    int anio;
}Fecha;

int esFechaValida(Fecha fecha);                             ///Ejercicio 14
int cantDiaMes(int mes,int anio);
int esBisiesto(int anio);
int fechaAnterior(const Fecha* f1,const Fecha* f2);
Fecha diaSiguiente(const Fecha* fecha);                     ///Ejercicio 15
Fecha diaAnterior(const Fecha* fecha);
Fecha sumaDias(const Fecha* fecha,int cantDias);            ///Ejercicio 16
Fecha restaDias(const Fecha* fecha,int cantDias);           ///Ejercicio 17
int difEnDias(const Fecha* fecha1,const Fecha* fecha2);     ///Ejercicio 18
int diaDeSemana(const Fecha* fecha);                        ///Ejercicio 19


#endif // FECHA_H
