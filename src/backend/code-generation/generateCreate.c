#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include <string.h>
#include "listUtils.h"
#include "generators.h"
#include <ctype.h>

#define CD_LEN 1024
#define TC_LEN 128

char tc_name[TC_LEN];
char key[TC_LEN];
char currentEnum[TC_LEN];
char enums[CD_LEN];
char * code;
int size;
int progress;


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
    strcat(code,columnName);
    strcat(code," ");
    stringToUpper(singleType->tc_name);
    strcat(code,singleType->tc_name);
    strcat(code, " REFERENCES ");
    strcat(code,tcNameFrom);
    strcat(code, "(");
    strcat(code, columnNameFrom);
    strcat(code, ")");
    if(action != NULL){
        strcat(code, " ");
        strcat(code, action);
        switch(options->type)
        {
            case(OCASCADE):
                strcat(code, " CASCADE");
                break;
            case(OSET_NULL):
                strcat(code," SET NULL");
                break;
            case(ORESTRICT):
                strcat(code, " RESTRICT");
                break;
            default:
                break;
        }
    }
}

void generateSingleType(char * columnName, SingleType * singleType ){
    strcat(code,columnName);
    strcat(code, " ");
    stringToUpper(singleType->tc_name);
    strcat(code,singleType->tc_name);
    if(key != NULL && strcmp(columnName, key)){
        strcat(code, " PRIMARY KEY ");
        return;
    }
}

void generateWithVarType(char * columnName,  char * varType ){
    strcat(code,columnName);
    strcat(code, " ");
    stringToUpper(varType);
    //stringToUpper(singleType->tc_name)
    strcat(code,varType);
    if(key != NULL && strcmp(columnName, key)){
        strcat(code, " PRIMARY KEY");
        return;
    }
}

void generateColumn(Column * column, char * varType ){
    LogDebug("puta madre %s", code);
    strcat(code,column->tc_name);
    strcat(code, " ");
    stringToUpper(varType);
    strcat(code,varType);
    if(key != NULL && !strcmp(column->tc_name, key)){
        strcat(code, " PRIMARY KEY");
        return;
    }
    if(column->is_unique){
        strcat(code, " UNIQUE");
    }
}
void generateColumns( Columns * columns, char * varType ){
    if ( columns->columns != NULL )
    {
        generateColumns(columns->columns, varType);
        strcat(code, ",\n\t");
    }
   if ( columns == NULL )
        return;
        
    generateColumn( columns->column, varType );

}
void generateStatement( Statement * statement ){
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

void generateStatements( Statements * statements ){
    if ( statements->statements != NULL )
    {
        generateStatements(statements->statements);
        strcat(code, ",\n\t");
    }
    if ( statements == NULL )
        return;
        
    generateStatement( statements->statement );
    
    
}

char * generateCreate( CreateBody * createBody ){
    code = malloc(CD_LEN);
    size = 1;
    strcat(code,"CREATE TABLE ");
    strcpy(tc_name, createBody->createTable->tc_name);
    strcat(code, tc_name);
    if(createBody->createTable->using_key){
        strcpy(key, createBody->createTable->key_name);
    }
    strcat(code," ( \n\t");
    generateStatements(createBody->statements);
    strcat(code, "\n);");
    return code;
}