#include "helpers.h"

void readFile(char *fileName, Cfg *cfg) {
	int numLines = 0;
	int i = 0;

	cfg->variablesGroup.group = malloc(sizeof(Group));
	cfg->variablesGroup.size = 0;
	cfg->symbolsGroup.group = malloc(sizeof(Group));
	cfg->symbolsGroup.size = 0;
	cfg->productions = malloc(sizeof(Production));

	FILE *file = NULL;
	char *line = malloc(sizeof(char) * 100);

	file = fopen(fileName, "r");
	if (file == NULL) {
		exit(-1);
	}

	// First line containing the Grammar variables
	fscanf(file, "%s", line);
	char *token = strtok(line, ",");
	while (token != NULL) {
		cfg->variablesGroup.group[cfg->variablesGroup.size++] = *token;
		token = strtok(NULL, ",");
		cfg->variablesGroup.group = realloc(cfg->variablesGroup.group, sizeof(char) * cfg->variablesGroup.size);
	}

	// Second line containing the Grammar symbols
	fscanf(file, "%s", line);
	token = strtok(line, ",");
	while (token != NULL) {
		cfg->symbolsGroup.group[cfg->symbolsGroup.size++] = *token;
		token = strtok(NULL, ",");
		cfg->symbolsGroup.group = realloc(cfg->symbolsGroup.group, sizeof(char) * cfg->symbolsGroup.size);
	}

	// Third line containing the number of productions
	fscanf(file, "%d", &cfg->numProductions);

	fgets(line, 10, file);
	free(line);
	// Next n lines containing the Productions
	do {
		cfg->productions[i].destination = malloc(sizeof(char) * 10);
		fscanf(file, "%c->%s\n", &cfg->productions[i].source, cfg->productions[i].destination);
		i++;
	} while (i != (cfg->numProductions));

	// Last line containing the initial variable
	fscanf(file, "%c", &cfg->initialVariable);
	fclose(file);
}

void showCfg(Cfg *cfg) {
	printf("V = ");
	printGroup(cfg->variablesGroup);
	printf("T = ");
	printGroup(cfg->symbolsGroup);
	printf("P = {\n");
	for (int i = 0; i < cfg->numProductions; i++) {
		printf("\t %c -> %s\n", cfg->productions[i].source, cfg->productions[i].destination);
	}
	printf("\t}\nS = %c\n", cfg->initialVariable);
}

int main(void) {
	Cfg *cfg = malloc(sizeof(Cfg));
	readFile("input.txt", cfg);

	showCfg(cfg);

	return 0;
}
