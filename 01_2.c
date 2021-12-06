#include <stdio.h>
#include <stdlib.h>

struct Window{
	int val;
	int n;
	struct Window *next;
};

int main(void) {
	FILE *fp = fopen("01_in.txt", "r");
	char line[100];
	int l;

	struct Window *head = malloc(sizeof(struct Window));
	head->val = 0;
	head->n = 0;
	head->next = NULL;
	struct Window *current = head;
	struct Window *tail = current;

	while (fgets(line, 100, fp)) {
		if (sscanf(line, "%d", &l) == EOF) {
			continue;
		}

		struct Window *w = current;
		do {
			w->val += l;
			w->n++;
			w = w->next;
		} while (w != NULL);

		if (current->n >= 3) {
			current = current->next;
		}

		tail->next = malloc(sizeof(struct Window));
		tail = tail->next;
		tail->val = 0;
		tail->n = 0;
		tail->next = NULL;
	}

	current = head;
	int result = 0;
	while (current->next) {
		if (current->n == 3
				&& current->next->n == 3
				&& current->next->val > current->val) {
			result++;
		}

		current = current->next;
	}

	current = head;
	int i = 0;
	while (current) {
		if (current->n == 3) i++;
		struct Window *t = current->next;
		free(current);
		current = t;
	}

	printf("%d\n", result);
}
