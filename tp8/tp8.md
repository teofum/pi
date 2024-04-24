# 01.

### a.

Se pierde `p` al reasignarlo como `&c`, pero no es clara la intención del código.

### b.

Es innecesario el uso de `calloc`, se asignan los valores del struct de inmediato. Solución: usar `malloc`.  
Mejora de estilo: definir `art` con `typedef struct`.

### c/d.

Doble `free`. Solución: liberar una sola vez.  
Mejor solución: no mantener múltiples punteros a la misma dirección en un mismo scope, ya que es fácil causar estos
problemas.

### e.

Se pasa del vector, dereferencia `vec[dim]` en la última iteración.  
Solución:

```c
for (int i = 1; i < dim; i++) {
  if (vec[i - 1] == vec[i]) {
    ...
```

### f.

Retorna puntero a stack. Solución: usar `malloc` (ver b.).

### g.

`p` no está inicializado, causa UB al llamar `realloc`. Solución: `int *p = NULL;`.

# 02.

- a. Falso. Un `struct` puede contener miembros de cualquier tipo.
- b. Falso. Se debe comparar algún miembro de la unión, y deben tener el mismo tipo.
- c. Falso. No define un tipo nuevo, es un alias de un tipo existente.
- d. Verdadero. No se pueden comparar dos `structs`, por más que todos los miembros sean iguales, ya que el _padding_
  entre miembros contiene basura y puede ser distinto.  
  Para poder comparar structs hay dos posibilidades: o bien comparar miembro a miembro, o bien asegurarse al crear el
  struct (por ejemplo en una función `new_struct`) que el padding esté inicializado a un valor consistente (por ejemplo
  usando `calloc`).
- e. Verdadero. Como mínimo un `struct` necesita el espacio de sus miembros, a eso se le puede sumar padding.
- Falso. `typedef` no reserva memoria, define un type alias, no una variable.

# 03.

- a. Se dereferencia `cPtr` dos veces. Solución: `cPtr->figura` o `(*cPtr).figura`.
- b. Falta indexar el array: `corazones[10].figura`.
- c. ???
- d. Se debe declarar como `struct persona m` o bien usar `typedef struct` en la definición.
- e. El segundo es correcto, el primero pierde la referencia al vector original.
