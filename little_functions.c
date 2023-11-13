/* Marcu Gentiana Adeane 313CB */
#include "little_functions.h"


void freeIntCells(t_intLine *line) {
	t_intCell *aux, *i;
	// going through cells and freeing them one by one
	for (i = line->cells; i != NULL;) {
		aux = i;
		i = i->next;
		free(aux);
	}
	free(line);
}

void freeStringCells(t_stringLine *line) {
	t_stringCell *aux, *i;
	// going through cells and freeing them one by one
	for (i = line->cells; i != NULL;) {
		aux = i;
		i = i->next;
		free(aux->value);
		free(aux);
	}
	free(line);
}

void freeFloatCells(t_floatLine *line) {
	t_floatCell *aux, *i;
	// going through cells and freeing them one by one
	for (i = line->cells; i != NULL;) {
		aux = i;
		i = i->next;
		free(aux);
	}
	free(line);
}

void freeIntLines(t_intLine *line) {
	t_intLine *i, *aux;
	// going through lines and freeing them one by one
	for (i = line; i != NULL;) {
		aux = i;
		i = i->next;
		freeIntCells(aux);
	}
}

void freeStringLines(t_stringLine *line) {
	t_stringLine *i, *aux;
	// going through lines and freeing them one by one
	for (i = line; i != NULL;) {
		aux = i;
		i = i->next;
		freeStringCells(aux);
	}
}

void freeFloatLines(t_floatLine *line) {
	t_floatLine *i, *aux;
	// going through lines and freeing them one by one
	for (i = line; i != NULL;) {
		aux = i;
		i = i->next;
		freeFloatCells(aux);
	}
}

// free all lines from a table no matter their type
void freeLines(t_table *table) {
	if (table->type == INT) {
		freeIntLines(table->lines);
	}
	else if (table->type == STRING) {
		freeStringLines(table->lines);
	}
	else {
		freeFloatLines(table->lines);
	}
	table->lines = NULL;
}


t_table *searchTable(t_db *db, char *table_name) {
	t_table *i;
	// going through tables
	for (i = db->tables; i != NULL; i = i->next) {
		if (strcmp(i->name, table_name) == 0) {
			return i;
		}
	}
	printf("Table \"%s\" not found in database.\n", table_name);
	return NULL;
}