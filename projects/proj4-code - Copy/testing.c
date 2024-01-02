#include <stdio.h>

typedef struct num {
    int number;
    int *number_pointer;
    struct num *next;

} num_t;


int main(){
    // int i = 9;
    // printf("%d\n", i);
    num_t temporary_next;
    temporary_next.number = 1;

    num_t temporary_next2;
    temporary_next2.number = 2;

    num_t testing;
    testing.number = 5;
    testing.number_pointer = testing.number;
    testing.next = &temporary_next;

    printf("testing\nnumber = %d\nnumber_pointer = %p\nnext num_t number = %d\n\n", testing.number, (void *)testing.number_pointer, testing.next->number);

    num_t *testing2;
    testing2 = &testing;
    testing2->number = 10;
    testing2->number_pointer = 15;
    testing2->next = &temporary_next2;

    printf("testing2 (which is a pointer)\nnumber = %d\nnumber_pointer = %p\nnext num_t number = %d\n\n", testing2->number, (void *)testing2->number_pointer, testing2->next->number);

    printf("testing\nnumber = %d\nnumber_pointer = %p\nnext num_t number = %d\n\n", testing.number, (void *)testing.number_pointer, testing.next->number);

    // num_t testing3;
    // testing3 = testing;
    // testing3 = &testing;

    // printf("testing\nnumber = %d\nnumber_pointer = %p\n\n", testing.number, (void *)testing.number_pointer);

}