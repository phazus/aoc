#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define N_DIGITS 12
#define MCB(n_ones, n_digits) ((n_digits) % 2) ? (n_ones) > ((n_digits) / 2) : (n_ones) >= ((n_digits) / 2)

int get_rating(int *arr, size_t n_arr, int ones_in_msb, int use_mcb);

int main() {
  int numbers[10000]; int ones[N_DIGITS] = {0}; int n_num;
  char str[64];
  FILE *f = fopen("03_in.txt", "r");
  for (n_num = 0; fgets(str, 64, f) != NULL && str[0] != '\n'; n_num++) {
    int num = 0;
    for (int i = 0; str[i] != '\n'; i++) {
      ones[i] += str[i] - '0';
      num <<= 1;
      num += str[i] - '0';
    }
    numbers[n_num] = num;
  }
  fclose(f);
 
  long g = 0; long e = 0;
  for (size_t i = 0; i < N_DIGITS; i++)
  {
    g <<= 1; e <<= 1;
    int mcb = MCB(ones[i], n_num);
    g += mcb; e += !mcb;
  }
  printf("1 : %ld\n", (long)g*e);

  int ox = get_rating(numbers, n_num, ones[0], 1);
  int co2 = get_rating(numbers, n_num, ones[0], 0);
  printf("2 : %ld\n", (long)ox*co2);
}

int get_rating(int *arr, size_t n_arr, int ones_in_msb, int use_mcb) {
  int n[n_arr];
  for (size_t i = 0; i < n_arr; i++)
    n[i] = arr[i];
  
  int r = n_arr;
  int n_ones = ones_in_msb; 
  for (int i = 1; i <= N_DIGITS && r > 1; i++) {
    int mcb = MCB(n_ones, r);
    int eq = 0;
    n_ones = 0;
    for (int j = 0; j < r; j++) {
      int digit = (n[j] >> (N_DIGITS-i)) & 1;
      if (digit == (mcb ^ !use_mcb)) {
        n[eq++] = n[j];
        n_ones += (n[j] >> (N_DIGITS-i-1)) & 1; // next digit
      }
    }
    r = eq;
  }
  return n[0];
}
