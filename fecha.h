#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include "rlutil.h"

class Fecha{

private:

    int dia,mes,anio;

public:

    bool setDia(int d){

        if(d < 1 || d > 31){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " DIA INVALIDO " << endl;
            rlutil::setColor(rlutil::WHITE);
            return false;
        }
        else{
            dia=d;
            return true;
        }
    }

    bool setMes(int m){

        if(m < 1 || m > 12){
            cout << " MES INVALIDO " << endl;
            return false;
        }
        else{
            mes=m;
            return true;
        }
    }

    bool setAnio(int a){

        if(a <= 0){
            cout << " ANIO INVALIDO " << endl;
            return false;
        }
        else{
            anio=a;
            return true;
        }
    }

    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

    bool cargar(){

        cout << endl;
        cout << " INGRESE DIA " << endl;
        cin >> dia;
        if(setDia(dia)==false){
            return false;
        }
        cout << endl;
        cout << " INGRESE MES " << endl;
        cin >> mes;
        if(setMes(mes)==false){
            return false;
        }
        cout << endl;
        cout << " INGRESE ANIO " << endl;
        cin >> anio;
        if(setAnio(anio)==false){
            return false;
        }
        return true;
    }

    void mostrar(){

        cout << endl;
        cout << " DIA " << endl;
        cout << getDia() << endl << endl;
        cout << " MES " << endl;
        cout << getMes() << endl << endl;
        cout << " ANIO " << endl;
        cout << getAnio() << endl << endl;
    }

    bool modificarFecha(){

        cout << " INGRESE DIA " << endl;
        cin >> dia;
        if(setDia(dia)==false){
            return false;
        }
        cout << " INGRESE MES " << endl;
        cin >> mes;
        if(setMes(mes)==false){
            return false;
        }
        cout << " INGRESE ANIO " << endl;
        cin >> anio;
        if(setAnio(anio)==false){
            return false;
        }

        return true;
    }

};


#endif // FECHA_H_INCLUDED
