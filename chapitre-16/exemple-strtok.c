// ------------------------------------------------------------------
// exemple-strtok.c
// Fichier d'exemple du livre "Developpement Systeme sous Linux"
// (C) 2000-2019 - Christophe BLAESS <christophe@blaess.fr>
// https://www.blaess.fr/christophe/
// ------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

int main (void)
{
	char	*line;
	char	*field;
	int	n, c;

	if ((line = malloc(MAX_LENGTH)) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	n = 1;
	while (fgets(line, MAX_LENGTH, stdin) != NULL) {
		fprintf(stdout, "Line %d\n", n);
		c = 1;
		field = strtok(line, " \t");
		while (field != NULL) { 
			fprintf(stdout, "  field %d : %s\n", c, field);
			field = strtok(NULL, " \t");
			c ++;
		}
		n ++;
	}
	return EXIT_SUCCESS;
}
