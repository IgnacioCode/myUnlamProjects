#include "Lista_Dinamica.h"

Nodo* crearNodo(void* elem,size_t tamElem){

    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo){
        free(nue);
        free(elemNodo);
        return NULL;
    }

    memcpy(elemNodo,elem,tamElem);

    nue->elem=elemNodo;
    nue->tamElem=tamElem;
    nue->sig=NULL;

    return nue;

}

void destruirNodo(Nodo* nae,void* elem,size_t tamElem){

    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);

}

void crearLista(Lista* pl){
    *pl=NULL;
}

booleano insertarEnListaFondo(Lista* pl,void* elem,size_t tamElem){

    while(*pl){
        pl=&(*pl)->sig;
    }

    Nodo* nue = crearNodo(elem,tamElem);
    if(!nue){
        return FALSO;
    }

    *pl=nue;
    nue->sig=NULL;

    return VERDADERO;

}

void sumarDuplicadosListaOrdenada(Lista* pl,Suma sum,Cmp cmp){

    Lista* act=pl;  //Inicio ambos igual
    Nodo* nae;

    while(*act){

        act=&(*pl)->sig;    //Me muevo al 2do elemento ya que el 1ro siempre va a aparecer

        if(*act && cmp((*pl)->elem,(*act)->elem)==0){   //Mientras haya un elemento act, y sea igual al anterior (pl) entra

            nae=*act;
            sum((*pl)->elem,(*act)->elem);  //Sumo los valores de ambos y los guardo en el del 1ro
            if(nae->sig){
                (*pl)->sig=(*act)->sig;     //Si hay siguiente, se desconecta el anterior y se lo apunta al proximo
            }
            else{
                (*pl)->sig=NULL;        //Si no hay siguiente, el anterior apunta a NULL para que no apunte a memoria liberada
            }

            free(nae->elem);    //Liberamos el Nodo repetido
            free(nae);
        }
        else{
            pl=act;         //Si no son iguales, avanzo anterior (pl) para tambien luego mover el actual
        }
    }

}



void recorrerLista(Lista* pl,Accion accion,void* datosAccion){

    while(*pl){
        accion((*pl)->elem,datosAccion);
        pl = &(*pl)->sig;
    }

}
