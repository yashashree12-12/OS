#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if(pid == 0)
    {
        printf("Child process: Running 'ls -l'\n");
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl failed");
    }
    else
    {
        printf("Parent process: waiting for child to complete...\n");
        wait(NULL);
        printf("Parent process: child finished.\n");
    }

    return 0;
}
