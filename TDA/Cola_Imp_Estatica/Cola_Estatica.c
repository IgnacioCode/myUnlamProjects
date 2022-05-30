#define COLA_IMPL_ESTATICA
#include "Cola_Estatica.h"
#define DESTINO_FONDO pc->vec+pc->fondo

void encolarSegmentado(Cola* pc,const void* elem, size_t tamElem);
void desencolarSegmentado(Cola* pc,void* elem, size_t tamElem, size_t tamElemEncolado);
void verFrenteSegmentado(const Cola* pc,void* elem, size_t tamElem, size_t tamElemEncolado);

void crearCola(Cola* pc){

    pc->frente = pc->fondo = 0; 
    pc->tamDisponible=TAM_COLA;

}

booleano encolar(Cola* pc,const void* elem,size_t tamElem){
    if(tamElem + sizeof(size_t) > pc->tamDisponible){
        return FALSO;
    }

    //*(size_t*)(DESTINO_FONDO) = tamElem;
    //No hacemos eso ya que la idea es aprovechar el espacio si no entra un size_t

    encolarSegmentado(pc,&tamElem,sizeof(size_t));
    encolarSegmentado(pc,elem,tamElem);

    //memcpy(DESTINO_FONDO,&tamElem,sizeof(size_t));
    //pc->fondo+=sizeof(size_t);

    pc->tamDisponible-=tamElem + sizeof(size_t);

    return VERDADERO;
}

booleano desencolar(Cola* pc,void* elem,size_t tamElem){
    if(pc->tamDisponible==TAM_COLA){
        return FALSO;
    }

    size_t tamElemEncolado;

    desencolarSegmentado(pc,&tamElemEncolado,sizeof(size_t),sizeof(size_t));
    desencolarSegmentado(pc,elem,MIN(tamElemEncolado,tamElem),tamElemEncolado);
}

booleano verFrenteDeCola(Cola* pc,void* elem, size_t tamElem){

    if(pc->tamDisponible==TAM_COLA){
        return FALSO;
    }

    size_t tamElemEncolado;
    unsigned frente = pc->frente;

    desencolarSegmentado(pc,&tamElemEncolado,sizeof(size_t),sizeof(size_t));
    verFrenteSegmentado(pc,elem,MIN(tamElemEncolado,tamElem),tamElemEncolado);
    pc->frente=frente;

}

booleano colaVacia(Cola* pc){
    return pc->tamDisponible == TAM_COLA;
}

booleano colaLLena(Cola* pc,size_t tamElem){
    return tamElem + sizeof(size_t) > pc->tamDisponible;
}

void vaciarCola(Cola* pc){
    pc->frente=pc->fondo=0;
    pc->tamDisponible=TAM_COLA;
}

//---------------------------------------------------------------------------------
//                              Funciones Segmentadoras
//---------------------------------------------------------------------------------


void verFrenteSegmentado(const Cola* pc,void* elem, size_t tamElem, size_t tamElemEncolado){

    size_t cantACopiarTotal,cantACopiar1,cantACopiar2,tamElemContiguo;
    unsigned frente = pc->frente;

    cantACopiarTotal = MIN(tamElem,tamElemEncolado);    //Como siempre debemos copiar lo que menos ocupe, nos quedamos con lo que podamos copiar

    tamElemContiguo = frente > pc->fondo? MIN(tamElemEncolado,TAM_COLA-frente):tamElemEncolado;

    cantACopiar1= MIN(tamElemContiguo,cantACopiarTotal); //Espacio hasta el final
    cantACopiar2= cantACopiarTotal - cantACopiar1;  //Espacio desde el inicio hasta donde termina el elemento

    memcpy(elem,pc->vec + frente,cantACopiar1);//Si llega al TAM_COLA vuelve automaticamente a 0, sino el resto vale el valor

    if(cantACopiar2>0){
        memcpy(elem + cantACopiar1,pc->vec,cantACopiar2);   
    }


}

void desencolarSegmentado(Cola* pc,void* elem, size_t tamElem, size_t tamElemEncolado){

    size_t cantACopiarTotal,cantACopiar1,cantACopiar2,tamElemContiguo;

    cantACopiarTotal = MIN(tamElem,tamElemEncolado);    //Como siempre debemos copiar lo que menos ocupe, nos quedamos con lo que podamos copiar

    tamElemContiguo = pc->frente > pc->fondo? MIN(tamElemEncolado,TAM_COLA-pc->frente):tamElemEncolado;

    cantACopiar1= MIN(tamElemContiguo,cantACopiarTotal); //Espacio hasta el final
    cantACopiar2= cantACopiarTotal - cantACopiar1;  //Espacio desde el inicio hasta donde termina el elemento

    memcpy(elem,pc->vec + pc->frente,cantACopiar1);
    pc->frente = (pc->frente+tamElemContiguo) % TAM_COLA;   //Si llega al TAM_COLA vuelve automaticamente a 0, sino el resto vale el valor

    if(cantACopiar2>0){
        memcpy(elem + cantACopiar1,pc->vec,cantACopiar2);   
    }

    pc->frente+=tamElemEncolado-tamElemContiguo; //Sumamos asi ya que cantACopiar2 es el resto de lo que recibimos (que es lo mas chico)

    pc->tamDisponible+=tamElemEncolado;
}

void encolarSegmentado(Cola* pc,const void* elem, size_t tamElem){

    size_t tamContiguo;
    size_t cantACopiar1,cantACopiar2;

    tamContiguo = pc->frente > pc->fondo? pc->tamDisponible: TAM_COLA - pc->fondo;

    cantACopiar1 = MIN(tamElem,tamContiguo);
    cantACopiar2 = tamElem - cantACopiar1;

    memcpy(pc->vec + pc->fondo,elem,tamContiguo);
    pc->fondo= (pc->fondo + cantACopiar1) % TAM_COLA;

    if(cantACopiar2 > 0){
        memcpy(pc->vec,elem + cantACopiar1,cantACopiar2);
        pc->fondo += cantACopiar2;
    }

    pc->tamDisponible -= tamElem;

}
