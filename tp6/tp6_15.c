#include <assert.h>
#include <stdio.h>

#define HEIGHT 6
#define WIDTH 5

#define min(a, b) ((a) < (b)) ? (a) : (b)
#define max(a, b) ((a) < (b)) ? (b) : (a)

typedef unsigned int uint;
typedef unsigned char uchar;

void box_blur(const uchar img[HEIGHT][WIDTH], uint w, uchar out[HEIGHT][WIDTH]);
uchar blur_pixel(const uchar img[HEIGHT][WIDTH], int w, int x, int y);

int equals(uint cols, uchar m1[][cols], uchar m2[][cols], uint rows) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (m1[i][j] != m2[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

int main(void) {
  uchar bmp[HEIGHT][WIDTH] = {
      {10, 10, 20, 23, 24}, //
      {10, 12, 18, 25, 23}, //
      {12, 14, 18, 26, 22}, //
      {12, 14, 19, 20, 22}, //
      {13, 16, 19, 20, 22}, //
      {14, 14, 19, 21, 23}
  };
  uchar out[HEIGHT][WIDTH];

  uchar blurred[HEIGHT][WIDTH] = {
      {10, 13, 18, 22, 23}, //
      {11, 13, 18, 22, 23}, //
      {12, 14, 18, 21, 23}, //
      {13, 15, 18, 20, 22}, //
      {13, 15, 18, 20, 21}, //
      {14, 15, 18, 20, 21}
  };
  box_blur(bmp, 3, out);
  assert(equals(WIDTH, out, blurred, HEIGHT));
  puts("w = 3 OK!");

  uchar blurred5[HEIGHT][WIDTH] = {
      {14, 16, 17, 19, 20}, //
      {14, 16, 17, 18, 20}, //
      {14, 16, 17, 18, 20}, //
      {15, 16, 17, 18, 20}, //
      {15, 16, 17, 18, 20}, //
      {15, 16, 17, 18, 19}
  };
  box_blur(blurred, 5, out);
  assert(equals(WIDTH, out, blurred5, HEIGHT));
  puts("w = 5 OK!");

  return 0;
}

void box_blur(
    const uchar img[HEIGHT][WIDTH],
    uint w,
    uchar out[HEIGHT][WIDTH]
) {
  if (w < 3 || !(w % 2))
    return;

  for (int y = 0; y < HEIGHT; y++)
    for (int x = 0; x < WIDTH; x++)
      out[y][x] = blur_pixel(img, w, x, y);
}

uchar blur_pixel(const uchar img[HEIGHT][WIDTH], int w, int x, int y) {
  int xmin = max(0, x - w / 2);
  int xmax = min(WIDTH - 1, x + w / 2);
  int ymin = max(0, y - w / 2);
  int ymax = min(HEIGHT - 1, y + w / 2);

  uint value = 0;
  for (int yy = ymin; yy <= ymax; yy++)
    for (int xx = xmin; xx <= xmax; xx++)
      value += img[yy][xx];

  value /= ((xmax - xmin + 1) * (ymax - ymin + 1));
  return value;
}
