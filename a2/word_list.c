#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_list.h"


/* Starting with words (returned by read_words), generate and return
   a new word list with only those words of length len. 

   Allocate exactly enough memory to store only those words of length len.

   Note: Do not make copies of the words.
*/
char **prune_word_list(char **word_list, int len) {
    // TODO: complete this function, replacing the return statement
    int count = 0;
    int i = 0;
    while(word_list[i]!=NULL){
        if(strlen(word_list[i])==len){
            if(count==0){
                printf("word is %s \n", word_list[i]);
                printf("word length however is %ld", strlen(word_list[i]));
                for (int j = 0; word_list[i][j] != '\0'; j++) {
                    printf("%d ", word_list[i][j]);
                }
                printf("\n");
            }
            count++;
        }
        i++;
    }
    char **new_wordlist = malloc(sizeof(char*)*count);
    count = 0;
    i = 0;
    while(word_list[i]!=NULL){
        if(strlen(word_list[i])==len){
            new_wordlist[count]=word_list[i];
            count++;
        }
        i++;
    }
    return new_wordlist;
}


/* Free memory acquired by prune_word_list.
*/
void deallocate_pruned_word_list(char **word_list) {
    free(word_list);
}
