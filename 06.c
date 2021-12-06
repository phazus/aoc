#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 0 - 8
#define VALID_TIMER_VALUES 9
#define DAYS 256

int main() {
  char input[1024];
  FILE *f = fopen("06_in.txt", "r");
  if (fgets(input, 1024, f) == NULL) 
    return -1;
  fclose(f);
  
  unsigned long long fish[VALID_TIMER_VALUES] = {0};
 
  char *d = strtok(input, ",");
  while (d != NULL) {
    fish[atoi(d)]++;
    d = strtok(NULL, ",");
  }

  unsigned long long res1 = 0, res2 = 0;
  unsigned long long fish_n[VALID_TIMER_VALUES]; // next day

  for (int i = 0; i < DAYS; i++) {
    if (i == 80)
      for (int i = 0; i < VALID_TIMER_VALUES; i++)
        res1 += fish[i];

    for (int t = 0; t < VALID_TIMER_VALUES; t++)
      fish_n[t] = fish[(t+1) % VALID_TIMER_VALUES];
    fish_n[6] += fish[0];

    for (int t = 0; t < VALID_TIMER_VALUES; t++)
      fish[t] = fish_n[t];
  }

  for (int i = 0; i < VALID_TIMER_VALUES; i++)
    res2 += fish[i];

  printf("1: %llu\n", res1);
  printf("2: %llu\n", res2);
}
