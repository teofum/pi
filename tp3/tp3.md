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

Ver `book/book_1.3.c`, `book/book_1.4.c`.

# 9.

Ver `book/book_1.8.c`, `book/book_1.12.c`.

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

# 17.

Eventualmente va a hacer overflow, hay infinitos múltiplos de 10.

# 22.

Ver `book/book_1.9.c`, `book/book_1.10.c`.

# 23.

```c
int n,c;

/* al salir del ciclo n debe ser un número par mayor que cero */
do
  n = getint("");
while(n <= 0 || n % 2);

/* este ciclo debe incluir la lectura de caracteres y debe ejecutarse
 * mientras no sea fin de archivo y los caracteres sean  dígitos o minúsculas
 */
while ((c = getchar()) != EOF && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')))
  putchar(c);
```

# 24.

No son iguales. El literal `0.1` es de tipo `double`, pero la variable `a` es de tipo `float`. Como `0.1` no tiene representación exacta, difiere entre `float` y `double`.  
Al hacer la comparación, se promueve `a` a `double`, pero su valor queda distinto al de `0.1`.

Hay dos formas de que la comparación de igual:

1. Cambiar el tipo de `a` por `double`
2. Cambiar el literal double `0.1` por la versión float `0.1f`

De todos modos, es una demostración de por qué nunca hay que usar `==` para igualar floats y las comparaciones siempre se deberían hacer con un epsilon (e.g. `a - 1.0 < 1e-12`).

# 26.

### a.

```c
int a = getint("Ingrese un número entero:");
if (a > 0)
  printf("Es mayor que cero\n");
if (a < 0)
  printf("Es menor que cero\n");
if (a == 0)
  printf("Es igual a cero\n");
```

Problema: el código es repetitivo (repite el mensaje) y verbose.

Solución:

```c
int a = getint("Ingrese un número entero: ");
printf("Es %s que cero\n", a == 0 ? "igual" : (a < 0 ? "menor" : "mayor"));
```

### b.

```c
int a = ( b > 0 ) ? 0 : 1;
```

Problema: el operador condicional es redundante.

Solución:

```c
int a = b <= 0;
```

### c.

```c
int a = 0;
while (1) {
  f(a);   // f es una función
  a = a + 1;
  if (a >= 10)
    break;
}

```

Problema: el operador condicional es redundante.

Solución:

```c
int a = 0;
while (a < 10) {
   f(a);
   a += 1;
}
```

### d.

```c
if (b > 0)
  a = 1;
else
  a = 0;
```

Problema: es b. pero peor

Solución:

```c
int a = b > 0;
```

### e.

```c
if (a > 0)
  if (b < 0)
    c = 10;
  else
    c = 20;
else
  c = 20;
```

Problema: hay condiciones anidadas sólo para hacer un and, y el `20` se debe especificar dos veces.

Solución:

```c
int c = (a > 0 && b < 0) ? 10 : 20;
```

### f.

```c
int i = 0;
int a = 10;
for ( ; i < 10; ) {
  a += getint("");
  i += 1;
}
printf("El valor de a es %d\n", a);
```

Problema: declarar y modificar la variable iteradora fuera de la línea del `for` es mala forma.

Solución:

```c
int a = 10;
for (int i = 0; i < 10; i++) {
  a += getint("");
}
printf("El valor de a es %d\n", a);
```

### g.

```c
int suma;
for (int i = 0; i < 100; i++) {
  if (i == 0)
    suma = getint("Ingrese la base: ");
  else
    suma += i;
}
printf("La suma es %d\n", a);
```

Problema: manejar el primer caso con una condición dentro del loop es poco claro.

Solución:

```c
int suma = getint("Ingrese la base: ");
for (int i = 1; i <= 99; i++) {
  suma += i;
}
printf("La suma es %d\n", a);
```

### h.

```c
cant = 0;
for (int i = 0; i < dim; i++) {
  if (i >= 1) {
    if(last != v[i]) {
	    last = v[i];
	    cant++;
    }
  } else {
    last = v[i];
	  cant++;
  }
}
```

Problema: idem anterior, pero peor.

Solución:

```c
last = v[i];
cant = 1;
for (int i = 0; i < dim; i++) {
  if(last != v[i]) {
	  last = v[i];
	  cant++;
  }
}
```
