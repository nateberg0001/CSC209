#include <stdio.h>
// Do not add any other header files

/* basename_inplace returns the file-name component of path. It is similar to
 * the library function described in the man pages on teach.cs (man 3 basename)
 * The return value of this function will be exactly the same as running the
 * system program "basename" with no additional arguments on the commandline 
 * on teach.cs, so you have a convenient way to test it
 *  - If path is "/" then return "/".
 *  - Return the component of path following the final '/'. Trailing '/' 
 *    characters are not counted as part of the pathname.
 *  - If path does not contain a slash, return path.
 *  - If path is a null pointer or points to an empty string, then 
 *    return ".".
 * 
 * Write this function without declaring any character arrays, or 
 * dynamically allocating memory. You may need to modify path.  
 * Do not use any string functions from string.h, not even strlen()
 *
 * Remember to run this program as "./basename" since there is a system
 * level program with the same name.
 */

char* basename_inplace(char* input){
    // base cases
    if(input == NULL || input[0]=='\0'){
        return ".";
    }
    if(input[0]=='/' && input[1]=='\0'){
        return "/";
    }
    // find last_slash
    int last_slash = -1;
    int slast_slash = -1;
    int index = 0;
    while(input[index]!='\0'){
        if(input[index]=='/'){
            slast_slash=last_slash;
            last_slash = index;
        }
        index++;
    }
    // if no slashes then return whole string
    if(last_slash==-1){
        return input;
    }
    // if last_slash is at the end, it is "trailing", and doesn't count
    if(input[last_slash+1]=='\0'){
        input[last_slash]='\0';
        last_slash=slast_slash;
    }
    // reassign important part to beginning of string
    index = 1;
    while(input[last_slash+index]!='\0'){
        input[index-1]=input[last_slash+index];
        index++;
    }
    input[index-1]=input[last_slash+index];
    return input;
}

int main(int argc, char **argv) {

    if(argc != 2) {
        fprintf(stderr, "Usage: basename <path>\n");
        return 1;
    }

    printf("%s\n", basename_inplace(argv[1]));

    return 0;
}
