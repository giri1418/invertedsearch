#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* Macro Definitions */
#define FAILURE 0
#define SUCCESS 1
#define DATA_NOT_FOUND 2

/* Structure Definitions */ 

typedef struct file_node
{
    char FileName[20];
    struct file_node *next;
}file_node;

typedef struct Slist
{
    char file[20];
    struct Slist *next;
} Slist;

typedef struct main_node
{
    int file_count;
    char word[100];
    struct sub_node *sublink;
    struct main_node *next_mainlink;
}main_node;

typedef struct sub_node
{
    int word_count;
    char filename[20];
    struct sub_node* next_sublink;
}sub_node;

typedef struct hash_table
{
    int index;
    main_node *main_link;
}hash_t;

/* Function Prototypes */

int validate_file_argument(Slist **head, char *argv[]);
int create_database(hash_t *ht, int size, Slist **head,file_node **file_head);
int check_and_insert_file(file_node **file_head, char *filename);
int display_database(const char *filename);
int search_word(hash_t *ht, int size, char* word);
int save_database(hash_t *ht, int size, const char *filename);
int update_database(hash_t *ht, int size, const char *filename,file_node **file_head);

#endif