# TSSOO-taller1

##### ignacio lopez - ignacio.lopezl@alumnos.uv.cl

###### Universidad de Valparaíso

---



## 1. Introducción

En el presente documento se detallara el desarrollo del taller 03 de la asignatura taller se sistemas operativos de la universidad de valparaiso, esta consta de realizar el diseño y la implementacion mediante OMP orientando al trabajo con hilos, y evaluar su efeciencia temporal comparado con paralelizacion manual y teniendo en cuenta el tiempo secuencial, esta actividad consta de dos modulos, el primer encargado de llenar un arreglo de numeros uint32_t dentro de un rango de numeros aleatorios, el segundo modulo es realiaz la suma de esos numeros dentro de arreglo, para eso fue necesario ciertos parametros de entradas como el largo del arreglo que al ejecutar el codigo se especifica como "-N", el numero de hilos "-t", la cota minima de random "-l", la cota maxima de random "-L" y finalmente la ayuda "-h", la forma de uso se detalla a continuacion, en este reporte tambien exisitira una comparacion con el taller 02 pero no se explicara el diseño, solo se hablara de los resultados.

```
./ sumArray -N numero -t  numero -l  numero -L  numero -h
```

## 2. Diseño
 
El diseño general en el cual se baso para general el codigo consta de ciertos paramemtros de entrada que se detallo en la introduccion mas un arreglo vacio, con estos parametros pasan a traves del modulo 1 dejando como salida al arreglo lleno de numeros randomicos que fueron llenados mediante hilos, este arreglo sirve de entrada para el segundo modulo, el cual hara la suma de los numeros randomicos de la misma manera que el primer modulo con hilos.

### 2.1 Modulo 1

 Como ya se detallo en el diseño general en este modulo se encarga de llenar un arreglo de numero randomicos mediante hilos, para eso se utilizo para eso se utilizo una funcion llenar en donde en esta se implementa OMP en dos caso, cuando es secuencial, y cuando es paralelo,  en esta funcion se llena el arreglo, al pasarle paramentros de tipo, cantidad de hilos, estos varian dependiendo de cuandos hilo se crean, y posteriormente se crean los hilos con la funcion.


### 2.2 Modulo 2
 
En este modulo se encarga de la suma paralela de los numeros randomicos llenados anteriormente, para eso se utilizo un funcion llamada suma donde en esta se implementa OMP, que del mismo modo se divide en dos casos, paralelo y secuencial. Y del mismo modo que se hizo en el modulo anterior se se trabajo con parameros tipo e hilos, esta suma se asigna a un variable global y asi se obtener la suma total

## 3. Conclusiones 
Una vez habiendo terminado, la ejecucion del codigo y haber obtenido resultados,se puede observar que al comparar las lass implementaciones manual y OMP se observa que la implementacion OMP es mas eficiente en los dos casos, pero con mas diferencia se observa en la suma paralela, ademas se concluye de igual forma que en el reporte 02 para los dos casos de implementacion, en referencia a que se puede observar que efectivamente mejora el rendimiento temporal al aplicar paralelismo mediante hilos, pero esto solo se puede aplicar hasta cierto punto por limitaciones de hardware, dado que un core permite una cierta cantidad de hilos, por lo cual limita la mejora, tambien se puede destacar que la paralelizacion depende de la complejidad de lo que se requiera hacer, eso se puede aborado de dos puntos de vista, la primera es que el codigo esta tan sencillo que no mejorar su rendimiento al hacer una paralelizacion mediante hilos, y la segunda es que le codigo sea tan complejo que es dificil encontrar una paralelizacion, pero a diferencia que la primera es factible y mejorar el tiempo, estos son los puntos mas importantes tratos en este taller.
