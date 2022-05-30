#include "Fecha.h"
#define VERDADERO 1
#define FALSO 0
#define ANIO_BASE 1600
#define ANIO_TOPE 9999

int esFechaValida(Fecha fecha){

    if(fecha.anio>ANIO_BASE && fecha.anio<ANIO_TOPE){

        if(fecha.mes>=1 && fecha.mes<=12){

            if(fecha.dia>=1 && fecha.dia<=cantDiaMes(fecha.mes,fecha.anio)){
                return 1;
            }

        }
    }

    return 0;

}

int cantDiaMes(int mes,int anio){

    if( mes==1 || mes==3 || mes==7 || mes==5 || mes==8 || mes==10 || mes==12 ){
        return 31;
    }
    else if( mes==4 || mes==6 || mes==9 || mes==11 ){
        return 30;
    }
    else{
        if(esBisiesto(anio)){
            return 29;
        }
        else{
            return 28;
        }
    }


    ///Metodo utilizando vector para dias del mes
    /*
    const static int cdm[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(mes==2 && esBisiesto(anio)){
        return 29;
    }

    return cdm[mes];

    */

}

int esBisiesto(int anio){
    return anio%4==0 &&(!anio%100==0 || anio%400==0);
}

int difEnDias(const Fecha* fecha1,const Fecha* fecha2){

    Fecha f1=*fecha1;
    Fecha f2=*fecha2;
    //Fecha fechaAux;

    int diferencia=0;

    /*if(fechaAnterior(&f1,&f2)==2){
        fechaAux=f2;
        f2=f1;
        f1=fechaAux;
    }*/

    if(f1.anio!=f2.anio){   ///Metodo cuando hay mas de un año

        diferencia-=f1.dia;
        while(f1.mes<=12){
            diferencia+=cantDiaMes(f1.mes,f1.anio);
            f1.mes++;
        }

        diferencia-=cantDiaMes(f2.mes,f2.anio)-f2.dia;

        while(f2.mes>=1){

            diferencia+=cantDiaMes(f2.mes,f2.anio);
            f2.mes--;

        }

        f1.anio++;

        while(f1.anio!=f2.anio){
            diferencia+=365;
            if(esBisiesto(f1.anio)){
                diferencia++;
            }
            f1.anio++;
        }

    }
    else{                   ///Metodo cuando hay solo meses de diferencia

        diferencia=f2.dia-f1.dia;

        while(f1.mes!=f2.mes){

            diferencia+=cantDiaMes(f1.mes,f1.anio);
            f1.mes++;

        }

    }

    return diferencia;

}

int fechaAnterior(const Fecha* f1,const Fecha* f2){

    if(f1->anio==f2->anio){

        if(f1->mes==f2->mes){

            if(f1->dia==f2->dia){
                return 0;
            }
            else if(f1->dia<f2->dia){
                return 1;
            }

        }
        else if(f1->mes<f2->mes){

            return 1;

        }

    }
    else if((f1->anio) < (f2->anio)){
        return 1;
    }

    return 2;

}

Fecha diaSiguiente(const Fecha* fecha){

    Fecha nuevoDia=*fecha;

    nuevoDia.dia++;
    if(!esFechaValida(nuevoDia)){
        nuevoDia.dia=1;
        nuevoDia.mes++;
        if(!esFechaValida(nuevoDia)){
            nuevoDia.mes=1;
            nuevoDia.anio++;
        }

    }

    return nuevoDia;

}

Fecha diaAnterior(const Fecha* fecha){

    Fecha nuevoDia=*fecha;

    nuevoDia.dia--;
    if(!esFechaValida(nuevoDia)){
        nuevoDia.mes--;
        nuevoDia.dia=cantDiaMes(nuevoDia.mes,nuevoDia.anio);
        if(!esFechaValida(nuevoDia)){
            nuevoDia.dia=31;
            nuevoDia.mes=12;
            nuevoDia.anio--;
        }
    }

    return nuevoDia;

}

Fecha sumaDias(const Fecha* fecha,int cantDias){

    Fecha nuevoDia=*fecha;

    nuevoDia.dia+=cantDias;

    while(!esFechaValida(nuevoDia)){
        nuevoDia.dia-=cantDiaMes(nuevoDia.mes,nuevoDia.anio);
        nuevoDia.mes++;
        if(!esFechaValida(nuevoDia)){
            nuevoDia.mes=1;
            nuevoDia.anio++;
        }
    }

    return nuevoDia;

}

Fecha restaDias(const Fecha* fecha, int cantDias){

    Fecha nuevoDia=*fecha;

    nuevoDia.dia-=cantDias;
    if(!esFechaValida(nuevoDia)){
        nuevoDia.mes--;
        if(nuevoDia.mes==0){
            nuevoDia.mes=12;
            nuevoDia.anio--;
        }
        nuevoDia.dia+=cantDiaMes(nuevoDia.mes,nuevoDia.anio);
    }

    return nuevoDia;

}

int diaDeSemana(const Fecha* fecha){

    Fecha fechaBase={1,1,1995};

    int diferencia=difEnDias(&fechaBase,fecha)%7;

    switch(diferencia){

    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;

    }

}
