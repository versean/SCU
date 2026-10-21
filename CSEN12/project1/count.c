/*
count.c
Sean Cajigal
September 25, 2025
This C program will count the number of words inside a file (path passed as an argument).
*/

#include <stdio.h>

int main(int argc, char* argv[])
{
    // Check argument validity
    if (argc != 2) 
    {
        printf("Usage: ./a.out </file/path.txt>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    // Check if the file exists before continuing.
    if (!file)
    {
        printf("File cannot be found.\n");
        return 1;
    } 
    
    // Variable intialization 
    int MAX_WORD_LENGTH = 30;
    char nextWord[MAX_WORD_LENGTH];
    int numWords = 0;
    
    // File scanning loop, linear-time big-o
    while (fscanf(file, "%30s", nextWord) == 1)
        numWords += 1;
    
    printf("%d total words\n", numWords);

    fclose(file);
    return 0;
}