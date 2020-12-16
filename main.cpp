#include <iostream>
#include <cstdlib>
using namespace std;
#include "prototipos.h"
#include "rlutil.h"


int main(){

    bool salir=0;
    int opc;
    bool opcioninvalida=0;

    system("COLOR 1F");
    rlutil::locate(29,15);
    cout << " LIBRERIAS WENNER " << endl;
    rlutil::locate(1,30);
    system("pause");
    system("cls");

    while(salir==0){

      cout << " ---------------------------- " << endl;
      cout << " MENU PRINCIPAL " << endl << endl;
      cout << endl << endl << endl << endl << endl;
      cout << " 1 - EMPLEADOS " << endl;
      cout << " 2 - LIBROS " << endl;
      cout << " 3 - VENTAS " << endl;
      cout  << endl << endl;
      cout << " 0 - SALIR DEL PROGRAMA " << endl << endl << endl;
      cout << " ---------------------------- " << endl;
      cout << " INGRESE OPCION: ";
      cin >> opc;

      while(opcioninvalida==0){

         if(opc<0 || opc>3){
             rlutil::locate(1,20);
             rlutil::setColor(rlutil::LIGHTRED);
             cout << " OPCION INVALIDA " << endl << endl;
             rlutil::setColor(rlutil::WHITE);
             cout << " INGRESE OPCION: ";
             cin >> opc;
          }
          else{opcioninvalida=1;}
      }
      system("cls");

      switch(opc){

      case 1:

        menuEmpleados();

      break;

      case 2:

        menuLibros();

      break;

      case 3:

        menuVentas();

      break;

      case 0:

        salir=1;

      break;
      }
    }

    return 0;
}
