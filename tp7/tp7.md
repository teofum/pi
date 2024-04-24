# 03.

No hace nada. `misterio1` sólo modifica los punteros (pasados por valor), no toca los strings.

# 04.

Imprime el largo de un string (es equivalente a llamar `strlen`).

# 10.

```
main
├─ play
│  ╰─ check_char
│     ╰─ draw_hangman
╰─ get_random_word
```

| Nombre          | Descripción                                                                                                                  | Parámetros                                 |                                                                                                          |
|-----------------|------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------|----------------------------------------------------------------------------------------------------------|
| main            | Elige una palabra aleatoria y simula un juego de ahorcado.                                                                   | ---                                        |                                                                                                          |
| get_random_word | Devuelve un puntero a una palabra aleatoria.                                                                                 | ---                                        |                                                                                                          |
| check_char      | Verifica si una letra está en la palabra. Modifica la palabra mostrada y devuelve 1 si se ganó el juego. Dibuja el ahorcado. | **secret**; **revealed**; **lives**; **c** | (char *, i) palabra secreta; (char *, i/o) palabra mostrada; (int, i/o) vidas restantes; (char, i) letra |
| draw_hangman    | Dibuja el ahorcado.                                                                                                          | **lives**                                  | (int, i) vidas restantes                                                                                 |

# 11.

### a.

Invisible; el array se mantiene igual y `1`, `2`, `3` no son caracteres gráficos.

### b.

```
HOLA MUNDO
HOLA MUNDO
```

### c.

```
LA MUNDO
HOLA MUNDO
```

### d.

```
HELLO WORLD
```

# 12.

### a.

Depende de la arquitectura: `sizeof(char *) * 6`. En 32 bits ocupa `4 * 6 = 24` bytes, en 64 bits ocupa `8 * 6 = 48`
bytes.

### b.

| Expresión          | Expresión equivalente | Valor |
|--------------------|-----------------------|-------|
| `***p`             | `p[0][0][0]`          | `'a'` |
| `**p[1]`           | `p[1][0][0]`          | `'j'` |
| `**(p[1] + 2)`     | `p[3][0][0]`          | ???   |
| `*(*(p+1)+1)[7]`   | `p[1][8][0]`          | ???   |
| `(*(*(p+1)+1))[7]` | `p[1][1][7]`          | `'w'` |
| `*(p[1][2]+2)`     | `p[1][4][0]`          | ???   |

# 13.

### a.

`numero` contiene basura, osea, apunta a una dirección de memoria potencialmente inválida, causando UB al
dereferenciarlo.  
Solución: no dereferenciar un puntero no inicializado.

### b.

No se puede hacer la asignación ya que los tipos `float *` y `long *` son incompatibles.  
Solución: usar un cast explícito `integerPtr = (long *) realPtr;`  
Nota: de todos modos esto es una mala idea, en una arquitectura actual de 32/64 bits `long` es un tipo de 8 bytes
y `float` de 4, con lo cual al dereferenciar el valor de `realPtr` como `long *` va a tomar 4 bytes de basura.

### c.

Los tipos `int *` y `int` no son compatibles.  
Solución: `x = &y;`.

### d.

No se puede incrementar `s`: no es un lvalue.  
Solución: declarar `s` como `char *s = "...";`

### e.

No se puede dereferenciar `void *`.  
Solución: usar `numPtr` directamente: `result = *numPtr + 7;`

### f.

`s` contiene basura, osea, apunta a una dirección de memoria potencialmente inválida, causando UB al dereferenciarlo (
implícitamente dentro de `printf`).  
Solución: no dereferenciar un puntero no inicializado.

### g.

Doble `free`: o bien `realloc` libera `s` al hacer la realocación, en cuyo caso `free(s)` es UB; o bien encuentra lugar
en `s`, en cuyo caso `s = aux` y `free(aux)` es UB.

Solución: usar el mismo pointer:

```c
char *s = malloc(20);
s = realloc(s, 100);
free(s);
```

# 14.

a. La dirección de memoria del comienzo del array.  
b. La dirección del tercer elemento del array.  
c. El valor del primer elemento del array.  
d. El valor del primer elemento del array, +2.  
e. El valor del tercer elemento del array.  
f. `0x1100` (`0x10F0 + 0x0004 * 4`)

# 18.

### a.

Devuelve un pointer a memoria inválida (un array en el stack que es liberado al salir de la función).

```c
char *to_upper(const char *s) {
  char *upper = malloc(strlen(s) + 1);
  int i;
  for (i = 0; s[i] != '\0'; i++)
    upper[i] = toupper(s[i]);
  
  upper[i] = '\0';
  return upper;
}
```

### b.

1. Devuelve `int`, debería devolver `int *`.
2. Declara `resp` como array (no es un lvalue!), debe ser `int *`.
3. Reserva `dim` bytes, cuando debe reservar lugar para `dim` enteros.
4. Itera en el intervalo `(0; dim]` en vez de `[0; dim)`.

```c
int *reverse_copy(int *v, int size) {
  int *rev = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    rev[size - i - 1] = v[i];
  }
  
  return rev;
}
```