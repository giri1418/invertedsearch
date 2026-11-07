#include "main.h"

void store_database(hash_t *ht, int size, FILE *fp)
{
    for(int i = 0; i < size; i++)
    {
        main_node *main_temp = ht[i].main_link;

        while(main_temp != NULL)
        {
            /* #index;word;file_count; */
            fprintf(fp, "#%d;%s;%d;",
                    i,
                    main_temp->word,
                    main_temp->file_count);

            /* filename;word_count */
            sub_node *sub_temp = main_temp->sublink;

            while(sub_temp != NULL)
            {
                fprintf(fp, "%s;%d",
                        sub_temp->filename,
                        sub_temp->word_count);

                sub_temp = sub_temp->next_sublink;

                if(sub_temp != NULL)
                    fprintf(fp, " ");
            }

            /* End of one record */
            fprintf(fp, "#\n");

            main_temp = main_temp->next_mainlink;
        }
    }
}

int save_database(hash_t *ht, int size, const char* filename)
{
    printf("INFO: # Saving database to file #\n");

    /* Check if the file has a .txt extension */
    char *ptr = strstr(filename,".txt");
    if(ptr == NULL || strcmp(ptr,".txt") != 0)
    {
        printf("Error: Invalid file extension -> %s\n", filename);
        return FAILURE;
    }

    FILE *fp = fopen(filename,"r");
    if(fp == NULL)
    {
        /* File does not exist, create it */
        fp = fopen(filename,"w");
        if(fp == NULL)
        {
            printf("Error: Failed to create file %s\n", filename);
            return FAILURE;
        }
        store_database(ht, size, fp);
        fclose(fp);
        printf("INFO: Database saved successfully to file %s\n", filename);
        return SUCCESS;
    }
    /* if the file is already present and it is empty */
    else if(getc(fp) == EOF)
    {
        printf("INFO: File %s is empty. Saving database...\n", filename);
        fclose(fp);
        fp = fopen(filename,"w");
        if(fp == NULL)
        {
            printf("Error: Failed to open file %s for writing\n", filename);
            return FAILURE;
        }
        store_database(ht, size, fp);
        fclose(fp);
        printf("INFO: Database saved successfully to file %s\n", filename);
        return SUCCESS;
    }
    
    // /* if file is Non_empty */
    else
    {
        fseek(fp, -2, SEEK_END);
        if(fgetc(fp) != '#')
        {
            printf("Invalid file. Last character in the file must be end with '#' \n");
            fclose(fp);
            return FAILURE;
        }
        printf("File is already present\n1.Overwrite the file\n2.Append the data\n");
        int op;
        scanf("%d", &op);
        if(op == 1)
        {
            fclose(fp);
            fp = fopen(filename, "w");
            if(fp == NULL)
            {
                printf("Error: Failed to open file %s for writing\n", filename);
                return FAILURE;
            }
            store_database(ht, size, fp);
            fclose(fp);
            printf("INFO: Database saved successfully to file %s\n", filename);
            return SUCCESS;
        }
        else if(op == 2)
        {
            fclose(fp);
            fp = fopen(filename, "a");
            if(fp == NULL)
            {
                printf("Error: Failed to open file %s for appending\n", filename);
                return FAILURE;
            }
            store_database(ht, size, fp);
            fclose(fp);
            printf("INFO: Database appended successfully to file %s\n", filename);
            return SUCCESS;
        }
        else
        {
            printf("Invalid option\n");
            fclose(fp);
            return FAILURE;
        }
    }
}