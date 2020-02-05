#ifndef CH_HEAD2
#define CH_HEAD2

struct LinkedList
{
    char *word;
    int count;
    struct LinkedList *next;
};

//count words:
struct LinkedList *wordcounter(char *word, int count, struct LinkedList *next);
//add into a linked list:
void add_link(struct LinkedList **counter, char *store);
#endif