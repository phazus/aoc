#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 5

#define ROW_MATCH_XOR (0b11111)
#define COL_MATCH_XOR (0b0000100001000010000100001)

size_t read_drawn_numbers(int (*arr)[], size_t max, FILE *f);
size_t read_boards(int (*arr)[][BOARD_SIZE][BOARD_SIZE], size_t max, FILE *f);

int main() {
  FILE *f = fopen("04_in.txt", "r");
  int drawn_numbers[128] = {0};
  size_t drawn_s = read_drawn_numbers(&drawn_numbers, 128, f);

  int boards[128][BOARD_SIZE][BOARD_SIZE] = {0};
  size_t boards_s = read_boards(&boards, 128, f);
  fclose(f);

  int n_won = 0;
  char finished[boards_s];
  memset(finished, 0, boards_s * sizeof(char));
  long res1 = 0, res2 = 0;

  for (size_t num_index = BOARD_SIZE - 1; num_index < drawn_s && n_won < boards_s; num_index++)
    for (size_t board_index = 0; board_index < boards_s && n_won < boards_s; board_index++) {
      if (finished[board_index])
        continue;
      long marker = 0;
      long score = 0;

      // Construct marker
      for (size_t row = 0; row < BOARD_SIZE; row++)
        for (size_t col = 0; col < BOARD_SIZE; col++) {
          int match = 0;
          int cell = boards[board_index][row][col];
          for (size_t n = 0; n <= num_index; n++)
            match |= (cell == drawn_numbers[n]);

          score += !match * cell;
          marker <<= 1;
          marker |= match;
        }

      // Evaluate
      int won = 0;

      // Check for row match
      for (size_t col = 0; col < BOARD_SIZE; col++) {
        int mask = ROW_MATCH_XOR << (BOARD_SIZE * col);
        won |= !((marker & mask) ^ mask);
      }

      // Check for column match
      for (size_t row = 0; row < BOARD_SIZE; row++) {
        int mask = COL_MATCH_XOR << row;
        won |= !((marker & mask) ^ mask);
      }

      if (won) {
        finished[board_index] = 1;
        n_won++;
        if (n_won == 1)
          res1 = drawn_numbers[num_index] * score;
        if (n_won == (int)boards_s)
          res2 = drawn_numbers[num_index] * score;
      }
    }

  printf("1 : %ld\n", res1);
  printf("2 : %ld\n", res2);
}

size_t read_drawn_numbers(int (*arr)[], size_t max, FILE *f) {
  size_t size = 0;
  int num = 0;
  char c;

  do {
    c = fgetc(f);
    if (c >= '0' && c <= '9')
      num = num * 10 + c - '0';
    else {
      (*arr)[size++] = num;
      num = 0;
    }
  } while (c != '\n' && size <= max);

  return size;
}

size_t read_boards(int (*arr)[][BOARD_SIZE][BOARD_SIZE], size_t max, FILE *f) {
  size_t size = 0;
  char str[32];
  int row_index = 0;

  while (fgets(str, 32, f) != NULL && size <= max) {
    if (str[0] == '\n') {
      row_index = 0;
    } else {
      char *line = str;
      char *s;
      int col_index = 0;
      while ((s = strsep(&line, " ")) != NULL) {
        int n;
        if (sscanf(s, "%d", &n) == 1)
          (*arr)[size][row_index][col_index++] = n;
      }

      row_index += col_index == BOARD_SIZE;

      if (row_index == BOARD_SIZE && col_index == BOARD_SIZE)
        size++;
    }
  }

  return size;
}
