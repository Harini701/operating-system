#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    char file_name[50];
    char buffer[BUFFER_SIZE];
    ssize_t num_bytes;

    printf("Enter the name of the file to create: ");
    scanf("%s", file_name);

    int file_descriptor = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        perror("Error creating the file");
        return 1;
    }

    printf("Enter data to write to the file (press Ctrl+D to finish):\n");
    while ((num_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        if (write(file_descriptor, buffer, num_bytes) != num_bytes) {
            perror("Error writing to the file");
            return 1;
        }
    }

    if (num_bytes == -1) {
        perror("Error reading input");
        return 1;
    }

    close(file_descriptor);

    file_descriptor = open(file_name, O_RDONLY);
    if (file_descriptor == -1) {
        perror("Error opening the file for reading");
        return 1;
    }

    printf("Data read from the file:\n");
    while ((num_bytes = read(file_descriptor, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, num_bytes) != num_bytes) {
            perror("Error writing to console");
            return 1;
        }
    }

    if (num_bytes == -1) {
        perror("Error reading file");
        return 1;
    }

    close(file_descriptor);

    return 0;
}

