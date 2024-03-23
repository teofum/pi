# 01.

```c
#define N 10
#define M 20

int main(void) {
  int dim = 7;
  int vectorA[M * N];
  int vectorB[-10]; // El tamaño debe ser > 0
  int vectorC[10.0]; // Tamaño debe ser un entero
  int vectorD[dim];
  vectorC[2.5] = 'a'; // Index debe ser un entero
  vectorB[-1] = 5;
  vectorA['0'] = 10;
  vectorC[vectorA[48]] = 5.5;
  vectorA[1000] = 0;
  vectorA[M * N] = 10;
  return 0;
}

```

# 30.

```c
typedef enum {MON=0, TUE, WEN, THU, FRI, SAT, SUN} TDay;
typedef TDay TVec[10];
typedef TVec TMat[5];

TMat m1;
int m2[10][5];
int m3[5][10];
```

a. Falso, `typedef enum {...} T;` es equivalente a `enum T {...};`  
b. Verdadero.  
c. Verdadero. `TVec` es equivalente a `TDay[10]`.  
d. Verdadero. `TMat` es equivalente a `TVec[5]`, que es equivalente a `TDay[10][5]`.  
e/f. Verdadero. `t[n][m]` es equivalente a `t[m*n]` en memoria, aunque son semánticamente diferentes.  
g. Falso. `TDay` es de tipo `int` y puede tomar cualquier valos asignable al mismo.  
h. Verdadero. Un `enum` es efectivamente documentación.  
i. Falso. Si se declara una variable de tipo `TVec` el compiler reserva `10 * sizeof(int)` bytes en memoria.

### Aclaración sobre e/f

Un array en memoria son lugares contiguos sin información de inicio o fin, por lo cual un array de arrays es equivalente a un único array. Por ejemplo:

```c
int flat[6] = {1, 2, 3, 4, 5, 6};         // 1, 2, 3, 4, 5, 6
int m1[3][2] = {{1, 2}, {3, 4}, {5, 6}};  // 1, 2, 3, 4, 5, 6
int m2[2][3] = {{1, 2, 3}, {4, 5, 6}};    // 1, 2, 3, 4, 5, 6
```

Observar cómo todos son equivalentes en memoria. La diferencia está en el acceso:

```c
flat[1]; // 2
m1[1]; // Equivalente a (m1 + sizeof(int[2]))
m1[1][0]; // 3
m2[1]; // Equivalente a (m1 + sizeof(int[3]))
m2[1][0]; // 4
```
