# Trabajo Práctico 2
### Taller de Programación I (75.42)

#### Martinez Sastre, Gonzalo Gabriel - 102321

Link al repositorio de Github: https://github.com/gonzalomartinezs/tp2-taller

## Introducción
El objetivo del presente trabajo consiste en realizar un verificador de programas eBPF, el cual es capaz de reconocer si dentro del mismo existen posibles loops infinitos o instrucciones sin utilizar.

La característica principal de este programa reside en la inclusión de multhreading, es posible ejecutar la verificación de cada archivo eBPF en paralelo por medio de distintos hilos.

## Desarrollo del programa
Para la realización de esta actividad se decidió dividir el desarrollo de la misma en bloques. Por este motivo, en un principio se procedió a codificar un grafo con sus respectivos vértices y, una vez finalizado esto, se puso a prueba el correcto funcionamiento del mismo.

El siguiente paso fue armar una clase capaz de parsear correctamente las instrucciones de un programa eBPF y adaptarlas al formato de un grafo. Análogamente al caso anterior, se corroboró el funcionamiento de las mismas mediante sus respectivos tests.

A continuación, se codificaron las clases involucradas en el multithreading (`Thread`, `Lock`, `DetectAnomalies`, `ProtectedFiles` y `ProtectedResults`). Tras esto, se procedió a juntar todo lo implementado hasta el momento de manera que se cumpliera la consigna y se corroboró que se pudiera ejecutar el programa en varios hilos. Además. luego se creó la clase `eBPFVerifier` con el fin de englobar toda la lógica del programa.

Finalmente,  una vez terminado todo lo anterior, se inició el proceso de debugging y refactorización, el cual se vió intercalado con entregas en el SERCOM. 

## Compilación y ejecución
Para compilar el programa simplemente se debe correr el comando:

```
make
```
Luego, se ejecutará el programa de la siguiente manera:
```
./tp <cantidad de hilos> <archivo> [<archivo>...]
```

## Sobre el programa

### Estructura

Se puede decir que este programa se divide en dos bloques que resultan interesantes de analizar. Por un lado, se encuentra la interacción entre `DetectAnomalies`, la clase hija de `Thread`, y los monitores `ProtectedFiles` y `ProtectedResults`. Por el otro, la relación entre las clases `eBPFAnalyzer`, `Graph` y `GraphWalker`, utilzadas para parsear los archivos y detectar anomalías tales como ciclos o instrucciones sin utilizar.

A continuación se muestra un diagrama que resume este primer bloque.

![alt text][clases_threads]

Como aspecto destacable, se puede observar que `eBPFVerifier` contiene una instancia de `ProtectedFiles`, una de `ProtectedResults` y una lista de `DetectAnomalies`, de la cual todas sus instancias contienen una referencia a las mismas intancias de ambos monitores.

Por su parte, el parseo y análisis de los archivos eBPF es llevado a cabo mediante la siguiente relación de clases.

![alt text][clases_parsing]

### Flujo de ejecución

El aspecto principal de este programa reside en la posibilidad de utilizar varios hilos para ejecutar la verificación de los archivos eBPF. Es por ellos que los diagramas de esta sección esquematizan el flujo del programa en dichas situaciones.

![alt text][sec_threads]

Por un lado, este diagrama resume a grandes rasgos lo que ocurre cuando se realiza la llamada al método `run()` de `eBPFVerifier`. En primer lugar, cuando dicha clase llama al método `start()` de `DetectAnomalies`, este se pasa a la clase madre `Thread` en donde sí se encuentra implementado. Lo que sucede aquí es que le envía al hilo (`std::thread`) como parámetro el método `run()` de su clase hija.  Cabe destacar que la condición de corte dentro del loop de dicho método es el `getFile()` de `ProtectedFiles`, pero por limitaciones del software dicha llamada fue puesta dentro de este loop.

Una vez que se obtiene el archivo a leer, este es enviado a `eBPFAnalyzer` para que se proceda a realizar el parseo y adaptación al formato de grafo del mismo. Al finalizar dicha acción, se prosigue a detectar anomalías y, en función al resultado arrojado por `detectAnomalies()`, se envía el mensaje correspondiente a `ProtectedResults`.  
  
![alt text][sec_lock]

Aquí se puede observar una ampliación de lo que ocurre cuando el mensaje *"GOOD"* es enviado a una instancia de `ProtectedFiles`.  

![alt text][sec_parsing]

Por otra parte, este diagrama resume el proceso de parsing de un programa eBPF. Cabe destacar que el accionar del método assignReference consiste en agregar a una lista de referencias uno o dos pares (dependiendo de la operación) de `{instruccion_origen, instruccion_destino}` los cuales resumen el flujo del programa eBPF (qué instrucción se ejecuta luego de cada una).

![alt text][sec_detecting]

Finalmente, este esquema muestra la realización del proceso de detección de anomalías en el caso en que el recorrido DFS visitó una cantidad de vértices igual al número de vértices en el grafo, es decir, que no existen ciclos ni instrucciones sin utilizar.

### Detalles de implementación
En esta sección se indican algunas suposiciones realizadas y decisiones tomadas a la hora de desarrollar el programa.

- Siempre que se definió un destructor no vacío, se respetò la *"Regla de los tres"* (*Rule of three*), definiendo así el constructor por copia y el operador asignación.

- Se consideró que en los archivos eBPF no hay etiquetas repetidas (aclarado, asimismo, en la consigna del trabajo).

- El método `cycleDetectDFS()` de la clase `GraphWalker` recibe una lista de vértices y no un grafo puesto que ello significaría crear un método `getVertices()` en el grafo, lo cual se consideró que no era una buena idea puesto que dicha primitiva dejaba expuesto al grafo a ser modificado internamente.

- En un momento la clase 'ProtectedFiles' contaba con un método llamado `isEmpty()`, el cual retornaba un booleano indicando si el container de dicha clase se encontraba vacío o no. Con este, la implementación de `DetectAnomalies::run()` quedaba de la siguiente manera:

```c++
void DetectAnomalies::run() {    
    while (!(this->files.isEmpty())){
        std::string file = this->files.getFile();
        ...
    }
}
```
Sin embargo, luego se descubrió que esto era un gran problema, debido a que si bien cada método contaba con su propio `lock`, podrían darse situaciones como la siguiente: Si el container de `ProtectedFiles` contiene un único elemento puede ocurrir que para un hilo `isEmpty()` retorne `false` y, en el lapso que este ejecuta la siguiente instrucción, dicho método también retorne `false` para otro hilo. De tal manera, se tendría dos hilos realizando un `getFile` de un container con un único elemento. 

## Conclusión

Este trabajo resultó de gran ayuda para comprender el funcionamiento del multithreading en un programa. Las implementaciones realizadas permitieron comprender en buena medida cómo funciona este aspecto básico y fundamental para un ingeniero informático/licenciado.



[clases_threads]:https://github.com/gonzalomartinezs/tp2-taller/blob/master/img/clases_threads.png
[clases_parsing]:https://github.com/gonzalomartinezs/tp2-taller/blob/master/img/clases_parsing.png
[sec_threads]:https://github.com/gonzalomartinezs/tp2-taller/blob/master/img/sec_threads.png
[sec_lock]:https://github.com/gonzalomartinezs/tp2-taller/blob/master/img/sec_lock.png
[sec_parsing]:https://github.com/gonzalomartinezs/tp2-taller/blob/master/img/sec_parsing.png
[sec_detecting]:https://github.com/gonzalomartinezs/tp2-taller/blob/master/img/sec_detecting.png