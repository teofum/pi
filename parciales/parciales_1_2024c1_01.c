#include <assert.h>
#include <limits.h>
#include <stdio.h>

// type aliases to keep things short
typedef unsigned char uchar;
typedef unsigned int uint;

void firstN(uchar v[], int dim, uint n, int *outDim, int *del);

int main(void) {
  unsigned char v[] = {1, 2, 1, 3, 1, 4, 5, 2};
  int dim, del;
  firstN(v, 8, 3, &dim, &del); // dim es 8, del es 0, v no cambia
  assert(dim == 8);
  assert(del == 0);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 1);
  assert(v[3] == 3);
  assert(v[4] == 1);
  assert(v[5] == 4);
  assert(v[6] == 5);
  assert(v[7] == 2);

  firstN(v, 8, 8, &dim, &del); // dim es 8, del es 0, v no cambia
  assert(dim == 8);
  assert(del == 0);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 1);
  assert(v[3] == 3);
  assert(v[4] == 1);
  assert(v[5] == 4);
  assert(v[6] == 5);
  assert(v[7] == 2);

  firstN(v, 8, 4, &dim, &del); // dim es 8, del es 0, v no cambia
  assert(dim == 8);
  assert(del == 0);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 1);
  assert(v[3] == 3);
  assert(v[4] == 1);
  assert(v[5] == 4);
  assert(v[6] == 5);
  assert(v[7] == 2);

  firstN(v, 8, 1, &dim, &del); // dim=5, del=3, v = {1, 2, 3, 4, 5};
  assert(dim == 5);
  assert(del == 3);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 3);
  assert(v[3] == 4);
  assert(v[4] == 5);

  unsigned char w[] = {1, 2, 1, 3, 1, 4, 5, 2};
  firstN(w, 8, 0, &dim, &del); // dim=0, del=8, w = {}
  assert(dim == 0);
  assert(del == 8);

  unsigned char t[] = {1, 2, 1, 3, 1, 4, 5, 2};
  firstN(t, 8, 2, &dim, &del); // dim=7, del=1, t = {1, 2, 1, 3, 4, 5, 2}
  assert(dim == 7);
  assert(del == 1);
  assert(t[0] == 1);
  assert(t[1] == 2);
  assert(t[2] == 1);
  assert(t[3] == 3);
  assert(t[4] == 4);
  assert(t[5] == 5);
  assert(t[6] == 2);

  puts("OK!");

  return 0;
}

void firstN(uchar v[], int dim, uint n, int *outDim, int *del) {
  // amount of each char found, indexed by character
  uint amount[UCHAR_MAX + 1] = {0}; // initialize to 0
  int j = 0;
  *del = 0;

  for (int i = 0; i < dim; i++) {
    if (amount[v[i]] >= n) {
      (*del)++; // if there were at least n of this char before skip it
    } else {
      amount[v[i]]++; // count
      v[j++] = v[i];  // and copy
    }
  }

  *outDim = j;
}
