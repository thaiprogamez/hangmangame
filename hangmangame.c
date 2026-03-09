#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// Function to draw the hangman based on incorrect guesses
void hangmandraw(int incorrectguess) {
    printf(" +---+\n");
    printf(" |   |\n");
    if (incorrectguess >= 1) {
        printf(" O   |\n");
    } else {
        printf("     |\n");
    }
    if (incorrectguess >= 2) {
        printf(" |   |\n");
    } else {
        printf("     |\n");
    }
    if (incorrectguess >= 3) {
        printf(" |   |\n");
    } 
    if (incorrectguess >= 4) {
        printf("/|\\  |\n");
    } else {
        printf("     |\n");
    }
    if (incorrectguess >= 5) {
        printf(" |   |\n");
    } 
    if (incorrectguess >= 6) {
        printf(" |   |\n");
    } 
    if (incorrectguess >=7) {
        printf("/|\\  |\n");  
    } else {
        printf("     |\n");
    }
    printf("=======\n");
}

int main() {
    // 1. Word bank

    const char *wordlist[] = {
        "programming",
        "keyboard",
        "computer",
        "artificial intelligence",
        "operating system",
        "tablet",
        "smartphone",
        "architecture",
        "array",
        "earphone",
        "memory",
        "server",
        "devops",
        "engineer",
        "software",
        "graphics",
        "application",
        "network",
        "system on chip",
        "cable",
        "charger",
        "windows",
        "macos",
        "ios",
        "android",
        "linux",
        "discrete",
        "library",
        "python",
        "ruby on rails",
        "java",
        "unix",
        "central processing unit",
        "graphical processing unit",
        "image signalling processor",
        "modem",
        "router",
        "semiconductor",
    };
    int totalword=sizeof(wordlist)/sizeof(wordlist[0]);
    srand(time(NULL));
    int randomindex=rand() % totalword;
    const char *secretword = wordlist[randomindex];
    int wordlength = strlen(secretword);
    
    // Fix 1: Allocate enough space for hidden word (use wordlength + 1)
    // Changed from fixed 20 to wordlength + 1 to handle longest word
    char hiddenword[30];  // Fixed size array - large enough for longest word
    
    // Fix 2: Initialize hidden word display - reveal spaces automatically
    for (int i = 0; i < wordlength; i++) {
        if (secretword[i] == ' ') {
            hiddenword[i] = ' ';  // Show spaces automatically
        } else {
            hiddenword[i] = '_';
        }
    }
    hiddenword[wordlength] = '\0';
    
    char guess;
    int incorrectguess = 0;
    // Fix 3: Changed max incorrect guesses from 4 to 6 to match hangman drawing
    int maxincorrectguess = 7;
    int gameover = 0;
    int haswon = 0;  // Track if player has won
    
    // 4. Game loop
    while (incorrectguess < maxincorrectguess && !gameover) {
        // Display current state
        hangmandraw(incorrectguess);
        printf("Welcome to the hangman game! In this game, you have to guess the correct word related to technological terms. \nYou have a limited amount of lives. If you can't guess the correct word, you lose the game. \n");
        printf("The hidden word is: %s\n", hiddenword);
        printf("Incorrect guesses: %d/%d\n", incorrectguess, maxincorrectguess);
        printf("Enter your guess: ");
        scanf(" %c", &guess);
        guess = tolower(guess);
        
        // Check if letter is in word
        int found = 0;
        for (int i = 0; i < wordlength; i++) {
            if (secretword[i] == guess) {
                hiddenword[i] = guess;
                found = 1;
            }
        }
        
        // Update display or reduce lives
        if (!found) {
            incorrectguess++;
            printf("Sorry, '%c' is not in the word!\n", guess);
        } else {
            printf("Good job! '%c' is in the word!\n", guess);
        }
        
        // Check win condition - all non-space letters must be revealed
        haswon = 1;
        for (int i = 0; i < wordlength; i++) {
            if (secretword[i] != ' ' && hiddenword[i] == '_') {
                haswon = 0;        // Still has hidden letters
                break;
            }
        }

        if (haswon) {
            gameover = 1;
        }
    }
    
    // 5. End game message - Display final hangman
    hangmandraw(incorrectguess);
    
    // Fix 4: Use haswon variable instead of strcmp for win check
    if (haswon) {
        printf("Word: %s\n", hiddenword);
        printf("Congratulations, you won this round!\n");
    } else {
        printf("You lost the game!\n");
        printf("The word was: %s\n", secretword);
    }
    
    // 6. Replay option (could be added here)
    return 0;
}
