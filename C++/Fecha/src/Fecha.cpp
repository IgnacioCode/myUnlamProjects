#include "Fecha.h"
#include "..\FechaExc.h"

Fecha::Fecha(){

    this->diaRel=0;

}


Fecha::Fecha(int dia,int mes,int anio){

    int diasAcum = anio*365 + anio/4 - anio/100 + anio/400 + cantDiaMesAcum(mes,anio) + dia;

    this->diaRel = diasAcum;

}

void Fecha::setDMA(int dia,int mes, int anio){

    if(!esFechaValida(dia,mes,anio)){
        throw FechaExc(dia + '/' + mes + '/' + anio + "no es una fecha valida");
    }

    int nuevoDiaAcum = anio*365 + anio/4 - anio/100 + anio/400 + cantDiaMesAcum(mes,anio) + dia;

    this->diaRel = nuevoDiaAcum;

}

bool Fecha::esFechaValida(int dia,int mes,int anio){

    if(anio > 0){
        if(mes > 1 && mes < 12){
            if(dia > 0 && dia < cantDiaMes(mes,anio)){
                return true;
            }
        }
    }

    return false;
}

int Fecha::cantDiaMes(int mes,int anio){

    static int diasMeses[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    return mes == 2 && esBisiesto(anio)? diasMeses[mes] + 1 : diasMeses[mes];

}

int Fecha::cantDiaMesAcum(int mes, int anio){
    static int diasAcum[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

    return mes>2 && esBisiesto(anio)? diasAcum[mes] + 1 : diasAcum[mes];
}

bool Fecha::esBisiesto(int anio){
    return anio%4 == 0 && (anio%100 != 0 || anio%400 == 0);
}