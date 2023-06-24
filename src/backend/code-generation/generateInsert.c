#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>

#define LEN 1024
#define TC_LEN 128

static char tc_name[TC_LEN];
static char * code;
static int progress;

void generatePair( Pair * pair ){
    char aux[LEN] = {0};

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

    // strcat el codigo a generar sobre code

    generatePairs(objects->object->pairs);

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