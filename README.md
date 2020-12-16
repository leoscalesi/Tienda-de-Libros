# Tienda-de-Libros
Sistema de gestion de tienda de venta de libros utilizando programacion estructurada y orientada a objetos.
En esta ocasion, les presento un sistema de gestion de archivos para una tienda de venta de libros.

En este proyecto utilizo conceptos de archivos, asignacion dinamica de memoria, programacion estructurada y orientada a objetos.

El sistema permite hacer ABM sobre 4 archivos.

-----------------------------------------------------------------------------------------

REQUERIMIENTOS


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


__________________________

RESTRICCIONES:

__________________________

-NO SE PERMITIRA CARGAR CODIGOS DE EMPLEADOS DUPLICADOS.

-LA FECHA DE INGRESO DEL EMPLEADO NO PODRA SER MAYOR A LA FECHA DEL SISTEMA.

-EL DNI NO PODRA SER UNA CADENA VACIA,NO PODRA CONTENER ESPACIOS,NO PODRA TENER MENOS DE SIETE DIGITOS Y NO PODRA CONTENER LETRAS.

-EL CUIT NO PODRA SER UNA CADENA VACIA,NO PODRA CONTENER ESPACIOS,NO PODRA TENER MENOS DE 10 DIGITOS Y NO PODRA CONTENER LETRAS.

-EL NOMBRE Y APELLIDO NO PODRA SER UNA CADENA VACIA, NO PODRA CONTENER DIGITOS Y SOLO ADMITIRA UN ESPACIO.

-SOLO SE PODRA LISTAR UN EMPLEADO POR SU CODIGO SI ES QUE EXISTE EN EL ARCHIVO empleados.dat.

-SOLO SE PODRA MODIFICAR LA FECHA DE INGRESO DE UN EMPLEADO EXISTENTE EN EL ARCHIVO empleados.dat.

-SOLO SE PODRA ELIMINAR UN EMPLEADO EXISTENTE EN EL ARCHIVO empleados.dat.

-SOLO SE LISTARAN LOS EMPLEADOS QUE NO HAYAN SIDO ELIMINADOS.



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


-----------------------------------------------------------------------------------------

RESTRICCIONES

-----------------------------------------------------------------------------------------

-NO SE PERMITIRA CARGAR CODIGOS DE LIBROS DUPLICADOS.

-EL NOMBRE Y APELLIDO DE AUTOR NO PODRA SER UNA CADENA VACIA, NO PODRA CONTENER DIGITOS Y SOLO ADMITIRA UN ESPACIO.

-NO SE ADMITIRAN PRECIOS DE LIBROS MENORES O IGUALES A CERO.

-NO SE ADMITIRAN STOCK NEGATIVOS.

-LA FECHA DE PUBLICACION DEL LIBRO NO PODRA SER MAYOR A LA FECHA DEL SISTEMA.

-SOLO SE PODRA LISTAR UN LIBRO POR SU CODIGO SI ES QUE EXISTE EN EL ARCHIVO libros.dat.

-SOLO SE PODRA MODIFICAR EL PRECIO DE UN LIBRO EXISTENTE EN EL ARCHIVO libros.dat.

-SOLO SE PODRA ELIMINAR UN LIBRO EXISTENTE EN EL ARCHIVO libros.dat.

-SOLO SE PODRA RENOVAR EL STOCK DE UN LIBRO EXISTENTE EN EL ARCHIVO libros.dat.

-SOLO SE LISTARAN LOS LIBROS QUE NO HAYAN SIDO ELIMINADOS.



-----------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------

SUBMENU VENTAS (venta.cpp)


1-CARGAR VENTA

2-LISTAR VENTA POR ID VENTA

3-MODIFICAR PRECIO LIBRO

4-ELIMINAR VENTA

5-LISTAR VENTA


0-VOLVER AL MENU PRINCIPAL


LA VENTA ESTA DIVIDIDA EN DOS ARCHIVOS: VENTA CABECERA Y VENTA DETALLE.

-----------------------------------------------------------------------------------------

RESTRICCIONES

-----------------------------------------------------------------------------------------

-EL CODIGO DE EMPLEADO DEBE EXISTIR EN EL ARCHIVO empleados.dat.

-EL CODIGO DE LIBRO DEBE EXISTIR EN EL ARCHIVO libros.dat.

-NO SE PERMITIRA VENDER MAS LIBROS QUE LOS QUE HAY EN STOCK PARA EL CODIGO DE LIBRO CORRESPONDIENTE.

-NO SE PERMITIRA VENDER LIBROS CON STOCK 0.

-EL ID DE LA VENTA SE GENERARA AUTOMATICAMENTE.

-AL VENDER LIBROS SE DEBE RESTAR AUTOMATICAMENTE EL STOCK EN EL ARCHIVO libros.dat.

-PUEDE HABER MAS DE UN DETALLE PARA UNA MISMA CABECERA.

-AL ELIMINAR UNA VENTA SE ELIMINARA SU CABECERA JUNTO CON TODOS SUS DETALLES.

-SOLO SE PODRA LISTAR UNA VENTA POR SU CODIGO SI ES QUE EXISTE EN EL ARCHIVO ventas.dat.

-SOLO SE PODRA ELIMINAR UNA VENTA EXISTENTE EN EL ARCHIVO ventas.dat.

-SOLO SE LISTARAN LAS VENTAS QUE NO HAYAN SIDO ELIMINADAS.




-----------------------------------------------------------------------------------------














