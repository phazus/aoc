#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Implement using median and mean

int main() {
  int pos[4096];
  size_t pos_s = 0;

  int min = INT_MAX, max = 0;
  FILE *f = fopen("07_in.txt", "r");
  for (int p; fscanf(f, "%d,", &p) == 1;) {
    pos[pos_s++] = p;
    if (p < min)
      min = p;
    if (p > max)
      max = p;
  }
  fclose(f);

  int ans1 = INT_MAX, ans2 = INT_MAX;
  for (int i = min; i < max; i++) {
    int fuel1 = 0;
    int fuel2 = 0;
    for (size_t j = 0; j < pos_s; j++) {
      int n = abs(pos[j] - i);
      fuel1 += n;

      // Triangular number
      // * . . . .
      // * * . . .
      // * * * . .
      // * * * * .
      fuel2 += ((n * (n + 1)) / 2);
    }

    if (fuel1 < ans1)
      ans1 = fuel1;
    if (fuel2 < ans2)
      ans2 = fuel2;
  }

  printf("1: %d\n", ans1);
  printf("2: %d\n", ans2);
}
