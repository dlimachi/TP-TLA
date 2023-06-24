#include "listUtils.h"
#include <stdio.h>
#include <stdlib.h>

stringList createList(){
    stringList toReturn = malloc(sizeof(stringNode));
    toReturn->next = NULL;
    toReturn->string = calloc(128, sizeof(void *));
    return toReturn;
}

stringList addToList( stringList list, char * string ){

    if (list == NULL)
        return NULL;

    if ( list->next == NULL )
    {
        stringList newNode = malloc(sizeof(stringNode));
        newNode->next = NULL;
        newNode->string = malloc(strlen(string)+1);
        strcpy(newNode->string, string);

        list->next = newNode;
        return list;
    }

    return addToList(list->next, string);
}

void freeList( stringList list ){
    if ( list == NULL )
        return;

    freeList(list->next);

    free(list->string);
    free(list);

    return;
}