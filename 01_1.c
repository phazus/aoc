#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *fp = fopen("01_in.txt", "r");
  char line[100];
  int x, y;
  int ctr = 0;

  fgets(line, 100, fp);
  sscanf(line, "%d", &x);

  while (fgets(line, 100, fp)) {
    sscanf(line, "%d", &y);
    if (y > x) ctr++;
    x = y;
  }

  printf("%d\n", ctr);
}
