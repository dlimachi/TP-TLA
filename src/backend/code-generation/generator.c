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
	switch (program->general->type)
	{
	default:
		break;
	}
	//insert

	//delete

	//check

	//query


}
