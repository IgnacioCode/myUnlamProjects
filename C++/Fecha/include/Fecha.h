#ifndef FECHA_H
#define FECHA_H


class Fecha
{
    public:
        Fecha();
        Fecha(int dias,int mes,int anio);

        Fecha sumarDias(int dias) const;
        int difEnDias(const Fecha* otraFecha) const;
        int operator -(const Fecha* otraFecha) const;

    private:
        int diaRel;

};

#endif // FECHA_H
