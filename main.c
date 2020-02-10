/*Musat Mihai-Robert - 313CB*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "structuri.h"

int main(int argc, char** argv) {
	FILE *input, *output;
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	stiva s;	
	initS(&s);
	char op[30], cul[30];
	while(fscanf(input, "%s", op) != EOF) {
		if(!strcmp(op, "add")) {
			fscanf(input, "%s", cul);
			int dim;
			fscanf(input, "%d", &dim);
			int ok = addSGr(&s, cul, dim);
			if(ok == 0) {
				gru g;
				initGr(&g, cul);
				insertGr(&g, &dim, sizeof(int));
				insertS(&s, &g, sizeof(struct grup));
			}
		}
		if(!strcmp(op, "show")) {
			fscanf(input, "%s", cul);
			int ok = showCul(&s, cul, output);
			if(ok == 0) {
				fprintf(output, "A_%s:\n", cul);
				fprintf(output, "B_%s:\n", cul);
				fprintf(output, "C_%s:\n", cul);
			}
		}
		if(!strcmp(op, "play")) {
			int numar;
			fscanf(input, "%s%d", cul, &numar);
			playG(&s, cul, numar);	
		}
		if(!strcmp(op, "show_moves")) {
			int numar;
			fscanf(input, "%s%d", cul, &numar);
			showMoves(&s, cul, numar, output);
		}
	}
	dezalocSGr(&s);
	fclose(input);
	fclose(output);		
	return 0;
}
