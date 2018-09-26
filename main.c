#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAJOR 2
#define MINOR 0

// notes: in v 2.0 there is no more the limit of a 25 chars message

// algorithm for the Caesar cipher
void cipher(char *str, long int key, unsigned int length) {
    int i, shift;
    for (i = 0; i < length; i++) {
        shift = str[i] + key;
        if (shift > 122)
            // if the shifted char goes beyond 'z', start from 'a' again
            str[i] = 96 + (key - (122 - str[i]));
        else if (shift < 97)
            // if the shifted char goes beyond 'a', go to 'z'
            str[i] = 123 + (key + (str[i] - 97));
        else
            str[i] = shift;   
    }
}

void usage() {
    // documentation
    printf(
    "caesarcipher written in C by drvladbancila\n"
    "https://github.com/drvladbancila\n\n"
    "Usage: caesar <option> <text> <key>\n\n"
    "Options:\n" 
    "   -e      encryption mode\n"
    "   -d      decryption mode\n"
    "   -v      version\n\n"
    "EVERY CHARACTER HAS TO BE LOWERCASE\n\n"
    "Example: caesar -e hello 5\n");
      
}

int main(int argc, char *argv[]) {

    char *message;
    long int key;
    unsigned int strDim;
    int mode;

    if(argc < 2) {
        usage();
        return EXIT_SUCCESS;
    }

    if(!strcmp(argv[1], "-e") && argc > 3) {
        // encryption mode
        mode = 0;
    } else if(!strcmp(argv[1], "-d") && argc > 3) {
        // decryption mode
        mode = 1;
    } else if(!strcmp(argv[1], "-v")) {
        printf("caesarcipher v%d.%d\n", 
        MAJOR, MINOR); // shows info
        return EXIT_SUCCESS;
    } else {
        usage();
        return EXIT_SUCCESS;
    }

    key = (strtol(argv[3], &argv[3], 10)) % 26; // take the third arg as a key
    strDim = strlen(argv[2]);
    message = (char *)malloc(sizeof(char) * strDim);
    strcpy(message, argv[2]);
    if (mode) {
        key = -key;
    }
    cipher(message, key, strDim);
    puts(message);

    free(message);

    return(EXIT_SUCCESS);
}
