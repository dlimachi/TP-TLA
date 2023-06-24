#define LEN 128

typedef struct stringNode
{
    char * string;
    struct stringNode * next;
}stringNode;

typedef stringNode * stringList;

