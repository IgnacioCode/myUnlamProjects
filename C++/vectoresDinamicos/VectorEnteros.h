#ifndef VECTORENTEROS_H
#define VECTORENTEROS_H

#include <iostream>

using namespace std;

class VectorEnteros
{
    public:
        VectorEnteros();
        ~VectorEnteros();
        VectorEnteros(const VectorEnteros& vec2);
        VectorEnteros(const VectorEnteros& vec1,const VectorEnteros vec2);
        VectorEnteros(const int* vec,const unsigned cantElem);
        
        VectorEnteros& agregar(const int* vec,const unsigned cantElem);

        VectorEnteros operator +(const VectorEnteros& vec2);
        VectorEnteros operator +(const int num);
        VectorEnteros& operator =(const VectorEnteros& vec2);
        friend ostream& operator <<(ostream& os,const VectorEnteros& vec2);
    protected:

    private:
        int* vec;
        unsigned cantElem; 
};



#endif // VECTORENTEROS_H
