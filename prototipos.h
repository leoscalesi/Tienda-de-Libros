#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

int buscaCodigoArchivoEmpleado(char *cod);

void cargarCadena(char *pal, int tam);

void listarEmpleados();

void menuEmpleados();

void listarEmpleados();

int cantRegistrosArchivoVentasCabecera();

int generaIdAutomatico();

void listarVentas();

int buscaIdVentasCabecera(int);

void menuVentas();

int buscaCodigoArchivoLibro(char *);

void restarStockLibro(char *,int);

float devuelveTotalVentaPorIdVenta(int id);

bool sobreescribirArchivoEmpleados(class Empleado obj,int pos);

void listarVentasDetalle();

void listarLibros();

void menuLibros();

float buscaPrecioLibro(char *);

bool sobreescribirArchivoLibros(class Libro obj,int pos);

bool modificarPrecio();

bool buscaStockLibroCodigo(char *cod);

void actualizarTotalCabecera(int cant,float precio,int id);

bool sobreescribirCabecera(class VentasCabecera obj,int pos);

bool sobreescribirDetalle(class VentasDetalle *v,int tam);

bool cambiarFechaIngresoEmpleado();

void listarVentaId();

bool venta();

int devuelveStockLibro(char *);

void muestraCabeceraId(int id);

void muestraDetalleId(int id);

bool eliminarVenta();

int buscaPosicionCabecera(int id);

int cantRegistrosDetalle();

void cargarVector(class VentasDetalle *v,int tam);

void listarVector(class VentasDetalle *v,int tam);

void cambioEstadoVector(class VentasDetalle *v,int tam,int id);






int cantRegistrosArchivoEmpleados();

int cuentaEspaciosVacios(char *);

bool validaCodigoEmpleado(char *);

bool validaDni(char *);

int cuentaLetras(char *);

int cuentaDigitos(char *);

bool validaNombreApellido(char *);

bool validaCuit(char *);

void calculaFechaSistema(int *);

bool verificaFechaMenorIgualSistema(class Fecha);



bool validaCodigoLibro(char *);

int cantRegistrosArchivoLibros();

bool validaTituloLibro(char *);

bool validaNombreEditorial(char *);

void muestraTituloLibro(char *);

bool renuevaStockLibro();




#endif // PROTOTIPOS_H_INCLUDED
