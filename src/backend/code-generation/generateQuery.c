#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "listUtils.h"
#include "generators.h"

char * query_code;
int query_size;
static char query_tc_name[TC_LEN];
static int query_progress;

static void generateColumn( Column * column ){
    if ( column->is_unique )
        strcat(query_code, "UNIQUE ");
    strcat(query_code, column->tc_name);

}

void generateColumns( Columns * columns ){
    if(columns==NULL){
        return;
    }
    generateColumns(columns->columns);
    switch (columns->type)
    {
    case MULTIPLE:
        strcat(query_code, ",");
        generateColumn(columns->column);
        break;
    case SINGLE:
        generateColumn(columns->column);
        break;
    default:
        break;
    }
}

void generateRequest( Request * request ){
    switch (request->type)
    {
    case RTC_NAME:
        generateColumns(request->columns);
        strcat(query_code, " FROM ");
        break;
    case COLUMNS:
        generateColumns(request->columns);
        strcat(query_code, " FROM ");
        break;
    case DISTINCT_COLUMNS:
        strcat(query_code, "DISTINCT ");
        generateColumns(request->columns);
        strcat(query_code, " FROM ");
        break;
    case RALL:
        strcat(query_code, "* FROM ");
        break;    
    default:
        break;
    }
}

char * generateQuery( QueryBody * queryBody ){
    query_code = malloc(CD_LEN);
    query_size = 1;
    query_code[0] = 0;
    int query_progress = 0;

    strcat(query_code, "SELECT ");
    generateRequest(queryBody->request);
    strcat(query_code, queryBody->tc_name);
    if ( queryBody->condition != NULL )
    {
        strcat(query_code, " WHERE ");
        generateCondition(queryBody->condition);
    }

    return query_code;
}