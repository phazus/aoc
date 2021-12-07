#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Crab {
  int pos;
  struct Crab *next;
};

struct Crab *new_crab(int pos) {
  struct Crab *c = malloc(sizeof(struct Crab));
  c->next = NULL;
  c->pos = pos;
  return c;
}

void sorted_insert(struct Crab **head_ref, struct Crab *n) {
  if (*head_ref == NULL || n->pos < (*head_ref)->pos) {
    n->next = *head_ref;
    *head_ref = n;
  } else {
    struct Crab *c = *head_ref;
    while (c->next != NULL && c->next->pos < n->pos)
      c = c->next;
    n->next = c->next;
    c->next = n;
  }
}

void free_crabs(struct Crab *head) {
  while (head != NULL) {
    struct Crab *t = head->next;
    free(head);
    head = t;
  }
}

void solve(struct Crab *head, int median, float mean) {
  int mean_f = floor(mean), mean_c = ceil(mean);
  int ans1 = 0, ans2_1 = 0, ans2_2 = 0;
  while (head != NULL) {
    ans1 += (abs(head->pos - median));
    
    int d = abs(head->pos - mean_f);
    ans2_1 += (d * (d + 1)) / 2;

    d = abs(head->pos - mean_c);
    ans2_2 += (d * (d + 1)) / 2;

    head = head->next;
  }

  printf("1: %d\n", ans1);
  printf("2: %d\n", (int)fmin(ans2_1, ans2_2));
}

int main() {
  struct Crab *head = NULL;

  size_t crabs_s = 0;
  int sum = 0;

  FILE *f = fopen("07_in.txt", "r");
  for (int p; fscanf(f, "%d,", &p) == 1;) {
    sorted_insert(&head, new_crab(p));
    sum += p;
    crabs_s++;
  }
  fclose(f);

  float mean = (float)sum / (int)crabs_s;
  int median;
  struct Crab *c = head;
  for (size_t i = 0; i < crabs_s / 2; i++)
    c = c->next;
  median = c->pos;
  printf("Median value: %d\n", median);
  
  solve(head, median, mean);
  free_crabs(head);
}
