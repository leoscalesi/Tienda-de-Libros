# Tienda-de-Libros
Sistema de gestion de tienda de venta de libros utilizando programacion estructurada y orientada a objetos.
En esta ocasion, les presento un sistema de gestion de archivos para una tienda de venta de libros.

El sistema permite hacer ABM sobre 4 archivos.

REQUERIMIENTOS
______________


El sistema debera poseer un menu principal, de la siguiente manera:

-----------------------------------------------------------------------------------------

MENU PRINCIPAL (main.cpp)


1-EMPLEADOS

2-LIBROS

3-VENTAS

0-SALIR DEL PROGRAMA

-----------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------


SUBMENU EMPLEADOS (empleado.cpp)


1-CARGAR EMPLEADO

2-LISTAR EMPLEADO POR CODIGO DE EMPLEADO

3-MODIFICAR FECHA INGRESO

4-ELIMINAR EMPLEADO

5-LISTAR EMPLEADOS

0-VOLVER AL MENU PRINCIPAL




RESTRICCIONES:

-NO SE PERMITIRA CARGAR CODIGOS DE EMPLEADOS DUPLICADOS.

-LA FECHA DE INGRESO DEL EMPLEADO NO PODRA SER MAYOR A LA FECHA DEL SISTEMA.

-EL DNI NO PODRA SER UNA CADENA VACIA,NO PODRA CONTENER ESPACIOS,NO PODRA TENER MENOS DE SIETE DIGITOS Y NO PODRA CONTENER LETRAS.

-EL CUIT NO PODRA SER UNA CADENA VACIA,NO PODRA CONTENER ESPACIOS,NO PODRA TENER MENOS DE 10 DIGITOS Y NO PODRA CONTENER LETRAS.

-EL NOMBRE Y APELLIDO NO PODRA SER UNA CADENA VACIA, NO PODRA CONTENER DIGITOS Y SOLO ADMITIRA UN ESPACIO.


-----------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------

SUBMENU LIBROS (libro.cpp)


1-CARGAR LIBRO

2-LISTAR LIBRO POR CODIGO DE LIBRO

3-MODIFICAR PRECIO LIBRO

4-ELIMINAR LIBRO

5-LISTAR LIBROS

6-RENOVAR STOCK


0-VOLVER AL MENU PRINCIPAL


RESTRICCIONES


-NO SE PERMITIRA CARGAR CODIGOS DE LIBROS DUPLICADOS.

-EL NOMBRE Y APELLIDO DE AUTOR NO PODRA SER UNA CADENA VACIA, NO PODRA CONTENER DIGITOS Y SOLO ADMITIRA UN ESPACIO.

-NO SE ADMITIRAN PRECIOS DE LIBROS MENORES O IGUALES A CERO.

-NO SE ADMITIRAN STOCK NEGATIVOS.

-LA FECHA DE PUBLICACION DEL LIBRO NO PODRA SER MAYOR A LA FECHA DEL SISTEMA.


-----------------------------------------------------------------------------------------




