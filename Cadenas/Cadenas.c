#include "Cadenas.h"

void leerPal(SecPal* sl,Palabra* pal){

    while(*sl->cursor!='\0' && !esLetra(*sl->cursor)){
        sl->cursor++;
    }
    if(*sl->cursor=='\0'){
        sl->finSec=VERDADERO;
        return;
    }

    pal->inicio=sl->cursor;

    while(*sl->cursor!='\0' && esLetra(*sl->cursor)){
        sl->cursor++;
    }

    pal->fin=sl->cursor-1;

}

void creaSecPal(SecPal* sl,char* origen){

    sl->cursor = origen;

    sl->iniCad = origen;

    sl->finSec=FALSO;

}

int finSecPal(SecPal* secuencia){

    return secuencia->finSec? 1:0;

}

int esLetra(char letra){

    return ((letra >= 'a' && letra <= 'z' )||( letra >= 'A' && letra <= 'Z'))? 1:0;

}

void escribePal(SecPal* se, Palabra* pal){

    char* i;

    for(i=pal->inicio;i!=pal->fin;i++){
        *(se->cursor)=*i;
        se->cursor++;
    }
    *(se->cursor)=*i;
    se->cursor++;

}

void escribeCaracter(SecPal* se, char caracter){

    *(se->cursor)=caracter;
    se->cursor++;

}

void mueveCursor(SecPal* se, int movimiento){

    se->cursor+= movimiento;

}

void rebobinarSecPal(SecPal* sec){

    sec->cursor=sec->iniCad;

}

void formateoMayusyMin(Palabra* pal){

    char* i=(pal->inicio)+1;

    *(pal->inicio)=aMayuscula(*(pal->inicio));

    while(i!=pal->fin){
        *i=aMinuscula(*i);
        i++;
    }
    *i=aMinuscula(*i);


}

char aMayuscula(char caracter){

    if(caracter>='a' && caracter<='z'){
        return caracter-32;
    }
    else{
        return caracter;
    }
}

char aMinuscula(char caracter){

    if(caracter>='A' && caracter<='Z'){
        return caracter+32;
    }
    else{
        return caracter;
    }
}

void normalizar(const char* origen, const char* destino){

    Palabra pal;

    SecPal sl,se;

    creaSecPal(&sl,origen);
    creaSecPal(&se,destino);

    leerPal(&sl,&pal);

    while(!finSecPal(&sl)){

        formateoMayusyMin(&pal);
        escribePal(&se,&pal);
        escribeCaracter(&se,' ');

        leerPal(&sl,&pal);
    }

    escribeCaracter(&se,'\0');

}
