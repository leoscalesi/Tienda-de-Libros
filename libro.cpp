#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
#include "prototipos.h"
#include "fecha.h"
#include "rlutil.h"


class Libro{

 private:

    char codigolibro[10];
    char titulolibro[60];
    char nombreautor[50];
    char apellidoautor[50];
    char nombreeditorial[50];
    Fecha fechapublicacion;
    float preciolibro;
    int stock;
    bool estadolibro;

 public:

     bool setCodigoLibro(char * cod){

        if(validaCodigoLibro(cod)==false){return false;}
        strcpy(codigolibro,cod);
        return true;
     }

     bool setTituloLibro(char * t){

         if(validaTituloLibro(t)==false){return false;}
         strcpy(titulolibro,t);
         return true;
     }

     bool setNombreAutor(char *n){

         if(validaNombreApellido(n)==false){return false;}
         strcpy(nombreautor,n);
         return true;
     }

     bool setApellidoAutor(char *a){

         if(validaNombreApellido(a)==false){return false;}
         strcpy(apellidoautor,a);
         return true;
     }

     bool setNombreEditorial(char * ne){

         if(validaNombreEditorial(ne)==false){return false;}
         strcpy(nombreeditorial,ne);
         return true;

     }

     bool setPrecioLibro(float p){

         if(p <=0){

             rlutil::setColor(rlutil::LIGHTRED);
             cout << " NO SE ADMITEN PRECIOS MENORES O IGUALES QUE CERO " << endl;
             rlutil::setColor(rlutil::WHITE);
             return false;
         }

         preciolibro=p;
         return true;
     }

     bool setStock(int s){

         if(s<0){

            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN STOCKS MENORES QUE CERO " << endl;
            rlutil::setColor(rlutil::WHITE);
            return false;
         }

         stock=s;
         return true;
     }

     bool setEstadoLibro(bool e){estadolibro=e;}

     bool setFechaPublicacion(Fecha fecha){

         if(verificaFechaMenorIgualSistema(fecha)==false){return false;}
         fechapublicacion=fecha;
         return true;
     }

     char * getCodigoLibro(){return codigolibro;}
     char * getTituloLibro(){return titulolibro;}
     char * getNombreAutor(){return nombreautor;}
     char * getApellidoAutor(){return apellidoautor;}
     char * getNombreEditorial(){return nombreeditorial;}
     float getPrecioLibro(){return preciolibro;}
     int getStock(){return stock;}
     bool getEstadoLibro(){return estadolibro;}
     Fecha getFechaPublicacion(){return fechapublicacion;}


     bool cargar();
     bool guardar();
     void mostrar();
     bool eliminarLibro();
     void listarLibroCodigo();
     Libro devuelveLibro(int);
};


bool Libro::cargar(){

     cout << endl << endl;
     cout << " INGRESE CODIGO DE LIBRO " << endl;
     cout << " MINIMO 5 CARACTERES " << endl;
     cargarCadena(codigolibro,10);
     if(setCodigoLibro(codigolibro)==false){return false;}
     cout << endl;

     cout << " INGRESE TITULO DEL LIBRO " << endl;
     cargarCadena(titulolibro,60);
     if(setTituloLibro(titulolibro)==false){return false;}
     cout << endl;

     cout << " INGRESE NOMBRE DEL AUTOR" << endl;
     cargarCadena(nombreautor,50);
     if(setNombreAutor(nombreautor)==false){return false;}
     cout << endl;

     cout << " INGRESE APELLIDO DEL AUTOR " << endl;
     cargarCadena(apellidoautor,50);
     if(setApellidoAutor(apellidoautor)==false){return false;}
     cout << endl;

     cout << " INGRESE NOMBRE DE LA EDITORIAL " << endl;
     cargarCadena(nombreeditorial,50);
     if(setNombreEditorial(nombreeditorial)==false){return false;}

     system("cls");
     cout << " INGRESE FECHA DE PUBLICACION " << endl;

     if(fechapublicacion.cargar()==false){return false;}

     if(setFechaPublicacion(fechapublicacion)==false){return false;}
     cout << endl;

     cout << " INGRESE PRECIO DEL LIBRO " << endl;
     cin >> preciolibro;

     if(setPrecioLibro(preciolibro)==false){return false;}
     cout << endl;

     cout << " INGRESE STOCK " << endl;
     cin >> stock;
     if(setStock(stock)==false){return false;}
     cout << endl;

     setEstadoLibro(true);

     return true;
}

bool Libro::guardar(){

        FILE *p;
        bool escribio;
        p=fopen("libros.dat","ab");
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



void Libro::mostrar(){

     if(estadolibro==true){
        cout << endl << endl;
        cout << " CODIGO LIBRO " << endl;
        cout << getCodigoLibro() << endl << endl;
        cout << " TITULO DEL LIBRO " << endl;
        cout <<getTituloLibro() << endl << endl;
        cout << " NOMBRE DEL AUTOR" << endl;
        cout << getNombreAutor() << endl << endl;
        cout << " APELLIDO DEL AUTOR " << endl;
        cout << getApellidoAutor()<< endl << endl;
        cout << " NOMBRE DE LA EDITORIAL " << endl;
        cout << getNombreEditorial()<< endl << endl;
        cout << " PRECIO DEL LIBRO " << endl;
        cout << "$ " << getPrecioLibro() << endl << endl;
        cout << " STOCK " << endl;
        cout << getStock() << endl << endl;
        cout << " FECHA DE PUBLICACION " << endl;
        fechapublicacion.mostrar();
       }
}


bool Libro::eliminarLibro(){

    Libro obj;
    int pos;
    bool sobreescribio;
    string respuesta;

    cout << " INGRESE CODIGO DE LIBRO A ELIMINAR " << endl;
    cargarCadena(codigolibro,10);
    pos=buscaCodigoArchivoLibro(codigolibro);

    if(pos<0){

        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ENCONTRO EL CODIGO " << endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    obj=devuelveLibro(pos);

    if(obj.getEstadoLibro()==true){
        system("cls");
        cout << " USTED QUIERE ELIMINAR EL SIGUIENTE LIBRO " << endl << endl;

        obj.mostrar();

        cout << endl << endl;
        cout << " CONFIRMA?  (S/N): ";
        cin >> respuesta;

        if(respuesta=="s"||respuesta=="S"){

           obj.setEstadoLibro(false);
           sobreescribio=sobreescribirArchivoLibros(obj,pos);

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
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO EXISTE EL CODIGO " << endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
     }
}



Libro Libro::devuelveLibro(int pos){

        FILE *p;
        Libro obj;
        p=fopen("libros.dat","rb");
        if(p==NULL){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
            rlutil::setColor(rlutil::WHITE);
            obj.setCodigoLibro(00000);
            return obj;
        }

        fseek(p,pos*sizeof(Libro),0);
        fread(&obj,sizeof(Libro),1,p);

        return obj;

        fclose(p);
}

void Libro::listarLibroCodigo(){

        int pos;

        cout << endl << endl;
        cout << " INGRESE CODIGO LIBRO " << endl;
        cargarCadena(codigolibro,10);


        pos=buscaCodigoArchivoLibro(codigolibro);

        if(pos<0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ENCONTRO EL CODIGO DE LIBRO " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            return;
        }

        system("cls");
        FILE *p;
        p=fopen("libros.dat","rb");
        if(p==NULL){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
            rlutil::setColor(rlutil::WHITE);
            return;
        }
        fseek(p,pos*sizeof(*this),0);
        fread(this,sizeof(*this),1,p);
        this->mostrar();

        fclose(p);
        cout << endl << endl;
        system("pause");
        system("cls");

}

void menuLibros(){

    Libro obj;
    bool salir=0;
    int opc;
    bool opcioninvalida=0;

    while(salir==0){

      cout << " ---------------------------- " << endl;
      cout << " MENU LIBROS " << endl << endl;
      cout << endl << endl << endl << endl << endl;
      cout << " 1 - CARGAR LIBRO " << endl;
      cout << " 2 - LISTAR LIBRO POR CODIGO DE LIBRO " << endl;
      cout << " 3 - MODIFICAR PRECIO LIBRO " << endl;
      cout << " 4 - ELIMINAR LIBRO " << endl;
      cout << " 5 - LISTAR LIBROS " << endl;
      cout << " 6 - RENOVAR STOCK " << endl << endl;
      cout  << endl << endl;
      cout << " 0 - VOLVER AL MENU PRINCIPAL " << endl << endl << endl;
      cout << " ---------------------------- " << endl;

      cout << " INGRESE OPCION: " ;
      cin >> opc;

      while(opcioninvalida==0){

          if(opc<0 || opc>6){

             rlutil::locate(1,22);
             rlutil::setColor(rlutil::LIGHTRED);
             cout << " OPCION INVALIDA " << endl << endl;
             rlutil::setColor(rlutil::WHITE);
             cout << " INGRESE OPCION: ";
             cin >> opc;
          }
          else{

              opcioninvalida=1;
          }
      }

      system("cls");

      switch(opc){

      case 1:

        if(obj.cargar()==true){
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " EL LIBRO SE CARGO EXITOSAMENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            if(obj.guardar()==true){
                rlutil::setColor(rlutil::LIGHTGREEN);
                cout << " EL LIBRO SE GUARDO EXITOSAMENTE " << endl;
                rlutil::setColor(rlutil::WHITE);
                system("pause");
                system("cls");
            }
            else{
                rlutil::setColor(rlutil::LIGHTRED);
                cout << " EL LIBRO NO SE PUDO GUARDAR " << endl;
                rlutil::setColor(rlutil::WHITE);
                system("pause");
                system("cls");
            }
        }
        else{
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO CARGAR EL LIBRO " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
        }

      break;

      case 2:

        obj.listarLibroCodigo();

      break;

      case 3:

        if(modificarPrecio()==true){
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " SE MODIFICO EL PRECIO CON EXITO " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }
        else{
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO MODIFICAR EL PRECIO " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }

      break;

      case 4:

        if(obj.eliminarLibro()==true){
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " EL LIBRO SE ELIMINO EXITOSAMENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }
        else{
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ELIMINAR EL LIBRO " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }

      break;

      case 5:

        listarLibros();

      break;

      case 6:

        if(renuevaStockLibro()==false){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO RENOVAR EL STOCK DEL LIBRO " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl;
            system("pause");
            system("cls");
        }
        else{
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " EL STOCK SE RENOVO CORRECTAMENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl;
            system("pause");
            system("cls");
        }

      break;

      case 0:

        salir=1;

      break;
      }
    }
}

int buscaCodigoArchivoLibro(char *codigolibro){

       int pos=0;
       Libro obj;
       FILE *p;
       p=fopen("libros.dat","rb");
       if(p==NULL){

          if(cantRegistrosArchivoLibros()>0){

              rlutil::setColor(rlutil::LIGHTRED);
              cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
              rlutil::setColor(rlutil::WHITE);
              return -1;
          }
       }
       while(fread(&obj,sizeof(Libro),1,p)==1){

            if(strcmp(obj.getCodigoLibro(),codigolibro)==0 && obj.getEstadoLibro()==true){

                fclose(p);
                return pos;
            }
            pos ++;
        }

        fclose(p);
        return -2;
}

int cantRegistrosArchivoLibros(){

    FILE *p;
    int bytes,cantregistros;

    p=fopen("libros.dat","rb");
    if(p==NULL){

       ///cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       return 0;
    }
    fseek(p,0,SEEK_END);
    bytes=ftell(p);
    cantregistros=bytes/sizeof(Libro);

    fclose(p);
    return cantregistros;
}


void listarLibros(){

    FILE *p;
    Libro obj;
    p=fopen("libros.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }
    while(fread(&obj,sizeof(Libro),1,p)==1){
        obj.mostrar();
        cout << endl << endl;
    }

    system("pause");
    system("cls");

    fclose(p);
}

float buscaPrecioLibro(char * cod){

    FILE *p;
    Libro obj;
    p=fopen("libros.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        return -1;
    }
    while(fread(&obj,sizeof(Libro),1,p)==1){

        if(strcmp(obj.getCodigoLibro(),cod)==0 && obj.getEstadoLibro()==true){

            return obj.getPrecioLibro();
        }
    }

    fclose(p);

    return -2;

}

bool sobreescribirArchivoLibros(class Libro obj,int pos){

    FILE *p;
    p=fopen("libros.dat","rb+");
    if(p==NULL){
       rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);
       return false;
    }

    fseek(p,pos*sizeof(Libro),0);
    fwrite(&obj,sizeof(Libro),1,p);

    fclose(p);

    return true;
}


bool modificarPrecio(){

         Libro obj;
         int pos;
         bool sobreescribio;
         float nuevoprecio;
         string respuesta;
         char codigolibro[10];

         cout << " INGRESE CODIGO DE LIBRO " << endl;
         cargarCadena(codigolibro,10);
         pos=buscaCodigoArchivoLibro(codigolibro);

         if(pos<0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ENCONTRO EL CODIGO DE LIBRO " << endl;
            rlutil::setColor(rlutil::WHITE);
            return false;
         }

         obj=obj.devuelveLibro(pos);

         system("cls");

         if(obj.getEstadoLibro()==true){
            cout << " USTED QUIERE MODIFICAR EL PRECIO DEL SIGUIENTE REGISTRO " << endl << endl;

            obj.mostrar();

            cout << endl << endl;

            cout << " CONFIRMA?  (S/N): ";
            cin >> respuesta;

            if(respuesta=="s"||respuesta=="S"){
                system("cls");
                cout << " INGRESE NUEVO PRECIO " << endl;
                cin >> nuevoprecio;
                if(obj.setPrecioLibro(nuevoprecio)==true){

                      sobreescribio=sobreescribirArchivoLibros(obj,pos);

                      if(sobreescribio==false){return false;}

                      else{return true;}
                }

                 else{return false;}
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
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO EXISTE EL CODIGO DE LIBRO ";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }
}


int devuelveStockLibro(char *cod){

    FILE *p;
    Libro obj;
    p=fopen("libros.dat","rb");
    if(p==NULL){
       rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);
       return -1;
    }

     while(fread(&obj,sizeof(Libro),1,p)==1){

        if(strcmp(obj.getCodigoLibro(),cod)==0 && obj.getEstadoLibro()==true){

            if(obj.getStock()<=0){

                ///PRUEBA NUEVA
                /*rlutil::setColor(rlutil::LIGHTRED);
                cout << " NO HAY STOCK " << endl;
                rlutil::setColor(rlutil::WHITE);
                fclose(p);
                return -2;*/
                return 0;
            }
            else{
                fclose(p);
                return obj.getStock();
            }
        }
     }
}


void restarStockLibro(char *cod,int cant){

      Libro obj;
      int pos,nuevostock;
      bool sobreescribio;
      string respuesta;

      pos=buscaCodigoArchivoLibro(cod);
      obj=obj.devuelveLibro(pos);
      nuevostock=obj.getStock()-cant;

      cout << " NUEVO STOCK " << nuevostock;

      obj.setStock(nuevostock);
      sobreescribio=sobreescribirArchivoLibros(obj,pos);

      if(sobreescribio==false){

        return;
      }
}

bool validaCodigoLibro(char * cod){

         int pos,espacios;
         pos=buscaCodigoArchivoLibro(cod);

         if(pos>=0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " CODIGO DE LIBRO YA EXISTENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
         }

         if(strlen(cod)<5){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " EL CODIGO DE LIBRO DEBE TENER MINIMO 5 CARACTERES " << endl;
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


bool validaTituloLibro(char * titulo){

    if(strlen(titulo)==0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN CADENAS VACIAS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
     }
     return true;
}


bool validaNombreEditorial(char * editorial){

    if(strlen(editorial)==0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE ADMITEN CADENAS VACIAS " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
     }
     return true;
}

void muestraTituloLibro(char *cod){

    FILE *p;
    Libro obj;
    p=fopen("libros.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        return;
    }
    while(fread(&obj,sizeof(Libro),1,p)==1){

        if(strcmp(obj.getCodigoLibro(),cod)==0 && obj.getEstadoLibro()==true){
                cout << endl;
                cout << " TITULO DEL LIBRO " << "  " << obj.getTituloLibro();
        }
    }

    fclose(p);
}

bool renuevaStockLibro(){

    int nuevostock,stockactual,cant;
    Libro obj;
    char codigolibro[10];
    int posicion;
    cout << endl;
    cout << " INGRESE CODIGO LIBRO " << endl;
    cargarCadena(codigolibro,10);

    posicion=buscaCodigoArchivoLibro(codigolibro);

    if(posicion < 0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO EXISTE EL CODIGO DE LIBRO ";
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl;
        system("pause");
        system("cls");
        return false;
    }

    obj=obj.devuelveLibro(posicion);

    cout << endl << endl;
    cout << " INGRESE CANTIDAD " << endl;
    cin >> cant;

    if(cant<=0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ADMITEN CANTIDADES MENORES O IGUALES QUE CERO " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl;
        system("pause");
        system("cls");
        return false;
    }

    stockactual=obj.getStock();
    nuevostock=stockactual+cant;
    obj.setStock(nuevostock);

    if(sobreescribirArchivoLibros(obj,posicion)==false){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << "  NO SE PUDO SOBREESCRIBIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl;
        system("pause");
        system("cls");
        return false;
    }

    return true;
}

