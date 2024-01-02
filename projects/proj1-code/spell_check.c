#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

#define MAX_CMD_LEN 128

// A helper function to spell check a specific file
// 'file_name': Name of the file to spell check
// 'dict': A dictionary containing correct words
int spell_check_file(const char *file_name, const dictionary_t *dict) {
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL){
        return -1; // fail to open file
    }

    char curr; //input line
    char word[127]; // word to check
    int word_index = 0; // wordindex

    while((curr = fgetc(input_file)) != EOF){
        if (isalpha(curr)) {
            word[word_index++] = curr;
        } else {
            if (word != 0){
                word[word_index] = '\0';
                if(dict_find(dict, word) != 1){
                    printf("%s[X]", word);
                } else {
                    printf("%s", word);
                }

                // clearing the previous word memory
                int x = 0;
                while (word[x] != '\0'){
                    word[x++] = 0;
                }
                word[x] = 0;
                word_index = 0;
            }
            printf("%c", curr);
        }
    }

    fclose(input_file);
    return 1; // success
}

int main(int argc, char **argv) {
    dictionary_t *dict = NULL;
    char cmd[MAX_CMD_LEN];

    if (argc >= 2){
        FILE *file = fopen(argv[1], "r");
        if (file == NULL){ // if fail to open
            printf("Failed to read dictionary from text file\n");
            // fclose(file); // if file fail to open, there is no need to close it or else i think itll cause seg error
            return 0;
        } else { // create a dictionary
            dict = read_dict_from_text_file(argv[1]);        
            if (dict != NULL){
                printf("Dictionary successfully read from text file\n");
            } else {
                printf("Failed to read dictionary from text file\n");
                fclose(file);
                return 0;
            }
        }
        if (argc >= 3){
            FILE *file2 = fopen(argv[2], "r");
            if (file2 == NULL){
                printf("Spell check failed\n");
                fclose(file);
                // fclose(file2); // if file fail to open, there is no need to close it or else it will cause seg error
                dict_free(dict);
                return 0;
            }
            int out = spell_check_file(argv[2], dict);
            if (out != 1){ // fail
                printf("Spell check failed\n");
            } 
            fclose(file);
            fclose(file2);
            dict_free(dict); // spell_check pass or not, the programme will end. thus, all memory malloc-ed must be returned
            return 0;
        }
        // fclose(file);
    }

    char word[127];

    printf("CSCI 2021 Spell Check System\n");
    printf("Commands:\n");
    printf("  add <word>:              adds a new word to dictionary\n");
    printf("  lookup <word>:           searches for a word\n");
    printf("  print:                   shows all words currently in the dictionary\n");
    printf("  load <file_name>:        reads in dictionary from a file\n");
    printf("  save <file_name>:        writes dictionary to a file\n");
    printf("  check <file_name>: spell checks the specified file\n");
    printf("  exit:                    exits the program\n");

    while (1) {
        printf("spell_check> ");
        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        if (strcmp("exit", cmd) == 0) {
            break;
        }

        else if (strcmp("add", cmd) == 0) {
            scanf("%s", word);
            word[strlen(word)] = '\0';

            if (dict == NULL){
                dict = create_dictionary();
            }
            dict_insert(dict, word);
        }

        else if (strcmp("lookup", cmd) == 0) {
            // length = 127 - 6;
            scanf("%s", word);
            // word[127] = '\0';
            int out = dict_find(dict, word);
            if (out == 1){
                printf("\'%s\' present in dictionary\n", word);
            } else {
                printf("\'%s\' not found\n", word);
            }
        }

        else if (strcmp("print", cmd) == 0) {
            dict_print(dict);
        }

        else if (strcmp("load", cmd) == 0) {
            scanf("%s", word);
            dict_free(dict);
            dict = read_dict_from_text_file(word);

            if (dict == NULL){
                printf("Failed to read dictionary from text file\n");
            } else {
                printf("Dictionary successfully read from text file\n");
            }
        }

        else if (strcmp("save", cmd) == 0) {
            scanf("%s", word);
            int out = write_dict_to_text_file(dict, word);

            if (out == 0){
                printf("Dictionary successfully written to text file\n");
            } else {
                printf("Failed to write dictionary to text file\n");
            }
        }

        else if (strcmp("check", cmd) == 0) {
            scanf("%s", word);
            int out = spell_check_file(word, dict);

            if (out == -1){
                printf("Spell check failed\n");
            }
        }

        else {
            printf("Unknown command %s\n", cmd);
        }
    }

    dict_free(dict);
    return 0;
}
