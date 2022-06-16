#include "consts.h"
#include "helpers.h"

void readFile(char *fileName, Automata *automata) {
	int counter = 0;
	int i = 0;
	
	automata->symbols = malloc(sizeof(Symbols));
	automata->symbols->symbols = malloc(sizeof(char) * 100);

	automata->states = malloc(sizeof(States));
	automata->states->states = malloc(sizeof(int) * 100);

	automata->finalStates = malloc(sizeof(States));
	automata->finalStates->states = malloc(sizeof(int) * 100);

	automata->transitionFunction = NULL;

	automata->symbols->numSymbols = 0;
	automata->states->numStates = 0;
	automata->finalStates->numStates = 0;

	FILE *file = NULL;
	char *line = malloc(sizeof(char) * 100);

	file = fopen(fileName, "r");
	if (file == NULL) {
		exit(-1);
	}

	while (fgets(line, 100, file)) {
		counter++;
		if (counter == 1) {
			char *token = strtok(line, " ");
			while (token != NULL) {
				automata->symbols->symbols[automata->symbols->numSymbols++] = *token;
				token = strtok(NULL, " ");
			}
			automata->symbols->symbols = realloc(automata->symbols->symbols, sizeof(char) * automata->symbols->numSymbols);
		}

		if (counter == 2) {
			char *token = strtok(line, " ");
			while (token != NULL) {
				automata->states->states[automata->states->numStates++] = atoi(token);
				token = strtok(NULL, " ");
			}
			automata->states->states = realloc(automata->states->states, sizeof(int) * automata->states->numStates);
		}

		if (counter == 3) {
			char *token = strtok(line, " ");
			automata->inicialState = atoi(token);
		}

		if (counter == 4) {
      char *token = strtok(line, " ");
			while (token != NULL) {
				automata->finalStates->states[automata->finalStates->numStates++] = atoi(token);
				token = strtok(NULL, " ");
			}
			automata->finalStates->states = realloc(automata->finalStates->states, sizeof(char) * automata->finalStates->numStates);
		
      break;
		}
  }
  automata->transitionFunction = malloc((sizeof(int) * (automata->states->numStates * automata->symbols->numSymbols)));
  int x;
  char y;

	int **transition = NULL;
	transition = malloc(sizeof(int) * (automata->symbols->numSymbols * automata->states->numStates));

	for (int i = 0; i < automata->states->numStates; i++) {
		transition[i] = malloc(sizeof(int) * automata->symbols->numSymbols);
		automata->transitionFunction[i] = malloc((sizeof(int) * (automata->symbols->numSymbols)));
	}
	
  for (int j = 0; j < automata->states->numStates; j++) {
    for (int k = 0; k < automata->symbols->numSymbols; k++) {
			fgets(line, 100, file);
      fscanf(file, "(%d,%c)=%d", &x, &y, &transition[j][k]);
    }
  }
  free(line);
  for (int i = 0; i < automata->states->numStates; i++) {
    automata->transitionFunction[i] = transition[i];
  }
  free(transition);

	fclose(file);
}

int checkSymbols(char *word, Automata *automata) {
	int valid = 0;

	for (int i = 0; i < strlen(word); i++) {
		valid = 0;
		for (int j = 0; j < automata->symbols->numSymbols; j++) {
			if (word[i] == automata->symbols->symbols[j]) {
				valid = 1;
				break;
			}
		}
		if (!valid) {
			// valid = 0
			return valid;
		}
	}

	// valid = 1
	return valid;
}

int validateWord(char *word, Automata *automata) {
	int inicialStateIsFinal = 0;
	
  for (int i = 0; i < automata->finalStates->numStates; i++) {
    if (automata->inicialState == automata->finalStates->states[i]) {
    	inicialStateIsFinal = 1;
      break;
    }
  }

  if (inicialStateIsFinal && strlen(word) == 0) {
	  return 1;
  } else if (!checkSymbols(word, automata)) {
		return 0;
	}

	int actualState = automata->inicialState;
	char actualSymbol = word[0];
  int valid = 0;

	for (int i = 0; i < strlen(word) ; i++) {
    actualState = automata->transitionFunction[actualState][word[i] - 'a'];
    if (actualState == -1) {
      return 0;
    }
	}
  for (int i = 0; i < automata->finalStates->numStates; i++) {
    if (actualState == automata->finalStates->states[i]) {
      valid = 1;
      return valid;
    }
  }
  return valid;
}

void printAutomata(Automata *automata) {
	printf("Quintupla do automato:\n\n");
	printf("Alfabeto[%d]: {", automata->symbols->numSymbols);
	for (int i = 0; i < automata->symbols->numSymbols; i++) {
		if (i == automata->symbols->numSymbols - 1) {
			printf("%c}", automata->symbols->symbols[i]);
		} else {
			printf("%c, ", automata->symbols->symbols[i]);
		}
	}
	printf("\n");

	printf("Conjunto de estados[%d]: {", automata->states->numStates);
	for (int i = 0; i < automata->states->numStates; i++) {
		if (i == automata->states->numStates - 1) {
			printf("%d}", automata->states->states[i]);
		} else {
			printf("%d, ", automata->states->states[i]);
		}
	}
	printf("\n");

	printf("Estado inicial: %d\n", automata->inicialState);

	printf("Conjunto de estados finais[%d]: {", automata->finalStates->numStates);
	for (int i = 0; i < automata->finalStates->numStates; i++) {
		if (i == automata->finalStates->numStates - 1) {
			printf("%d}", automata->finalStates->states[i]);
		} else {
			printf("%d, ", automata->finalStates->states[i]);
		}
		
	}
	printf("\n");

	printf("Funcao Programa:\n");
	
	for (int i = 0; i < automata->states->numStates; i++) {
    for (int j = 0; j < automata->symbols->numSymbols; j++) {
  		printf("δ(%d, %c) = %d\n", automata->states->states[i], automata->symbols->symbols[j], automata->transitionFunction[i][j]);    
    }
	}
}

int main(void) {
	Automata *automata = malloc(sizeof(Automata));
	char *word = malloc(sizeof(char) * 50);
  int inicialStateIsFinal = 0;
	readFile("input.txt", automata);
	clearScreen();

	while (1) {
		printAutomata(automata);
		printf("\nDigite a palavra que quer verificar se pertence a linguagem.\n");
		printf("Digite :quit para sair.\n");
		fgets(word, 50, stdin);
		word[strlen(word)-1] = '\0';

		if (!strcmp(word, ":quit\0")) {
			return 0;
		}
		printf("\n");
	  
		if (validateWord(word, automata)) {
	    printf("Palavra aceita pela linguagem!\n"); 
	  } else {
	    printf("Palavra nao aceita pela linguagem\n");
	  }
		
		printf("\n");
		systemPause();
		clearScreen();
	}

	return 0;
}
