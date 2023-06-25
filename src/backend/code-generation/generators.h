#include "../semantic-analysis/abstract-syntax-tree.h"

char * generateDelete(DeleteBody * deleteBody);
char * generateQuery(QueryBody * queryBody);
char * generateCreate(CreateBody * createBody);
char * generateCheck(Check * check);
char * generateInsert(InsertBody * insertBody);

#define CD_LEN 1024
#define TC_LEN 128