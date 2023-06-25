#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"

#define CD_LEN 1024
#define TC_LEN 128

char * code;
int size;
static char tc_name[TC_LEN];
static int progress;
// stringList code = createList();
/*

stringList generateFactor(Factor * factor){
    if(factor == null)
        return null;

    switch (factor->type) {
        case (FTC_NAME):
            addToList(code, factor->data);
            break;
        case INT:
            addToList(code, atoi(factor->data));
            break;
        case STRING:
            addToList(code, factor->data);
            break;
    }
    return code;
}

void generateTerm(Term * term){
    if (term == NULL)
        return null;

    switch (term->type) {
        case (FACTOR):
            generateFactor(term->factor);
            break;
        case TALL:
            generateTerm(term->term);
            code = addToList(code, term->type); //deberia tener el valor de esto
            generateCondition(checkBody->condition);
            break;
        case TDIV:
            generateCheckBody(checkBody->checkBody);
            code = addToList(code, term->type); //deberia tener el valor de esto
            generateCondition(checkBody->condition);
            break;
    }
    return code;
}

stringList generateExpression(Expression * expression){
    if (expression == NULL)
        return null;

    switch (expression->type) {
        case (TERM):
            generateTerm(expression->term);
            break;
        case EADD:
            generateExpression(expression->expression);
            addToList(code, expression->type);
            generateTerm(expression->term);
            break;
        case TDIV:
            generateExpression(expression->expression);
            addToList(code, expression->type);
            generateTerm(expression->term);
            break;

}

stringList generateComparison(Comparison * comparison){
    return addToList(code, comparison->type);
}

void generateCondition(Condition * condition){
    if(condition == NULL)
        return null;
    generateExpression(condition->leftExpression);
    generateComparison(condition->comparison);
    generateExpression(condition->rightExpression);
}


void generateCheckBody(CheckBody * checkBody){
    if (checkBody == NULL)
        return null;

    switch (checkBody->type) {
        case (CONDITION):
            generateCondition(checkBody->condition);
            break;
        case CAND:
            addToList(code, checkBody->type);
            generateCheckBody(checkBody->checkBody);
            generateCondition(checkBody->condition);
            break;
        case COR:
            addToList(code, checkBody->type);
            generateCheckBody(checkBody->checkBody);
            generateCondition(checkBody->condition);
            break;
    }
}

stringList generateCheck(Check * check) {
    strcpy(tc_name,check->tc_name);
    return code;
}
*/

void generateComparisson( Comparison * comparison ){
    switch (comparison->type)
    {
    case CGT:
        strcat(code, " > ");
        break;
    case CLT:
        strcat(code, " < ");
        break;
    case CEQ:
        strcat(code, " == ");
        break;
    case CGTEQ:
        strcat(code, " >= ");
        break;
    case CLTEQ:
        strcat(code, " <= ");
        break;
    case CNEQ:
        strcat(code, " <> ");
        break;
    
    default:
        break;
    }
}

void generateFactor( Factor * factor ){
    switch (factor->type)
    {
    case FTC_NAME:
        strcat(code, remover_comillas_extremos(factor->data));
        break;
    case INT:
        strcat(code, remover_comillas_extremos(factor->data));
        break;
    case FSTRING:
        strcat(code, modificar_comillas(factor->data));
        break;
    default:
        break;
    }
}

void generateTerm( Term * term ){
    switch (term->type)
    {
    case TALL:
        generateFactor(term->factor);
        strcat(code, " * ");
        generateTerm(term->term);
        break;
    case TDIV:
        generateFactor(term->factor);
        strcat(code, " / ");
        generateTerm(term->term);
        break;
    case TERM:
        generateFactor(term->factor);
        break;
    
    default:
        break;
    }
}

void generateExpression( Expression * expression ){
    switch (expression->type)
    {
    case TERM:
        generateTerm(expression->term);
        break;
    case EADD:
        generateTerm(expression->term);
        strcat(code, " + ");
        generateExpression(expression->expression);
        break;
    case ESUB:
        generateTerm(expression->term);
        strcat(code, " - ");
        generateExpression(expression->expression);
        break;
    
    default:
        break;
    }
}

void generateCondition( Condition * condition ){
    generateExpression(condition->leftExpression);
    generateComparisson(condition->comparison);
    generateExpression(condition->rightExpression);
}

void generateCheckBody( CheckBody * checkBody ){
    progress = strlen(code);
    if ( progress % CD_LEN < CD_LEN/9 )
        code = realloc(code, CD_LEN * ++size);
    
    switch (checkBody->type)
    {
    case CONDITION:
        generateCondition(checkBody->condition);
        break;
    case CAND:
        generateCondition(checkBody->condition);
        strcat(code, " AND ");
        generateCheckBody(checkBody->checkBody);
        break;
    case COR:
        generateCondition(checkBody->condition);
        strcat(code, " OR ");
        generateCheckBody(checkBody->checkBody);
        break;
    
    default:
        break;
    }

    
}


char * generateCheck( Check * check ){
    code = malloc(CD_LEN);
    size = 1;
    code[0] = 0;
    code[CD_LEN]=0;
    int progress = 0;

    char checkName[TC_LEN];
    strcpy(checkName,check->tc_name);

    strcat(code, "CONSTRAINT ");
    strcat(code, check->tc_name);


    strcat(code, "( ");
    generateCheckBody( check->checkBody );
    strcat(code, " )");

    return code;
}