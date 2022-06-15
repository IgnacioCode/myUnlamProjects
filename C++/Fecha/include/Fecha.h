#ifndef FECHA_H
#define FECHA_H

#define FECHA_BASE 0

class Fecha
{
    public:
        
        Fecha();
        Fecha(int dias,int mes,int anio);

        
        int difEnDias(const Fecha* otraFecha) const;

        int operator -(const Fecha* otraFecha) const;

    private:
        int diaRel;
        int cantDiaMesAcum(int mes);

};

#endif // FECHA_H
