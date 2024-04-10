#include <assert.h>
#include <math.h>
#include <stdio.h>

double std_deviation(const unsigned char vec[], int size);

int main(void) {
  unsigned char vec2[] = {0x33, 0x33, 0x33, 0x33, 0x33};
  for (int i = 0; i <= 10; i++)
    assert(std_deviation(vec2, i) == 0);

  unsigned char vec[] = {0x37, 0xF2, 0x03, 0x4A, 0xFF};
  assert(std_deviation(vec, 1) == 0);
  assert(std_deviation(vec, 2) == 2.0);

  assert(std_deviation(vec, 3) > 4.98 && std_deviation(vec, 3) < 4.99);

  assert(std_deviation(vec, 10) > 5.6071 && std_deviation(vec, 3) < 5.6072);

  puts("OK!");
}

void unpack_values(const unsigned char vec[], double values[], int size) {
  for (int i = 0; i < size; i++) {
    int vi = i / 2;
    unsigned char mask = i % 2 ? 0x0f : 0xf0;
    unsigned char shift = i % 2 ? 0 : 4;
    values[i] = (double)((vec[vi] & mask) >> shift);
  }
}

double average(const double values[], int size) {
  double avg;
  for (int i = 0; i < size; i++)
    avg += values[i];
  avg /= size;

  return avg;
}

double variance(const double values[], int size, double avg) {
  double var;
  for (int i = 0; i < size; i++) {
    double dev = values[i] - avg;
    double dev_squared = dev * dev;
    var += dev_squared;
  }
  var /= size;

  return var;
}

// https://en.wikipedia.org/wiki/Standard_deviation
double std_deviation(const unsigned char vec[], int size) {
  if (size == 0)
    return 0; // Handle the trivial empty list case

  // First, unpack the values into doubles and calculate the average
  double values[size];

  unpack_values(vec, values, size);
  double avg = average(values, size);

  // Then, calculate the variance
  double var = variance(values, size, avg);

  // Standard deviation is the square root of variance
  return sqrt(var);
}
