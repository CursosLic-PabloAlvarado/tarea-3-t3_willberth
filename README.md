[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=16114992&assignment_repo_type=AssignmentRepo)

# Benchmarking 

Aparte del ejecutable principal de la tarea, se generó un ejecutable *bench*, que utiliza *Google Benchmark* para medir los tiempos de cálculo del process implementado en cada una de sus respectivas clases.

# Utilización de SIMD

La implementación de las clases ``` parallel_simd_df2 ``` y ``` parallel_simd_tdf2 ``` en los archivos con su respectivo nombre, implementan paralelización del cálculo de ``` process ``` utilizando SIMD, en el código final únicamente se utiliza la implementación de ``` parallel_simd_df2 ``` debido a que era más rápida. En ejecución se puede presionar la tecla "*s*" para realizar el cálculo con este método.

Para generar el filtro para ser calculado con ``` AVX2 ```, se obtuvo la matriz de polos, ceros y ganancia, obteniendo la matriz de SOS de la misma manera. Una vez obtenidos los coeficientes del filtro completo, se calculó su expansión en fracciones parciales con *Wolfram Alpha*.

**NOTA IMPORTANTE!**: El filtro ***hard-coded*** en ``` parallel_simd_df2 ``` es un filtro butterworth paso banda, ya que el proceso para obtener los coeficientes de la expansión de fracciones parciales fue hecho a mano y es necesario para los otros filtros, esto quiere decir q esta clase únicamente permite ``` process ``` con este filtro y no funcionará con los otros, debido a falta de tiempo para implementación. El ``` process ``` de la clase ``` cascade ``` sí permite utilizar cualquier filtro de los generados en el archivo ``` .mat ```, como se solicitó en el enunciado de la tarea.


# Ejemplo base de Jack en C++

Esta versión permite recibir una lista de archivos .wav, que se ejecutan
uno tras otro, reemplazando la entrada de micrófono en tanto hayan datos
de los archivos disponibles.  Una vez que todos los archivos terminan de
ejecutarse, regresa al modo "pass-through".

## Dependencias

Requiere C++ en su estándar del 2020 (g++ 12, clang 14).

En derivados de debian (ubuntu, etc):

     sudo apt install jackd2 libjack-jackd2-dev qjackctl build-essential meson ninja-build jack-tools libsndfile1-dev libsndfile1 libboost-all-dev 
     
Jack requiere que su usuario pertenezca al grupo audio, o de otro modo
no tendrá privilegios para el procesamiento demandante en tiempo
real...

     sudo usermod -aG audio <su usuario>

## Construcción

Para construir los ejemplos la primera vez utilice

     meson setup builddir
     cd builddir
     ninja


Si requiere reconstruir todo, utilice

     meson setup --wipe builddir
     cd builddir
     ninja

o si solo requiere reconfigurar por haber agregado otro archivo:

    meson --reconfigure builddir

## Latencia y tamaño de bloque

Para reducir la latencia por medio del tamaño del "periodo" (esto es,
el número de "frames" que cada ciclo de procesamiento recibe, en
QjackCtl, en Settings, se indica en Frames/Period.  Eso es un
parámetro del servidor de Jack y no lo puede controlar la aplicación
como tal.
