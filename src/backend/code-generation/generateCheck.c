#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"

#define LEN 1024
#define TC_LEN 128

static char tc_name[TC_LEN];
static int progress;
stringList code = createList();

stringList generateFactor(Factor * factor){
    if(factor == null)
        return null;

    switch (factor->type) {
        case (FTC_NAME):
            strcpy(code->string, factor->data);
            break;
        case INT:
            strcpy(code->string, atoi(factor->data));
            break;
        case STRING:
            strcpy(code->string, factor->data);
            break;
    }
    return code;
}

void generateTerm(Term * term){
    if (term == NULL)
        return null;

    switch (term->type) {
        case (FACTOR):
            code = addToList(generateFactor(term->factor));
            break;
        case TALL:
            code = addToList(generateTerm(term->term));
            code = addToList(term->type); //deberia tener el valor de esto
            code = addToList(generateCondition(checkBody->condition));
            break;
        case TDIV:
            code = addToList(generateCheckBody(checkBody->checkBody));
            code = addToList(generateCondition(checkBody->condition));
            break;
    }
    return code;
}

stringList generateExpression(Expression * expression){
    if (expression == NULL)
        return null;

    generateTerm(expression->term);

}

stringList generateCondition(Condition * condition){
    if(condition == NULL)
        return null;
}


stringList generateCheckBody(CheckBody * checkBody){
    if (checkBody == NULL)
        return null;

    switch (checkBody->type) {
        case (CONDITION):
            code = addToList(generateCondition(checkBody->condition));
            break;
        case CAND:
            code = addToList(generateCheckBody(checkBody->checkBody));
            code = addToList(generateCondition(checkBody->condition));
            break;
        case COR:
            code = addToList(generateCheckBody(checkBody->checkBody));
            code = addToList(generateCondition(checkBody->condition));
            break;
    }
    return code;
}

stringList generateInsert(Check * check) {
    strcpy(tc_name,check->tc_name);
    return code;
}
