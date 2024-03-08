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

# 11.

Ver `tp2_11.c`

Salida:

```
❯ ./out/tp2_11 < tp2/tp2_11_in_1.txt
B

❯ ./out/tp2_11 < tp2/tp2_11_in_2.txt
A

❯ ./out/tp2_11 < tp2/tp2_11_in_3.txt
A
```

El programa sólo compara los primeros dos caracteres, entonces en el primer caso ignora `CD`, en el segundo y tercero ignora `B` y compara `A` con `\n` y `\t` respectivamente, ambos son < `A`.

# 17.

```c
int main(void) {
  printf("%x\n", "3" + "4");  // No compila
  printf("%x\n", '3' + '4');  // 'g' = 0x67 ('3' = 0x33 + '4' = 0x34)
  printf("%x\n", 3 + 4);      // 7
  printf("%x\n", '3' + 4);    // '7' = 0x37 ('3' = 0x33 + 4)
  printf("%x\n", 3 + '4');    // '7' = 0x37 ('4' = 0x34 + 3)
  printf("%x\n", "3" + '4');  // 0xXXXXXXXX (*)
  printf("%x\n", "3" + 4);    // 0xXXXXXXXX (*)

  return 0;
}
```

Qué ocurre en los últimos dos casos? Estamos sumando un número (`'4' = 0x34` o `4 = 0x04`) a un dato de tipo `char*` (puntero a un `char`, que es como C representa un string).

Este `char*` contiene una dirección de memoria donde comienza el string `"3"`, que es distinta en cada ejecución. Por lo tanto, vemos un valor aleatorio.

Una observación interesante: a pesar de que `"3"` está definido dos veces, gcc es lo suficientemente "inteligente" para darse cuenta que es la misma constante, y ubicarla en un único lugar en el ejecutable. Esto causa que la dirección de memoria sea la misma, como se ve en esta salida particular:

```
f67fdc
f67fac
```

En este caso tenemos:

```c
"3" + '4' = "3" + 0x34 = 0x00f67fdc
"3" +  4  = "3" + 0x04 = 0x00f67fac
```

Observemos que `'4' = 0x34 = 4 + 0x30`, y efectivamente,

```c
0x00f67fdc = 0x00f67fac + 0x30
```

Luego, podemos calcular el lugar donde cayó `"3"`:

```c
"3" = 0x00f67fac - 0x04 = 0x00f67fa8
```

# 18.

### a.

Falso. Sólo comienza en una línea nueva si ponemos `\n` al principio.

### b.

Verdadero. Usar `%` con floats no compila.

### c.

Verdadero, aunque hay lugares donde una variable no hace nada (por ejemplo, después del `return`).

### d.

Falso. Un `printf` puede contener varios `\n` dentro.

# 19.

```c
int c1 = getchar();
int c2 = getchar();
c1 > c2 ? printf("%c es mayor\n", c1) : printf("%c es mayor\n", c2);
```

En esta versión, el segundo `printf` es redundante. La línea queda demasiado larga y es difícil de leer.

Esta versión sería apropiada si los mensajes fuesen distintos, pero incluso en ese caso es preferible usar un `if` para mejorar la legibilidad (en general, es mejor evitar el operador condicional excepto en casos muy breves).

```c
int c1, c2;
printf("%c es mayor", (c1 = getchar()) > (c2 = getchar()) ? c1 : c2);
```

Esta versión es demasiado compacta y difícil de leer.

```c
int c1 = getchar();
int c2 = getchar();
printf("%c es mayor\n", c1 > c2 ? c1 : c2);
```

Esta es la mejor versión, alcanza un buen punto medio entre concisa y legible.

# 21

### a/b.

```
c=2147483647   d=-2   e=-2147483648
```

### c.

Se producen errores en runtime, el sanitizer indica que `int` no puede representar los valores de `d` y `e`.

# 22

`EOF` tiene valor `-1`. El tipo `char` no tiene default, y depende de la arquitectura y SO si es signed o unsigned.

Si es unsigned, `c` nunca va a tener un valor negativo y el programa funciona correctamente.

Si es signed, `getchar()` puede leer `255 = -1` y asumir que es `EOF`, terminando antes de tiempo.
