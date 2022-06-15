#ifndef CADENA_H
#define CADENA_H

using namespace std;

#include <string.h>
#include <iostream>
#include <queue>

class Cadena{
    public:
        Cadena();
        Cadena(const Cadena& cad2);
        Cadena(int num);
        Cadena(char c);
        Cadena(const float& num);
        Cadena(const char* str);
        ~Cadena();

        Cadena& operator =(const Cadena& cad2);
        Cadena& operator =(const char* str);
        Cadena& operator +=(const Cadena& cad2);    //Devuelvo una referencia ya que conservo el objeto llamador
        char operator [](int i) const;

        //El operador va a convertir implictamente algun argumento a una cadena
        //utilizando el constructor que necesite segun el tipo de dato
        friend Cadena operator +(const Cadena& cad1,const Cadena& cad2);
        friend ostream& operator <<(ostream& os,const Cadena& cad1);
        friend istream& operator >>(istream& is,Cadena& cad1);

        bool esEnteroPositivo();
        unsigned longitud() const;

    private:

        char* cadena;
        static int cantDigitos(int num);
        Cadena(char* str);

};




#endif // CADENA_H
