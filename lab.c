#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedlist.h"

int main(int argc, char *argv[])
{
    //linked list for storing word:
    struct LinkedList *counter = wordcounter(NULL, 0, NULL);
    //take each letter:
    char *buf = (char *)malloc(sizeof(char *));
    //store the letter:
    //method: store each valid letter from the file (buf) into  store to make a whole word and the word ends when buf meets invalid symbol
    char *store = (char *)malloc(30 * sizeof(char));
    //check which method of reading file to use:
    int in = 0;
    //case for compiled program called wordfreak and a subsequential list of programs: ./wordfreak file1 file2:
    if (argc > 1)
    {
        //check if there is file to read
        int a = 1;
        while (a < argc)
        {
            //open file:
            int fd = open(argv[a], O_RDONLY);
            //error opening file:
            if (fd == -1)
            {
                printf("Error opening file\n");
                return 0;
            }

            //read each letter
            int check;

            while ((check = read(fd, buf, 1)) > 0)
            {
                //if valid letter, store it in store, if invalid, store will just not get added
                if ((*buf >= 'a' && *buf <= 'z') || (*buf >= 'A' && *buf <= 'Z'))
                {
                    strcat(store, buf);
                }

                //if not the end of string and store is empty, skip:
                else if (*buf != '\0' && strcmp(store, "") == 0)
                    continue;

                //add to linked list
                else
                {
                    //add the end of the string symbol into store:
                    strcat(store, "\0");
                    add_link(&counter, store);
                    store = (char *)malloc(30 * sizeof(char));
                }
                //end of the linked list
            }
            //check for error reading:
            if (check < 0)
                return 4;
            //close file:
            int closefd = close(fd);
            if (closefd == -1)
                printf("Error closing file");
            //move to next file index:
            a++;
        }
        //condition help not to jump in other cases below:
        in = 1;
    }

    //case for an environment variable called WORD_FREAK set to a single file from the command line to be analyzed
    char *c = getenv("WORD_FREAK");
    //check the condition: not in previous loop, numer of files fewer than 1, there is the environment required
    if (in == 0 && argc <= 1 && c != NULL)
    {
        //check for opening file:
        int fd = open(c, O_RDONLY);
        //error opening file:
        if (fd == -1)
        {
            printf("Error opening file\n");
            return 0;
        }
        //read each letter
        int check;

        while ((check = read(fd, buf, 1)) > 0)
        {
            //if valid letter, store it in store, if invalid, store will just not get added
            if ((*buf >= 'a' && *buf <= 'z') || (*buf >= 'A' && *buf <= 'Z'))
            {
                strcat(store, buf);
            }
            //if not the end of string and store is empty, skip:
            else if (*buf != '\0' && strcmp(store, "") == 0)
                continue;
            //add to linked list
            else
            {
                //add the end of the string symbol into store:
                strcat(store, "\0");
                add_link(&counter, store);
                store = (char *)malloc(30 * sizeof(char));
            }
        }
        //check for error reading:
        if (check < 0)
            return 4;
        //close file:
        int closefd = close(fd);
        if (closefd == -1)
            printf("Error closing file");
        //condition help not to jump in the other case below:
        in = 1;
    }

    //case for text files from standard input:
    else if (in == 0 && argc <= 1)
    {
        //read each letter
        int check;

        while ((check = read(STDIN_FILENO, buf, 1)) > 0)
        {
            //if valid letter, store it in store, if invalid, store will just not get added
            if ((*buf >= 'a' && *buf <= 'z') || (*buf >= 'A' && *buf <= 'Z'))
            {
                strcat(store, buf);
            }
            //if not the end of string and store is empty, skip:
            else if (*buf != '\0' && strcmp(store, "") == 0)
                continue;
            //add the the linked list:
            else
            {
                //add the end of the string symbol into store:
                strcat(store, "\0");
                add_link(&counter, store);
                store = (char *)malloc(30 * sizeof(char));
            }
        }
        //check for error reading:
        if (check < 0)
            return 4;
    }

    int w;
    //while loop for printing out result:
    //if not null, print out:
    while (counter != NULL)
    {
        //string for store the formate:
        char string[100];
        //formatting print out:
        //I chose this space size because of the common words are usually 24 words or fewer letters
        //the number may also be 2 digit.
        sprintf(string, "%-24s: %2i\n", counter->word, counter->count);
        //write on the output screen:
        int cnt = strlen(string);
        //if write less than byte desired, continue until enough:
        while ((w = write(STDOUT_FILENO, string, cnt)) < cnt)
        {
            if (w < 0)
            {
                return 5;
            }
            cnt -= w;
        }
        //move onto the next node:
        counter = counter->next;
    }
    //free all the pointer used:
    free(counter);
    free(buf);
    free(store);
    return 0;
}