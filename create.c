#include"main.h"

int check_and_insert_file(file_node **file_head, char *filename)
{
    file_node *temp = *file_head;

    /* Check if file already exists */
    while(temp != NULL)
    {
        if(strcmp(temp->FileName, filename) == 0)
        {
            return DATA_NOT_FOUND;
        }

        temp = temp->next;
    }

    /* File does not exist, create a new node */
    file_node *new = malloc(sizeof(file_node));

    if(new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->FileName, filename);
    new->next = NULL;

    /* Insert first node */
    if(*file_head == NULL)
    {
        *file_head = new;
    }
    else
    {
        temp = *file_head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new;
    }

    return SUCCESS;
}


int create_database(hash_t *ht, int size, Slist **head, file_node **file_head)
{
    printf("INFO: # Creating database #\n");
    Slist *current = *head;
    while(current)
    {   
        if(check_and_insert_file(file_head, current->file) != SUCCESS)
        {
            printf("File %s already exists. Skipping...\n", current->file);
            current = current->next;
            continue;
        }

        FILE *fp = fopen(current->file, "r");
        if(fp == NULL)
        {
            printf("Error: Failed to open file %s\n", current->file);
            current = current->next;
            continue;
        }
        /* Read words from the file and insert them into the hash table */
        char word[100];
        while(fscanf(fp, "%99s", word) == 1)
        {
            int index;
            if(word[0] >= 'A' && word[0] <= 'Z')
            index = word[0] - 'A';
            else if(word[0] >= 'a' && word[0] <= 'z')
            index = word[0] - 'a';
            else
            index = 26; // For non-alphabetic characters

            /* if no main_node exists for this word. create main node and subnode */
            if(ht[index].main_link == NULL)
            {
                main_node *new_main = malloc(sizeof(main_node));
                if(new_main == NULL)
                {
                    printf("Memory allocation failed for main_node\n");
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->next_mainlink = NULL;

                sub_node *new_sub = malloc(sizeof(sub_node));
                if(new_sub == NULL)
                {
                    printf("Memory allocation failed for sub_node\n");
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(new_sub->filename, current->file);
                new_sub->word_count = 1;
                new_sub->next_sublink = NULL;

                new_main->sublink = new_sub;
                ht[index].main_link = new_main;
            }
            /* if main_node exists for this word, and the word is already present*/
            else
            {
                main_node *tempmain = ht[index].main_link;
                main_node *prevmain = NULL;
                int flag_main = 0;
                while(tempmain)
                {
                    if(strcmp(tempmain->word, word) == 0)
                    {
                        flag_main = 1;
                        break;
                    }
                    prevmain = tempmain;
                    tempmain = tempmain->next_mainlink;
                }
                if(flag_main)
                {
                    /* Word is already present, check if it's in the current file */
                    sub_node *tempsub = tempmain->sublink;
                    sub_node *prevsub = NULL;
                    int flag_sub = 0;
                    while(tempsub)
                    {
                        if(strcmp(tempsub->filename, current->file) == 0)
                        {
                            tempsub->word_count++;
                            flag_sub = 1;
                            break;
                        }
                        prevsub = tempsub;
                        tempsub = tempsub->next_sublink;
                    }
                    if(!flag_sub)
                    {
                        /* Word is not present in the current file, create a new sub_node */
                        sub_node *new_sub = malloc(sizeof(sub_node));
                        if(new_sub == NULL)
                        {
                            printf("Memory allocation failed for sub_node\n");
                            fclose(fp);
                            return FAILURE;
                        }
                        strcpy(new_sub->filename, current->file);
                        new_sub->word_count = 1;
                        new_sub->next_sublink = NULL;

                        /* Insert the new sub_node at the end of the sublink list */
                        if(prevsub)
                            prevsub->next_sublink = new_sub;
                        else
                            tempmain->sublink = new_sub;

                        tempmain->file_count++;
                    }
                }
                else
                {
                    /* Word is not present in the hash table, create a new main_node and sub_node */
                    main_node *new_main = malloc(sizeof(main_node));
                    if(new_main == NULL)
                    {
                        printf("Memory allocation failed for main_node\n");
                        fclose(fp);
                        return FAILURE;
                    }
                    strcpy(new_main->word, word);
                    new_main->file_count = 1;
                    new_main->next_mainlink = NULL;

                    sub_node *new_sub = malloc(sizeof(sub_node));
                    if(new_sub == NULL)
                    {
                        printf("Memory allocation failed for sub_node\n");
                        fclose(fp);
                        return FAILURE;
                    }
                    strcpy(new_sub->filename, current->file);
                    new_sub->word_count = 1;
                    new_sub->next_sublink = NULL;

                    new_main->sublink = new_sub;

                    /* Insert the new main_node at the end of the main_link list */
                    if(prevmain)
                        prevmain->next_mainlink = new_main;
                    else
                        ht[index].main_link = new_main;
                }
            }
        }
        fclose(fp);
        current = current->next;
    }
    return SUCCESS;
}