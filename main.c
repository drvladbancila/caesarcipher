/*
#########################CAESAR CIPHER v1.0##################################
#                                                                           #
#    This program is free software: you can redistribute it and/or modify   #
#    it under the terms of the GNU General Public License as published by   #
#    the Free Software Foundation, either version 3 of the License, or      #
#    (at your option) any later version.                                    #
#                                                                           #
#    This program is distributed in the hope that it will be useful,        #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of         #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          #
#    GNU General Public License for more details.                           #
#                                                                           #
#    You should have received a copy of the GNU General Public License      #
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.  #
#                                                                           # 
#############################################################################
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VERSION 1.0
#define SIZE 25     // max size of the message

// global variables
char plainText[SIZE];
char encryptedText[SIZE];
int key;

// algorithm for the Caesar cipher
void cipher() {
    int i, shift;
    int length = strlen(plainText);
    for(i = 0; i < length; i++) {
        shift = plainText[i] + key;
        if (shift > 122)
            // if the shifted char goes beyond 'z', start from 'a' again
            encryptedText[i] = 96 + (key - (122 - plainText[i]));
        else if (shift < 97)
            // if the shifted char goes beyond 'a', go to 'z'
            encryptedText[i] = 123 + (key + (plainText[i] - 97));
        else
            encryptedText[i] = shift;   
    }
}

void help() {
    // documentation
    printf(
    "Caesar cipher written in C by Vlad Bancila\n\n"
    "Usage: caesar <option> <text> <key>\n\n"
    "Options:\n" 
    "   -e      encryption mode\n"
    "   -d      decryption mode\n"
    "   -v      version\n\n"
    "EVERY CHARACTER HAS TO BE LOWERCASE\n\n"
    "Example: caesar -e hello 5\n");
      
}

void checkParameters(int k, char l[]) {
    // check if the parameters are acceptable in order to prevent bugs and buffer overflows
    if (k < 0 || k > 26) {
        printf("ERROR: the key must be a value between 1 and 26\n");
        exit(0);
    }
    if (strlen(l) > SIZE) {
        printf("ERROR: the message can't be more than 25 characters long\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    
    if(argc < 2) {
        help();
        exit(0);
    }

    if((strcmp(argv[1], "-e") == 0) && (argc > 2)) {
        // encryption mode
        key = atoi(argv[3]);
        strcpy(plainText, argv[2]);
        checkParameters(key, plainText);
        cipher();
        printf("%s\n", encryptedText); // prints the result
    } else if((strcmp(argv[1], "-d") == 0) && (argc > 2)) {
        // decryption mode
        // which is basically an encryption with key = - key
        key = atoi(argv[3]);
        strcpy(plainText, argv[2]);
        checkParameters(key, plainText);
        key = -key;
        cipher();
        printf("%s\n", encryptedText); // prints the result
    } else if(strcmp(argv[1], "-v") == 0) {
        printf("Caesar cipher by Vlad Bancila. Version %f\n", VERSION); // shows info
    } else {
        help();
    }

    return(EXIT_SUCCESS);
}
