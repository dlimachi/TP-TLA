#include "../support/logger.h"
#include "generator.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "generators.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listUtils.h"

stringList createList(){
    
    stringList toReturn = malloc(sizeof(stringNode));
    toReturn->next = NULL;
    toReturn->string = calloc(128, sizeof(char));
    return toReturn;
}

stringList addToList( stringList list, char * string ){
    if (list == NULL || string == NULL)
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
#define CD_LEN 1024
#define TC_LEN 128

char tc_name[TC_LEN];
char * code;
int size;
int progress;

stringList colsList = NULL;
stringList valuesList = NULL;
stringList typesList = NULL;
/**
 * Implementación de "generator.h".
 */
char * generateDelete(DeleteBody * deleteBody);
char * generateQuery(QueryBody * queryBody);
char * generateCreate(CreateBody * createBody);
char * generateCheck(Check * check);

void generatePair( Pair * pair ){
    if(pair==NULL){
        return;
    }

    addToList(colsList,pair->column_name);
    addToList(valuesList,pair->column_value_string);
    addToList(typesList, "pair->type");

}

void generatePairs( Pairs * pairs ){
    if ( pairs == NULL )
        return;

    generatePair( pairs->pair );

    generatePairs(pairs->pairs);

}

void generateObjects( Objects * objects ){
    if (objects == NULL){
        return;
    }
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
    LogDebug("llegamoss");
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


void Generator(Program * program) {
	// Generator va a generar un archivo .sql
	// nombre del archivo harcodeado
	LogInfo("El resultado de la expresion computada es: '%d'.", program);

	//recorro el arbol desde program y formo el correcto codigo sql
	//casos por tipo de general
	char * code = NULL;

	switch (program->general->type) {
        case(GINSERT):
            code = generateInsert(program->general->insertBody);
            break;
            /*
        case(GDELETE):
            generateDelete(program->general->deleteBody);
            break;
        case(GQUERY):
            generateQuery(program->general->queryBody);
            break;
        case(GCREATE):
            generateCreate(program->general->createBody);
            break;
        case(GCHECK):
            generateCheck(program->general->check);
            break;
            */
	    default:
		    break;
	}

	printf(code);
	LogInfo(code);

	//generar archivo con code

	FILE * output = fopen("output.sql", "w");
	if ( output == NULL )
		return;
	
	fprintf( output, "%s", code);
	
	fclose(output);


}

