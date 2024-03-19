# 02.

### a.

Salida:

```
46 . .	no no no no no no no si
47 / /	no no no no no no no si
48 0 0	si no si no no si no no
49 1 1	si no si no no si no no
50 2 2	si no si no no si no no
51 3 3	si no si no no si no no
52 4 4	si no si no no si no no
53 5 5	si no si no no si no no
54 6 6	si no si no no si no no
55 7 7	si no si no no si no no
56 8 8	si no si no no si no no
57 9 9	si no si no no si no no
58 : :	no no no no no no no si
59 ; ;	no no no no no no no si
60 < <	no no no no no no no si
61 = =	no no no no no no no si
62 > >	no no no no no no no si
63 ? ?	no no no no no no no si
64 @ @	no no no no no no no si
65 A a	si si no no si si no no
66 B b	si si no no si si no no
67 C c	si si no no si si no no
68 D d	si si no no si si no no
69 E e	si si no no si si no no
70 F f	si si no no si si no no
71 G g	si si no no si no no no
72 H h	si si no no si no no no
```

### b.

Salida:

```
-1.000000  1.000000   -1.000000   -1.000000
1.000000  nan
-0.500000  0.500000   -0.000000   -1.000000
0.250000  nan
0.000000  0.000000   0.000000   0.000000
0.000000  0.000000
0.500000  0.500000   1.000000   0.000000
0.250000  0.707107
1.000000  1.000000   1.000000   1.000000
1.000000  1.000000
1.500000  1.500000   2.000000   1.000000
2.250000  1.224745
```

# 04.

```c
int rand_in_range(int min, int max) { return rand() % (max + 1 - min) + min; }
```

# 05.

```c
double power(double base, double exp) {
  if (base == 0) return 0;
  if (exp == 0) return 1;
  double res = 1;
  if (exp > 0) {
    for (int i = 0; i < exp; i++) res *= base;
  } else {
    for (int i = 0; i < -exp; i++) res /= base;
  }

  return res;
}
```
