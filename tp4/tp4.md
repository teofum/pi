# 1.

### a.

`a = 1`, `b = 3`. `PI` se trunca pues `b` es un `int`, y `a++` es postincremento con lo cual se suma `0`.

### b.

No compila, no se puede incrementar un literal (es un **rvalue**, el operador `++` espera un **lvalue**).

Si se reemplaza la línea por `b = a + PI + 1` queda `b = 4.14`.

### c.

- `b = 13`, pues expande a `b = a+1 * a+1 * a+1` y como `*` tiene mayor precedencia que `+`, la cuenta que se hace es `b = a + (1 * a) + (1 * a) + 1`.
- `c = 125`.

### d.

- `b = 4 * 5 * 6 = 120` (los `++a` se pueden ejecutar en cualquier orden, pero al ser una multiplicación es equivalente).
- `c = 6 * 7 * 8 = 336` (idem anterior, pero es postincremento).
- `d = 6`.
- `e = 4 * 5 * 6 = 120` (idem `b`).
- `f = 3 * 4 * 5 = 60`.

### e.

No compila: el parámetro `z` de `DIVISION` debe ser un **lvalue** pues se le asigna un valor. Si reemplazamos `DIVISION(x, y, 0)` por `DIVISION(x, y, z)`:

- `a = 20`.
- `b = 5`.
- `c = 4`.
- `m = 6`.
- `n = 2` (se decrementa dos veces, pues `y` aparece dos veces en el loop de `DIVISION` y se ejecuta una vez).
- `p = 1`.
- `x = 15`.
- `y = 3`.
- `z = 5`.

# 2.

- En c, la versión correcta de la macro `CUBO` es la de d.
- En e, la macro `DIVISION` está curseadísima y no hay arreglo que valga.

# 4.

Ver `book/book_4.14.c`.

# 5.

```c
#define MAX2(x, y, out) (out = ((x) > (y)) ? (x) : (y))
```

Obesrvación: este estilo de macros con un parámetro de salida en general son muy mala forma a menos que sea evidentemente obvio lo que hacen. En este caso, sería mejor que la macro simplemente retorne el máximo y hacer la asignación por afuera:

```c
#define MAX2_BETTER(x, y) (((x) > (y)) ? (x) : (y))

int max = MAX2_BETTER(x, y);
```

# 6.

```c
#define MAX3(x, y, z, out) MAX2(x, y, out); MAX2(out, z, out)
```

Es equivalente a:

```c
int max = MAX2_BETTER(x, y);
int max = MAX2_BETTER(max, z);
```

Observación: con la mejor versión de la macro anterior de puede hacer una mejor versión de esta también:

```c
#define MAX3_BETTER(x, y, z) MAX2_BETTER(MAX2_BETTER(x, y), z)
```

# 7.

```c
#define isdigit(c) (c >= '0' && c <= '9')
```

# 8.

### a.

C no permite definir funciones dentro de otras funciones.

Solución:

```c
void f1(void) {
  printf("Dentro de la función f1\n");
}

void f2(void) {
  printf("Dentro de f2\n");
}
```

### b.

La función no devuelve nada.

Solución: agregar un `return`:

```c
int suma(int x, int y) {
  int respuesta;
  respuesta = x + y;
  return respuesta;
}
```

Mejor:

```c
int suma(int x, int y) {
  return x + y;
}
```

### c.

No todos los caminos tienen un `return`.

Solución: agregar un `return` al `else`.

```c
int suma(int n) {
  if (n <= 0)
    return 0;
  else
    return n + 1;
}
```

Observación 1: el `else` es redundante; como la rama del `if` sale de la función, la ejecución sólo continúa si no se toma ese branch. Entonces, se puede escribir de modo equivalente

```c
int suma(int n) {
  if (n <= 0)
    return 0;

  return n + 1;
}
```

Observación 2: este patrón se llama _early return_ y tiene gran utilidad, pero es considerado muy mala práctica no tener un return "default" al final de la función, ya que hace más fácil introducir bugs.

El uso más común de _early return_ es tener un camino normal o "feliz" para la función que llega hasta el return final, y usar early return si ocurre un error que impide seguir la ejecución, o llegamos a un resultado que hace redundante el resto de la función.

Por ejemplo, consideremos una función que encuentra las raíces de una cuadrática:

```c
// Returns the number of roots (0, 1 or 2)
// Stores roots in r1 and r2 if there are any
// If there is only one root it will be stored in both r1 and r2
int quadratic_roots(
  double a, double b, double c,
  double *r1, double *r2
) {
  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return 0;
  }

  double sqrt_discriminant = sqrt(discriminant);
  *r1 = (-b - sqrt_discriminant) / 2.0;
  *r2 = (-b + sqrt_discriminant) / 2.0;

  return (*r1 == *r2) ? 1 : 2;
}
```

Podemos ver que si el discriminante es igual a 0, podemos devolver 0 directamente y ahorrarnos el resto de las cuentas, ya que la ecuación no tiene raíces.

### d.

`a` contiene basura. Solución: inicializar la variable. Buena práctica: _siempre_ inicializar las variables en la misma declaración (excepción: variables que sólo se asignan dentro de un loop/condicional).

### e.

El tercer `putchar` está recibiendo `"\n"`, que es de tipo `const char*`.

Solución: cambiar la línea por `putchar('\n')`.

# 9.

Problema: al testear hora y minutos por separado, no considera el caso que la hora sea menor y el minuto mayor. Por ejemplo:

```c

#define ENT_HORA 8
#define ENT_MINUTOS 30

// ...

int a = llegaTemprano(7, 55); // Devuelve 0, pues 55 > 30

```

Solución:

```c
int llegaTemprano(const int hora, const int minutos) {
  return (hora < ENT_HORA || (hora == ENT_HORA && minutos <= ENT_MINUTOS));
}
```
