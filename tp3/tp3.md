# 4.

### a.

Salida:

```
#######
********
```

Solución:

```c
if (x < 10)
  if (y > 10)
    printf("#######\n");
  else
    // Obs: este printf es inválido, queda un % suelto
    printf("%%%%%\n");
printf("********\n");

```

### b.

Salida:

```
########
```

Solución:

```c
if (x < 10) {
  if (y > 10)
    printf("########\n");
} else {
  printf("%%%%%\n");
  printf("********\n");
}

```

### c.

```c
if (x < 3) {
  printf("x < 3");
  if (z < 5)
    printf("x < 3 y z < 5");
} else {
  printf("x >= 3");
}

```

### d.

```c
if (x == 1) {
  if (z > 1)
    printf("x == 1 y z > 1");
} else if (x > 1) {
  printf("x > 1");
} else {
  printf("x < 1");
}
```

# 6.

### a.

```c
int a = 0;
while (a <= 4)
  resultado += a;
  a++;
```

Problema: nunca se ejecuta `a++` dentro del `while`.  
Solución:

```c
int a = 0;
while (a <= 4) {
  resultado += a;
  a++;
}
```

### b.

No compila, sobran comas y falta `;` en la segunda línea.

Solución:

```c
if (sueldo >= 1000)
  printf ( "El sueldo es mayor o igual a 1.000\n");
else
  printf ("El sueldo es menor a 1.000\n");
```

### c.

El código funciona, pero `var2` no está inicializada y contiene basura, con lo cual da un resultado inesperado.

Solución:

```c
int var1 = 1, var2 = 0;
while (var1 <= 8) {
  var2 += var1;
  ++var1;
}
```

### d.

El `;` inmediatamente después del `while` hace que el cuerpo del ciclo esté vacío y `printf` sólo corre una vez al terminar.

Solución:

```c
while ('Y' != (c = getchar()))
  printf ("Pulse Y para abandonar este ciclo \n");
```

### e.

Al usar tipo `char` para `c`, o bien no puede representar `EOF` (si es unsigned), o bien un caracter de ASCII extendido (`0xff`) se toma incorrectamente como `EOF`. `c` debe ser de tipo `int`:

```c
int c;
while((c = getchar()) != EOF)
  putchar(c);
```

### f.

C no tiene capacidades de _reflection_ como algunos lenguajes de alto nivel para poder hacer print del nombre asignado al enum, con lo cual se debe hacer manualmente.

Solución 1 (muy verbose):

```c
int main(void) {
  enum dias dia = LUN;
  switch (dia) {
    case LUN:
      printf("Hoy es lunes\n"); break;
    case MAR:
      printf("Hoy es martes\n"); break;
    //...
    case DOM:
      printf("Hoy es domingo\n"); break;
  }

  return 0;
}
```

Solución 2 (más concisa, pero usa cosas no vistas):

```c
enum dias { LUN = 0, MAR, MIE, JUE, VIE, SAB, DOM };
const char *dias_str[7] = {
  "lunes", "martes", "miércoles", "jueves",
  "viernes", "sábado", "domingo"
};

int main(void) {
  enum dias dia = LUN;
  printf("Hoy es %s\n", dias_str[dia]);

  return 0;
}
```

# 7.

Imprime la suma de todos los elementos de una lista de `n`, dividido por el último elemento de la lista.

# 8.

Ver `book/book_1.3.c`, `book/book_1.4.c`, `book/book_2.1.c`, `book/book_2.2.c`.

# 9.

Ver `book/book_1.8.c`, `book/book_1.11.c`, `book/book_1.12.c`.

# 10.

### a.

Hay dos errores: primero, `1/3` da como resultado `0` pues es división de enteros; segundo, se comparan floats con `!=`.

Solución:

```c
float x = 1.0 / 3.0;

while(x < 0.52)
  x += 0.01;
```

### b.

Al comparar floats con `!=` la suma de `0.1` diez veces no ez exactamente igual a `1.0`, la condición `y == 1.0` nunca se cumple y el loop sigue infinitamente.

Solución:

```c
for (y = 0.1; y <= 1.0; y += 0.1)
  printf("%f\n", y);
```

### c.

Falta un `break` luego del primer caso y el switch "cae" al caso 2.

### d.

Como `!=` tiene mayor precedencia que `=`, se hace primero la comparación y luego la asignación, de modo que se le asigna a `c` el resultado de `getchar() != EOF` (que siempre es 0 o 1).

Solución:

```c
int c, mayor = 0;

while ((c = getchar()) != EOF) {
  if (c > mayor)
    mayor = c;
}

printf ("El mayor es %c\n", mayor);
```
