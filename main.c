#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int menu();

char *getWord() {

    FILE *file = fopen("words.txt", "r");
    char *word = (char*)malloc(32 * sizeof(char));
    int curLine = 0;

    if (word == NULL) {
        printf("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int line = rand() % 100;

    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(word, 32, file) != NULL) {

        if (word[strlen(word) - 1] == '\n') { // to remove the \n at the ending
            word[strlen(word) - 1] = '\0';
        }

        if (curLine == line) {
            break;
        }
        curLine++;
    }

    return word;

}

int game() {

    char *word = getWord();

    printf("The word is %s\n", word);

    menu();

}

int menu() {

    int exit = 0;
    int option;

    printf("\nChoose an option:\n");
    printf("1. Start new game.\n");
    printf("2. Leave.\n");

    scanf("%d", &option);

    switch(option) {
        case 1:
            game();
            break;

        case 2:
            printf("Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice.\n");
            menu();
    }

}

int main() {

    printf("Welcome to Hangman!\n");

    menu();

    return 0;
}

