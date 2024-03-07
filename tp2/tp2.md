# 01.

### a.

Ninguna variable termina con el mismo valor:
`letra` contiene basura, con lo cual no se puede determinar su valor y tampoco el valor final de `flag`.

### b.

En ambos casos `y = 5`.  
En el primer caso, `x = 5/3 ~ 1.666...7`. En el segundo caso, `x = 1` pues la división se hace en enteros antes del cast a float.

### c.

Idem b., pero en este caso la segunda vez la división se hace en float y luego es truncada a enteros por el tipo de `x`.

### d.

En ambos casos `y = 5.5` y `x = 1`. La división se hace en float y el resultado es truncado por el tipo de `x`.

### e.

En ambos casos `x = 25, y = 5`, pero en el primer caso `y` es entero y en el segundo float.

### f.

En ambos casos `x = 6, y = 5`:

- Se asigna `x = 5`, en un caso se promueve un `char` y en otro caso se trunca un float pero el resultado es el mismo.
- `y = x++` asigna el valor de `x` a `y` y _luego_ incrementa `x`.

### g.

Asumiendo arquitectura 32 bits, en ambos casos `i = j = 20000, k = 40000`.

En arquitectura 16 bits, el primer caso causa un overflow y `k = -25536`.

### h.

En ambos casos `a = b = 60, c = 120`.

### i.

En el segundo caso `a = b = 60, c = 120`. El primer caso depende de la arquitectura pues `char` no tiene default, puede ser `c = 120` o `c = -8`.

### j.

En el primer caso, `x = 45, y = 44`:

- `(char) 300` es truncado a `300 % 256 = 44` y se asigna a `x`
- `y = x++` asigna el valor a `y` y luego incrementa `x`

En el segundo caso, `x = 301, y = 300` pues la conversión float a int no pierde datos en este caso.

### k.

En ambos casos `x, y = 2, z = 4`:

- Caso 1: `(x = 2)` retorna `2`, y `(y = x)` también ya que los operandos de `+` se evalúan izquierda a derecha. Luego `z = 4`.
- Caso 2 es trivial.

# 02.

```c
#include <stdio.h>

int main() {
  printf("Este\nes\nun\nprograma\nen\nC\n");

  return 0;
}
```

Mejor:

```c
#include <stdio.h>

int main() {
  printf("Este\n"
         "es\n"
         "un\n"
         "programa\n"
         "en\n"
         "C\n");

  return 0;
}
```

# 03.

No. C no permite extender un string literal en dos líneas.

# 04.

Salida:

```
<vacío>
<vacío>
7
0.000000
2.122e-314
```

- La primera línea imprime el caracter `BEL` (`\a`), un caracter de control invisible, por eso se ve vacía.
- La segunda línea interpreta `7` como `char`, y imprime el caracter con ASCII `0x07` que también es `BEL`.
- La tercera línea interpreta `7` como entero y lo imprime correctamente.
- Las últimas dos líneas interpretan los bits de `7 = 0x00000007` como float IEEE 754, que resulta en un número subnormal muy cercano a cero, y lo imprimen en notación normal y científica respectivamente.

# 05.

Salida:

```
t
116
0.000000
```

- `%c` lo interpreta como caracter y imprime el caracter con ASCII `0x74`, `t`.
- `%d` lo interpreta como entero y imprime el ASCCI en decimal `116`.
- `%f` interpreta los bytes `'t' = 0x00000074` como IEEE 754, que resulta en un número subnormal muy cercano a cero.

# 06.

Salida:

```
num1=         53
num2= 0000000004
num1= 53
num1+num2=    57
num1+num2= 0.000000
num3= 6.87
num1= 53
num2= 4
num3= 6.9
num3(como entero)= -536870912
num1 / num2 = 13
num2 / num1 = 0
esta es la ultima prueba
```

# 07.

Ver `tp2_07.c`

Salida:

```
25
0000000025
185.65
      90
```
