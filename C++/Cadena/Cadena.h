#include <string>
#include <stdlib>

using namespace std

class Cadena{

    public:
        Cadena();
        ~Cadena();
        Cadena(char* str);

        Cadena operator +(Cadena cad2);

    private:
        char* cadena;
        static int cantDigitos(int num);


}

