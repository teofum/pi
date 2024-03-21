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
