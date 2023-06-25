#include "../support/logger.h"
#include "generator.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "generators.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listUtils.h"



void Generator(Program * program) {
	// Generator va a generar un archivo .sql
	// nombre del archivo harcodeado
	LogInfo("El resultado de la expresion computada es: '%d'.", program);

	//recorro el arbol desde program y formo el correcto codigo sql
	//casos por tipo de general
	char * codeFinal = NULL;

	switch (program->general->type) {
        case(GINSERT):
            codeFinal = generateInsert(program->general->insertBody);
            break;
        case(GDELETE):
            codeFinal = generateDelete(program->general->deleteBody);
            break;
        case(GQUERY):
            codeFinal = generateQuery(program->general->queryBody);
            break;
        case(GCREATE):
            codeFinal = generateCreate(program->general->createBody);
            break;
        case(GCHECK):
			LogInfo("apunto de hacer un check!");
            codeFinal = generateCheck(program->general->check);
            break;
	    default:
		    break;
	}

	printf(codeFinal);
	LogInfo(codeFinal);

	//generar archivo con code

	FILE * output = fopen("output.sql", "w");
	if ( output == NULL )
		return;
	
	fprintf( output, "%s", codeFinal);
	
	fclose(output);


}

