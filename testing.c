#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>

void phase05(int hash){
    int answer = 27;
    int n;
    int m = (hash % 30) + 21;;
    int t = (hash % 30) + 21;;
    int s = 0;

    while (answer >= 2 && answer <= 2147483647){
        printf("now trying out answer = %d\n", answer);
        n = answer;
        s = 0;
        while (n > 1) {
            if (n & 1) {
                n = (n<<2) - n + 1;
            }
            else {
                n = n >> 1;
            }
            if (s == t && m == t) {
                printf("the answer is %d\n", answer);
                return;
            }
            printf("s: %d --> n: %d\n", s, n);
            s++;
        }
        answer++;
        printf("\n\n\n");
    }
    return;
}

void phase06(int hash){
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int max = 50;

    for (a = 0; a <= max; a++) {
        for (b = 0; b <= max; b++) {
            for (c = 0; c <= max; c++) {
                for (d = 0; d <= max; d++) {
                    // printf("trying combination: a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);
                    char expect[128] = "There are 10 kinds of people in the world: those who understand binary and those who don't";
                    char actual[128] = "There are 10 kinds of people in the world: those who understand binary and those who don't";
                    int slen = strlen(expect);
                    int ilen = slen / sizeof(int) - 1;
                    int munge1 = (hash % 211) % ilen;
                    int munge2 = (hash % 311) % ilen;
                    ((int *)actual)[munge1] = 0x58585858;
                    ((int *)actual)[munge2] = 0x59595959;
                    *(((int *)actual) + a) = b;
                    *(((int *)actual) + c) = d;
                
                    if (strncmp(expect,actual,128) == 0) {
                        printf("your answer is %d %d %d %d\n",a, b, c, d);
                        return;
                    }
                }
                printf("d reached 128; c++ = %d\n", c);
            }
            printf("c reached 128; b++ = %d\n", b);
            // printf("trying combination: a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);

        }
        printf("b reached 128; a++ = %d\n", a);
        // printf("trying combination: a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);
    }
    printf("trying combination: a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);
    printf("a reached 128; THE END\n");
}

void phase07(int hash) {
    float a = 3683249062674430.000000;
    union {
        int i;
        float f;
    } flint;
    flint.i = hash;

    // printf("%f\n", a);
    // printf("%f\n", flint.f);
    // printf("%f\n", fabs(a-flint.f));
    // printf("%f\n", 1e-8 );
    if (fabs(a-flint.f) < 1e-8 ) {
        printf("your answer a = %d\n", a);
        printf("your answer a = %f\n", a);
        return;
    }
}

void phase10(int hash){
    long a = 1;
    while (a <= 1){
        if (a % 100000000 == 0){
            printf("trying %ld\n", a);
        }

        char ans[] = "        ";
        for (int i = 0; i < 8; i++) {
            ans[i] = (char) (a >> (7*i) & 0x7F);
        }

        char *accept = "chen7647";
        if (strcmp(ans, accept)==0) {
            printf("your answer is %ld\n", a);
            return;
        } 
        a--;
    }
    printf("you have reached the biggest positive number --> %ld\n", a);
}

int main(){
    // printf("pls input your hash here --> \n");
    int hash = 1498504788;
    // scanf("%d", &hash);
    // printf("%d\n", hash);
    // 1498504788

    // phase05(hash);
    // phase06(hash); // not working

    // int a, b, c, d;
    // for (a = 0; a <= 127; a++) {
    //         for (b = 0; b <= 127; b++) {
    //             for (c = 0; c <= 127; c++) {
    //                 for (d = 0; d <= 127; d++) {
    //                     // Process the current permutation of a, b, c, d
    //                     // For example, you can print the values
    //                         printf("a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
    //                 }
    //             }
    //         }
    //     }

    // phase07(hash);
    phase10(hash);

    
}
