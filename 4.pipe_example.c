#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];  // fd[0] = read end, fd[1] = write end
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(fd[1]); // Close unused write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]); // Close unused read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
    }

    return 0;
}

// How to Compile and Run (on Linux or WSL):
// Save as: pipe_example.c

// Open terminal and compile:

// bash
// Copy code
// gcc pipe_example.c -o pipe_example
// Run the program:

// bash
// Copy code
// ./pipe_example
// ✅ Sample Output:
// csharp
// Copy code
// Child received: Hello from parent!
// 📌 What This Code Does:
// Creates a pipe using pipe(fd).

// Parent writes a message to the pipe.

// Child reads from the pipe and prints the message.

