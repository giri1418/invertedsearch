#include "main.h"

int update_database(hash_t *ht, int size, const char *filename,file_node **file_head)
{
    /* Check if the file has a .txt extension */
    char *ptr = strstr(filename, ".txt");
    if(ptr == NULL || strcmp(ptr, ".txt") != 0)
    {
        printf("Error: Invalid file extension -> %s\n", filename);
        return FAILURE;
    }

    /* Check if the file can be opened */
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: File %s not found\n", filename);
        return FAILURE;
    }
    /* check the first char is # */
    char first_char;
    if (fscanf(fp, " %c", &first_char) == EOF)
    {
        printf("Error: Failed to read from file %s\n", filename);
        fclose(fp);
        return FAILURE;
    }
    if (first_char != '#')
    {
        printf("Error: Invalid file format -> %s\n", filename);
        fclose(fp);
        return FAILURE;
    }
    rewind(fp);

    int index,file_count;
    char word[100];
    while (fscanf(fp, "#%d;%[^;];%d;", &index,word,&file_count) == 3)
    {
        /* create a main node*/
        main_node *mn = malloc(sizeof(main_node));
        if (mn == NULL)
        {
            printf("Error: Failed to allocate memory\n");
            fclose(fp);
            return FAILURE;
        }

        strcpy(mn->word, word);
        mn->file_count = file_count;
        mn->sublink = NULL;
        mn->next_mainlink = NULL;

        for(int i = 0; i < file_count; i++)
        {
            sub_node *sn = malloc(sizeof(sub_node));

            if(sn == NULL)
            {
                printf("Error: Failed to allocate memory\n");
                fclose(fp);
                return FAILURE;
            }

            char file[100];
            int word_count;

            if(fscanf(fp, " %99[^;];%d", file, &word_count) != 2)
            {
                printf("Error: Invalid file format -> %s\n", filename);
                free(sn);
                free(mn);
                fclose(fp);
                return FAILURE;
            }

            strcpy(sn->filename, file);
            sn->word_count = word_count;
            sn->next_sublink = NULL;

            if(check_and_insert_file(file_head, file) == FAILURE)
            {
                printf("Error: Failed to insert file %s\n", file);
                free(sn);
                free(mn);
                fclose(fp);
                return FAILURE;
            }

            if(mn->sublink == NULL)
            {
                mn->sublink = sn;
            }
            else
            {
                sub_node *temp = mn->sublink;

                while(temp->next_sublink != NULL)
                {
                    temp = temp->next_sublink;
                }

                temp->next_sublink = sn;
            }
        }

        if(fgetc(fp) != '#')
        {
            printf("Error: Invalid database record\n");
            free(mn);
            fclose(fp);
            return FAILURE;
        }

        /* Insert the main_node into the hash table */ 
        if(ht[index].main_link == NULL)
        {
            ht[index].main_link = mn;
        }
        else
        {
            main_node *temp = ht[index].main_link;

            while(temp->next_mainlink != NULL)
            {
                temp = temp->next_mainlink;
            }

            temp->next_mainlink = mn;
        }
    }

    fclose(fp);

    return SUCCESS;
}