#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[20];
    float salary;
} EmployeeRecord;

int main() {
    // Open binary file with owner-only Read/Write access (0600)
    int fd = open("database.dat", O_CREAT | O_RDWR | O_TRUNC, 0600);
    if (fd < 0) {
        perror("Failed to open database file");
        return EXIT_FAILURE;
    }

    EmployeeRecord record1 = {101, "Alice", 55000.0f};
    EmployeeRecord record2 = {102, "Bob",   62000.0f};

    write(fd, &record1, sizeof(EmployeeRecord));
    write(fd, &record2, sizeof(EmployeeRecord));
    printf("Initial database entries committed.\n");

    // Seek directly to record 2 (Index 1) for update
    off_t target_offset = sizeof(EmployeeRecord) * 1;
    lseek(fd, target_offset, SEEK_SET);

    EmployeeRecord record2_updated = {102, "Bob", 68000.0f};
    write(fd, &record2_updated, sizeof(EmployeeRecord));
    printf("Record ID 102 updated via seek offset.\n");

    // Reset cursor to read back initial entry
    lseek(fd, 0, SEEK_SET);

    EmployeeRecord read_buffer;
    read(fd, &read_buffer, sizeof(EmployeeRecord));
    printf("Read Back Record [ID: %d | Name: %s | Salary: %.2f]\n", 
            read_buffer.id, read_buffer.name, read_buffer.salary);

    close(fd);
    return EXIT_SUCCESS;
}