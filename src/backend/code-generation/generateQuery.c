#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "listUtils.h"

#define CD_LEN 1024
#define TC_LEN 128

char tc_name[TC_LEN];
char * code;
int size;
int progress;


void generateColumn( Column * column ){
    if ( column->is_unique )
        strcat(code, "UNIQUE ");
    strcat(code, column->tc_name);

}

void generateColumns( Columns * columns ){
    switch (columns->type)
    {
    case MULTIPLE:
        strcat(code, "( ");
        generateColumn(columns->column);
        columns = columns->columns;
        strcat(code, ",");
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

void generateRequest( Request * request ){
    switch (request->type)
    {
    case RTC_NAME:
        generateColumns(request->columns);
        strcat(code, " FROM ");
        strcat(code, request->tc_name);
        break;
    case COLUMNS:
        generateColumns(request->columns);
        strcat(code, " FROM ");
        strcat(code, request->tc_name);
        break;
    case DISTINCT_COLUMNS:
        strcat(code, " * FROM ");
        strcat(code, request->tc_name);
        strcat(code, " EXCEPT SELECT ");
        generateColumns(request->columns);
        strcat(code, " FROM ");
        strcat(code, request->tc_name);
        break;
    case RALL:
        strcat(code, "* FROM ");
        strcat(code, request->tc_name);
        break;    
    default:
        break;
    }
}

char * generateQuery( QueryBody * queryBody ){
    code = malloc(CD_LEN);
    size = 1;
    code[0] = 0;
    int progress = 0;

    strcat(code, "SELECT ");

    generateRequest(queryBody->request);

    if ( queryBody->condition != NULL )
    {
        strcat(code, " WHERE ");
        strcat(code, queryBody->condition);
    }

    return code;
}