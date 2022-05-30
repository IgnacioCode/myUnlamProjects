#include <stdio.h>
#include <stdlib.h>
#include "..\TDA\Lista\Lista.h"
#include <stdio.h>
#include <string.h>

#define TAM_FECHA 11
#define TAM_NOMBRE 26
#define TAM_MONTO 11
#define TAM_LINEA 120

typedef struct{

    int dia;
    int mes;
    int anio;

}Fecha;

// 11/10/22,mabel.pizza.roma,YCBC,pedro.mama.pan,Santander,17005.04

typedef struct{

    Fecha fecha;    // 8 caracteres
    char ctaOrigen[26];
    char bcoOrigen[26];
    char ctaDestino[26];
    char bcoDestino[26];
    float monto;    // 10 caracteres

    //caracteres totales 8 + 26 + 26 + 26 + 26 + 10 = 122 caracteres
}Transferencia;

void lineaATransferencia(char* linea, Transferencia* trans);
void convierteTextoABinario(FILE* pfT,FILE* pfB);
Fecha lineaAFecha(char* linea);
char* cargaDato(char* carAct,char* strDestino, char carFin);

int main(){

    FILE* pfS = fopen("Transferencias_Sentander.txt","rt");     //Archivo origen
    FILE* pfY = fopen("Transferencias_YCBC.txt","rt");          //Archivo origen
    FILE* pfP = fopen("Transferencias.dat","rb");               //Archivo origen

    FILE* pfSB = fopen("Transferencias_Santander.dat","wb");
    FILE* pfYB = fopen("Transferencias_YCBC.dat","wb");

    FILE* pfC = fopen("Cuentas.dat","rb");      //Archivo a actualizar

    convierteTextoABinario(pfS,pfSB);

    fclose(pfS);
    fclose(pfY);
    fclose(pfP);
    fclose(pfSB);
    fclose(pfYB);
    fclose(pfC);


}

void convierteTextoABinario(FILE* pfT,FILE* pfB){


    Transferencia transAux;
    char lineaLeida[TAM_LINEA];

    fgets(lineaLeida,TAM_LINEA,pfT);

    while(!feof(pfT)){

        lineaATransferencia(lineaLeida,&transAux);

        fwrite(&transAux,sizeof(Transferencia),1,pfB);

        fgets(lineaLeida,TAM_LINEA,pfT);

    }


}

void lineaATransferencia(char* linea, Transferencia* trans){

    char* carAct=linea;
    char fechaAux[TAM_FECHA];
    char nombreAux[TAM_NOMBRE];
    char montitoAux[TAM_MONTO];

    carAct = cargaDato(carAct,fechaAux,'|'); //Cargo los caracteres hasta el proximo pipe
    trans->fecha=lineaAFecha(fechaAux);

    carAct = cargaDato(carAct,nombreAux,'|');
    strcpy(trans->ctaOrigen,nombreAux);

    carAct = cargaDato(carAct,nombreAux,'|');
    strcpy(trans->bcoOrigen,nombreAux);

    carAct = cargaDato(carAct,nombreAux,'|');
    strcpy(trans->ctaDestino,nombreAux);

    carAct = cargaDato(carAct,nombreAux,'|');
    strcpy(trans->bcoDestino,nombreAux);

    carAct = cargaDato(carAct,nombreAux,'\0');
    trans->monto = atof(montitoAux);

}

char* cargaDato(char* carAct,char* strDestino, char carFin){

    while(*carAct != carFin){
        *strDestino=*carAct;
        strDestino++;
        carAct++;
    }
    *strDestino = '\0';
    return carAct+1;
}

Fecha lineaAFecha(char* linea){

    Fecha nuevaFecha;
    char num[5];
    char* posNum=num;

    while(*linea!='/'){
        *posNum=*linea;
        linea++;
        posNum++;
    }
    num[2]='\0';
    nuevaFecha.dia=atoi(num);
    posNum=num;
    linea++;

    while(*linea!='/'){
        *posNum=*linea;
        linea++;
        posNum++;
    }
    num[2]='\0';
    nuevaFecha.mes=atoi(num);
    posNum=num;
    linea++;

    while(*linea!='\0'){
        *posNum=*linea;
        linea++;
        posNum++;
    }
    num[4]='\0';
    nuevaFecha.anio=atoi(num);

    return nuevaFecha;
}
