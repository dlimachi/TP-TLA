#define LEN 128

typedef struct stringNode
{
    char * string;
    struct stringNode * next;
}stringNode;

typedef stringNode * stringList;

stringList createList();

stringList addToList( stringList list, char * string );

void freeList( stringList list );

