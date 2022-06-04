#ifndef CADENA_H
#define CADENA_H

using namespace std;

#include <cstring>
#include <iostream>


class Cadena{
    public:
        Cadena();
        ~Cadena();
        Cadena(char* str);

        Cadena operator +(Cadena& cad2);
        friend ostream& operator <<(ostream& os,Cadena cad);
    private:
        char* cadena;
        static int cantDigitos(int num);

};

#endif // CADENA_H
