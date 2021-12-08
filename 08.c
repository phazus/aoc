#include <stdio.h>
#include <string.h>

#define INDEX_SEG_A [8][2]
#define INDEX_SEG_B [6][2]
#define INDEX_SEG_C [8][4]
#define INDEX_SEG_D [7][2]
#define INDEX_SEG_E [4][1]
#define INDEX_SEG_F [9][4]
#define INDEX_SEG_G [7][1]

#define PATTERN_MAX_LENGTH 8    // incl. \0
#define N_DIGITS 10             // 0 - 9
#define N_OUTPUT_VALUES 4

int main() {
    char lookup[N_DIGITS][N_DIGITS] = {{0}};
    char signal_patterns[N_DIGITS][PATTERN_MAX_LENGTH];
    char output_values[N_OUTPUT_VALUES][PATTERN_MAX_LENGTH];

    int res1 = 0, res2 = 0;

    FILE *f = fopen ("08_in.txt", "r");
    while(fscanf(f, " %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] | %[^ ] %[^ ] %[^ ] %s",
                signal_patterns[0],
                signal_patterns[1],
                signal_patterns[2],
                signal_patterns[3],
                signal_patterns[4],
                signal_patterns[5],
                signal_patterns[6],
                signal_patterns[7],
                signal_patterns[8],
                signal_patterns[9],
                output_values[0],
                output_values[1],
                output_values[2],
                output_values[3]) == 14) {

        // Build the lookup table
        for (char segment = 'a'; segment <= 'g'; segment++) {
            int cnt1 = 0, cnt2 = 0;

            for (int digit_index = 0; digit_index < 10; digit_index++) {
                char *digit = signal_patterns[digit_index];
                int l = strlen(digit);
                cnt1 += (strchr(digit, segment) != NULL);
                cnt2 += (l == 2 || l == 3 || l == 4 || l == 7) && strchr(digit, segment) != NULL;
            }

            lookup[cnt1][cnt2] = segment;
        }

        int value = 0;
        for (int val_index = 0; val_index < N_OUTPUT_VALUES; val_index++) {
            char *digit = output_values[val_index];
            int d = 0;
            switch(strlen(digit)) {
                case 2 :
                    d = 1; res1++; break;
                case 3 :
                    d = 7; res1++; break;
                case 4 :
                    d = 4; res1++; break;
                case 5:
                    if (strchr(digit, (lookup INDEX_SEG_A)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_C)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_D)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_E)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_G)) != NULL) d = 2;

                    else if (strchr(digit, (lookup INDEX_SEG_A)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_C)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_D)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_F)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_G)) != NULL) d = 3;
                    
                    else if (strchr(digit, (lookup INDEX_SEG_A)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_B)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_D)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_F)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_G)) != NULL) d = 5;
                    break;
                case 6 :
                    if (strchr(digit, (lookup INDEX_SEG_A)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_B)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_C)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_E)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_F)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_G)) != NULL) d = 0;

                    else if (strchr(digit, (lookup INDEX_SEG_A)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_B)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_D)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_E)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_F)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_G)) != NULL) d = 6;
                    
                    else if (strchr(digit, (lookup INDEX_SEG_A)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_B)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_C)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_D)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_F)) != NULL
                            && strchr(digit, (lookup INDEX_SEG_G)) != NULL) d = 9;
                   break; 
                case 7 :
                    d = 8; res1++; break;
                default: break;
            }
            
            value *= 10;
            value += d;
        }

        res2 += value;

    }
   
    fclose(f);
    
    printf("1: %d\n", res1);
    printf("1: %d\n", res2);
    return 0;
}

// 0 : [a b c   e f g]
// 1 : [    c     f  ]
// 2 : [a   c d e   g]
// 3 : [a   c d   f g]
// 4 : [  b c d   f  ]
// 5 : [a b   d   f g]
// 6 : [a b   d e f g]
// 7 : [a   c     f  ]
// 8 : [a b c d e f g]
// 9 : [a b c d   f g]

//      8 6 8 7 4 9 7

// 1 : [    c     f  ]
// 7 : [a   c     f  ]
// 4 : [  b c d   f  ]
// 8 : [a b c d e f g]
//
//      8 6 8 7 4 9 7
//      2 2 4 2 1 4 1
//
// [8][2] = a
// [6][2] = b
// [8][2] = a
// [8][2] = a
//
// 1. Zähle Anzahl für jeden Buchstaben
// 2. Zähle Anzahl für jeden Buchstaben in "besonderen Wörtern"
// 
// // Alle Ziffern:
// 4x Vorkommen -> 'e'
// 6x Vorkommen -> 'b'
// 9x Vorkommen -> 'f'
// 
// // Besondere:
// In 7 vorkommen und nicht in 1 -> 'a'
//
// 1x Vorkommen && != 'e' -> 'g'
// In 1 Vorkommen && != 'f' -> 'c'
// Der restliche : 'd'
