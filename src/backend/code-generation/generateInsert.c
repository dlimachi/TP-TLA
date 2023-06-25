#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"
#include "generators.h"

stringList colsList = NULL;
stringList valuesList = NULL;
stringList typesList = NULL;

char * insert_code;
int insert_size;
static char insert_tc_name[TC_LEN];
static int insert_progress;

static void generatePair( Pair * pair ){
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
            
            addToList(valuesList,modificar_comillas(pair->column_value_string));
            break;
    }
    addToList(typesList, "pair->type");

}

static void generatePairs( Pairs * pairs ){
    if ( pairs == NULL )
        return;

    generatePairs(pairs->pairs);
    generatePair( pairs->pair );


}

static void generateObjects( Objects * objects ){
    if (objects == NULL){
        return;
    }
    generateObjects(objects->objects);
    colsList = createList();
    valuesList = createList();
    typesList = createList();

    // strcat el codigo a generar sobre insert_code
    strcat(insert_code,"INSERT INTO ");
    strcat(insert_code, insert_tc_name);

    insert_progress = strlen(insert_code);
    if ( insert_progress % CD_LEN < CD_LEN/9 )
        insert_code = realloc(insert_code, CD_LEN * ++insert_size);
    generatePairs(objects->object->pairs);
    strcat(insert_code,"(");
    
    strcat(insert_code, colsList->string);
    colsList = colsList->next;

    insert_progress = strlen(insert_code);
    if ( insert_progress % CD_LEN < CD_LEN/9 )
        insert_code = realloc(insert_code, CD_LEN * ++insert_size);
    int i = 0;
    while ( colsList != NULL ){
        if(i>0){
            strcat(insert_code,", ");
        }
        strcat(insert_code,remover_comillas_extremos(colsList->string));

        insert_progress = strlen(insert_code);
        if ( insert_progress % CD_LEN < CD_LEN/9 )
            insert_code = realloc(insert_code, CD_LEN * ++insert_size);

        colsList = colsList->next;
        i++;

    }
    freeList(colsList);

    strcat(insert_code,") VALUES (");

    insert_progress = strlen(insert_code);
    if ( insert_progress % CD_LEN < CD_LEN/9 )
        insert_code = realloc(insert_code, CD_LEN * ++insert_size);
    
    strcat(insert_code, valuesList->string);
    valuesList = valuesList->next;

    insert_progress = strlen(insert_code);
    if ( insert_progress % CD_LEN < CD_LEN/9 )
        insert_code = realloc(insert_code, CD_LEN * ++insert_size);
    i=0;
    while ( valuesList != NULL ){
        if (i>0){
            strcat(insert_code,", ");
        }
        strcat(insert_code,valuesList->string);

        insert_progress = strlen(insert_code);
        if ( insert_progress % CD_LEN < CD_LEN/9 )
            insert_code = realloc(insert_code, CD_LEN * ++insert_size);

        valuesList = valuesList->next;
        i++;

    }
    freeList(valuesList);

    strcat(insert_code, ");");

    strcat(insert_code,"\n");

}

char * generateInsert(InsertBody * insertBody) {
	insert_code = calloc(1,CD_LEN);
    insert_size = 1;
    insert_code[0] = 0;
    insert_code[CD_LEN]=0;
    int insert_progress = 0;

    // guardo el nombre de tabla
    strcpy(insert_tc_name,insertBody->tc_name);
    // creo un insert --> \n --> siguiente insert
    generateObjects(insertBody->objects);
    return insert_code;
    
}