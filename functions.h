/* Marcu Gentiana Adeane 313CB */
#include "structures.h"


// data definition

t_db *INIT_DB(char *db_name);

void DELETE_DB(t_db *db);

void CREATE(t_db *db, char *table_name, char *type, int n, char **column_names);

void DELETE_TABLE(t_db *db, char *table_name); // deletes the whole table

// data query

void PRINT(t_db *db, char *table_name);

void PRINT_DB(t_db *db);

void SEARCH(t_db *db, char *table_name, char *column, char *relation);

// data manipulation

void CLEAR(t_db *db, char *table_name);

void ADD(t_db *db, char *table_name);

void DELETE_LINES(t_db *db, char *table_name, char *column, char *relation);