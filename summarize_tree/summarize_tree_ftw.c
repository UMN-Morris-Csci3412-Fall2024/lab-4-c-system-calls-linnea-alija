#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH_LEN 4096

static int num_dirs = 0, num_regular = 0;

bool is_dir(const char* path) {
    struct stat buf;
    if (stat(path, &buf) != 0) {
        perror("stat");
        return false;
    }
    return S_ISDIR(buf.st_mode);
}

void process_directory(const char* path) {
    DIR* dir = opendir(path);
    struct dirent* entry;

    if (!dir) {
        perror("opendir");
        return;
    }

    num_dirs++;  // Count the directory

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[MAX_PATH_LEN];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (is_dir(full_path)) {
            process_directory(full_path);
        } else {
            num_regular++;
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    if (!is_dir(argv[1])) {
        printf("Error: %s is not a directory.\n", argv[1]);
        return 1;
    }

    num_dirs = -1;  // Exclude the base directory
    num_regular = 0;

    process_directory(argv[1]);

    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
