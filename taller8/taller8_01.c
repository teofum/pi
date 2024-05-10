#include <stdio.h>

#include "random.h"
#include "vector.h"

#define RANGE 2

typedef struct {
  int x, y;
} point;

void move_particle(vector *positions, point *current_pos, point d);

int main(void) {
  seed_with_timestamp();

  vector positions = vec(point);
  point current_pos = {0, 0};
  vec_push(&positions, &current_pos);

  do {
    point d = {random_int(-RANGE, RANGE), random_int(-RANGE, RANGE)};
    move_particle(&positions, &current_pos, d);
  } while (current_pos.x != 0 || current_pos.y != 0);

  for (int i = 0; i < positions.size; i++) {
    vec_get(&positions, i, &current_pos);
    printf("(%3d, %3d)\n", current_pos.x, current_pos.y);
  }

  vec_delete(&positions);
  return 0;
}

void move_particle(vector *positions, point *current_pos, point d) {
  current_pos->x += d.x;
  current_pos->y += d.y;
  vec_push(positions, current_pos);
}
