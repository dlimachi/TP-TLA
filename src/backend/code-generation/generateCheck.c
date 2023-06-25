#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"
#include "../support/logger.h"

#include "generators.h"



char * check_code;
int check_size;
static char check_tc_name[TC_LEN];
static int check_progress;

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

static void generateComparisson( Comparison * comparison ){
    LogInfo("entrando a un comparisson!");
    switch (comparison->type)
    {
    case CGT:
        strcat(check_code, " > ");
        break;
    case CLT:
        strcat(check_code, " < ");
        break;
    case CEQ:
        strcat(check_code, " == ");
        break;
    case CGTEQ:
        strcat(check_code, " >= ");
        break;
    case CLTEQ:
        strcat(check_code, " <= ");
        break;
    case CNEQ:
        strcat(check_code, " <> ");
        break;
    
    default:
        LogInfo("ACA ESTA TODO MAL!");
        break;
    }
}

static void generateFactor( Factor * factor ){
    LogInfo("entrando a un factor!");
    switch (factor->type)
    {
    case FTC_NAME:
        
        strcat(check_code, remover_comillas_extremos(factor->data));
        break;
    case INT:
        strcat(check_code, remover_comillas_extremos(factor->data));
        break;
    case FSTRING:
        LogInfo("Hola que tal!");
        strcat(check_code, modificar_comillas(factor->data));
        break;
    default:
        LogInfo("ACA ESTA TODO MAL!");
        break;
    }
}

static void generateTerm( Term * term ){
    LogInfo("entrando a un term!");
    switch (term->type)
    {
    case TALL:
        generateFactor(term->factor);
        strcat(check_code, " * ");
        generateTerm(term->term);
        break;
    case TDIV:
        generateFactor(term->factor);
        strcat(check_code, " / ");
        generateTerm(term->term);
        break;
    case TERM:
        generateFactor(term->factor);
        break;
    
    default:
        LogInfo("ACA ESTA TODO MAL!");
        break;
    }
}

static void generateExpression( Expression * expression ){
    LogInfo("entrando a un expression!");
    switch (expression->type)
    {
    case TERM:
        generateTerm(expression->term);
        break;
    case EADD:
        generateTerm(expression->term);
        strcat(check_code, " + ");
        generateExpression(expression->expression);
        break;
    case ESUB:
        generateTerm(expression->term);
        strcat(check_code, " - ");
        generateExpression(expression->expression);
        break;
    
    default:
        LogInfo("ACA ESTA TODO MAL!");
        break;
    }
}

static void generateCondition( Condition * condition ){
    LogInfo("entrando a un condition!");
    generateExpression(condition->leftExpression);
    LogInfo("Hola que tal!");
    generateComparisson(condition->comparison);
    generateExpression(condition->rightExpression);
}

static void generateCheckBody( CheckBody * checkBody ){
    LogInfo("entrando a un checkBody!");
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
        LogInfo("Hola que tal!");
        strcat(check_code, " AND ");
        generateCheckBody(checkBody->checkBody);
        break;
    case COR:
        generateCondition(checkBody->condition);
        strcat(check_code, " OR ");
        generateCheckBody(checkBody->checkBody);
        break;
    
    default:
        LogInfo("ACA ESTA TODO MAL!");
        break;
    }

    
}


char * generateCheck( Check * check ){
    
    check_code = malloc(CD_LEN);
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
    strcat(check_code, " )");

    return check_code;
}