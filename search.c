#include "main.h"

int search_word(hash_t *ht, int size,char *word)
{
    printf("INFO: # Searching for word '%s' in the database #\n", word);
    /* find the index */
    int index;
    if(word[0] >= 'A' && word[0] <= 'Z')
    index = word[0] - 'A';
    else if(word[0] >= 'a' && word[0] <= 'z')
    index = word[0] - 'a';
    else
    index = 26;

    if(ht[index].main_link == NULL)
    return DATA_NOT_FOUND;
    else
    {
        main_node *temp = ht[index].main_link;
        while(temp)
        {
            if(strcmp(temp->word,word) == 0)
            {
                printf("# index : Word : File count : File name -> Word count #\n");
                printf("# %d : %s : %d : ",index,temp->word,temp->file_count);

                sub_node *temp_sub = temp->sublink;
                while(temp_sub)
                {
                    printf("%s -> %d ",temp_sub->filename,temp_sub->word_count);
                    temp_sub = temp_sub->next_sublink;
                }
                printf("#\n");
                return SUCCESS;
            }
            temp = temp->next_mainlink;
        }
    }
    return DATA_NOT_FOUND;
}