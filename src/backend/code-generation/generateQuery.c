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


static void generateComparisson( Comparison * comparison ){
    switch (comparison->type)
    {
    case (CGT):
        strcat(query_code, " > ");
        break;
    case (CLT):
        strcat(query_code, " < ");
        break;
    case (CEQ):
        strcat(query_code, " == ");
        break;
    case (CGTEQ):
        strcat(query_code, " >= ");
        break;
    case (CLTEQ):
        strcat(query_code, " <= ");
        break;
    case (CNEQ):
        strcat(query_code, " <> ");
        break;
    
    default:
        break;
    }
}

static void generateFactor( Factor * factor ){
    switch (factor->type)
    {
    case FTC_NAME:
        
        strcat(query_code, remover_comillas_extremos(factor->data));
        break;
    case INT:
        strcat(query_code, factor->data);
        break;
    case FSTRING:
        strcat(query_code, modificar_comillas(factor->data));
        break;
    default:
        break;
    }
}

static void generateTerm( Term * term ){
    switch (term->type)
    {
    case TALL:
        generateTerm(term->term);
        strcat(query_code, " * ");
        generateFactor(term->factor);
        break;
    case TDIV:
        generateFactor(term->factor);
        strcat(query_code, " / ");
        generateTerm(term->term);
        break;
    case FACTOR:
        generateFactor(term->factor);
        break;
    
    default:
        break;
    }
}

static void generateExpression( Expression * expression ){
    switch (expression->type)
    {
    case TERM:
        generateTerm(expression->term);
        break;
    case EADD:
        generateExpression(expression->expression);
        strcat(query_code, " + ");
        generateTerm(expression->term);
        break;
    case ESUB:
        generateExpression(expression->expression);
        strcat(query_code, " - ");
        generateTerm(expression->term);
        break;
    
    default:
        break;
    }
}

static void generateCondition( Condition * condition ){
    generateExpression(condition->leftExpression);
    generateComparisson(condition->comparison);
    generateExpression(condition->rightExpression);
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
    strcat(query_code,";");
    return query_code;
}