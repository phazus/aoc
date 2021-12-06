#include <stdio.h>
#include <stdlib.h>

int main() {
  int h = 0;
  int d = 0;
  int aim = 0; // same as depth in Part 1

  char *str = NULL;
  size_t str_max = 64;
  ssize_t str_len;
  FILE *f = fopen("02_in.txt", "r");
  for (; (str_len = getline(&str, &str_max, f)) != -1;) {
    int x;
    if (sscanf(str, "forward %d", &x) == 1) {
      h += x;
      d += aim * x;
    } else if (sscanf(str, "down %d", &x) == 1)
      aim += x;
    else if (sscanf(str, "up %d", &x) == 1)
      aim -= x;
  }
  fclose(f);
  free(str);

  printf("1 : %d\n", h * aim);
  printf("2 : %d\n", h * d);
}
