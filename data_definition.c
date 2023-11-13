/* Marcu Gentiana Adeane 313CB */
#include "little_functions.h"
#include "functions.h"


// initializing database
// first command
t_db *INIT_DB(char *db_name){

	t_db *db = (t_db *)calloc(1, sizeof(t_db));
	if (!db) { // if it fails
		printf("Error allocating database\n");
		return NULL;
	}
	strcpy(db->name, db_name);
	return db;
}

void freeColumns(t_column *column) {
	t_column *aux, *i;
	// going through columns
	for (i = column; i != NULL;) {
		aux = i;
		i = i->next;
		free(aux);
	}
}

// freeing the whole table
void freeTable(t_table *table){
	freeLines(table);
	freeColumns(table->columns);
	free(table);
}

// frees used memory
// last command
void DELETE_DB(t_db *db){
	t_table *i, *aux;
	// going through tables
	for (i = db->tables; i != NULL;) {
		aux = i;
		i = i->next;
		freeTable(aux);
	}
	free(db);
}


void CREATE(t_db *db, char *table_name, char *type, int n,
	char **column_names){

	t_table *j = NULL;
	if (db->tables) {
		// going through tables to see if it already exists
		for (j = db->tables; j->next != NULL; j = j->next) {
			if (strcmp(j->name, table_name) == 0) {
				printf("Table \"%s\" already exists.\n", table_name);
				return;
			}
		}
	}


	t_table *table = (t_table *)calloc(1, sizeof(t_table));
	if (!table) {
		return;
	}

	int i;
	t_column *head, *act; // head of column list and actual element
	head = (t_column *)calloc(1, sizeof(t_column)); // alocating the head
	if (!head) {
		return;
	}
	// head takes the first name from the array
	strcpy(head->name, column_names[0]);
	act = head;
	// going through array of column names to create the list of column names
	for (i = 1; i < n; i++) {
		act->next = (t_column *)calloc(1, sizeof(t_column));
		if (!act->next) {
			free(head);
			return;
		}
		strcpy(act->next->name, column_names[i]);
		act = act->next;
	}

	table->columns = head; // adding the list i created to the table

	if (strcmp(type, "INT") == 0) {
		table->type = INT;
	}
	else if (strcmp(type, "STRING") == 0) {
		table->type = STRING;
	}
	else {
		table->type = FLOAT;
	}

	strcpy(table->name, table_name);

	// if the table I created is the first table from the database...
	if (db->tables == NULL) {
		db->tables = table; // ... make it be the first table of the database...
	}
	else {
		j->next = table; // ...else, add it after the last table
	}
}

// delete a table

void DELETE_TABLE(t_db *db, char *table_name){
	t_table *ant, *act, *i;
	// going through tables
	for (i = db->tables, ant = NULL; i != NULL;) {
		if (strcmp(i->name, table_name) == 0) {
			act = i;
			i = i->next;
			if (ant == NULL) { // if it's the first table
				db->tables = i; // head of list of tables becomes the next table
			}
			else {
				ant->next = i;
			}
			freeTable(act);
			return;
		}
		else {
			ant = i;
			i = i->next;
		}
	}
	printf("Table \"%s\" not found in database.\n", table_name);
}
