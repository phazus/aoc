#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  char straight[1000][1000] = {{0}};
  char diag[1000][1000] = {{0}};
  int x1, y1, x2, y2;

  FILE *f = fopen("05_in.txt", "r");
  while (fscanf(f, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {

    // . * .
    // . * .
    // . * .
    if (x1 == x2) {
      for (int y = fmin(y1, y2); y <= fmax(y1, y2); y++)
        straight[x1][y]++;
      continue;
    }

    // . . .
    // * * *
    // . . .
    if (y1 == y2) {
      for (int x = fmin(x1, x2); x <= fmax(x1, x2); x++)
        straight[x][y1]++;
      continue;
    }
    
    // . . *
    // . * .
    // * . .
    if (x1 - y1 == x2 - y2) {
      int i = 0;
      for (int x = fmin(x1, x2); x <= fmax(x1, x2); x++)
        diag[x][(int)fmin(y1, y2) + (i++)]++;
      continue;
    }

    // . . *
    // . * .
    // * . .
    if (x1 + y1 == x2 + y2) {
      int i = 0;
      for (int x = fmin(x1, x2); x <= fmax(x1, x2); x++)
        diag[x][(int)fmax(y1, y2) - (i++)]++;
      continue;
    }

  }
  fclose(f);

  int res1 = 0;
  int res2 = 0;
  for (int i = 0; i < 1000; i++)
    for (int j = 0; j < 1000; j++) {
      res1 += straight[i][j] >= 2;
      res2 += (straight[i][j] + diag[i][j]) >= 2;
    }

  printf("1 : %d\n", res1);
  printf("2 : %d\n", res2);
}
