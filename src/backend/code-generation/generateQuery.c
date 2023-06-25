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

static void generateColumns( Columns * columns ){
    switch (columns->type)
    {
    case MULTIPLE:
        strcat(query_code, "( ");
        generateColumn(columns->column);
        columns = columns->columns;
        strcat(query_code, ",");
        while( columns != NULL ){
            generateColumn(columns->column);
            columns = columns->columns;
        }
        break;
    case SINGLE:
        generateColumn(columns->column);
        break;
    default:
        break;
    }
}

static void generateRequest( Request * request ){
    switch (request->type)
    {
    case RTC_NAME:
        generateColumns(request->columns);
        strcat(query_code, " FROM ");
        strcat(query_code, request->tc_name);
        break;
    case COLUMNS:
        generateColumns(request->columns);
        strcat(query_code, " FROM ");
        strcat(query_code, request->tc_name);
        break;
    case DISTINCT_COLUMNS:
        strcat(query_code, " * FROM ");
        strcat(query_code, request->tc_name);
        strcat(query_code, " EXCEPT SELECT ");
        generateColumns(request->columns);
        strcat(query_code, " FROM ");
        strcat(query_code, request->tc_name);
        break;
    case RALL:
        strcat(query_code, "* FROM ");
        strcat(query_code, request->tc_name);
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

    if ( queryBody->condition != NULL )
    {
        strcat(query_code, " WHERE ");
        strcat(query_code, queryBody->condition);
    }

    return query_code;
}