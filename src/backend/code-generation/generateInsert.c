#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"
#include "generators.h"

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
    if(pair==NULL){
        return;
    }

    addToList(colsList,pair->column_name);
    switch(pair->type){
        case(PVTRUE):
            addToList(valuesList,"true");
            break;
        case(PVFALSE):
            addToList(valuesList,"false");
            break;
        case(PVNULL):
            addToList(valuesList,"null");
            break;
        default:
            
            addToList(valuesList,replaceQuotes(pair->column_value_string));
            break;
    }
    addToList(typesList, "pair->type");

}

void generatePairs( Pairs * pairs ){
    if ( pairs == NULL )
        return;

    generatePairs(pairs->pairs);
    generatePair( pairs->pair );


}

void generateObjects( Objects * objects ){
    if (objects == NULL){
        return;
    }
    generateObjects(objects->objects);
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
    int i = 0;
    while ( colsList != NULL ){
        if(i>0){
            strcat(code,", ");
        }
        strcat(code,remover_comillas_extremos(colsList->string));

        progress = strlen(code);
        if ( progress % CD_LEN < CD_LEN/9 )
            code = realloc(code, CD_LEN * ++size);

        colsList = colsList->next;
        i++;

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
    i=0;
    while ( valuesList != NULL ){
        if (i>0){
            strcat(code,", ");
        }
        strcat(code,valuesList->string);

        progress = strlen(code);
        if ( progress % CD_LEN < CD_LEN/9 )
            code = realloc(code, CD_LEN * ++size);

        valuesList = valuesList->next;
        i++;

    }
    freeList(valuesList);

    strcat(code, ");");

    strcat(code,"\n");

}

char * generateInsert(InsertBody * insertBody) {
	code = malloc(CD_LEN);
    size = 1;
    code[0] = 0;
    code[CD_LEN]=0;
    int progress = 0;

    // guardo el nombre de tabla
    strcpy(tc_name,insertBody->tc_name);
    // creo un insert --> \n --> siguiente insert
    generateObjects(insertBody->objects);
    return code;
    
}