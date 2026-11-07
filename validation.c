#include "main.h"

/* Function to validate file arguments */
#include "main.h"

/* Function to validate file arguments */
int validate_file_argument(Slist **head, char *argv[])
{
    printf("\nINFO: # Validating file arguments...#\n");

    for(int i = 1; argv[i] != NULL; i++)
    {
        /* Check if the file has a .txt extension */
        char *ptr = strstr(argv[i], ".txt");

        if(ptr == NULL || strcmp(ptr, ".txt") != 0)
        {
            printf("Error: Invalid file extension -> %s\n", argv[i]);
            continue;
        }

        /* Check if the file can be opened */
        FILE *fp = fopen(argv[i], "r");

        if(fp == NULL)
        {
            printf("Error: File %s not found\n", argv[i]);
            continue;
        }

        /* Check if the file is empty */
        fseek(fp, 0, SEEK_END);

        if(ftell(fp) == 0)
        {
            printf("Error: File %s is empty\n", argv[i]);
            fclose(fp);
            continue;
        }

        /* File is valid and not empty */

        /* Check for duplicate file */
        Slist *temp = *head;
        int found = 0;

        while(temp != NULL)
        {
            if(strcmp(temp->file, argv[i]) == 0)
            {
                printf("Error: File %s is repeated\n", argv[i]);
                found = 1;
                break;
            }

            temp = temp->next;
        }

        if(found)
        {
            fclose(fp);
            continue;
        }

        /* Create new Slist node */
        Slist *new = malloc(sizeof(Slist));

        if(new == NULL)
        {
            printf("Error: Memory allocation failed\n");
            fclose(fp);
            return FAILURE;
        }

        strcpy(new->file, argv[i]);
        new->next = NULL;

        /* Insert into Slist */
        if(*head == NULL)
        {
            *head = new;
        }
        else
        {
            temp = *head;

            while(temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = new;
        }

        fclose(fp);
    }

    return SUCCESS;
}