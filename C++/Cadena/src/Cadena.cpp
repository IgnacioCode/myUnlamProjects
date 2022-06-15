#include "..\include\Cadena.h"
#include "..\FueraDeRangoExc.h"

Cadena::Cadena(){
    cadena = new char[1];
    cadena[0]= '\0';
}

Cadena::Cadena(char c){

    this->cadena = new char[2];
    cadena[0] = c;
    cadena[1] = '\0';
}

Cadena::Cadena(int num){

    this->cadena = new char[cantDigitos(num)+1];
    sprintf(cadena,"%d",num);
}

Cadena::Cadena(char* str){

    this->cadena = str;

}

Cadena::Cadena(const char* str){

    this->cadena = new char[strlen(str)+1];
    strcpy(this->cadena,str);


}

Cadena::Cadena(const Cadena& cad2){

    this->cadena = new char[strlen(cad2.cadena)+1];
    strcpy(this->cadena,cad2.cadena);
}

Cadena::~Cadena(){
    delete [] this->cadena;
}

Cadena& Cadena::operator =(const Cadena& cad2){

    if(strlen(this->cadena)!=strlen(cad2.cadena)){
        delete [] this->cadena;
        this->cadena = new char[strlen(cad2.cadena)+1];
    }

    strcpy(this->cadena,cad2.cadena);

    return *this;
}

Cadena& Cadena::operator =(const char* str){

    if(strlen(this->cadena)!=strlen(str)){
        delete [] this->cadena;
        this->cadena = new char[strlen(str)+1];
    }

    strcpy(this->cadena,str);

    return *this;
}

Cadena& Cadena::operator +=(const Cadena& cad2){

    char* aux= new char[strlen(this->cadena) + strlen(cad2.cadena) + 1 ];
    strcpy(aux,this->cadena);
    strcat(aux,cad2.cadena);
    delete [] this->cadena;
    this->cadena = aux;

    return *this;
}

char Cadena::operator [](int i) const{
    if(i>=0 && i>(int)strlen(cadena)){
        throw FueraDeRangoExc("Indice fuera de Rango");
    }
    return cadena[i];
}

Cadena operator +(const Cadena& cad1,const Cadena& cad2){ //friend

    char* nuevoPuntero;

    nuevoPuntero = new char[strlen(cad1.cadena)+strlen(cad2.cadena)+1];

    strcpy(nuevoPuntero,cad1.cadena);
    strcat(nuevoPuntero,cad2.cadena);

    return Cadena(nuevoPuntero);

}

ostream& operator <<(ostream& os,const Cadena& cad1){ //friend

    os << cad1.cadena;

    return os;

}
/*
istream& operator >>(istream& is,Cadena& cad1){ //friend

    char cadena[500];
    is.getline(cadena,500);
    delete [] cad1.cadena;

    cad1.cadena = new char[strlen(cadena)+1];
    strcpy(cad1.cadena,cadena);
    return is;

}*/

istream& operator >>(istream& is,Cadena& cad1){ //friend

    queue<char> cola;   //Template de cola (queue) es como un void "reemplazable"
    char c;
    int i=0;

    do{
        c = is.get();
        cola.push(c);

    }while(c!='\n' && c!= EOF);

    if(strlen(cad1.cadena)!=cola.size()){
        delete [] cad1.cadena;
        cad1.cadena = new char[cola.size()+1];
    }

    while(!cola.empty()){
        cad1.cadena[i] = cola.front();
        cola.pop();
        i++;
    }

    cad1.cadena[i] = '\0';

    return is;

}

int Cadena::cantDigitos(int num){
    int cantDigitos=0;
    do{
       num/=10;
       cantDigitos++;
    }while(num>0);
    return cantDigitos;
}

bool Cadena::esEnteroPositivo(){

    int largoCadena = strlen(cadena);

    if( !cadena[0] || cadena[0]=='-' || cadena[0]<'0' || cadena[0]>'9'){
        return false;
    }

    for(int i=0;largoCadena;i++){
        if(cadena[i]<'0' || cadena[i]>'9'){
            return false;
        }
    }

    return true;
}

unsigned Cadena::longitud()const{
    return strlen(cadena);
}
