#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"
#include "generators.h"
#include <ctype.h>
#include "generators.h"



char key[TC_LEN];
char currentEnum[TC_LEN];
char enums[CD_LEN];
char * create_code;
int create_size;
static char create_tc_name[TC_LEN];
static int create_progress;


void stringToUpper(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = toupper(str[i]);
        i++;
    }
}

void appendEnums(EnumTypes * enumTypes){
    if(enumTypes==NULL){
        return;
    }
    appendEnums(enumTypes->enumTypes);

    if(enumTypes->enumTypes!=NULL){
        strcat(enums,", ");
    }

    strcat(enums, enumTypes->string);
}

void generateEnums(char * columnName, EnumTypes * enumTypes){
    strcat(enums,"CREATE TYPE ");
    stringToUpper(currentEnum);
    strcat(enums, currentEnum);
    strcat(enums, " AS ENUM (");

    appendEnums(enumTypes);
    strcat(enums, ");");
    strcat(enums, "\n");
}

void generateForm(char* columnName, SingleType * singleType, char* tcNameFrom, char * columnNameFrom, char * action, Options * options){
    strcat(create_code,columnName);
    strcat(create_code," ");
    stringToUpper(singleType->tc_name);
    strcat(create_code,singleType->tc_name);
    strcat(create_code, " REFERENCES ");
    strcat(create_code,tcNameFrom);
    strcat(create_code, "(");
    strcat(create_code, columnNameFrom);
    strcat(create_code, ")");
    if(action != NULL){
        strcat(create_code, " ");
        strcat(create_code, action);
        switch(options->type)
        {
            case(OCASCADE):
                strcat(create_code, " CASCADE");
                break;
            case(OSET_NULL):
                strcat(create_code," SET NULL");
                break;
            case(ORESTRICT):
                strcat(create_code, " RESTRICT");
                break;
            default:
                break;
        }
    }
}

void generateSingleType(char * columnName, SingleType * singleType ){
    strcat(create_code,columnName);
    strcat(create_code, " ");
    stringToUpper(singleType->tc_name);
    strcat(create_code,singleType->tc_name);
    if(key != NULL && strcmp(columnName, key)){
        strcat(create_code, " PRIMARY KEY ");
        return;
    }
}

void generateWithVarType(char * columnName,  char * varType ){
    strcat(create_code,columnName);
    strcat(create_code, " ");
    stringToUpper(varType);
    //stringToUpper(singleType->tc_name)
    strcat(create_code,varType);
    if(key != NULL && strcmp(columnName, key)){
        strcat(create_code, " PRIMARY KEY");
        return;
    }
}

static void generateColumn(Column * column, char * varType ){
    LogDebug("puta madre %s", create_code);
    strcat(create_code,column->tc_name);
    strcat(create_code, " ");
    stringToUpper(varType);
    strcat(create_code,varType);
    if(key != NULL && !strcmp(column->tc_name, key)){
        strcat(create_code, " PRIMARY KEY");
        return;
    }
    if(column->is_unique){
        strcat(create_code, " UNIQUE");
    }
}
static void generateColumns( Columns * columns, char * varType ){
    if ( columns->columns != NULL )
    {
        generateColumns(columns->columns, varType);
        strcat(create_code, ",\n\t");
    }
   if ( columns == NULL )
        return;
        
    generateColumn( columns->column, varType );

}
static void generateStatement( Statement * statement ){
    switch (statement->type)
    {
    case NORMAL:
        generateColumns(statement->columns, statement->as_name);
        break;
    case STNULLABLE:
        generateColumns(statement->columns, statement->as_name);
        break;
    case SINGLETYPE:
        generateSingleType(statement->column_name, statement->singleType);
        break;
    case NORMALFROM:
        generateForm(statement->column_name, statement->singleType, statement->tc_name_from, statement->column_name_from, NULL, NULL);
        break;
    case ONDELETEFROM:
        generateForm(statement->column_name, statement->singleType, statement->tc_name_from, statement->column_name_from, "ON DELETE", statement->options);
        break;
    case ONUPDATEFROM:
        generateForm(statement->column_name, statement->singleType, statement->tc_name_from, statement->column_name_from, "ON UPDATE", statement->options);
        break;
    case ASENUMCOLUMNS:
        memset(currentEnum, '\0', sizeof(currentEnum));
        strcat(currentEnum, statement->columns->column->tc_name);
        strcat(currentEnum,"_type");
        generateEnums(statement->column_name, statement->enumTypes);
        generateColumns(statement->columns, currentEnum);
        break;
    case ASENUMS:
        memset(currentEnum, '\0', sizeof(currentEnum));
        strcat(currentEnum, statement->column_name);
        strcat(currentEnum,"_type");
        generateEnums(statement->column_name, statement->enumTypes);
        generateWithVarType(statement->column_name, currentEnum);
        break;
    
    default:
        break;
    }


}

static void generateStatements( Statements * statements ){
    if ( statements->statements != NULL )
    {
        generateStatements(statements->statements);
        strcat(create_code, ",\n\t");
    }
    if ( statements == NULL )
        return;
        
    generateStatement( statements->statement );
    
    
}

char * generateCreate( CreateBody * createBody ){
    create_code = malloc(CD_LEN);
    create_size = 1;
    strcat(create_code,"CREATE TABLE ");
    strcpy(create_tc_name, createBody->createTable->tc_name);
    strcat(create_code, create_tc_name);
    if(createBody->createTable->using_key){
        strcpy(key, createBody->createTable->key_name);
    }
    strcat(create_code," ( \n\t");
    generateStatements(createBody->statements);
    strcat(create_code, "\n);");
    return create_code;
}