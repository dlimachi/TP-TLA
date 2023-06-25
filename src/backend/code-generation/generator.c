#include "../support/logger.h"
#include "generator.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "generators.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listUtils.h"
char* replaceQuotes(char* input) {
    int length = strlen(input);
    if(length < 2) {
        return NULL; // Si el string es demasiado corto, retornamos NULL.
    }

    // Verificamos si la primera y última caracter son comillas (simples o dobles)
    if((input[0] == '\"' && input[length-1] == '\"')) {
        input[0]='\'';
        input[length-1]='\'';
        input[length]='\0';
        return input;
    } else {
        return strdup(input); // Si la cadena original no comienza y termina con comillas, la retornamos tal cual.
    }
}

char* remover_comillas_extremos(char* input) {
    int length = strlen(input);
    if(length < 2) {
        return NULL; // Si el string es demasiado corto, retornamos NULL.
    }

    // Verificamos si la primera y última caracter son comillas (simples o dobles)
    if((input[0] == '\"' && input[length-1] == '\"') || (input[0] == '\'' && input[length-1] == '\'')) {
        char* new_str = malloc(length - 1); // Creamos una nueva cadena con espacio para la nueva cadena sin las comillas.
        if(new_str == NULL) {
            return NULL; // Si no se pudo asignar la memoria, retornamos NULL.
        }
        strncpy(new_str, input + 1, length - 2); // Copiamos la cadena original sin las comillas.
        new_str[length - 2] = '\0'; // Aseguramos que la cadena es nula terminada.
        return new_str;
    } else {
        return strdup(input); // Si la cadena original no comienza y termina con comillas, la retornamos tal cual.
    }
}

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

