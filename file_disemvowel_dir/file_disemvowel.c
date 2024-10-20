#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SIZE 1024

// Function to check if a character is a vowel (case-insensitive)
bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// Function to copy non-vowel characters from in_buf to out_buf
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    int j = 0; // Index for out_buf
    for (int i = 0; i < num_chars; i++) {
        if (!is_vowel(in_buf[i])) {
            out_buf[j++] = in_buf[i]; // Copy non-vowel character
        }
    }
    return j; // Return the number of non-vowels copied
}

// Function to disemvowel the contents of inputFile and write to outputFile
void disemvowel(FILE* inputFile, FILE* outputFile) {
    char in_buf[BUF_SIZE];
    char out_buf[BUF_SIZE];
    size_t num_read, num_written;

    // Read input in chunks of BUF_SIZE
    while ((num_read = fread(in_buf, 1, BUF_SIZE, inputFile)) > 0) {
        // Copy non-vowels to out_buf
        int num_non_vowels = copy_non_vowels(num_read, in_buf, out_buf);
        // Write non-vowels to outputFile
        num_written = fwrite(out_buf, 1, num_non_vowels, outputFile);
        if (num_written < num_non_vowels) {
            fprintf(stderr, "Error writing to output file.\n");
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    // Handle command-line arguments
    if (argc > 1) {
        // Open input file specified by the first argument
        inputFile = fopen(argv[1], "r");
        if (!inputFile) {
            fprintf(stderr, "Error opening input file: %s\n", argv[1]);
            return 1;
        }
    }

    if (argc > 2) {
        // Open output file specified by the second argument
        outputFile = fopen(argv[2], "w");
        if (!outputFile) {
            fprintf(stderr, "Error opening output file: %s\n", argv[2]);
            fclose(inputFile); // Close the input file if open
            return 1;
        }
    }

    // Perform disemvowel operation
    disemvowel(inputFile, outputFile);

    // Close files
    if (inputFile != stdin) fclose(inputFile);
    if (outputFile != stdout) fclose(outputFile);

    return 0;
}
