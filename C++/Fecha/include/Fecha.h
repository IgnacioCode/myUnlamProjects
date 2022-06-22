#ifndef FECHA_H
#define FECHA_H

using namespace std;

#include <iostream>

#define FECHA_BASE 0



class Fecha
{
    public:
        
        Fecha();
        Fecha(int dia,int mes,int anio);

        void setDMA(int dia,int mes,int anio);
        int getDiaRel() const;


        int difEnDias(const Fecha& otraFecha) const;

        bool operator >(const Fecha& otraFecha) const;
        bool operator <(const Fecha& otraFecha) const;
        int operator -(const Fecha& otraFecha) const;
        
        bool esFechaValida(const Fecha& otraFecha) const;
        static bool esFechaValida(int dia,int mes,int anio);
        static bool esBisiesto(int anio);
    private:
        int diaRel;
        static int cantDiaMesAcum(int mes, int anio);
        static int cantDiaMes(int mes,int anio);
        
        

};

ostream& operator <<(ostream& os, const Fecha& otraFecha);
istream& operator >>(istream& is, const Fecha& otraFecha);

#endif // FECHA_H
