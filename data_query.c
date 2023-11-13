/* Marcu Gentiana Adeane 313CB */
#include "little_functions.h"
#include "functions.h"


void printIntCells(t_intLine *line) {
	t_intCell *i;
	// going through cells
	for (i = line->cells; i != NULL; i = i->next) {
		printf("%*d ",-MAX_COLUMN_NAME_LEN, i->value);
	}
	printf("\n");
}

void printStringCells(t_stringLine *line) {
	t_stringCell *i;
	// going through cells
	for (i = line->cells; i != NULL; i = i->next) {
		printf("%*s ", -MAX_COLUMN_NAME_LEN, i->value);
	}
	printf("\n");
}

void printFloatCells(t_floatLine *line) {
	t_floatCell *i;
	// going through cells
	for (i = line->cells; i != NULL; i = i->next) {
		printf("%*f ", -MAX_COLUMN_NAME_LEN, i->value);
	}
	printf("\n");

}

void printIntLines(t_intLine *line) {
	t_intLine *i;
	// going through lines
	for (i = line; i != NULL; i = i->next) {
		printIntCells(i);
	}
}

void printStringLines(t_stringLine *line) {
	t_stringLine *i;
	// going through lines
	for (i = line; i != NULL; i = i->next) {
		printStringCells(i);
	}
}

void printFloatLines(t_floatLine *line) {
	t_floatLine *i;
	// going through lines
	for (i = line; i != NULL; i = i->next) {
		printFloatCells(i);
	}
}

// prints all lines no matter their type
void printLines(t_table *table) {
	if (table->type == INT) {
		printIntLines(table->lines);

	}
	else if (table->type == STRING) {
		printStringLines(table->lines);
	}
	else {
		printFloatLines(table->lines);
	}
}

// prints columns and returnes how many of them are
int printColumns(t_column *column){
	t_column *i;
	int columns_number = 0;
	// going through columns
	for (i = column; i != NULL; i = i->next) {
		printf("%s", i->name);
		printf("%*s", (int)(MAX_COLUMN_NAME_LEN - strlen(i->name) + 1), "");
		columns_number++;
	}
	printf("\n");
	return columns_number;
}

// prints padding
void printPadding(){
	int i;
	// i used a loop
	for (i = 0; i < MAX_COLUMN_NAME_LEN; i++) {
		printf("-");
	}
	printf(" ");
}

// prints table with all of his columns and lines
void printTable(t_table *table) {
	printf("TABLE: %s\n", table->name);
	int columns_number = printColumns(table->columns);
	int i;
	for (i = 0; i < columns_number; i++) {
		printPadding();
	}
	printf("\n");
	printLines(table);
	printf("\n");
}

void PRINT(t_db *db, char *table_name){
	t_table *table = searchTable(db, table_name);
	if (!table) { // if it doesn't find the table, print nothing
		return;
	}
	printTable(table);
}

// print database with all of its tables
void PRINT_DB(t_db *db){
	printf("DATABASE: ");
	printf("%s\n", db->name);
	printf("\n");
	t_table *i;
	for (i = db->tables; i != NULL; i = i->next) {
		printTable(i);
	}
}

void searchIntLine(t_table *table, int position, char *relation){
	int value, contor;
	scanf("%d", &value);
	t_intLine *i;
	t_intCell *j;
	// going through lines
	for (i = table->lines; i != NULL; i = i->next) {
		// going through cells
		for (contor = 0, j = i->cells; j != NULL; j = j->next, contor++) {
			if (contor == position) {
				if (strcmp(relation, "<") == 0) {
					if (j->value < value) {
						printIntCells(i);
					}
				}
				else if (strcmp(relation, "<=") == 0) {
					if (j->value <= value) {
						printIntCells(i);
					}
				}
				else if (strcmp(relation, "==") == 0) {
					if (j->value == value) {
						printIntCells(i);
					}
				}
				else if (strcmp(relation, "!=") == 0) {
					if (j->value != value) {
						printIntCells(i);
					}
				}
				else if (strcmp(relation, ">=") == 0) {
					if (j->value >= value) {
						printIntCells(i);
					}
				}
				else {
					if (j->value > value) {
						printIntCells(i);
					}
				}
				break;
			}
		}
	}
}

void searchStringLine(t_table *table, int position, char *relation){
	int contor;
	char *value = (char *)calloc(MAX_COLUMN_NAME_LEN, sizeof(char));
	if (!value) {
		return;
	}
	scanf("%s", value);
	t_stringLine *i;
	t_stringCell *j;
	// going through lines
	for (i = table->lines; i != NULL; i = i->next) {
		// going through cells
		for (contor = 0, j = i->cells; j != NULL; j = j->next, contor++) {
			if (contor == position) {
				if (strcmp(relation, "<") == 0) {
					if (strcmp(j->value, value ) < 0) {
						printStringCells(i);
					}
				}
				else if (strcmp(relation, "<=") == 0) {
					if (strcmp(j->value, value ) <= 0) {
						printStringCells(i);
					}
				}
				else if (strcmp(relation, "==") == 0) {
					if (strcmp(j->value, value ) == 0) {
						printStringCells(i);
					}
				}
				else if (strcmp(relation, "!=") == 0) {
					if (strcmp(j->value, value ) != 0) {
						printStringCells(i);
					}
				}
				else if (strcmp(relation, ">=") == 0) {
					if (strcmp(j->value, value ) >= 0) {
						printStringCells(i);
					}
				}
				else {
					if (strcmp(j->value, value ) > 0) {
						printStringCells(i);
					}
				}
				break;
			}
		}
	}
	free(value);
}

void searchFloatLine(t_table *table, int position, char *relation){
	int contor;
	float value;
	scanf("%f", &value);
	t_floatLine *i;
	t_floatCell *j;
	// going through lines
	for (i = table->lines; i != NULL; i = i->next) {
		// going through cells
		for (contor = 0, j = i->cells; j != NULL; j = j->next, contor++) {
			if (contor == position) {
				if (strcmp(relation, "<") == 0) {
					if (j->value < value) {
						printFloatCells(i);
					}
				}
				else if (strcmp(relation, "<=") == 0) {
					if (j->value <= value) {
						printFloatCells(i);
					}
				}
				else if (strcmp(relation, "==") == 0) {
					if (j->value == value) {
						printFloatCells(i);
					}
				}
				else if (strcmp(relation, "!=") == 0) {
					if (j->value != value) {
						printFloatCells(i);
					}
				}
				else if (strcmp(relation, ">=") == 0) {
					if (j->value >= value) {
						printFloatCells(i);
					}
				}
				else {
					if (j->value > value) {
						printFloatCells(i);
					}
				}
				break;
			}
		}
	}
}

void SEARCH(t_db *db, char *table_name, char *column, char *relation){
	t_table *table = searchTable(db, table_name);
	if (!table) {
		return;
	}
	int position = 0; // column position
	t_column *j;
	for (j = table->columns; j != NULL; j = j->next) {
		if (strcmp(j->name, column) == 0) {
			break;
		}
		position++;
	}
	if (!j) {
		printf("Table \"%s\" does not contain column \"%s\".\n",
			table_name, column);
		return;
	}
	printf("TABLE: %s\n", table->name);
	int columns_number = printColumns(table->columns);
	int i;
	for (i = 0; i < columns_number; i++) {
		printPadding();
	}
	printf("\n");
	if (table->type == INT) {
		searchIntLine(table, position, relation);
	}
	else if (table->type == STRING) {
		searchStringLine(table, position, relation);
	}
	else {
		searchFloatLine(table, position, relation);
	}
	printf("\n");
}