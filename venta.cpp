#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
#include "prototipos.h"
#include "rlutil.h"


class VentasCabecera{

private:

    int idventa;
    char codigoempleado[5];
    float totalventa;
    bool estadoventacabecera;

public:

    bool setIdVenta(int id){idventa=id;}

    bool setCodigoEmpleado(char * cod){

        int pos;
        pos=buscaCodigoArchivoEmpleado(cod);

        if(pos<0){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " CODIGO INEXISTENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl;
            system("pause");
            system("cls");
            return false;
        }

        strcpy(codigoempleado,cod);

        return true;
    }

    bool setTotalVenta(float t){totalventa=t;}
    bool setEstadoVentaCabecera(bool e){estadoventacabecera=e;}

    int getIdVenta(){return idventa;}
    char * getCodigoEmpleado(){return codigoempleado;}
    float getTotalVenta(){return totalventa;}
    bool getEstadoVentaCabecera(){return estadoventacabecera;}

    ///CUANDO FUNCIONE BIEN CAMIBIARLA A bool
    void guardar();

    /// VOY A MOSTRAR TANTO CABECERA COMO DETALLE PARA TODAS LAS VENTAS
    void mostrar();

    /// TAMBIEN VOY A LISTAR CABECERA Y DETALLE PARA UN ID PUNTUAL

    VentasCabecera devuelveCabecera(int);
};


void VentasCabecera::guardar(){

        FILE *p;
        bool escribio;
        p=fopen("ventascabecera.dat","ab");
        if(p==NULL){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ABRIR EL ARCHIVO " <<endl;
            rlutil::setColor(rlutil::WHITE);
            return;
        }
        escribio=fwrite(this,sizeof(*this),1,p);
        fclose(p);
}


void VentasCabecera::mostrar(){

  if(estadoventacabecera==true){

    cout << endl << endl;
    cout << " ID DE LA VENTA " << endl;
    cout << getIdVenta() << endl;
    cout << " CODIGO EMPLEADO " << endl;
    cout << getCodigoEmpleado() << endl;
    cout << " TOTAL DE LA VENTA " << endl;
    cout << "$ " << getTotalVenta() << endl;
  }
}

VentasCabecera VentasCabecera::devuelveCabecera(int pos){

        FILE *p;
        VentasCabecera obj;
        p=fopen("ventascabecera.dat","rb");
        if(p==NULL){
            cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;

            obj.setCodigoEmpleado("0000");
            obj.setIdVenta(0000);
            obj.setTotalVenta(0000);

            return obj;
        }
        fseek(p,pos*sizeof(VentasCabecera),0);
        fread(&obj,sizeof(VentasCabecera),1,p);

        fclose(p);

        return obj;
}

class VentasDetalle{

private:

    int idventa;
    char codigolibro[10];
    int cantidad;
    float importe;
    bool estadoventadetalle;

public:

    void setId(int id){idventa=id;}
    bool setCodigoLibro(char * cod){

        int pos;
        pos=buscaCodigoArchivoLibro(cod);

        if(pos<0){return false;}

        strcpy(codigolibro,cod);
        return true;
    }

    bool setCantidad(int c ){

        if(c<=0){return false;}
        cantidad=c;
        return true;
    }

    bool setImporte(float i){

        if(i<=0){return false;}
        importe=i;
        return true;
    }

    bool setEstadoVentaDetalle(bool e){estadoventadetalle=e;}

    int getId(){return idventa;}
    const char * getCodigoLibro(){return codigolibro;}
    int getCantidad(){return cantidad;}
    float getImporte(){return importe;}
    bool getEstadoVentaDetalle(){return estadoventadetalle;}

    float cargarDetalle(int);

    ///LUEGO CAMBIARLA A bool
    void guardar();

    // LA LLAMO DESDE MOSTRAR CABECERA

    void mostrar();
};


float VentasDetalle::cargarDetalle(int id){

    VentasDetalle det;
    float total;
    int stock;

    cout << endl;
    cout << " INGRESE CODIGO DE LIBRO " << endl;
    cargarCadena(codigolibro,10);

    if(det.setCodigoLibro(codigolibro)==false){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " CODIGO DE LIBRO INEXISTENTE " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl;
        system("pause");
        system("cls");
        return -1;
    }

    stock=devuelveStockLibro(codigolibro);

    if(stock==0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout  << " NO HAY STOCK " << endl;
        rlutil::setColor(rlutil::WHITE);
        return -4;
    }

    cout << endl;
    cout << " INGRESE CANTIDAD A VENDER DE ESE LIBRO " << endl;
    cin >> cantidad;

    if(det.setCantidad(cantidad)==false){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE ADMITEN CANTIDADES MENORES O IGUALES QUE CERO " << endl;
        rlutil::setColor(rlutil::WHITE);
        return -2;
    }

    if(cantidad>stock){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " LA CANTIDAD INGRESADA ES MAYOR AL STOCK DISPONIBLE " << endl;
        rlutil::setColor(rlutil::WHITE);
        return -3;
    }

    importe=buscaPrecioLibro(codigolibro);
    cout << endl << endl;
    cout << " IMPORTE UNITARIO " << "$ " << importe;

    muestraTituloLibro(codigolibro);
    importe=cantidad*importe;

    det.setImporte(importe);
    det.setId(id);
    det.setEstadoVentaDetalle(true);

    cout << endl << endl;

    det.guardar();
    restarStockLibro(codigolibro,cantidad);

    return importe;
}


void VentasDetalle::guardar(){

        FILE *p;
        bool escribio;
        p=fopen("ventasdetalle.dat","ab");
        if(p==NULL){
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ABRIR EL ARCHIVO " <<endl;
            rlutil::setColor(rlutil::WHITE);
            return;
        }
        escribio=fwrite(this,sizeof(*this),1,p);
        fclose(p);
}

void VentasDetalle::mostrar(){

    if(estadoventadetalle==true){
        cout << endl << endl;
        cout << " ID DE LA VENTA " << endl;
        cout << getId() << endl;
        cout << " CODIGO DEL LIBRO " << endl;
        cout << getCodigoLibro() << endl;
        cout << " CANTIDAD VENDIDA " << endl;
        cout << getCantidad() << endl;
        cout << " IMPORTE " << endl;
        cout << "$ " << getImporte() << endl;
    }
}

void menuVentas(){

    bool salir=0;
    int opc;
    bool opcioninvalida=0;

    while(salir==0){

      cout << " ---------------------------- " << endl;
      cout << " MENU VENTAS " << endl << endl;
      cout << endl << endl << endl << endl << endl;
      cout << " 1 - CARGAR VENTA " << endl;
      cout << " 2 - LISTAR VENTA POR ID VENTA " << endl;
      cout << " 3 - ELIMINAR VENTA " << endl;
      cout << " 4 - LISTAR VENTAS " << endl << endl << endl << endl;
      cout << " 0 - VOLVER AL MENU PRINCIPAL " << endl << endl << endl << endl;
      cout << " ---------------------------- " << endl;

      cout << " INGRESE OPCION: ";
      cin >> opc;

      while(opcioninvalida==0){

          if(opc<0 || opc>4){

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

        if(venta()==true){
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " LA VENTA SE CARGO Y GUARDO EXITOSAMENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }

        else {
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " PROBLEMAS AL REGISTRAR LA VENTA " << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << endl << endl << endl;
            system("pause");
            system("cls");
        }

      break;

      case 2:

        listarVentaId();

      break;

      case 3:

        if(eliminarVenta()==true){
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << " LA VENTA SE ELIMINO EXITOSAMENTE " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }
        else{
            rlutil::setColor(rlutil::LIGHTRED);
            cout << " NO SE PUDO ELIMINAR LA VENTA " << endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
        }

      break;

      case 4:

        listarVentas();

      break;

      case 0:

        salir=1;

      break;
      }
    }
}

bool venta(){

    /// PARA LLAMAR A LA FUNCION QUE CREA EL ID AUTOMATICO SOLO SI VALE 0
   /// ACUMULA EL IMPORTE DE CADA DETALLE DE LA MISMA VENTA
    int id,cont=0;
    float total=0,totalparcial;
    char codigoempleado[5];
    bool salir=0,salir1=0;
    string respuesta;
    VentasCabecera cab;
    VentasDetalle det;

    cout << " INGRESE CODIGO DE EMPLEADO " << endl;
    cargarCadena(codigoempleado,5);

    system("cls");

    if(cab.setCodigoEmpleado(codigoempleado)==false){return false;}

    id=generaIdAutomatico();
    cab.setIdVenta(id);
    cab.setEstadoVentaCabecera(true);

    while(salir==0){

        totalparcial=det.cargarDetalle(id);

        /// SI HUBO PROBLEMAS EN EL DETALLE EN LA PRIMER CARGA
        if(totalparcial <=0){

            /// SI HUBO PROBLEMAS EN EL DETALLE DESPUES DE LA PRIMER CARGA, POR ESO total > 0, PORQUE YA VA A TENER
            /// ALGO ACUMULADO
            if(total > 0){

               cab.setTotalVenta(total);
               cab.guardar();
               return true;
            }
            return false;
        }

        /// ESTE ES EL QUE VA A IR A CABECERA
        total+=totalparcial;
        cout << endl << endl;
        cout << " EL IMPORTE TOTAL ES " << " " << total << endl << endl;
        cout << " DESEA CARGAR OTRA VENTA? (S/N) " << endl;
        cin >> respuesta;

        system("cls");

        if(respuesta=="n" || respuesta=="N"){

            cab.setTotalVenta(total);
            cab.guardar();
            salir=1;
        }
        else{

           if(respuesta=="s" || respuesta=="S"){salir=0;}

           else{
              cout << endl;
              cout << " SOLO SE ADMITEN LOS CARACTERES s,S,n,N" << endl;
              return false;
           }
        }
     }

     return true;
}

int generaIdAutomatico(){

    /// CUENTO REGISTROS ARCHIVO Y LE SUMO 1 A ESE VALOR PARA GENERAR EL AUTONUMERICO
    int cant;
    cant=cantRegistrosArchivoVentasCabecera();
    cant=cant+1;

    return cant;
}


int cantRegistrosArchivoVentasCabecera(){

    FILE *p;
    int bytes,cantregistros;

    p=fopen("ventascabecera.dat","rb");
    if(p==NULL){
       /*rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);*/
       return 0;
    }

    fseek(p,0,SEEK_END);
    bytes=ftell(p);

    cantregistros=bytes/sizeof(VentasCabecera);

    fclose(p);
    return cantregistros;
}

void listarVentasDetalle(){

    FILE *p;
    VentasDetalle obj;
    p=fopen("ventasdetalle.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl;
        system("pause");
        system("cls");
        return;
    }

    while(fread(&obj,sizeof(VentasDetalle),1,p)==1){
        obj.mostrar();
        cout << endl << endl;
    }

    system("pause");
    system("cls");

    fclose(p);
}

void listarVentasCabecera(){

    FILE *p;
    VentasCabecera obj;
    p=fopen("ventascabecera.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << endl << endl;
        system("pause");
        system("cls");
        return;
    }

    while(fread(&obj,sizeof(VentasCabecera),1,p)==1){
        obj.mostrar();
        cout << endl << endl;
    }

    system("pause");
    system("cls");

    fclose(p);
}


void listarVentas(){

     cout << " CABECERAS " << endl << endl;
     listarVentasCabecera();
     cout << " DETALLES " << endl << endl;
     listarVentasDetalle();
}

// LA HAGO GLOBAL AUNQUE ME QUEDAN DUDAS SI DEBERIA SER DE LA CLASE

void listarVentaId(){

    int id,pos;

    cout << " INGRESE ID DE LA VENTA " << endl;
    cin >> id;
    system("cls");
    if(id<=0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " ID INVALIDO " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }

    ///VERIFICAR QUE EXISTA EL ID EN CABECERA

    pos=buscaPosicionCabecera(id);

    if(pos<0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO EXISTE EL ID " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }

    cout << " CABECERA " << endl << endl;
    muestraCabeceraId(id);
    cout << " DETALLE " << endl << endl;
    muestraDetalleId(id);

}

void muestraCabeceraId(int id){

    VentasCabecera obj;
    FILE *p;
    p=fopen("ventascabecera.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }

    while(fread(&obj,sizeof(VentasCabecera),1,p)==1){

        if(obj.getIdVenta()==id){

           obj.mostrar();
           cout << endl << endl;
        }
    }

    system("pause");
    system("cls");

    fclose(p);
}

void muestraDetalleId(int id){

    FILE *p;
    VentasDetalle obj;
    p=fopen("ventasdetalle.dat","rb");
    if(p==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    while(fread(&obj,sizeof(VentasDetalle),1,p)==1){

        if(obj.getId()==id){

           obj.mostrar();
           cout << endl << endl;
        }
    }

    system("pause");
    system("cls");

    fclose(p);
}


bool eliminarVenta(){

    int id,pos;
    VentasCabecera cab;

    cout << " INGRESE ID DE LA VENTA A ELIMINAR " << endl;
    cin >> id;
    system("cls");

    if(id<=0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " ID INVALIDO " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    pos=buscaPosicionCabecera(id);

    if(pos<0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO EXISTE EL ID " << endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    cab=cab.devuelveCabecera(pos);

    ///AHORA USO UN VECTOR DINAMICO PARA EL DETALLE, PIDO MEMORIA PARA LA CANTIDAD DE REGISTROS QUE TENGA
    ///EL DETALLE, LUEGO CARGO TODO EL VECTOR, CAMBIO ESTADO DE ACUERDO AL ID TANTO DE CABECERA COMO DE DETALLE
    ///Y LUEGO SOBREESCRIBO AMBOS ARCHIVOS

    VentasDetalle *v;
    int tam;
    ///EL TAMAÑO LO SACO DE CONTAR LOS REGISTROS EN DETALLE

    tam=cantRegistrosDetalle();
    v=new VentasDetalle[tam];

    if(v==NULL){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO HAY MEMORIA DISPONIBLE " << endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    cargarVector(v,tam);

    /// CAMBIO LOS ESTADOS DE CABECERA Y DETALLE
    ///CAMBIO ESTADO CABECERA
    cab.setEstadoVentaCabecera(false);

    ///CAMBIA BIEN ESTADO DETALLE
    cambioEstadoVector(v,tam,id);

    ///ELIMINA BIEN CABECERA
    if(sobreescribirCabecera(cab,pos)==false){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO SOBREESCRIBIR LA CABECERA " << endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    ///ELIMINA BIEN DETALLE
    if(sobreescribirDetalle(v,tam)==false){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << " NO SE PUDO SOBREESCRIBIR EL DETALLE " << endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    delete v;

    return true;
}


int buscaPosicionCabecera(int id){

       int pos=0;
       VentasCabecera obj;
       FILE *p;
       p=fopen("ventascabecera.dat","rb");
       if(p==NULL){
          rlutil::setColor(rlutil::LIGHTRED);
          cout << " NO SE PUDO ABRIR EL ARCHIVO " << endl;
          rlutil::setColor(rlutil::WHITE);
          return -1;
       }
       while(fread(&obj,sizeof(VentasCabecera),1,p)==1){

            if(obj.getIdVenta()==id){

                fclose(p);
                return pos;
            }
            pos ++;
        }

        fclose(p);
        return -2;
}


int cantRegistrosDetalle(){

    FILE *p;
    int bytes,cantregistros;

    p=fopen("ventasdetalle.dat","rb");
    if(p==NULL){
       rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);
       return 0;

    }

    fseek(p,0,SEEK_END);
    bytes=ftell(p);

    cantregistros=bytes/sizeof(VentasDetalle);

    fclose(p);
    return cantregistros;

}


void cargarVector(class VentasDetalle *v,int tam){

    FILE *p;
    VentasDetalle obj;
    int i;
    p=fopen("ventasdetalle.dat","rb");
    if(p==NULL){
       rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);
       return;
    }
    for(i=0;i<tam;i++){
        fread(&obj,sizeof(VentasDetalle),1,p);
        v[i]=obj;
    }

    fclose(p);
}


void listarVector(class VentasDetalle *v,int tam){

    int i;

    for(i=0;i<tam;i++){
        v[i].mostrar();
    }
}

void cambioEstadoVector(class VentasDetalle *v,int tam,int id){

    int i;

    for(i=0;i<tam;i++){

        if(v[i].getId()==id){
            v[i].setEstadoVentaDetalle(false);
        }
    }
}

bool sobreescribirCabecera(class VentasCabecera obj,int pos){

    FILE *p;
    p=fopen("ventascabecera.dat","rb+");
    if(p==NULL){
       rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);
       return false;
    }

    fseek(p,pos*sizeof(VentasCabecera),0);
    fwrite(&obj,sizeof(VentasCabecera),1,p);

    fclose(p);

    return true;
}

bool sobreescribirDetalle(class VentasDetalle *v,int tam){

    FILE *p;
    VentasDetalle det;
    int i;
    p=fopen("ventasdetalle.dat","rb+");
    if(p==NULL){
       rlutil::setColor(rlutil::LIGHTRED);
       cout << " NO SE PUDO LEER EL ARCHIVO " << endl;
       rlutil::setColor(rlutil::WHITE);
       return false;
    }

    for(i=0;i<tam;i++){

        det=v[i];
        fwrite(&det,sizeof(VentasDetalle),1,p);
    }

    fclose(p);

    return true;
}


















