#include <stdio.h>
#include <limits.h>

#define N_ROWS 100
#define N_COLS 100

int main() {
    int g[N_ROWS][N_COLS] = {{0}};

    FILE *f = fopen("09_in.txt", "r");
    for (int r = 0; r < N_ROWS; r++) {
        char line[128];
        if (fgets(line, 128, f) != NULL)
            for (int c = 0;  c < N_COLS; c++)
                g[r][c] = line[c] - '0';
    }
    fclose (f);

    int res1 = 0;
    for (int r = 0; r < N_ROWS; r++) {
        for (int c = 0; c < N_COLS; c++) {
            char is_min = 1;
            if (c > 0) is_min &= g[r][c] < g[r][c-1];
            if (r > 0) is_min &= g[r][c] < g[r-1][c];
            if (c < N_COLS - 1) is_min &= g[r][c] < g[r][c+1];
            if (r < N_ROWS - 1) is_min &= g[r][c] < g[r+1][c];
            res1 += is_min * (1 + g[r][c]);
        }
    }

    printf("1 : %d\n",  res1);

    return 0;
}
