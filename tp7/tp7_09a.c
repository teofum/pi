#include <stdio.h>

#include "random.h"

#define COLS 5
#define ROWS 3
#define N_MAX 90
#define MARKED (-1)
#define N 4

typedef int line_t[COLS];
typedef line_t board_t[ROWS];

void gen_board(board_t board);

int play(int numbers[N_MAX], board_t players[N]);

int draw_number(int numbers[N_MAX], int *undrawn);

int check_board(board_t board, int number);

int check_number(board_t board, int number);

int check_line(const line_t line);

void print_board(const board_t board);

void print_line(const line_t line);

int main(void) {
  seed_with_timestamp();

  // Generate an array of numbers in range 1-N_MAX
  int numbers[N_MAX];
  for (int i = 0; i < N_MAX; i++) numbers[i] = i + 1;

  // Shuffle the numbers once so we don't need to do random access later
  shuffle(numbers, sizeof(int), N_MAX);

  board_t players[N];
  for (int i = 0; i < N; i++)
    gen_board(players[i]);

  int winners = play(numbers, players);
  if (winners) {
    for (int i = 0; i < N; i++) {
      if (winners & (1 << i)) {
        printf("Bingo! Player %d won.\n", i + 1);
      }
    }
  } else {
    printf("Nobody won.\n");
  }

  return 0;
}

void gen_board(board_t board) {
  int numbers[N_MAX];
  for (int i = 0; i < N_MAX; i++) numbers[i] = i + 1;
  shuffle(numbers, sizeof(int), N_MAX);

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      board[i][j] = numbers[i * COLS + j];
    }
  }
}

int play(int numbers[N_MAX], board_t players[N]) {
  int undrawn = N_MAX, winners = 0, first_line = -1;

  while (undrawn > 0 && !winners) {
    int drawn = draw_number(numbers, &undrawn);
    printf("\nDrew %d\n", drawn);

    for (int i = 0; i < N; i++) {
      int complete = check_board(players[i], drawn);
      printf("Player %d:\n", i + 1);
      print_board(players[i]);

      if (complete > 0 && first_line == -1) {
        first_line = i;
        printf("Player %d completed the first line!\n", i + 1);
      }

      if (complete == ROWS) winners += (1 << i);
    }
  }

  return winners;
}

int draw_number(int numbers[N_MAX], int *undrawn) {
  return numbers[((*undrawn)--) - 1];
}

int check_board(board_t board, int number) {
  check_number(board, number);

  int complete = 0;
  for (int i = 0; i < ROWS; i++) {
    complete += check_line(board[i]);
  }

  return complete;
}

int check_number(board_t board, int number) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board[i][j] == number) {
        board[i][j] = -1;
        return 1;
      }
    }
  }

  return 0;
}

int check_line(const line_t line) {
  for (int j = 0; j < COLS; j++) {
    if (line[j] != MARKED) return 0;
  }

  return 1;
}

void print_board(const board_t board) {
  for (int i = 0; i < ROWS; i++) {
    print_line(board[i]);
  }
}

void print_line(const line_t line) {
  printf("| ");
  for (int j = 0; j < COLS; j++) {
    if (line[j] == MARKED) {
      printf("--- ");
    } else {
      printf("%3d ", line[j]);
    }
  }
  printf("|\n");
}
