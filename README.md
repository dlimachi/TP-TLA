[![✗](https://img.shields.io/badge/Release-v0.2.0-ffb600.svg?style=for-the-badge)](https://github.com/agustin-golmar/Flex-Bison-Compiler/releases)

# Compilador Flex/Bison

## Requerimientos

Para construir el compilador, se requieren las siguientes dependencias:

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.24.1](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)

Si en lugar de trabajar con un entorno _Linux_, se está construyendo el proyecto sobre un entorno _Microsoft Windows_, se debe instalar _Microsoft Visual Studio 2022_ con las extensiones para desarrollar aplicaciones en _C/C++_, así como también las herramientas requeridas, con excepción del compilador _GCC_ y la herramienta _Make_.

## Construcción

Para construir el proyecto por completo, ejecute en la raíz del repositorio los siguientes comandos (en _Linux_):

```bash
user@machine:path/ $ chmod u+x --recursive script
user@machine:path/ $ script/build.sh
```

En un entorno _Microsoft Windows_, en cambio, se debe ejecutar:

```bash
user@machine:path/ $ script\build.bat
```

Luego se deberá abrir la solución generada `bin\Compiler.sln` con el IDE _Microsoft Visual Studio 2022_. Los ejecutables que este sistema construye se depositan dentro del directorio `bin\Debug` y `bin\Release`, según corresponda.

## TP TLA 1° Cuatrimestre 2023

| Nombre | Apellido | Legajo | E-mail |
| --- | --- | --- | --- |
| Matias Ezequiel | Daneri | 60798 | mdaneri@itba.edu.ar |
| Desiree Melisa | Limachi | 59463 | dlimachi@itba.edu.ar |
| Juan Adolfo | Rosauer Herrmann | 61240 | jurosauer@itba.edu.ar |
| Nicolás | Suarez Durrels | 62468 | nsuarezdurrels@itba.edu.ar |

## **Introducción**

El objetivo principal del proyecto es desarrollar un lenguaje que permita generar un archivo .sql a partir de un archivo.

Nuestro lenguaje permite crear 5 tipos de consultas: intert into, delete, create, check y query, los cuales son muy conocidos en el lenguaje sql.Con este programa buscamos solucionar el problema de la dificultad que puede llegar a ser para algunas personas crear estas consultas, facilitandoles usando la misma.



## Consideraciones

Como se menciono en la corrección de la primera entrega, teníamos algunos token con espacios, por lo que decidimos corregir los mismos, logrando aun aceptar los mismos tests.

## Desarrollo del proyecto

### Frontend

La primer entrega consistió en la creación de la gramática y el uso de las herramientas Flex y Bison para que un texto de entrada pueda ser tokenizado y se pueda saber si pertenece o no al lenguaje generado por nuestra gramática.

Durante la entrega de la idea del proyecto y la entrega del frontend, se realizaron cambios de como se realiza una query, ya que la misma se veia confusa y disminua la usabilidad del proyecto.

Se demostró el mismo con trece tests, en los cuales vimos como se acepto y rechazo correctamente las gramáticas. Los mismos podrán ser encontrados  en la carpeta ‘test’ para poder probar el lenguaje creado.v

La cadena de pasos seguida por el Frontend fue:

- El analizador léxico (Flex) tokeniza la cadena de entrada
- El analizador sintáctico (Bison) se fija que la cadena de entrada tokenizada pertenezca al lenguaje
- Si Flex y Bison no devuelven error, se delega la creación del código HTML y Javascript al backend

Los test se pueden correr de la siguiente manera:

```powershell
Linux:
./script/test.sh
```

```bash
Windows:
./script/test.bat
```

### Backend

Para la segunda entrega se decidió utilizar distintos generadores de código por cada tipo de consulta, por lo cual se decidirá el uso del mismo en el generador principal.

En esta entrega, tuvimos que tambien realizar cambios de la entrega pasada, ya que encontrabamos ambigüedades en la gramatica, lo cual complicaba el recorrido del árbol, esto nos ayudo a poder avanzar en los generadores.

- Podemos preguntarnos por que tantos generadores, esta decisión se tomo por el formato de árbol que tomamos, como cada consulta tiene mas de una producción seria muy util poder recorrer de forma recursiva al mismo, buscando las producciones correspondientes de cada consulta.
- Para la generacion del codigo a partir de cada tipo de consulta, los generadores especificos crean y editan su propia cadena de codigo, con sus propias alocaciones de memoria las cuales son concatenadas y liberadas por el generador principal del programa.

## Uso del programa

Para utilizar el programa de debe correr dependiendo el SO utilizado:

```bash
Linux:
./script/start.sh <program>
```

```bash
Windows:
.\script\start.bat <program>
```

Abrir el archivo .sql ubicado en la carpeta donde se corrió el programa.

## Dificultades encontradas:

En un primer lugar, surgieron dificultades a la hora de elegir una gramática para el trabajo practico, se tuvieron más de una idea en mente, por lo cual como grupo se tomó la decisión de elegir por voto de la mayoría.

A la hora de avanzar en el proyecto, tuvimos una dificultad a la hora de concatenar consultas, al inicio al proponer la idea lo vimos como algo bueno e importante a la hora de ayudar a gente que quizá no entienda como creas consultas. Pero desde el lado de frontend y backend fue mas difícil cumplir el requisito, de todas formas superamos el desafio cumpliendo el requerimiento.

Gracias a la implementacion de un arbol sintactico muy robusto, la escritura de codigo para los generadores de los distintos tipos de consulta fue mas simple. La decision de temprana de incluir ENUMS para las distintas variedades/tipos de cada nodo ahorro la necesidad de crear logica compleja en los generadores.

## Futuras extensiones

Algunas posibles extensiones que nos propusimos son las siguientes:

- Aceptar consultas con UNION e INNER JOIN en este proyecto lo descartamos por la complejidad que previmos del mismo, como no guardamos los datos de 2 tablas para unir, no seria posible realizarlo, una posible solución podría ser que concatenemos las consultas de CREATE con estas mismas.
- Aceptar consultas con Group By, como mencionamos anteriormente, descartamos la idea también por los tiempos que veiamos que tendríamos, quiza esta idea sea menos compleja que la mencionada anteriormente.

## Conclusión

Para finalizar, consideramos que fue un proyecto bastante interesante y no fue sencillo. Tuvimos modificaciones de la primer a segunda entrega para poder optimizar los casos de uso y la comprensión del lado del usuario.
El trabajo practico nos ayudo a entender con mas claridad los conceptos vistos en clase y como aplicarlos, lo cual fue muy útil para cerrar la materia.