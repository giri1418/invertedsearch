/*
name - Kancharla Giri Babu
date - 18/10/26
description - Creates an inverted index from a list of files by reading each word, normalizing it to lowercase, 
              and removing punctuation. Uses 26 buckets (A–Z) based on the first letter to store words in main nodes.
              Each main node links to sub nodes that store file names and occurrence counts.
              Skips entire files already processed to avoid duplication.
              Ensures each word appears only once per bucket, updating counts if repeated.
*/

#include"main.h"

int main(int argc, char *argv[])
{
    int option, size = 27;

    Slist *head = NULL;
    file_node *file_head = NULL;

    /* Initialize the hash table */
    hash_t arr[size];
    for(int i = 0; i < size; i++)
    {
        arr[i].index = i;
        arr[i].main_link = NULL;
    }

    /* Validate the file arguments */
    if(argc > 1){
        if(validate_file_argument(&head,argv) == FAILURE)
        {
            printf("File validation failed\n");
            return FAILURE;
        }
        printf("INFO: # File validation successful #\n");
    }


    while(1)
    {
        printf("\n1. Create Database\n2. Display Database\n3. Search Word\n4. Save Database\n5. Update Database\n6. Exit\n");
        scanf("%d", &option);

        switch(option)
        {
        case 1:
            if(create_database(arr, size, &head, &file_head) == FAILURE)
            {
                printf("Failed to create database\n");
            }
            else
            {
                printf("INFO: # Database created successfully #\n");
            }
            break;

        case 2:
            char display_filename[100];
            printf("Enter the filename to display the database: ");
            scanf("%s", display_filename);
            if(display_database(display_filename) == FAILURE)
            {
                printf("Failed to display database\n");
            }
            break;
        
        case 3:
            /* Read the word */
            char word[100];
            printf("Enter the word to search: ");
            scanf("%s", word);
            if(search_word(arr, size, word) == DATA_NOT_FOUND)
            {
                printf("Word '%s' not found in the database\n", word);
            }
            break;
        
        case 4:
            char filename[100];
            printf("Enter the filename to save the database: ");
            scanf("%s", filename);
            if(save_database(arr, size, filename) == FAILURE)
            {
                printf("Failed to save database to file\n");
            }
            else
            {
                printf("INFO: # Database saved successfully #\n");
            }
            break;
        
        case 5:
            char update_file[100];
            printf("Enter the filename to update the database: ");
            scanf("%s", update_file);

            if(update_database(arr, size, update_file, &file_head) == FAILURE)
            {
                printf("Failed to update database from file\n");
            }
            else
            {
                printf("INFO: # Database updated successfully #\n");
            }
            break;
        case 6:
            exit(0);
        }
    }
}