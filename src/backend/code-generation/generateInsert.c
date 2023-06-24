#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"

#define CD_LEN 1024
#define TC_LEN 128

char tc_name[TC_LEN];
char * code;
int size;
int progress;

stringList colsList = NULL;
stringList valuesList = NULL;
stringList typesList = NULL;

void generatePair( Pair * pair ){

    addToList(colsList,pair->column_name);
    addToList(valuesList,pair->column_value_string);
    addToList(typesList, pair->type);

}

void generatePairs( Pairs * pairs ){
    if ( pairs == NULL )
        return;

    generatePair( pairs->pair );

    generatePairs(pairs->pairs);

}

void generateObjects( Objects * objects ){

    if (objects == NULL)
        return;

    colsList = createList();
    valuesList = createList();
    typesList = createList();

    // strcat el codigo a generar sobre code
    strcat(code,"INSERT INTO ");
    strcat(code, tc_name);

    progress = strlen(code);
    if ( progress % CD_LEN < CD_LEN/9 )
        code = realloc(code, CD_LEN * ++size);

    generatePairs(objects->object->pairs);

    strcat(code,"(");
    
    strcat(code, colsList->string);
    colsList = colsList->next;

    progress = strlen(code);
    if ( progress % CD_LEN < CD_LEN/9 )
        code = realloc(code, CD_LEN * ++size);

    while ( colsList != NULL ){
        strcat(code,", ");
        strcat(code,colsList->string);

        progress = strlen(code);
        if ( progress % CD_LEN < CD_LEN/9 )
            code = realloc(code, CD_LEN * ++size);

        colsList = colsList->next;

    }
    freeList(colsList);

    strcat(code,") VALUES (");

    progress = strlen(code);
    if ( progress % CD_LEN < CD_LEN/9 )
        code = realloc(code, CD_LEN * ++size);
    
    strcat(code, valuesList->string);
    valuesList = valuesList->next;

    progress = strlen(code);
    if ( progress % CD_LEN < CD_LEN/9 )
        code = realloc(code, CD_LEN * ++size);

    while ( valuesList != NULL ){
        strcat(code,", ");
        strcat(code,valuesList->string);

        progress = strlen(code);
        if ( progress % CD_LEN < CD_LEN/9 )
            code = realloc(code, CD_LEN * ++size);

        valuesList = valuesList->next;

    }
    freeList(valuesList);

    strcat(code, ");");

    strcat(code,"\n");

    // recursividad
    generateObjects(objects->objects);
}

char * generateInsert(InsertBody * insertBody) {
	code = malloc(CD_LEN);
    size = 1;
    code[0] = 0;
    int progress = 0;



    // guardo el nombre de tabla
    strcpy(tc_name,insertBody->tc_name);

    // creo un insert --> \n --> siguiente insert
    generateObjects(insertBody->objects);

    return code;
    
}