#include <stdio.h>

#include "../lib/my_getnum.h"

#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_HOUR 3600

int main(void) {
  int seconds;
  do {
    seconds = get_int("Enter a duration in seconds (positive integer)\n");
  } while (seconds <= 0);

  printf(
      "%d seconds are: %d hours, %d minutes and %d seconds\n", seconds,
      seconds / SECONDS_PER_HOUR,
      seconds / SECONDS_PER_MINUTE % MINUTES_PER_HOUR,
      seconds % SECONDS_PER_MINUTE
  );

  return 0;
}