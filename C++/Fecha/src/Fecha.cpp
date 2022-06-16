#include "Fecha.h"

Fecha::Fecha(){

    this->diaRel=0;

}


Fecha::Fecha(int dia,int mes,int anio){

    int diasAcum = anio*365 + anio/4 - anio/100 + anio/400 + cantDiaMesAcum(mes) + dia;

    this->diaRel = diasAcum;

}

void Fecha::setDMA(int dia,int mes, int anio){

    if(!esFechaValida(dia,mes,anio)){
        throw FechaExc(dia + '/' + mes + '/' + anio + "no es una fecha valida");
    }

    int nuevoDiaAcum = anio*365 + anio/4 - anio/100 + anio/400 + cantDiaMesAcum(mes) + dia;

    this->diaRel = nuevoDiaAcum;

}

bool Fecha::esFechaValida(int dia,int mes,int anio){

    if(anio > 0){
        if(mes > 1 && mes < 12)
    }

}

int Fecha::cantDiaMesAcum(int mes){
    static int diasAcum[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

    return diasAcum[mes];
}