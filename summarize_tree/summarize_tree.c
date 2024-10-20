#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH_LEN 4096  // Increased max path length for safety

static int num_dirs, num_regular;

// Function prototypes
bool is_dir(const char* path);
void process_directory(const char* path);
void process_file(const char* path);
void process_path(const char* path);

// Function to check if a path is a directory
bool is_dir(const char* path) {
    struct stat buf;
    // Use stat() to get information about the file
    if (stat(path, &buf) != 0) {
        perror("stat");
        return false;
    }
    // Check if the file is a directory
    return S_ISDIR(buf.st_mode);
}

// Function to process directories recursively
void process_directory(const char* path) {
    DIR* dir = opendir(path);
    struct dirent* entry;

    if (!dir) {
        perror("opendir");
        return;
    }

    // Update the number of directories seen
    num_dirs++;

    // Loop through directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." entries to avoid infinite loops
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path for the current entry
        char full_path[MAX_PATH_LEN];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Process the entry's path
        process_path(full_path);
    }

    closedir(dir);
}

// Function to process regular files
void process_file(const char* path) {
    // Update the number of regular files
    num_regular++;
}

// Function to process paths (recursively called for directories)
void process_path(const char* path) {
    // Check if the path is a directory or file
    if (is_dir(path)) {
        process_directory(path);
    } else {
        process_file(path);
    }
}

int main(int argc, char *argv[]) {
    char abs_path[MAX_PATH_LEN];

    // Ensure an argument was provided
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        printf("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    // Get the absolute path of the initial directory
    if (realpath(argv[1], abs_path) == NULL) {
        perror("realpath");
        return 1;
    }

    // Initialize counters
    num_dirs = 0;
    num_regular = 0;

    // Start processing the specified path
    process_path(abs_path);

    // Print results
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
