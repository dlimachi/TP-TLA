#include "listUtils.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "strings.h"
#include <stdio.h>


#define CD_LEN 1024
#define TC_LEN 128

char tc_name[TC_LEN];
char * code;
int size;
int progress;



void generateWhereDelete(char * column, char * condition){

    strcpy(code,"DELETE FROM ");
    strcat(code,tc_name);
    strcat(code," WHERE ");
    int progress = 13 + 7 + strlen(tc_name);

    char * aux = remover_comillas_extremos(column);
    progress += strlen(aux);

    strcat(code, aux);
    strcat(code, " = ");

    char * aux2 = replaceQuotes(condition);
    progress += strlen(aux2);

    strcat(code, aux2);
    strcat(code, ";");
}

void generatePair( Pair * pair ){
    if(pair->column_name==NULL){
        return;
    }
    char * aux = remover_comillas_extremos(pair->column_name);
    progress += strlen(aux);

    strcat(code, aux);
    strcat(code, " = ");

    switch (pair->type)
    {
    case PSTRING:
        strcat(code, replaceQuotes(pair->column_value_string));
        break;
    case PINTEGER:
        strcat(code, remover_comillas_extremos(pair->column_value_string));
        break;
    case PDECIMAL:
        strcat(code, remover_comillas_extremos(pair->column_value_string));
        break;
    case PVTRUE:
        strcat(code, "true");
        break;
    case PVFALSE:
        strcat(code, "false");
        break;
    case PVNULL:
        strcat(code, "NULL");
        break;
    
    default:
        break;
    }

}

void generatePairs( Pairs * pairs ){
    if ( pairs == NULL )
        return;
        
    generatePair( pairs->pair );
    if ( pairs->pairs != NULL )
    {
        strcat(code, " AND ");
        generatePairs(pairs->pairs);
    }
    
}

void generateObjectDelete( Object * object ){
    strcpy(code,"DELETE FROM ");
    strcat(code,tc_name);
    strcat(code," WHERE ");
    int progress = 13 + 7 + strlen(tc_name);
    generatePairs(object->pairs);

}

char * generateDelete( DeleteBody * deleteBody ){
    code = malloc(CD_LEN);
    size = 1;
    strcpy(tc_name, deleteBody->tc_name);
    switch (deleteBody->type)
    {
    case DWHERE:
        generateWhereDelete(deleteBody->column_name, deleteBody->condition_string);
        break;
    
    case OBJECT:
        generateObjectDelete(deleteBody->object);
        break;
    
    default:
        break;
    }
    return code;
}
