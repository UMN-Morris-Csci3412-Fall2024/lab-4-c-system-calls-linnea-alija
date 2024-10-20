#include <stdio.h>
#include <ftw.h>
#include <stdbool.h>

static int num_dirs = 0;
static int num_regular = 0;

// Callback function for ftw()
static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_D) {
        // Increment directory count if it's a directory
        num_dirs++;
    } else if (typeflag == FTW_F) {
        // Increment regular file count if it's a file
        num_regular++;
    }
    return 0; // Continue the traversal
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    // Use ftw() to traverse the file tree
    if (ftw(argv[1], callback, 16) == -1) {
        perror("ftw");
        return 1;
    }

    // Print results
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
