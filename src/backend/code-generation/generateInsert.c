#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"

#define LEN 1024
#define TC_LEN 128

char tc_name[TC_LEN];
char * code;
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

    generatePairs(objects->object->pairs);

    strcat(code,"(");
    
    strcat(code, colsList->string);
    colsList = colsList->next;

    while ( colsList != NULL ){
        strcat(code,", ");
        strcat(code,colsList->string);

        colsList = colsList->next;

    }
    freeList(colsList);

    strcat(code,") VALUES (");
    
    strcat(code, valuesList->string);
    valuesList = valuesList->next;

    while ( valuesList != NULL ){
        strcat(code,", ");
        strcat(code,valuesList->string);

        valuesList = valuesList->next;

    }
    freeList(valuesList);

    strcat(code, ");");

    strcat(code,"\n");

    // recursividad
    generateObjects(objects->objects);
}

void generateInsert(InsertBody * insertBody) {
	code = malloc(LEN);
    code[0] = 0;
    int progress = 0;



    // guardo el nombre de tabla
    strcpy(tc_name,insertBody->tc_name);

    // creo un insert --> \n --> siguiente insert
    generateObjects(insertBody->objects);
    
}