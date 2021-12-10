#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int compare (const void *a, const void *b);

int main() {
    int res1 = 0;

    char stack[100] = {0};
    long long int scores[100] = {0};
    size_t stack_s = 0, scores_s = 0;

    int corrupt = 0;
    FILE *f = fopen("10_in.txt", "r");
    for (char c; (c = fgetc(f)) != EOF;) {
        if (c == '\n') {
            res1 += corrupt;
            if (!corrupt) {
                long score = 0;
                while (stack_s > 0) {
                    int s = stack[--stack_s];
                    score *= 5;
                    switch (s) {
                        case '(' : score += 1; break;
                        case '[' : score += 2; break;
                        case '{' : score += 3; break;
                        case '<' : score += 4; break;
                    }
                }
                scores[scores_s++] = score;
            }

            corrupt = stack_s = 0;
        }
        else if (corrupt) ;
        else if (c == '(' || c == '{' || c == '[' || c == '<') 
            stack[stack_s++] = c;
        else
        {
            if (stack_s >= 0){
                int s = stack[--stack_s];
                if (c == ')' && s != '(')
                    corrupt += 3;
                else if (c == ']' && s != '[')
                    corrupt += 57;
                else if (c == '}' && s != '{')
                    corrupt += 1197;
                else if (c == '>' && s != '<')
                    corrupt += 25137;
            }
        }
    }
    fclose(f);

    // Ignore last '\n' 
    qsort(scores, --scores_s, sizeof(long long int), compare);

    printf("1 : %d\n", res1);
    printf("2 : %lld\n", scores[scores_s / 2]);

    return 0;
}

int compare (const void *a, const void *b)                                
{ 
    if( *(long long int*)a - *(long long int*)b < 0 )
        return -1;
    if( *(long long int*)a - *(long long int*)b > 0 )
        return 1;
    return 0;
}     

