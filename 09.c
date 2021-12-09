#include <stdio.h>
#include <limits.h>

#define N_ROWS 100
#define N_COLS 100

int g[N_ROWS][N_COLS] = {{0}};
int b[N_ROWS][N_COLS] = {{0}};

int find_neighbors(int r, int c) {
    int num = g[r][c];
    int n = 0;
    
    if (c > 0 && !b[r][c-1] && g[r][c-1] != 9 && g[r][c-1] > num) {
        b[r][c-1] = 1;
        n += 1 + find_neighbors(r, c-1);
    }
    
    if (r > 0 && !b[r-1][c] && g[r-1][c] != 9 && g[r-1][c] > num) {
        b[r-1][c] = 1;
        n += 1 + find_neighbors(r-1, c);
    }
    
    if (c < N_COLS - 1 && !b[r][c+1] && g[r][c+1] != 9 && g[r][c+1] > num) {
        b[r][c+1] = 1;
        n += 1 + find_neighbors(r, c+1);
    }
    
    if (r < N_ROWS - 1 && !b[r+1][c] && g[r+1][c] != 9 && g[r+1][c] > num) {
        b[r+1][c] = 1;
        n += 1 + find_neighbors(r+1, c);
    }
    
    return n;
}

int main() {
    FILE *f = fopen("09_in.txt", "r");
    for (int r = 0; r < N_ROWS; r++) {
        char line[128];
        if (fgets(line, 128, f) != NULL)
            for (int c = 0;  c < N_COLS; c++)
                g[r][c] = line[c] - '0';
    }
    fclose (f);

    int res1 = 0;
    long max1 = 0, max2 = 0, max3 = 0;
    for (int r = 0; r < N_ROWS; r++) {
        for (int c = 0; c < N_COLS; c++) {
            char is_min = 1;
            if (c > 0) is_min &= g[r][c] < g[r][c-1];
            if (r > 0) is_min &= g[r][c] < g[r-1][c];
            if (c < N_COLS - 1) is_min &= g[r][c] < g[r][c+1];
            if (r < N_ROWS - 1) is_min &= g[r][c] < g[r+1][c];

            if (is_min) {
                res1 += g[r][c] + 1;
                int basin_size = 1;
                b[r][c] = 1;
                basin_size += find_neighbors(r, c);
                printf("Basin : %d\n", basin_size);

                if (basin_size > max1) {
                    max3 = max2;
                    max2 = max1;
                    max1 = basin_size;
                }
                else if (basin_size > max2) {
                    max3 = max2;
                    max2 = basin_size;
                }
                else if (basin_size > max3) max3 = basin_size;
            }
        }
    }

    printf("1 : %d\n",  res1);
    printf("2 : %ld\n",  max1 * max2 * max3);

    return 0;
}
