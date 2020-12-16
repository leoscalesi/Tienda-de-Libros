#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
using namespace std;
#include "prototipos.h"
#include "fecha.h"
#include "rlutil.h"

class Empleado{

 private:

    char codigoempleado[5];
    char dni[15];
    char cuit[15];
    char nombre[25];
    char apellido[25];
    Fecha fechaingreso;
    bool estadoempleado;

 public:

     bool setCodigoEmpleado(char * cod){

         if(validaCodigoEmpleado(cod)==false){return false;}
         strcpy(codigoempleado,cod);
         return true;
     }

     bool setDni(char * d){

         if(validaDni(d)==false){return false;}
         strcpy(dni,d);
         return true;
     }

     bool setNombre(char *n){

         if(validaNombreApellido(n)==false){return false;}
         strcpy(nombre,n);
         return true;
     }

     bool setApellido(char *a){

         if(validaNombreApellido(a)==false){return false;}
         strcpy(apellido,a);
         return true;
     }

     bool setCuit(char * cu){

         if(validaCuit(cu)==false){return false;}
         strcpy(cuit,cu);
         return true;
     }

     bool setEstadoEmpleado(bool e){estadoempleado=e;}

     bool setFechaIngreso(Fecha fecha){

         if(verificaFechaMenorIgualSistema(fecha)==false){return false;}
         fechaingreso=fecha;
         return true;
     }

     char * getCodigoEmpleado(){return codigoempleado;}
     char * getDni(){return dni;}
     char * getNombre(){return nombre;}
     char * getApellido(){return apellido;}
     char * getCuit(){return cuit;}
     bool getEstadoEmpleado(){return estadoempleado;}
     Fecha getFechaIngreso(){return fechaingreso;}

     bool cargar();
     bool guardarEmpleadoArchivo();
     void mostrar();
     void listarEmpleadoCodigo();
     bool eliminarEmpleado();
     Empleado devuelveEmpleado(int);
};


bool Empleado::cargar(){

        cout << endl << endl;
        cout << " INGRESE CODIGO EMPLEADO " << endl;
        cout << " SE REQUIEREN EXACTAMENTE 4 CARACTERES ENTRE LETRAS Y NUMEROS " << endl;
        cargarCadena(codigoempleado,5);
        if(setCodigoEmpleado(codigoempleado)==false){return false;}
        cout << endl;

        cout << " INGRESE DNI " << endl;
        cout << " MINIMO 7 DIGITOS " << endl;
        cargarCadena(dni,15);
        if(setDni(dni)==false){return false;}
        cout << endl;

        cout << " INGRESE NOMBRE " << endl;
        cout << " SOLO UN ESPACIO ES ADMITIDO " << endl;
        cargarCadena(nombre,25);
        if(setNombre(nombre)==false){return false;}
        cout << endl;

        cout << " INGRESE APELLIDO " << endl;
        cout << " SOLO UN ESPACIO ES ADMITIDO " << endl;
        cargarCadena(apellido,25);
        if(setApellido(apellido)==false){return false;}
        cout << endl;

        cout << " INGRESE CUIT " << endl;
        cout << " MINIMO 10 DIGITOS " << endl;
        cargarCadena(cuit,15);
        if(setCuit(cuit)==false){return false;}
        cout << endl;

        system("cls");
        cout << " INGRESE FECHA DE INGRESO " << endl;

        if(fechaingreso.cargar()==false){return false;}

        /// VER SI CONVIENE PONER EN LA CLASE FECHA
        if(setFechaIngreso(fechaingreso)==false){return false;}
        cout << endl;

        setEstadoEmpleado(true);

        return true;
}


bool Empleado::guardarEmpleadoArchivo(){

        FILE *p;
        bool escribio;
        p=fopen("empleados.dat","ab");
        if(p==NULL){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ABRIR EL ARCHIVO " <<endl;
            rlutil::setColor(rlutil::WHITE);
            return false;
        }
        escribio=fwrite(this,sizeof(*this),1,p);
        fclose(p);
        return escribio;
}

 void Empleado::mostrar(){

       if(getEstadoEmpleado()==true){
        cout << endl << endl;
        cout << " CODIGO EMPLEADO " << endl;
        cout << getCodigoEmpleado() << endl << endl;
        cout << " DNI " << endl;
        cout << getDni() << endl << endl;
        cout << " NOMBRE EMPLEADO " << endl;
        cout << getNombre() << endl << endl;
        cout << " APELLIDO EMPLEADO " << endl;
        cout << getApellido() << endl << endl;
        cout << " CUIT " << endl;
        cout << getCuit() << endl << endl;
        cout << " FECHA DE INGRESO " << endl;
        fechaingreso.mostrar();
       }
 }

 void Empleado::listarEmpleadoCodigo(){

      int pos;

      cout << endl << endl;
      cout << " INGRESE CODIGO EMPLEADO " << endl;
      cargarCadena(codigoempleado,5);

      pos=buscaCodigoArchivoEmpleado(codigoempleado);

      if(pos<0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " CODIGO INEXISTENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            return;
       }

       system("cls");
       FILE *p;
       p=fopen("empleados.dat","rb");
       if(p==NULL){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
            rlutil::setColor(rlutil::WHITE);
            return;
       }

       fseek(p,pos*sizeof(*this),0);
       fread(this,sizeof(*this),1,p);
       this->mostrar();
       cout << endl << endl << endl << endl;
       system("pause");
       system("cls");

       fclose(p);
}

Empleado Empleado::devuelveEmpleado(int pos){

        FILE *p;
        Empleado obj;
        p=fopen("empleados.dat","rb");
        if(p==NULL){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
            rlutil::setColor(rlutil::WHITE);
            obj.setCodigoEmpleado(0000);
            return obj;
        }
        fseek(p,pos*sizeof(Empleado),0);
        fread(&obj,sizeof(Empleado),1,p);

        return obj;

        fclose(p);
}

bool Empleado::eliminarEmpleado(){

    Empleado obj;
    int pos;
    string respuesta;
    bool sobreescribio;

    cout << " INGRESE CODIGO DE EMPLEADO A ELIMINAR " << endl;
    cargarCadena(codigoempleado,5);

    pos=buscaCodigoArchivoEmpleado(codigoempleado);

    if(pos < 0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO EXISTE EL CODIGO " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    obj=devuelveEmpleado(pos);

    system("cls");

    if(obj.getEstadoEmpleado()==true){
        cout << " USTED QUIERE ELIMINAR EL SIGUIENTE REGISTRO " << endl << endl;

        obj.mostrar();

        cout << endl << endl;
        cout << " CONFIRMA?  (S/N): ";
        cin >> respuesta;

        if(respuesta=="s"||respuesta=="S"){

           obj.setEstadoEmpleado(false);
           sobreescribio=sobreescribirArchivoEmpleados(obj,pos);

           if(sobreescribio==false){return false;}

           else{return true;}

         }
          else{

             if(respuesta=="n"||respuesta=="N"){return false;}
             else{
                cout << endl;
                cout << " SOLO SE ADMITEN LOS CARACTERES s,S,n,N" << endl;
                return false;
             }
         }
    }
    else{
        cout << " NO EXISTE EL EMPLEADO ";
        return false;
    }
}

void menuEmpleados(){

    Empleado obj;
    bool salir=0;
    int opc;
    bool opcioninvalida=0;

    while(salir==0){

      cout << " ---------------------------- " << endl;
      cout << " MENU EMPLEADOS " << endl << endl;
      cout << endl << endl << endl << endl << endl;
      cout << " 1 - CARGAR EMPLEADO " << endl;
      cout << " 2 - LISTAR EMPLEADO POR CODIGO DE EMPLEADO " << endl;
      cout << " 3 - MODIFICAR FECHA INGRESO " << endl;
      cout << " 4 - ELIMINAR EMPLEADO " << endl;
      cout << " 5 - LISTAR EMPLEADOS " << endl << endl;
      cout  << endl << endl;
      cout << " 0 - VOLVER AL MENU PRINCIPAL " << endl << endl << endl;
      cout << " ---------------------------- " << endl;

      cout << " INGRESE OPCION: ";
      cin >> opc;

      while(opcioninvalida==0){

          if(opc<0 || opc>5){
             rlutil::locate(1,22);
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

        if(obj.cargar()==true){
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " EL EMPLEADO SE CARGO EXITOSAMENTE " << endl;
            rlutil::setColor(rlutil::WHITE);

            if(obj.guardarEmpleadoArchivo()==true){
                rlutil::setColor(rlutil::LIGHTGREEN);
                cout << " EL EMPLEADO SE GUARDO EXITOSAMENTE " << endl;
                rlutil::setColor(rlutil::WHITE);
                system("pause");
                system("cls");
            }
            else{
                rlutil::setColor(rlutil::LIGHTRED);
                cout << " EL EMPLEADO NO SE PUDO GUARDAR " << endl;
                rlutil::setColor(rlutil::WHITE);
                system("pause");
                system("cls");
            }
        }

        else{
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO CARGAR EL EMPLEADO " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
        }

      break;

      case 2:

        obj.listarEmpleadoCodigo();

      break;

      case 3:

       if(cambiarFechaIngresoEmpleado()==true){
            cout << endl;
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " LA FECHA SE CAMBIO CON EXITO " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl;
            system("pause");
            system("cls");
        }
        else{
            cout << endl;
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO MODIFICAR LA FECHA " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl;
            system("pause");
            system("cls");
        }

      break;

      case 4:

        if(obj.eliminarEmpleado()==true){
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " EL EMPLEADO SE ELIMINO EXITOSAMENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }
        else{
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ELIMINAR AL EMPLEADO " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }

      break;

      case 5:

        listarEmpleados();

      break;

      case 0:

        salir=1;

      break;

     }

    }
}

int buscaCodigoArchivoEmpleado(char *cod){

      Empleado obj;
      int pos=0;
      FILE *p;
      p=fopen("empleados.dat","rb");
      if(p==NULL){

          if(cantRegistrosArchivoEmpleados()>0){
              rlutil::setColor(rlutil::LIGHTRED);
              cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
              rlutil::setColor(rlutil::WHITE);
              return -1;
          }
       }
       while(fread(&obj,sizeof(Empleado),1,p)==1){

            if(strcmp(obj.getCodigoEmpleado(),cod)==0 && obj.getEstadoEmpleado()==true){

                fclose(p);
                return pos;
            }
            pos ++;
        }

        fclose(p);
        return -2;
}


void cargarCadena(char *pal, int tam){

  int i;
  fflush(stdin);
  for(i=0;i<tam;i++){
      pal[i]=cin.get();
	  if(pal[i]=='\n') break;
	  }
  pal[i]='\0';
  fflush(stdin);
}


void listarEmpleados(){

    FILE *p;
    Empleado obj;
    p=fopen("empleados.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }
    while(fread(&obj,sizeof(Empleado),1,p)==1){
        obj.mostrar();
        cout << endl << endl;
    }

    fclose(p);

    system("pause");
    system("cls");
}


bool sobreescribirArchivoEmpleados(class Empleado obj,int pos){

    FILE *p;
    p=fopen("empleados.dat","rb+");
    if(p==NULL){
       rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);
       return false;
    }

    fseek(p,pos*sizeof(Empleado),0);
    fwrite(&obj,sizeof(Empleado),1,p);

    fclose(p);

    return true;
}

bool cambiarFechaIngresoEmpleado(){

    Empleado obj;
    int pos;
    string respuesta;
    bool sobreescribio;
    char codigoempleado[5];
    Fecha fecha;

    cout << " INGRESE CODIGO DE EMPLEADO " << endl;
    cargarCadena(codigoempleado,5);

    pos=buscaCodigoArchivoEmpleado(codigoempleado);

    if(pos<0){

        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ENCONTRO EL CODIGO DE EMPLEADO  " << endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    obj=obj.devuelveEmpleado(pos);

    system("cls");

    if(obj.getEstadoEmpleado()==true){

        cout << " USTED QUIERE MODIFICAR EL SIGUIENTE REGISTRO " << endl << endl;

        obj.mostrar();

        cout << endl << endl;

        cout << " CONFIRMA?  (S/N): ";
        cin >> respuesta;

        if(respuesta=="s"||respuesta=="S"){

         system("cls");

          if(fecha.cargar()==false){return false;}

          if(obj.setFechaIngreso(fecha)==false){

            rlutil::setColor(rlutil::LIGHTRED);
            cout << endl;
            return false;
          }

          else{

            sobreescribio=sobreescribirArchivoEmpleados(obj,pos);

            if(sobreescribio==false){return false;}

            else{return true;}
           }
         }
         else{

             if(respuesta=="n"||respuesta=="N"){return false;}
             else{
                cout << endl;
                cout << " SOLO SE ADMITEN LOS CARACTERES s,S,n,N" << endl;
                return false;
             }
         }
    }
    else{return false;}
}


int cantRegistrosArchivoEmpleados(){

    FILE *p;
    int bytes,cantregistros;

    p=fopen("empleados.dat","rb");
    if(p==NULL){
       ///cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       return 0;
    }
    fseek(p,0,SEEK_END);
    bytes=ftell(p);
    cantregistros=bytes/sizeof(Empleado);

    fclose(p);
    return cantregistros;
}


int cuentaEspaciosVacios(char * cadena){

    int i;

    int cont=0;
    int contespacios=0;

    while(cadena[cont]!='\0'){

        if(cadena[cont]==' '){contespacios++;}

            cont ++;
    }
    return contespacios;
}

bool validaCodigoEmpleado(char * cod){

         int pos,espacios;
         pos=buscaCodigoArchivoEmpleado(cod);

         if(pos>=0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " CODIGO DE EMPLEADO YA EXISTENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
         }

         if(strlen(cod)!=4){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " EL CODIGO DE EMPLEADO DEBE TENER EXACTAMENTE 4 CARACTERES ENTRE LETRAS Y NUMEROS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
         }

         espacios=cuentaEspaciosVacios(cod);

         if(espacios>0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN ESPACIOS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
         }
         return true;
}

bool validaDni(char * dni){

    int digitos,letras,espacios;

    if(strlen(dni)==0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN CADENAS VACIAS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
     }

     espacios=cuentaEspaciosVacios(dni);

     if(espacios>0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN ESPACIOS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
     }

     digitos=cuentaDigitos(dni);

     if(digitos<7){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ADMITEN MENOS DE SIETE DIGITOS EN EL DNI " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl << endl;
        system("pause");
        system("cls");
        return false;
     }

     letras=cuentaLetras(dni);

     if(letras>0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ADMITEN LETRAS EN EL DNI " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl << endl;
        system("pause");
        system("cls");
        return false;
     }

     return true;
}


int cuentaLetras(char * cadena){

    int esdigito;
    int cont=0;
    int contletras=0;

    while(cadena[cont] != '\0'){

        esdigito=isdigit(cadena[cont]);

        if(esdigito==0){contletras ++;}

            cont++;
    }

    return contletras;
}


int cuentaDigitos(char * cadena){

    int esdigito;
    int cont=0;
    int contdigitos=0;

    while(cadena[cont] != '\0'){

        esdigito=isdigit(cadena[cont]);

        if(esdigito==1){contdigitos ++;}

            cont++;
    }
    return contdigitos;
}

bool validaNombreApellido(char * cadena){

    int digitos,letras,espacios;

    if(strlen(cadena)==0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN CADENAS VACIAS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
     }

    digitos=cuentaDigitos(cadena);

    if(digitos>0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ADMITEN DIGITOS EN EL NOMBRE " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl << endl;
        system("pause");
        system("cls");
        return false;
     }

    espacios=cuentaEspaciosVacios(cadena);

    if(espacios>1){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " MAXIMO SE ADMITEN UN ESPACIO PARA ESTE CAMPO " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl << endl;
        system("pause");
        system("cls");
        return false;
    }

    return true;

}

bool validaCuit(char * cuit){

    int digitos,letras,espacios;

    if(strlen(cuit)==0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN CADENAS VACIAS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
     }

     espacios=cuentaEspaciosVacios(cuit);

     if(espacios>0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN ESPACIOS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
     }

     digitos=cuentaDigitos(cuit);

     if(digitos<10){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ADMITEN MENOS DE 10 DIGITOS EN EL CUIT " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl << endl;
        system("pause");
        system("cls");
        return false;
     }

     letras=cuentaLetras(cuit);

     if(letras>0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ADMITEN LETRAS EN EL CUIT " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl << endl;
        system("pause");
        system("cls");
        return false;
     }
     return true;
}

void calculaFechaSistema(int * vDiaMesAnio){


  time_t tiempo;
  char cad[80];
  struct tm *tmPtr;

  tiempo = time(NULL);
  tmPtr = localtime(&tiempo);

  vDiaMesAnio[0]=tmPtr->tm_mday;
  vDiaMesAnio[1]=tmPtr->tm_mon+1;
  vDiaMesAnio[2]=1900+tmPtr->tm_year;
}


bool verificaFechaMenorIgualSistema(class Fecha fecha){

    int vDiaMesAnio[3]={0};  /// v[0] dia   v[1] mes     v[2]  anio

    calculaFechaSistema(vDiaMesAnio);

    if(fecha.getAnio()>vDiaMesAnio[2]){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " LA FECHA INGRESADA NO PUEDE SER MAYOR A LA FECHA ACTUAL " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl << endl;
        system("pause");
        system("cls");
        return false;
    }

    if(fecha.getAnio()==vDiaMesAnio[2]){

        if(fecha.getMes()>vDiaMesAnio[1]){
                rlutil::setColor(rlutil::LIGHTRED);
                cout << " LA FECHA DE INGRESO NO PUEDE SER MAYOR A LA FECHA ACTUAL " << endl;
                rlutil::setColor(rlutil::WHITE);
                cout << endl << endl << endl << endl;
                system("pause");
                system("cls");
                return false;
        }
    }

    if(fecha.getAnio()==vDiaMesAnio[2]){

        if(fecha.getMes()==vDiaMesAnio[1]){

                if(fecha.getDia()>vDiaMesAnio[0]){
                    rlutil::setColor(rlutil::LIGHTRED);
                    cout << " LA FECHA DE INGRESO NO PUEDE SER MAYOR A LA FECHA ACTUAL " << endl;
                    rlutil::setColor(rlutil::WHITE);
                    cout << endl << endl << endl << endl;
                    system("pause");
                    system("cls");

                    return false;
                }
        }
    }
    return true;
}

