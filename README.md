# Punteros inteligentes a partir de **C++11**

## Sobre esta pequeña tarea

El objetivo de esta pequeña tarea es proporcionar algunos elementos sobre los llamados punteros inteligentes provistos por el lenguaje de programación ***C++11***, específicamente ***unique_ptr*** y ***shared_ptr***. También brindaremos una posible implementación a los punteros antes mencionado.

## Sobre los punteros inteligentes

Son punteros pero con funcionalidades que evitan las desventajas y errores al usar raw pointers. Están diseñados para ayudar a manejar la vida de los objetos dinámicamente asignados, evitando de esta manera un "memory leak", asegurando que estos objetos sean destruidos en el momento apropiado, incluso durante la ocurrencia de excepciones. Estos son ***unique_ptr***, ***shared_ptr*** y ***weak_ptr***.

## Sobre unique_ptr

1. Envuelve lo que se conoce como semántica de posesión exclusiva, lo que significa que un ***unique_ptr*** non-null siempre posee lo que apunta.
2. Luego de su destrucción, destruye el objeto al que apunta. Por defecto, esto lo hace haciendo delete al raw pointer que contiene. Puede definir destructores personalizados.
3. Es un "move-only type", lo que significa que no se puede copiar. Si se copiara, se estaría violando el concepto de que es el único propietario del objeto al que apunta.
4. Se usa comúnmente como tipo de retorno de una función cuando se desea retornar una referencia.
5. Su tamaño en memoria es pequeño, siempre y cuando no se definan destructores personalizados, ya que en estos casos dependería del tamaño de los destructores.
6. Es eficiente y tiene los mismos operadores que un raw pointer.
7. Se puede convertir a ***shared_ptr*** en caso de que se quiera compartir la "posesión" del objeto al que se apunta.
8. Se puede usar como puntero array, pero no es recomendable, ya que de esta forma no tiene los operadores *, -> y [].

## Sobre shared_ptr

1. Se usa para compartir la posesión sobre un objeto.
2. Usa el recurso conteo por referencias (RC por sus siglas en inglés), al cual se accede con el campo use_count() que permite saber cuántos ***shared_ptr*** apuntan al mismo objeto.
3. El conteo por referencias está en un espacio de memoria (control block) reservado por el primer ***shared_ptr*** que se creó a partir de un objeto. Este espacio está dedicado a tal recurso, pero solo puede ser accedido por los ***shared_ptr*** que comparten la posesión de este objeto.
4. Al ser destruido, disminuye en uno la cantidad de referencias, y solo destruye el objeto si este valor es igual a cero.
5. Si se copia a partir de otro non_null ***shared_ptr*** aumenta su contador por referencias en uno. Lo anterior no es tan eficiente como se espera, lo cual es un factor a tener en cuenta a la hora de decidir el puntero a usar.
6. Sin embargo, si se mueve, mantiene intacto la cantidad de referencias. Lo anterior se logra de manera eficiente.
7. Internamente tiene dos punteros: uno al recurso y otro al espacio de memoria (control block), por lo que su tamaño es típicamente el doble del de un raw pointer.
8. Puede definir un destructor personalizado, el cual se ubica en el espacio de memoria (control block).
9. Tiene los mismos operadores que un raw pointer.
10. No se puede usar como un puntero array, solo está diseñado para usarlo como puntero simple.
11. No se puede crear un ***unique_ptr*** a partir de un ***shared_ptr*** ya que no se puede determinar la pertenencia sobre un objeto como única.

## Sobre la implementación

La implementación se encuentra totalmente en ***C++11***. Es recomendable tener conocimientos intermedios de este lenguaje de programación para un mejor entendimiento de las implementaciones propuestas.

## Sobre la ejecución

En el archivo [`run.sh`](Codigo/run.sh) proveemos una manera fácil, sencilla y rápida para correr nuestras implementaciones.

Para la ejecución, escriba las siguientes líneas en una terminal abierta en este directorio:

```bash
$ cd Codigo
$ ./run.sh <file_name>.cpp
```

## Sobre los autores

**Nombre** | **Correo** | **GitHub**
--|--|--
Ariel Plasencia Díaz | arielplasencia00@gmail.com | [@ArielXL](https://github.com/ArielXL)
Adriana Plasencia Díaz | adricivilpd@gmail.com | [@adria](https://github.com/fcadrianapladia)
