#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

char guessChar(const char *guessedLetters) {

    char guess;

    guess = tolower(getchar());

    int c;

    while ((c = getchar()) != '\n' && c != EOF);

    if (!isalpha(guess)) {
        printf("\nPlease type a letter: ");
        return guessChar(guessedLetters);
    }

    for (int i = 0; i < strlen(guessedLetters); i++) {
        if (guessedLetters[i] == guess) {
            printf("You've already tried this one. Please type a different letter: ");
            return guessChar(guessedLetters);
        }
    }

    return guess;
}

void drawGui(const char *answer, const char *guessed, int index, int chances) {

    char dummy5[] = " O";
    char dummy4[] = " O\n |";
    char dummy3[] = " O\n/|";
    char dummy2[] = " O\n/|\\";
    char dummy1[] = " O\n/|\\\n/";
    char dummy0[] = " O\n/|\\\n/ \\";

    printf("\n\n");

    printf("Word: %s", answer);

    if (index > 0) {
        printf("Letters guessed: ");
        for (int i = 0; i < index; i++) {
            printf("%c", guessed[i]);
        }
    }

    printf("\n\nChances left: %d\n", chances);

    if (chances == 5) {
        printf("%s", dummy5);
    } else if (chances == 4) {
        printf("%s", dummy4);
    } else if (chances == 3) {
        printf("%s", dummy3);
    } else if (chances == 2) {
        printf("%s", dummy2);
    } else if (chances == 1) {
        printf("%s", dummy1);
    } else if (chances == 0) {
        printf("%s", dummy0);
    }

    printf("\n\n");

}

int game() {

    char *word = getWord();
    int length = strlen(word);
    char guessedLetters[length + 6];
    int indexGuessedLetters = 0;
    char guess;
    char answer[length];
    int right = 0;
    int win = 0;

    int chances = 6;

    for (int i = 0; i < length; i++) {
        if (word[i] == '-') {
            answer[i] == '-';
        } else {
            answer[i] = '_';
        }
    }

    answer[length] = '\0';

    if (word[1] == '-') {
        answer[1] = '-';
    }

    printf("answer: %s\n", word);

    while (chances > 0 || win != 1) {

        drawGui(answer, guessedLetters, indexGuessedLetters, chances);

        printf("Guess a letter: ");

        guess = guessChar(guessedLetters);
        guessedLetters[indexGuessedLetters] = guess;
        indexGuessedLetters++;

        for (int j = 0; j < length; j++) {
            if (guess == word[j]) {
                answer[j] = guess;
                right = 1; // indicate user got it right
            } else if (j == length - 1 && right == 0) { // check if for loop ended and guess is right
                chances--;
            }
        }

        for (int k = 0; k < length; k++) {
            if (answer[k] == '_') {
                break;
            } else if (k == length - 1) {
                win = 1;
            }
        }

        if (chances == 0) {
            printf("You lost. The answer was \"%s\".\n\n\n\n\n", word);
            break;
        } else if (win == 1) {
            printf("You won! Congratulations! Answer: %s\n\n\n\n\n", word);
            break;
        }

        right = 0;
    }


    free(word);

    menu();
}

int menu() {

    int exit = 0;
    char option;

    printf("\nChoose an option:\n");
    printf("1. Start new game.\n");
    printf("2. Leave.\n");

    scanf("%c", &option);

    getchar(); // to consume the newline character

    switch(option) {
        case '1':
            game();
            break;

        case '2':
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

