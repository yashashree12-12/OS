#include <fcntl.h>     // for open()
#include <unistd.h>    // for read(), write(), close()
#include <stdio.h>     // for printf(), perror()
#include <string.h>    // for strlen()
 
int main() {
    int fd;
    char buffer[100] = {0};
 
    // 1. Create or open file for writing (truncate if exists)
    fd = open("demo.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open (write)");
        return 1;
    }
 
    // 2. Write to file
    const char *initialText = "Hello, File Handling!\n";
    write(fd, initialText, strlen(initialText));
    close(fd);
 
    // 3. Open file in append mode
    fd = open("demo.txt", O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("open (append)");
        return 1;
    }
 
    // 4. Append to the file
    const char *appendText = "This is appended text.\n";
    write(fd, appendText, strlen(appendText));
    close(fd);
 
    // 5. Open file for reading
    fd = open("demo.txt", O_RDONLY);
    if (fd < 0) {
        perror("open (read)");
        return 1;
    }
 
    // 6. Read file content
    read(fd, buffer, sizeof(buffer));
    printf("Final File Content:\n%s", buffer);
    close(fd);
 
    return 0;
}