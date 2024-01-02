#include <stdio.h>
#include <string.h>

void string_copy_index_notation(char *dst, char *src){
    int index = 0;
    while (src[index] != '\0'){
        dst[index] = src[index];
        index++;
    }
    dst[index] = '\0';
}

void string_copy_pointer_arithmetic(char *dst, char *src){
    while (*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    dst = '\0';
}

int main(){
    char *ori = "move by indexing";
    char copy[strlen(ori) + 1];

    string_copy_index_notation(copy, ori);
    printf("ori: %s\n", ori);
    printf("ori: %s\n", copy);

    char *ori2 = "move by pointer";
    char copy2[strlen(ori2) + 1];

    string_copy_pointer_arithmetic(copy2, ori2);
    printf("ori: %s\n", ori2);
    printf("ori: %s\n", copy2);
}