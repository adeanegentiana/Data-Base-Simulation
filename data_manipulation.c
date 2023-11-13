/* Marcu Gentiana Adeane 313CB */
#include "little_functions.h"
#include "functions.h"


// deletes all lines from a table
void CLEAR(t_db *db, char *table_name){
	t_table *table = searchTable(db, table_name);
	if (!table) {
		return;
	}
	freeLines(table);
}

void addIntLine(t_table *table, int columns_number) {
	t_intLine *line = (t_intLine *)calloc(1, sizeof(t_intLine));
	if (!line) {
		return;
	}
	line->cells = (t_intCell *)calloc(1, sizeof(t_intCell));
	if (!line->cells) {
		free(line);
		return;
	}
	scanf("%d", &line->cells->value);
	int j;
	t_intCell *act = line->cells;
	for (j = 1; j < columns_number; j++) {
		act->next = (t_intCell *)calloc(1, sizeof(t_intCell));
		if (!act->next) {
			free(act);
			free(line);
			return;
		}
		act = act->next;
		scanf("%d", &act->value);
	}
	if (table->lines == NULL) { // if table doesn't contain lines
		table->lines = line; // add first line to the table...
	}
	else {
		t_intLine *j;
		// else, going through lines
		for (j = table->lines; j->next != NULL; j = j->next);
		j->next = line; // add line I created after the last line from the table
	}
}

void addStringLine(t_table *table, int columns_number) {
	char *buffer = (char *)calloc(MAX_COLUMN_NAME_LEN, sizeof(char));
	if (!buffer) {
		return;
	}
	t_stringLine *line = (t_stringLine *)calloc(1, sizeof(t_stringLine));
	if (!line) {
		return;
	}
	line->cells = (t_stringCell *)calloc(1, sizeof(t_stringCell));
	if (!line->cells) {
		free(line);
		free(buffer);
		return;
	}
	scanf("%s", buffer);
	line->cells->value = strdup(buffer);
	if (!line->cells->value) {
		free(line->cells);
		free(line);
		free(buffer);
		return;
	}
	int j;
	t_stringCell *act = line->cells;
	for (j = 1; j < columns_number; j++) {
		act->next = (t_stringCell *)calloc(1, sizeof(t_stringCell));
		if (!act->next) {
			free(act);
			free(line);
			free(buffer);
			return;
		}
		act = act->next;
		scanf("%s", buffer);
		act->value = strdup(buffer);
		if (!act->value) {
			free(act);
			free(line);
			free(buffer);
			return;
		}
	}
	free(buffer);
	if (table->lines == NULL) { // if table doesn't contain lines
		table->lines = line; // add first line to the table...
	}
	else {
		t_stringLine *j;
		// else, going through lines
		for (j = table->lines; j->next != NULL; j = j->next);
		j->next = line; // add line I created after the last line from the table
	}
}

void addFloatLine(t_table *table, int columns_number) {
	t_floatLine *line = (t_floatLine *)calloc(1, sizeof(t_floatLine));
	if (!line) {
		return;
	}
	line->cells = (t_floatCell *)calloc(1, sizeof(t_floatCell));
	if (!line->cells) {
		free(line);
		return;
	}
	scanf("%f", &line->cells->value);
	int j;
	t_floatCell *act = line->cells;
	for (j = 1; j < columns_number; j++) {
		act->next = (t_floatCell *)calloc(1, sizeof(t_floatCell));
		if (!act->next) {
			free(act);
			free(line);
			return;
		}
		act = act->next;
		scanf("%f", &act->value);
	}
	if (table->lines == NULL) { // if table doesn't contain lines
		table->lines = line; // add first line to the table...
	}
	else {
		t_floatLine *j;
		// else, going through lines
		for (j = table->lines; j->next != NULL; j = j->next);
		j->next = line; // add line I created after the last line from the table
	}
}

void ADD(t_db *db, char *table_name) {
	t_table *table = searchTable(db, table_name);
	if (!table) {
		return;
	}
	int columns_number = 0;
	t_column *i;
	// going through columns...
	for (i = table->columns; i != NULL; i = i->next) {
		columns_number++; // ... to count them
	}
	if (table->type == INT) {
		addIntLine(table, columns_number);
	}
	else if (table->type == STRING) {
		addStringLine(table, columns_number);
	}
	else {
		addFloatLine(table, columns_number);
	}
}

void deleteIntLine(t_table *table, int position, char *relation){
	int value, contor;
	scanf("%d", &value);
	t_intLine *ant, *act, *i;
	t_intCell *j;
	// going through lines
	for (ant = NULL, i = table->lines; i != NULL; ) {
		// going through cells
		for (contor = 0, j = i->cells; j != NULL; j = j->next, contor++) {
			if (contor == position) {
				if (strcmp(relation, "<") == 0) {
					if (j->value < value) {
						break;
					}
				}
				else if (strcmp(relation, "<=") == 0) {
					if (j->value <= value) {
						break;
					}
				}
				else if (strcmp(relation, "==") == 0) {
					if (j->value == value) {
						break;
					}
				}
				else if (strcmp(relation, "!=") == 0) {
					if (j->value != value) {
						break;
					}
				}
				else if (strcmp(relation, ">=") == 0) {
					if (j->value >= value) {
						break;
					}
				}
				else {
					if (j->value > value) {
						break;
					}
				}
			}
		}
		if (j != NULL) {
			act = i;
			i = i->next;
			if (ant == NULL) {
				table->lines = i;
			}
			else {
				ant->next = i;
			}
			freeIntCells(act);
		}
		else {
			ant = i;
			i = i->next;
		}
	}
}

void deleteStringLine(t_table *table, int position, char *relation){
	char value[MAX_COLUMN_NAME_LEN];
	int contor;
	scanf("%s", value);
	t_stringLine *ant, *act, *i;
	t_stringCell *j;
	// going through lines
	for (ant = NULL, i = table->lines; i != NULL; ) {
		// going through cells
		for (contor = 0, j = i->cells; j != NULL; j = j->next, contor++) {
			if (contor == position) {
				if (strcmp(relation, "<") == 0) {
					if (strcmp(j->value, value ) < 0) {
						break;
					}
				}
				else if (strcmp(relation, "<=") == 0) {
					if (strcmp(j->value, value ) <= 0) {
						break;
					}
				}
				else if (strcmp(relation, "==") == 0) {
					if (strcmp(j->value, value ) == 0) {
						break;
					}
				}
				else if (strcmp(relation, "!=") == 0) {
					if (strcmp(j->value, value ) != 0) {
						break;
					}
				}
				else if (strcmp(relation, ">=") == 0) {
					if (strcmp(j->value, value ) >= 0) {
						break;
					}
				}
				else {
					if (strcmp(j->value, value ) > 0) {
						break;
					}
				}
			}
		}
		if (j != NULL) {
			act = i;
			i = i->next;
			if (ant == NULL) {
				table->lines = i;
			}
			else {
				ant->next = i;
			}
			freeStringCells(act);
		}
		else {
			ant = i;
			i = i->next;
		}
	}
}

void deleteFloatLine(t_table *table, int position, char *relation){
	float value;
	int contor = 0;
	scanf("%f", &value);
	t_floatLine *ant, *act, *i;
	t_floatCell *j;
	// going through lines
	for (ant = NULL, i = table->lines; i != NULL; ) {
		// going through cells
		for (contor = 0, j = i->cells; j != NULL; j = j->next, contor++) {
			if (contor == position) {
				if (strcmp(relation, "<") == 0) {
					if (j->value < value) {
						break;
					}
				}
				else if (strcmp(relation, "<=") == 0) {
					if (j->value <= value) {
						break;
					}
				}
				else if (strcmp(relation, "==") == 0) {
					if (j->value == value) {
						break;
					}
				}
				else if (strcmp(relation, "!=") == 0) {
					if (j->value != value) {
						break;
					}
				}
				else if (strcmp(relation, ">=") == 0) {
					if (j->value >= value) {
						break;
					}
				}
				else {
					if (j->value > value) {
						break;
					}
				}
			}
		}
		if (j != NULL) {
			act = i;
			i = i->next;
			if (ant == NULL) {
				table->lines = i;
			}
			else {
				ant->next = i;
			}
			freeFloatCells(act);
		}
		else {
			ant = i;
			i = i->next;
		}
	}
}

void DELETE_LINES(t_db *db, char *table_name, char *column, char *relation){
	t_table *table = searchTable(db, table_name);
	if (!table) {
		return;
	}
	int position = 0; // column position
	t_column *i;
	for (i = table->columns; i != NULL; i = i->next) {
		if (strcmp(i->name, column) == 0) {
			break;
		}
		position++;
	}
	if (!i) {
		printf("Table \"%s\" does not contain column \"%s\".\n",
			table_name, column);
		return;
	}
	if (table->type == INT) {
		deleteIntLine(table, position, relation);
	}
	else if (table->type == STRING) {
		deleteStringLine(table, position, relation);
	}
	else {
		deleteFloatLine(table, position, relation);
	}
}