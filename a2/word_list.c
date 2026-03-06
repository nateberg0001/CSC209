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
    int count = 0;
    int i = 0;
    while(word_list[i]!=NULL){
        if(strlen(word_list[i])==len){
            count++;
        }
        i++;
    }
    char **new_wordlist = malloc(sizeof(char*)*(count+1));
    new_wordlist[0]=NULL;
    int new_count = 0;
    i = 0;
    while(word_list[i]!=NULL){
        if(strlen(word_list[i])==len){
            new_wordlist[new_count]=word_list[i];
            new_count++;
        }
        i++;
    }
    new_wordlist[count]=NULL;
    return new_wordlist;
}


/* Free memory acquired by prune_word_list.
*/
void deallocate_pruned_word_list(char **word_list) {
    int i = 0;
    while(word_list[i]!=NULL){
        free(word_list[i]);
        i++;
    }
    free(word_list);
}
