#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"

#include "generators.h"



char * check_code;
int check_size;
static char check_tc_name[TC_LEN];
static int check_progress;

static void generateComparisson( Comparison * comparison ){
    switch (comparison->type)
    {
    case (CGT):
        strcat(check_code, " > ");
        break;
    case (CLT):
        strcat(check_code, " < ");
        break;
    case (CEQ):
        strcat(check_code, " == ");
        break;
    case (CGTEQ):
        strcat(check_code, " >= ");
        break;
    case (CLTEQ):
        strcat(check_code, " <= ");
        break;
    case (CNEQ):
        strcat(check_code, " <> ");
        break;
    
    default:
        break;
    }
}

static void generateFactor( Factor * factor ){
    switch (factor->type)
    {
    case FTC_NAME:
        
        strcat(check_code, remover_comillas_extremos(factor->data));
        break;
    case INT:
        strcat(check_code, factor->data);
        break;
    case FSTRING:
        strcat(check_code, modificar_comillas(factor->data));
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
        strcat(check_code, " * ");
        generateFactor(term->factor);
        break;
    case TDIV:
        generateFactor(term->factor);
        strcat(check_code, " / ");
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
        strcat(check_code, " + ");
        generateTerm(expression->term);
        break;
    case ESUB:
        generateExpression(expression->expression);
        strcat(check_code, " - ");
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

static void generateCheckBody( CheckBody * checkBody ){
    check_progress = strlen(check_code);
    if ( check_progress % CD_LEN < CD_LEN/9 )
        check_code = realloc(check_code, CD_LEN * ++check_size);
    
    switch (checkBody->type)
    {
    case CONDITION:
        generateCondition(checkBody->condition);
        break;
    case CAND:
        
        generateCondition(checkBody->condition);
        strcat(check_code, " AND ");
        generateCheckBody(checkBody->checkBody);
        break;
    case COR:
        generateCondition(checkBody->condition);
        strcat(check_code, " OR ");
        generateCheckBody(checkBody->checkBody);
        break;
    
    default:
        break;
    }

    
}


char * generateCheck( Check * check ){
    
    check_code = calloc(1,CD_LEN);
    check_size = 1;
    check_code[0] = 0;
    check_code[CD_LEN]=0;
    int check_progress = 0;

    char checkName[TC_LEN];
    strcpy(checkName,check->tc_name);

    strcat(check_code, "CONSTRAINT ");
    strcat(check_code, check->tc_name);


    strcat(check_code, "( ");
    
    generateCheckBody( check->checkBody );
    strcat(check_code, " );");

    return check_code;
}