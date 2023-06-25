#include "listUtils.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "strings.h"
#include <stdio.h>
#include "generators.h"

char * delete_code;
int delete_size;
static char delete_tc_name[TC_LEN];
static int delete_progress;

static void generateWhereDelete(char * column, char * condition){

    strcpy(delete_code,"DELETE FROM ");
    strcat(delete_code,delete_tc_name);
    strcat(delete_code," WHERE (");
    int delete_progress = 13 + 8 + strlen(delete_tc_name);

    char * aux = remover_comillas_extremos(column);
    delete_progress += strlen(aux);

    strcat(delete_code, aux);
    strcat(delete_code, " = ");

    char * aux2 = modificar_comillas(condition);
    delete_progress += strlen(aux2);

    strcat(delete_code, aux2);
    strcat(delete_code," )");
}

static void generatePair( Pair * pair ){
    if(pair->column_name==NULL){
        return;
    }
    char * aux = remover_comillas_extremos(pair->column_name);
    delete_progress += strlen(aux);

    strcat(delete_code, aux);
    strcat(delete_code, " = ");

    switch (pair->type)
    {
    case PSTRING:
        strcat(delete_code, modificar_comillas(pair->column_value_string));
        break;
    case PINTEGER:
        strcat(delete_code, remover_comillas_extremos(pair->column_value_string));
        break;
    case PDECIMAL:
        strcat(delete_code, remover_comillas_extremos(pair->column_value_string));
        break;
    case PVTRUE:
        strcat(delete_code, "true");
        break;
    case PVFALSE:
        strcat(delete_code, "false");
        break;
    case PVNULL:
        strcat(delete_code, "NULL");
        break;
    
    default:
        break;
    }

}

static void generatePairs( Pairs * pairs ){
    if ( pairs == NULL )
        return;
        
    generatePair( pairs->pair );
    if ( pairs->pairs != NULL )
    {
        strcat(delete_code, " AND ");
        generatePairs(pairs->pairs);
    }
    
}

static void generateObjectDelete( Object * object ){
    strcpy(delete_code,"DELETE FROM ");
    strcat(delete_code,delete_tc_name);
    strcat(delete_code," WHERE (");
    int delete_progress = 13 + 7 + strlen(delete_tc_name);
    generatePairs(object->pairs);
    strcat(delete_code, " )");

}

char * generateDelete( DeleteBody * deleteBody ){
    delete_code = calloc(1,CD_LEN);
    delete_size = 1;
    strcpy(delete_tc_name, deleteBody->tc_name);
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
    strcat(delete_code,";");
    return delete_code;
}
