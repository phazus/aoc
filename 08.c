#include <stdio.h>
#include <string.h>

//   0:      1:      2:      3:      4:       5:      6:      7:      8:      9:
//   aaaa    ....    aaaa    aaaa    ....    aaaa    aaaa    aaaa    aaaa    aaaa
//  b    c  .    c  .    c  .    c  b    c  b    .  b    .  .    c  b    c  b    c
//  b    c  .    c  .    c  .    c  b    c  b    .  b    .  .    c  b    c  b    c
//   ....    ....    dddd    dddd    dddd    dddd    dddd    ....    dddd    dddd
//  e    f  .    f  e    .  .    f  .    f  .    f  e    f  .    f  e    f  .    f
//  e    f  .    f  e    .  .    f  .    f  .    f  e    f  .    f  e    f  .    f
//   gggg    ....    gggg    gggg    ....    gggg    gggg    ....    gggg    gggg

// Count the number of occurences for each segment:
//
// 0 : [a b c   e f g] = 6 segments  |
// 1 : [    c     f  ] = 2 segments  | a : 8 occurences ┐
// 2 : [a   c d e   g] = 5 segments  | b : 6 occurences | -> duplicate
// 3 : [a   c d   f g] = 5 segments  | c : 8 occurences ┘
// 4 : [  b c d   f  ] = 4 segments  | d : 7 occurences ┐
// 5 : [a b   d   f g] = 5 segments  | e : 4 occurences | -> duplicate
// 6 : [a b   d e f g] = 6 segments  | f : 9 occurences |
// 7 : [a   c     f  ] = 3 segments  | g : 7 occurences ┘
// 8 : [a b c d e f g] = 7 segments  |
// 9 : [a b c d   f g] = 6 segments  |
//
// As the segments {a,c} and {d,g}
// cannot be inferred by the amount of total occurences,
// introduce a second characteristic:
//
// The amount of occurences in a set of digits
// that can be initially defined, i.e. by their amount of used segments.
// -> 1 4 7 8
//
// As will be seen in the next figure, the digit 4 suffices
// to get a distinction in {a,c} and {d,g}:
// 
//                                   | a : 0 occurences ┐
//                                   | b : 1 occurences | -> differ
//                                   | c : 1 occurences ┘
// 4 : [  b c d   f  ] = 4 segments  | d : 1 occurences ┐
//                                   | e : 0 occurences | -> differ
//                                   | f : 1 occurences |
//                                   | g : 0 occurences ┘
//

// A twodimensional lookup table can be constructed
// where the index in each dimension represents the amount of occurences 
// of a segment for all digits and for {4, 7}, respectively.

#define INDEX_SEG_A [8][0]
#define INDEX_SEG_B [6][1]
#define INDEX_SEG_C [8][1]
#define INDEX_SEG_D [7][1]
#define INDEX_SEG_E [4][0]
#define INDEX_SEG_F [9][1]
#define INDEX_SEG_G [7][0]

#define PATTERN_MAX_LENGTH 8    // incl. \0
#define N_DIGITS 10             // 0 - 9
#define N_OUTPUT_VALUES 4

int main() {
    char lookup[10][2] = {{0}}; // Big enough to contain all segments
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

        // Construct the lookup table.
        for (char segment = 'a'; segment <= 'g'; segment++) {
            int cnt1 = 0, cnt2 = 0;

            for (int digit_index = 0; digit_index < 10; digit_index++) {
                char *digit = signal_patterns[digit_index];
                
                // Count occurences in each digit
                cnt1 += (strchr(digit, segment) != NULL);

                // Count occurences in digit 4.
                int l = strlen(digit);
                cnt2 += l == 4 && strchr(digit, segment);
            }

            lookup[cnt1][cnt2] = segment;
        }

        // Query the lookup table.
        int value = 0;
        for (int val_index = 0; val_index < N_OUTPUT_VALUES; val_index++) {
            char *digit = output_values[val_index];
            int d = 0;

            switch(strlen(digit)) {

                // Some digits are defined by their amount of segments
                case 2 :
                    d = 1; res1++; break;
                case 3 :
                    d = 7; res1++; break;
                case 4 :
                    d = 4; res1++; break;
                case 7 :
                    d = 8; res1++; break;

                // Some digits have to be identified by checking
                // if they contain each of their segments 
                
                case 5:
                    if        (strchr(digit, (lookup INDEX_SEG_A))
                            && strchr(digit, (lookup INDEX_SEG_C))
                            && strchr(digit, (lookup INDEX_SEG_D))
                            && strchr(digit, (lookup INDEX_SEG_E))
                            && strchr(digit, (lookup INDEX_SEG_G))) d = 2;

                    else if   (strchr(digit, (lookup INDEX_SEG_A))
                            && strchr(digit, (lookup INDEX_SEG_C))
                            && strchr(digit, (lookup INDEX_SEG_D))
                            && strchr(digit, (lookup INDEX_SEG_F))
                            && strchr(digit, (lookup INDEX_SEG_G))) d = 3;
                    
                    else if   (strchr(digit, (lookup INDEX_SEG_A))
                            && strchr(digit, (lookup INDEX_SEG_B))
                            && strchr(digit, (lookup INDEX_SEG_D))
                            && strchr(digit, (lookup INDEX_SEG_F))
                            && strchr(digit, (lookup INDEX_SEG_G))) d = 5;
                    break;
                
                case 6 :
                    if        (strchr(digit, (lookup INDEX_SEG_A))
                            && strchr(digit, (lookup INDEX_SEG_B))
                            && strchr(digit, (lookup INDEX_SEG_C))
                            && strchr(digit, (lookup INDEX_SEG_E))
                            && strchr(digit, (lookup INDEX_SEG_F))
                            && strchr(digit, (lookup INDEX_SEG_G))) d = 0;

                    else if   (strchr(digit, (lookup INDEX_SEG_A))
                            && strchr(digit, (lookup INDEX_SEG_B))
                            && strchr(digit, (lookup INDEX_SEG_D))
                            && strchr(digit, (lookup INDEX_SEG_E))
                            && strchr(digit, (lookup INDEX_SEG_F))
                            && strchr(digit, (lookup INDEX_SEG_G))) d = 6;
                    
                    else if   (strchr(digit, (lookup INDEX_SEG_A))
                            && strchr(digit, (lookup INDEX_SEG_B))
                            && strchr(digit, (lookup INDEX_SEG_C))
                            && strchr(digit, (lookup INDEX_SEG_D))
                            && strchr(digit, (lookup INDEX_SEG_F))
                            && strchr(digit, (lookup INDEX_SEG_G))) d = 9;
                   break; 
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
