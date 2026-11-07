#include "main.h"

int display_database(const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Unable to open database file %s\n", filename);
        return FAILURE;
    }

    printf("INFO: # Displaying database #\n\n");

    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);

    return SUCCESS;
}