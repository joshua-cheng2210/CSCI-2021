// Construct memory diagrams for the blocks below
#include <stdio.h>

int main() {
    // // BLOCK A
    // int a = 5;
    // int b = 7;
    // double x = 4.5;
    // int *ip = &a;
    // ip = &b;
    // int c = *ip;
    // *ip = 19;

    // // DRAW MEMORY HERE
    // printf("Value of a: %d\n", a);
    // printf("Value of b: %d\n", b);
    // printf("Value of x: %lf\n", x);
    // printf("Value of *ip: %d\n", *ip);
    // printf("Value of c: %d\n", c);

    // BLOCK B
    int arr[4] = {12, 14, 16, 18};
    int *arp = arr;
    int brr = 11;
    arr[1] = 23;
    arp[3] = 29;

    // printf("\n");
    // printf("Value of arr[3]: %d\n", arr[3]);
    // printf("Value of arr[2]: %d\n", arr[2]);
    // printf("Value of arr[1]: %d\n", arr[1]);
    // printf("Value of arr[0]: %d\n", arr[0]);
    // printf("Value of brr   : %d\n", brr);
    // printf("Value of arp[3]: %d\n", arp[3]);
    // printf("Value of arp[2]: %d\n", arp[2]);
    // printf("Value of arp[1]: %d\n", arp[1]);
    // printf("Value of arp[0]: %d\n", arp[0]);


    arp = &arr[2];

    // printf("\n");
    // printf("Value of arr[3]: %d\n", arr[3]);
    // printf("Value of arr[2]: %d\n", arr[2]);
    // printf("Value of arr[1]: %d\n", arr[1]);
    // printf("Value of arr[0]: %d\n", arr[0]);
    // printf("Value of brr   : %d\n", brr);
    // printf("Value of arp[3]: %d\n", arp[3]);
    // printf("Value of arp[2]: %d\n", arp[2]);
    // printf("Value of arp[1]: %d\n", arp[1]);
    // printf("Value of arp[0]: %d\n", arp[0]);


    *arp = brr;
    // DRAW MEMORY HERE
    
    printf("\n");
    printf("Value of arr[3]: %d\n", arr[3]);
    printf("Value of arr[2]: %d\n", arr[2]);
    printf("Value of arr[1]: %d\n", arr[1]);
    printf("Value of arr[0]: %d\n", arr[0]);
    printf("Value of brr   : %d\n", brr);
    printf("Value of arp[3]: %d\n", arp[3]);
    printf("Value of arp[2]: %d\n", arp[2]);
    printf("Value of &brr  : %d\n", &brr  );
    printf("\n\n\n\n");

    printf("Value of arp[1]: %d\n", arp[1]);
    printf("Value of arp[0]: %d\n", arp[0]);


    // BLOCK C
    char *cp = NULL;
    char str[8] = "hello";
    str[5] = 'w';
    cp = str + 6;
    *cp = '\0';
    str[0] = 'y';
    // DRAW MEMORY HERE
}
