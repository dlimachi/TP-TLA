#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"

#define LEN 1024
#define TC_LEN 128

static char tc_name[TC_LEN];
static int progress;
stringList code = createList();
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