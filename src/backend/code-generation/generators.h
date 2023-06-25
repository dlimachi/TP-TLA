#include "../semantic-analysis/abstract-syntax-tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../support/logger.h"

char * generateDelete(DeleteBody * deleteBody);
char * generateQuery(QueryBody * queryBody);
char * generateCreate(CreateBody * createBody);
char * generateCheck(Check * check);
char * generateInsert(InsertBody * insertBody);

#define CD_LEN 2048
#define TC_LEN 128