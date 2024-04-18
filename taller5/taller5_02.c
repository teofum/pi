#define N 4
#define M 4

typedef unsigned char uchar;

void rgb_to_gray(const uchar color[N][M][3], uchar gray[N][M]);
uchar luma(const uchar color[3]);

void rgb_to_gray(const uchar color[N][M][3], uchar gray[N][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      gray[i][j] = luma(color[i][j]);
    }
  }
}

uchar luma(const uchar color[3]) {
  return 0.2989 * color[0] + 0.5870 * color[1] + 0.1140 * color[2];
}
