/* Marcu Gentiana Adeane 313CB */
#include "functions.h"

int main() {

	char *command = (char *)calloc(MAX_CMD_LEN, sizeof(char));
	if (!command) {
		return 0;
	}
	char *db_name = (char *)calloc(MAX_DB_NAME_LEN, sizeof(char));
	if (!db_name) {
		free(command);
		return 0;
	}
	char *table_name = (char *)calloc(MAX_TABLE_NAME_LEN, sizeof(char));
	if (!table_name) {
		free(db_name);
		free(command);
		return 0;
	}
	char *column_name = (char *)calloc(MAX_CMD_LEN, sizeof(char));
	if (!column_name) {
		free(table_name);
		free(db_name);
		free(command);
		return 0;
	}
	char **column_names;
	char *type = (char *)calloc(7, sizeof(char));
	if (!type) {
		free(column_name);
		free(table_name);
		free(db_name);
		free(command);
		return 0;
	}
	char *relation = (char *)calloc(3, sizeof(char));
	if (!relation) {
		free(type);
		free(column_name);
		free(table_name);
		free(db_name);
		free(command);
		return 0;
	}
	t_db *db;

	while (scanf("%s", command)) {

		// data definition:

		if (strcmp(command, "INIT_DB") == 0) {
			scanf("%s", db_name);
			db = INIT_DB(db_name);
		}
		if (strcmp(command, "DELETE_DB") == 0) {
			DELETE_DB(db);
			break;
		}
		if (strcmp(command, "CREATE") == 0) {
			scanf("%s %s", table_name, type);
			if (strcmp(type, "INT") != 0 && strcmp(type, "STRING") != 0 &&
				strcmp(type, "FLOAT") != 0) {
				printf("Unknown data type: \"%s\".\n", type);
			}
			fgets(column_name, MAX_CMD_LEN, stdin);
			char *column_name_copy = strdup(column_name);
			if (!column_name_copy) {
				free(type);
				free(column_name);
				free(table_name);
				free(db_name);
				free(command);
				return 0;
			}
			int n = 0;
			char *token = strtok(column_name, " \n");
			while (token != NULL) {
				n++;
				token = strtok(NULL, " \n");
			}
			column_names = (char **)calloc(n, sizeof(char *));
			if (!column_names) {
				free(column_name_copy);
				free(type);
				free(column_name);
				free(table_name);
				free(db_name);
				free(command);
				return 0;
			}
			int i = 0;
			token = strtok(column_name_copy, " \n");
			while (token) {
				column_names[i] = strdup(token);
				if (!column_names[i]) {
					free(column_names);
					free(column_name_copy);
					free(type);
					free(column_name);
					free(table_name);
					free(db_name);
					free(command);
					return 0;
				}
				i++;
				token = strtok(NULL, " \n");
			}
			CREATE(db, table_name, type, n, column_names);
			for (i = 0; i < n; i++) {
				free(column_names[i]);
			}
			free(column_names);
			free(column_name_copy);
		}
		if (strcmp(command, "DELETE") == 0) {
			char newline;
			scanf("%s", table_name);
			scanf("%c", &newline);
			if (newline == '\n') { // if there aren't any other arguments
				DELETE_TABLE(db, table_name);
			}
			else {
				scanf("%s %s", column_name, relation);
				DELETE_LINES(db, table_name, column_name, relation);
			}
		}
		if (strcmp(command, "PRINT_DB") == 0) {
			PRINT_DB(db);
		}
		if (strcmp(command, "PRINT") == 0) {
			scanf("%s", table_name);
			PRINT(db, table_name);
		}
		if (strcmp(command, "SEARCH") == 0) {
			scanf("%s %s %s", table_name, column_name, relation);
			SEARCH(db, table_name, column_name, relation);
		}
		if (strcmp(command, "ADD") == 0) {
			scanf("%s", table_name);
			ADD(db, table_name);
		}
		if (strcmp(command, "CLEAR") == 0) {
			scanf("%s", table_name);
			CLEAR(db, table_name);
		}
	}

	free(command);
	free(db_name);
	free(table_name);
	free(column_name);
	free(type);
	free(relation);
}
