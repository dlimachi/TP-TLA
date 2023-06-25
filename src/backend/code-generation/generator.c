#include "../support/logger.h"
#include "generator.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "generators.h"
#include "../../frontend/syntactic-analysis/bison-actions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listUtils.h"



void Generator(Program * program) {
	// Generator va a generar un archivo .sql
	// nombre del archivo harcodeado

	//recorro el arbol desde program y formo el correcto codigo sql
	//casos por tipo de general
	char * codeFinal = calloc(1,sizeof(CD_LEN));
	codeFinal[0] = 0;
	char * codeAux = NULL;

	Generals * toProcess = program->generals;

	while( toProcess != NULL ){
		switch (toProcess->general->type) {
        case(GINSERT):
            codeAux = generateInsert(toProcess->general->insertBody);
            break;
        case(GDELETE):
            codeAux = generateDelete(toProcess->general->deleteBody);
            break;
        case(GQUERY):
            codeAux = generateQuery(toProcess->general->queryBody);
            break;
        case(GCREATE):
            codeAux = generateCreate(toProcess->general->createBody);
            break;
        case(GCHECK):
            codeAux = generateCheck(toProcess->general->check);
            break;
	    default:
		    break;

		}

		size_t len = strlen(codeAux);
		size_t cur_len = strlen(codeFinal);

		codeFinal = realloc(codeFinal, cur_len + len);

		strcat(codeFinal,"\n");
		strcat(codeFinal,codeAux);

		// ACA!
		free(codeAux);

		if ( toProcess->type == MULTIPLE )
			toProcess = toProcess->generals;
		else
			break;
		
	}

	FreeProgram(program);
	LogInfo(codeFinal);

	//generar archivo con code

	FILE * output = fopen("output.sql", "w");
	if ( output == NULL )
		return;
	
	fprintf( output, "%s", codeFinal);
	
	fclose(output);

	free(codeFinal);


}

