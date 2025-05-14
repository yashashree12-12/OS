// B.Count number of vowels in the given sentence implement program using vfork().

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char sentence[100];
    int count = 0;
    
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    pid_t pid = vfork();  // use vfork

    if (pid < 0) {
        perror("vfork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child: count vowels
        for (int i = 0; sentence[i] != '\0'; i++) {
            char c = sentence[i];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                count++;
            }
        }
        printf("Child process: Number of vowels = %d\n", count);
        _exit(0);  // use _exit with vfork
    }
    else {
        // Parent waits passively
        wait(NULL);
        printf("Parent process: Child finished execution.\n");
    }

    return 0;
}

// gcc vfork_vowel.c -o vfork_vowel
// ./vfork_vowel
