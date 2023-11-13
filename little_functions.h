/* Marcu Gentiana Adeane 313CB */
#include "structures.h"

void freeLines(t_table *table);

t_table *searchTable(t_db *db, char *table_name);

void freeIntCells(t_intLine *line);

void freeStringCells(t_stringLine *line);

void freeFloatCells(t_floatLine *line);

