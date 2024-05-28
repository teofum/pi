#include "squirrelADT.h"

typedef struct squirrel_block {
  size_t block_number;
  size_t count;
  struct squirrel_block *tail;
} squirrel_block;

typedef struct squirrel_row {
  size_t row_number;
  struct squirrel_block *blocks;
  struct squirrel_row *tail;
} squirrel_row;

typedef struct squirrelCensusCDT {
  size_t block_size;
  squirrel_row *data;
} squirrelCensusCDT;

squirrelCensusADT squirrel_new(size_t block_size) {
  squirrelCensusADT squirrels = malloc(sizeof(squirrelCensusCDT));
  squirrels->data = NULL;
  squirrels->block_size = block_size;
  return squirrels;
}

static squirrel_row *create_row(size_t row_number) {
  squirrel_row *row = malloc(sizeof(squirrel_row));
  row->row_number = row_number;
  row->blocks = NULL;
  row->tail = NULL;
  return row;
}


static squirrel_block *create_block(size_t block_number) {
  squirrel_block *block = malloc(sizeof(squirrel_block));
  block->block_number = block_number;
  block->count = 0;
  block->tail = NULL;
  return block;
}

static squirrel_block *add_to_row(
  squirrel_block *block,
  size_t x,
  size_t *new_count
) {
  if (!block || block->block_number > x) {
    squirrel_block *new_block = create_block(x);
    new_block->tail = block;
    *new_count = new_block->count = 1;
    return new_block;
  }
  if (block->block_number == x) {
    *new_count = ++block->count;
  } else {
    block->tail = add_to_row(block->tail, x, new_count);
  }
  return block;
}

static squirrel_row *add_squirrel(
  squirrel_row *row,
  size_t y,
  size_t x,
  size_t *new_count
) {
  if (!row || row->row_number > y) {
    squirrel_row *new_row = create_row(y);
    new_row->tail = row;
    new_row->blocks = add_to_row(new_row->blocks, x, new_count);
    return new_row;
  }

  if (row->row_number == y) {
    row->blocks = add_to_row(row->blocks, x, new_count);
  } else {
    row->tail = add_squirrel(row->tail, y, x, new_count);
  }
  return row;
}

size_t squirrel_count(
  squirrelCensusADT squirrels,
  size_t y_dist,
  size_t x_dist
) {
  size_t block_y = y_dist / squirrels->block_size;
  size_t block_x = x_dist / squirrels->block_size;

  size_t new_count;
  squirrels->data = add_squirrel(squirrels->data, block_y, block_x, &new_count);
  return new_count;
}

static size_t get_squirrel_count_block(squirrel_block *block, size_t x) {
  if (!block || block->block_number > x) return 0;
  if (block->block_number == x) return block->count;
  return get_squirrel_count_block(block->tail, x);
}

static size_t get_squirrel_count(squirrel_row *row, size_t y, size_t x) {
  if (!row || row->row_number > y) return 0;
  if (row->row_number == y) return get_squirrel_count_block(row->blocks, x);
  return get_squirrel_count(row->tail, y, x);
}

size_t squirrel_in_block(
  const squirrelCensusADT squirrels,
  size_t y_dist,
  size_t x_dist
) {
  size_t block_y = y_dist / squirrels->block_size;
  size_t block_x = x_dist / squirrels->block_size;

  return get_squirrel_count(squirrels->data, block_y, block_x);
}

static void free_block(squirrel_block *block) {
  if (block) {
    free_block(block->tail);
    free(block);
  }
}

static void free_row(squirrel_row *row) {
  if (row) {
    free_block(row->blocks);
    free_row(row->tail);
    free(row);
  }
}

void squirrel_free(squirrelCensusADT squirrels) {
  free_row(squirrels->data);
  free(squirrels);
}
