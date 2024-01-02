#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

dictionary_t *create_dictionary() {
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    if (dict == NULL) {
        return NULL;
    }
    dict->root = NULL;
    dict->size = 0;
    return dict;
}

int dict_insert_node(node_t *curr, const char *word, node_t *new_node){
    int cmp;
    if (curr->word != NULL){
        cmp = strcmp(curr->word, word);
    }

    if (cmp == 0){ //the word already exists in the dict, no duplicated words in dict
            return -1;
    } else if (cmp == 1){ //go left
        if (curr->left != NULL){
            dict_insert_node(curr->left, word, new_node);
        } else{
            curr->left = new_node;
        }
        
    } else { //go right
        if (curr->right != NULL){
            dict_insert_node(curr->right, word, new_node);
        } else{
            curr->right = new_node;
        }
    }

    return 0;
}

int dict_insert(dictionary_t *dict, const char *word) {
    if (dict->root == NULL){
        dict->root = malloc(sizeof(node_t));
        if (dict->root == NULL){
            return -1; //fail to allocate memory for node_t
        }
        strcpy(dict->root->word, word);
        dict->root->left = NULL;
        dict->root->right = NULL;
        dict->size++;

        return 0;
    }else{

        node_t *new_node = malloc(sizeof(node_t));
        if (new_node == NULL){
            return -1; //fail to allocate memory
        }
        strcpy(new_node->word, word);
        new_node->left = NULL;
        new_node->right = NULL;

        int out = dict_insert_node(dict->root, word, new_node);

        if (out == -1){
            free(new_node);
            return -1;
        } else {
            dict->size++;
            return 0;
        }
    }
    // return 0;
}

int dict_find(const dictionary_t *dict, const char *query) {
    if (dict == NULL){
        return 0;
    }
    
    node_t *curr = dict->root;
    int cmp;

    while (curr->word != NULL) {
        cmp = strcmp(curr->word, query);

        if (cmp == 0){ // found the word
            return 1;
        } else if (cmp == 1){ //go left
            curr = curr->left;
        } else { //go right
            curr = curr->right;
        }
    }
    return 0;   
}

void dict_print_node(node_t *curr){   // do left, up, right
    if (curr != NULL){
        dict_print_node(curr->left);
        printf("%s\n", curr->word);
        dict_print_node(curr->right);
    }
}

void dict_print(const dictionary_t *dict) {  
    if (dict == NULL){
        return ;
    }
    dict_print_node(dict->root);
}

void dict_free_node(node_t *curr) {
    if (curr != NULL){
        dict_free_node(curr->left);
        dict_free_node(curr->right);
        free(curr);
    }
}

void dict_free(dictionary_t *dict) { 
    if (dict == NULL || dict->root == NULL){
        return ;
    }

    dict_free_node(dict->root);
    free(dict);
}

dictionary_t *read_dict_from_text_file(const char *file_name) { 
    FILE *file = fopen(file_name, "r");
    if (file == NULL){
        return NULL;
    }
    dictionary_t *out = create_dictionary();
    if (out == NULL){
        return NULL;
    }

    char word[127];
    while (fscanf(file, "%127s", word) == 1){
        dict_insert(out, word);
    }

    fclose(file);
    return out;
}

int write_file_helper(node_t *curr, FILE *file){
    if (curr == 0){
        return 0;
    } else {
        // printf("testing");

        fprintf(file, "%s\n", curr->word);

        if (curr->left != NULL){
            write_file_helper(curr->left, file);
        }
        if (curr->right != NULL){
            write_file_helper(curr->right, file);
        }
    } 
    return 0;
}

int write_dict_to_text_file(const dictionary_t *dict, const char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        return -1;
    }

    int result = write_file_helper(dict->root, file);
    fclose(file);

    return result;
}
