#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024

bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    



    /*
     * Copy all the non-vowels from in_buf to out_buf.
     * num_chars indicates how many characters are in in_buf,
     * and this function should return the number of non-vowels that
     * that were copied over.
     */
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    FILE *filePointer;

    filePointer = fopen(inputFile, "r");

    if (!filePointer) {
        printf("Error opening file.\n");
        return 1;
    }

    // Move the file pointer to the end of the file to get the size
    fseek(filePointer, 0, SEEK_END);
    long fileSize = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET); // Reset file pointer to the beginning

    char buffer[fileSize + 1];  //not sure if +1 is corrent here, need to test later

    size_t bytesRead = fread(buffer, 1, fileSize, filePointer);

    buffer[bytesRead] = '\0'; 

    int new_len = 0;
    int num_chars = bytesRead;

    // First, count how many non-vowel characters there are
    for (int i = 0; i < num_chars; i++) {
        if (!is_vowel(buffer[i])) {
            new_len++;
        }
    }

    char out_buff[new_len]; //may need +1 here

    int num_copied = copy_non_vowels(num_chars, buffer, out_buff);



    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out.
     */
}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    return 0;
}