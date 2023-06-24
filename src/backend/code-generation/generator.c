#include "../support/logger.h"
#include "generator.h"
#include "../semantic-analysis/abstract-syntax-tree.h"

/**
 * Implementación de "generator.h".
 */

void Generator(Program * program) {
	// Generator va a generar un archivo .sql
	// nombre del archivo harcodeado
	LogInfo("El resultado de la expresion computada es: '%d'.", program);

	//recorro el arbol desde program y formo el correcto codigo sql
	//casos por tipo de general
	switch (program->general->type) {
        case(INSERT):
            generateInsert(program->general->insertBody);
            break;
        case(DELETE):
            generateDelete(program->general->deleteBody);
            break;
        case(QUERY):
            generateQuery(program->general->queryBody);
            break;
        case(CREATE):
            generateCreate(program->general->createBody);
            break;
        case(CHECK):
            generateCheck(program->general->check);
            break;
	    default:
		    break;
	}

}

void generateInsert(InsertBody * insertBody) {

}

void generateDelete(DeleteBody * deleteBody) {

}

void generateQuery(QueryBody * queryBody) {

}

void generateCreate(CreateBody * createBody) {

}

void generateCheck(Check * check) {

}

