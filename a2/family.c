#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "family.h"

/* Number of word pointers allocated for a new family.
   This is also the number of word pointers added to a family
   using realloc, when the family is full.
*/
static int family_increment = 0;


/* Set family_increment to size, and initialize random number generator.
   The random number generator is used to select a random word from a family.
   This function should be called exactly once, on startup.
*/
void init_family(int size) {
    family_increment = size;
    srand(time(NULL));
}

char *get_sig(char* word,char letter, int size){
    char* sig = malloc(sizeof(char)*(size+1));
    for(int i = 0; i<size; i++){
        if(word[i]==letter){
            sig[i]=letter;
        }
        else{
            sig[i]='_';
        }
    }
    sig[size]='\0';
    return sig;
}

/* Given a pointer to the head of a linked list of Family nodes,
   print each family's signature and words.

   Do not modify this function. It will be used for marking.
   You may find it useful for testing.
*/
void print_families(Family* fam_list) {
    int i;
    Family *fam = fam_list;
    
    while (fam) {
        printf("***Family signature: %s Num words: %d\n",
               fam->signature, fam->num_words);
        for(i = 0; i < fam->num_words; i++) {
            printf("     %s\n", fam->word_ptrs[i]);
        }
        printf("\n");
        fam = fam->next;
    }
}


/* Return a pointer to a new family whose signature is 
   a copy of str, and whose fields are initialized as follows:
      - word_ptrs points to family_increment+1 pointers, 
      - numwords is 0, 
      - maxwords is family_increment, 
      - next is NULL.
*/
Family *new_family(char *str) {
    char **the_word_ptrs = malloc(sizeof(char*)*(family_increment+1));
    for(int i = 0; i<family_increment+1; i++){
        the_word_ptrs[i]=NULL;
    }
    char *copy = malloc(strlen(str) + 1);
    strcpy(copy, str);
    Family *new_family = malloc(sizeof(Family));
    new_family -> signature = copy;
    new_family -> word_ptrs = the_word_ptrs;
    new_family -> num_words = 0;
    new_family -> max_words = family_increment;
    new_family -> next = NULL;
    return new_family;
}


/* Add word to the next free slot in fam->word_ptrs.
   If fam->word_ptrs is full, first use realloc to allocate family_increment
   more pointers and then add the new pointer.
*/
void add_word_to_family(Family *fam, char *word) {
    int i = 0;
    while(fam->word_ptrs[i]!=NULL){
        i++;
    }
    fam->num_words++;
    fam->word_ptrs[i]=word;
    if(fam->num_words >= fam->max_words){
        printf("reallocating!!! num_words is %d \n", fam->num_words);
        fam->word_ptrs = realloc(fam->word_ptrs,sizeof(char*)*(family_increment+fam->max_words));
        fam->max_words = fam->max_words + family_increment;
        for(int j=i+1;j<fam->max_words;j++){
            fam->word_ptrs[j]=NULL;
        }
    }
    return;
}


/* Return a pointer to the family whose signature is sig;
   if there is no such family, return NULL.
   fam_list is a pointer to the head of a list of Family nodes.
*/
Family *find_family(Family *fam_list, char *sig) {
    while(fam_list!=NULL){
        if(strcmp(fam_list->signature, sig)==0){
            return fam_list;
        }
        fam_list = fam_list->next;
    }
    return NULL;
}


/* Return a pointer to the family in the list with the most words;
   if the list is empty, return NULL. If multiple families have the most words,
   return a pointer to any of them.
   fam_list is a pointer to the head of a list of Family nodes.
*/
Family *find_biggest_family(Family *fam_list){
    int max = 0;
    Family *max_family = NULL;
    while(fam_list!=NULL){
        if(fam_list->num_words >= max){
            max_family = fam_list;
            max = fam_list-> num_words;
        }
        fam_list = fam_list->next;
    }
    return max_family;
}


/* Deallocate all memory rooted in the List pointed to by fam_list. */
void deallocate_families(Family *fam_list) {
    while(fam_list!=NULL){
        free(fam_list->word_ptrs);
        free(fam_list->signature);
        fam_list=fam_list->next;
    }
    return;
}


/* Generate and return a linked list of all families using words pointed to
   by word_list, using letter to partition the words.

   Implementation tips: To decide the family in which each word belongs, you
   will need to generate the signature of each word. Create only the families
   that have at least one word from the current word_list.
*/
Family *generate_families(char **word_list, char letter) {
    // Generate signatures
    int len = strlen(word_list[0]);
    printf("size is %d", len);
    char** sigs = malloc(sizeof(char*)*(500));
    for(int i = 0; i<500; i++){
        sigs[i]=NULL;
    }
    int l = 0;
    while(word_list[l]!=NULL){
        char *sig = get_sig(word_list[l],letter,len);
        int k = 0;
        while(sigs[k]!=NULL && strcmp(sigs[k],sig)!=0){
            k++;
        }
        if(sigs[k]==NULL){
            sigs[k]=sig;
        }
        else if(strcmp(sigs[k],sig)==0){
            free(sig);
        }
        l++;
    }

    // Create empty families for each signature
    Family *head_family = new_family(sigs[0]);
    Family *previous_family = head_family;
    int k = 1;
    while(sigs[k]!=NULL){
        Family *current_family = new_family(sigs[k]);
        previous_family -> next = current_family;
        previous_family = current_family;
        k++;
    }

    // Iterate through words, adding to correct families
    l = 0;
    while(word_list[l]!=NULL){
        add_word_to_family(find_family(head_family,get_sig(word_list[l],letter,len)),word_list[l]);
        l++;
    }

    // Memory Cleanup
    while(sigs[k]!=NULL){
        free(sigs[k]);
        k++;
    }
    free(sigs);

    return head_family;
}


/* Return the signature of the family pointed to by fam. */
char *get_family_signature(Family *fam) {
    return fam->signature;
}


/* Return a pointer to an array of word pointers, each of which
   points to a word in fam. These pointers should not be the same
   as those used by fam->word_ptrs (i.e. they should be independently malloc'd),
   because fam->word_ptrs can move during a realloc.
   As with fam->word_ptrs, the final pointer should be NULL.
*/
char **get_new_word_list(Family *fam) {
    char **new_wordlist = malloc(sizeof(char*)*(fam->num_words+1));
    for(int i=0; i<fam->num_words; i++){
        new_wordlist[i] = malloc(sizeof(char)*(strlen(fam->word_ptrs[i])+1));
        strcpy(new_wordlist[i],fam->word_ptrs[i]);
    }
    new_wordlist[fam->num_words]=NULL;
    return new_wordlist;
}


/* Return a pointer to a random word from fam. 
   Use rand (man 3 rand) to generate random integers.
*/
char *get_random_word_from_family(Family *fam){
    int random = rand() % (fam->num_words);
    return fam->word_ptrs[random];
}


