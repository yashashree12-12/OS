#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0] for reading, fd[1] for writing
    pid_t pid;
    char buffer[100];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process – Producer
        close(fd[0]); // Close reading end

        char message[] = "Hello from Producer!";
        write(fd[1], message, strlen(message) + 1); // +1 to include null terminator
        printf("Producer: Sent message - %s\n", message);

        close(fd[1]); // Close writing end
    } else {
        // Child process – Consumer
        close(fd[1]); // Close writing end

        read(fd[0], buffer, sizeof(buffer));
        printf("Consumer: Received message - %s\n", buffer);

        close(fd[0]); // Close reading end
    }

    return 0;
}

// gcc producer_consumer_pipe.c -o pc_pipe
// ./pc_pipe
