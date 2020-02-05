#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedlist.h"

struct LinkedList *wordcounter(char *word, int count, struct LinkedList *next)
{
    struct LinkedList *newitem = NULL;
    newitem = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    if (newitem == NULL)
        return NULL;

    newitem->word = word;
    newitem->count = count;
    newitem->next = next;
    return newitem;
}

//add into a linked list
void add_link(struct LinkedList **counter, char *store)
{
    //check which case to go to:
    int ch = 0;
    //add at the head:
    if ((*counter)->word == NULL)
    {
        (*counter)->word = store;
        (*counter)->count = 1;
        ch = 1;
    }
    //traverse to check if the word exists:
    struct LinkedList *temp = *counter;
    struct LinkedList *temp2 = *counter;
    while (ch == 0 && temp != NULL)
    {
        if (strcmp(temp->word, store) == 0)
        {
            temp->count++;
            ch = 1;
            break;
        }
        temp = temp->next;
        //this will stop at the last node:
        if (temp2->next != NULL)
            temp2 = temp2->next;
    }
    //add from the last node:
    if (ch == 0)
    {
        temp2->next = wordcounter(NULL, 0, NULL);
        temp2->next->word = store;
        temp2->next->count++;
    }
}