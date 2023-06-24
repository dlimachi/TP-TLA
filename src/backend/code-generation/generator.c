#include "../support/logger.h"
#include "generator.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "generators.h"

/**
 * Implementación de "generator.h".
 */
void generateDelete(DeleteBody * deleteBody);
void generateQuery(QueryBody * queryBody);
void generateCreate(CreateBody * createBody);
void generateCheck(Check * check);

void Generator(Program * program) {
	// Generator va a generar un archivo .sql
	// nombre del archivo harcodeado
	LogInfo("El resultado de la expresion computada es: '%d'.", program);

	//recorro el arbol desde program y formo el correcto codigo sql
	//casos por tipo de general
	char * code;

	switch (program->general->type) {
        case(GINSERT):
            code = generateInsert(program->general->insertBody);
            break;
        case(GDELETE):
            generateDelete(program->general->deleteBody);
            break;
        case(GQUERY):
            generateQuery(program->general->queryBody);
            break;
        case(GCREATE):
            generateCreate(program->general->createBody);
            break;
        case(GCHECK):
            generateCheck(program->general->check);
            break;
	    default:
		    break;
	}

	printf(code);
	LogInfo(code);

	//generar archivo con code



}

