/*Musat Mihai-Robert - 313CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"

//initializeaza stiva s
void initS(stiva *s) {
	*s = NULL;
}

//insereaza informatia de tip void* in stiva generica
void insertS(stiva *s, void *info, int size) {
	struct celulag *x = malloc(sizeof(struct celulag));
	x -> info = malloc(size);
	memcpy(x -> info, info, size);
	x -> urm = *s;
	*s = x;
}

//verifica daca stiva s este goala
int esteG(stiva s) {
	if(s == NULL) {
		return 1;
	}
	return 0;
}

//elibereaza stiva s
void deleteS(stiva *s) {
	if(esteG(*s)) {
		return;
	}
	struct celulag *x = (*s);
	(*s) = (*s) -> urm;
	x -> urm = NULL;
	free(x -> info);
	free(x);
}

//dezaloca stiva cu informatie de tip int
void dezalocSInt(stiva *s) {
	while(!esteG(*s)) {
		deleteS(s);
	}
}

//adauga ordonat in stiva s informatie de tip int 
void addOrdS(stiva *s, void *info, int size) {
	stiva s1;
	initS(&s1);
	while(*s) {
		int x1 = *((int *)((*s) -> info));
		int x2 = *((int *) info);
		if(x1 >= x2) {
			break;
		} else {
			insertS(&s1, (*s) -> info, size);
			deleteS(s);
		}
	}
	insertS(s, info, size);
	while(s1) {
		insertS(s, s1 -> info, size);
		deleteS(&s1);
	}
}

//afiseaza o stiva 
void showS(stiva *s, char *culoare, int stack, FILE *output) {
	if(stack == 1) {
		fprintf(output, "A_");
	}
	if(stack == 2) {
		fprintf(output, "B_");
	}
	if(stack == 3) {
		fprintf(output, "C_");
	}
	fprintf(output, "%s:", culoare);
	stiva s1;
	initS(&s1);
	while(*s) {
		insertS(&s1, (*s) -> info, sizeof(int));
		deleteS(s);
	}
	while(s1) {
		fprintf(output, " %d", *((int *)(s1 -> info)));
		insertS(s, s1 -> info, sizeof(int));
		deleteS(&s1);
	}
	fprintf(output, "\n");
}

//initializeaza un grup de stive 
void initGr(gru *g, char *nume) {
	g -> culoare = strdup(nume);
	g -> size = 0;
	g -> mutari = 0;
	initS(&(g -> a));
	initS(&(g -> b));
	initS(&(g -> c));
}

//insereaza intr-un grup de stive
void insertGr(gru *g, void *info, int size) {
	g -> size++;
	addOrdS(&(g -> a), info, size);
}

//dezaloca grup de stive 
void dezalocGr(gru *g) {
	free(g -> culoare);
	dezalocSInt(&(g -> a));
	dezalocSInt(&(g -> b));
	dezalocSInt(&(g -> c));
}

//dezaloca stive de grupuri
void dezalocSGr(stiva *s) {
	while(*s) {
		struct celulag *x = (*s);
		(*s) = (*s) -> urm;
		dezalocGr((gru *)(x -> info));
		free(x -> info);
		free(x);
	}
}

//afiseaza un grup de stive 
void showGr(gru *g, FILE *output) {
	showS(&(g -> a), g -> culoare, 1, output);
	showS(&(g -> b), g -> culoare, 2, output);
	showS(&(g -> c), g -> culoare, 3, output);
}

//adauga discul de dimensiune disc in grupul cu culoarea nume 
int addSGr(stiva *s, char *nume, int disc) {
	stiva s1;
	initS(&s1);
	int ok = 0;
	while(*s) {
		gru *g = ((gru *)((*s) -> info));
		if(!strcmp(nume, g -> culoare)) {
			insertGr(g, &disc, sizeof(int));
			ok = 1;
			break;
		}
		insertS(&s1, (*s) -> info, sizeof(gru));
		deleteS(s);
	}
	while(s1) {
		insertS(s, s1 -> info, sizeof(gru));
		deleteS(&s1);
	}
	return ok;
}

//afiseaza stiva din grupul de stive dupa culoare
int showCul(stiva *s, char *nume, FILE *output) {
	int ok = 0;
	stiva s1;
        initS(&s1);
        while(*s) {
                gru *g = ((gru *)((*s) -> info));
                if(!strcmp(nume, g -> culoare)) {
			showGr(g, output);
			ok = 1;
			break;
                }
                insertS(&s1, (*s) -> info, sizeof(gru));
                deleteS(s);
        }
        while(s1) {
                insertS(s, s1 -> info, sizeof(gru));
                deleteS(&s1);
        }
	return ok;
}

//muta cel mai mic disc in varful stivei opuse
int legalMove(stiva *a, stiva *b) {
	if(*a == NULL && *b == NULL) {
		return 0;
	}
	if(*a == NULL) {
		insertS(a, (*b) -> info, sizeof(int));
		deleteS(b);
		return 2;
	}
	if(*b == NULL) {
		insertS(b, (*a) -> info, sizeof(int));
		deleteS(a);
		return 1;
	}
	int x = *((int *)((*a) -> info));
	int y = *((int *)((*b) -> info));
	if(x <= y) {
		insertS(b, (*a) -> info, sizeof(int));
		deleteS(a);
		return 1;
	} else {
		insertS(a, (*b) -> info, sizeof(int));
		deleteS(b);
		return 2;
	}
}

//urmatoarea mutare din grupul de stive 
int nextMove(gru *g) {
	int m = g -> mutari;
	int n = g -> size;
	g -> mutari++;
	m++;
	if(m >= (1 << n)) {
		return - 1;
	}
	if(!(n % 2)) {
		if(m % 3 == 1) {
			int x = legalMove(&(g -> a), &(g -> b));
			if(x == 1) {
				return 1;
			} else {
				return 2;
			}
		
		}
		if(m % 3 == 2) {
			int x = legalMove(&(g -> a), &(g -> c));
			if(x == 1) {
				return 3;
			} else {
				return 4;
			}
		}
		if(m % 3 == 0) {
			int x = legalMove(&(g -> b), &(g -> c));
			if(x == 1) {
				return 5;
			} else {
				return 6;
			}
		}
	} else {
		 if(m % 3 == 1) {
                        int x = legalMove(&(g -> a), &(g -> c));
			if(x == 1) {
				return 3;
			} else {
				return 4;
			}
                }
                if(m % 3 == 2) {
                        int x = legalMove(&(g -> a), &(g -> b));
			if(x == 1) {
				return 1;
			} else {
				return 2;
			}
                }
                if(m % 3 == 0) {
                        int x = legalMove(&(g -> b), &(g -> c));
			if(x == 1) {
				return 5;
			} else {
				return 6;
			}
                }
	}
	return 0;
}

//joaca cate mutari dau ca parametru din grupul g
void playGr(gru *g, int mutari) {
	while(mutari != 0) {
		nextMove(g);
		mutari--;
	}
}

//afiseaza urmatoarele mutari
void playGr1(gru *g, int mutari, FILE *output) {
	fprintf(output, "M_");
	fprintf(output, "%s", g -> culoare);
	fprintf(output, ":");
	while(mutari != 0) {
		int x = nextMove(g);
		mutari--;
		if(x == 1) {
			fprintf(output, " A->B");
		}
		if(x == 2) {
			fprintf(output, " B->A");
		}
		if(x == 3) {
			fprintf(output, " A->C");
		}
		if(x == 4) {
			fprintf(output, " C->A");
		}
		if(x == 5) {
			fprintf(output, " B->C");
		}
		if(x == 6) {
			fprintf(output, " C->B");
		}
	}
	fprintf(output, "\n");
}

//joaca numar de mutari fix pentru o stiva cu un anumit nume
void playG(stiva *s, char *nume, int mutari) {
	stiva s1;
        initS(&s1);
        while(*s) {
                gru *g = ((gru *)((*s) -> info));
                if(!strcmp(nume, g -> culoare)) {
          		playGr(g, mutari);  
                        break;
                }
                insertS(&s1, (*s) -> info, sizeof(gru));
                deleteS(s);
        }
        while(s1) {
                insertS(s, s1 -> info, sizeof(gru));
                deleteS(&s1);
        }
}

//copiaza o stiva in alta stiva folosind stiva auxiliara
void copyS(stiva *s1, stiva *s2) {
	stiva s3;
	initS(&s3);
	while(*s1) {
		insertS(&s3, (*s1) -> info, sizeof(int));
		deleteS(s1);
	}
	while(s3) {
		insertS(s1, s3 -> info, sizeof(int));
		insertS(s2, s3 -> info, sizeof(int));
		deleteS(&s3);
	}
}

//copiaza un grup de stive
void copyG(gru *g1, gru *g2) {
	initGr(g2, g1 -> culoare);
	g2 -> size = g1 -> size;
	g2 -> mutari = g1 -> mutari;
	copyS(&(g1 -> a), &(g2 -> a));
	copyS(&(g1 -> b), &(g2 -> b));
	copyS(&(g1 -> c), &(g2 -> c));
}

//afiseaza numarul de mutari care trebuie executate pentru a termina jocul 
void showMoves(stiva *s, char *nume, int mutari, FILE *output) {
        stiva s1;
        initS(&s1);
        while(*s) {
                gru *g = ((gru *)((*s) -> info));
                if(!strcmp(nume, g -> culoare)) {
			gru g1;
			copyG(g, &g1);
                        playGr1(&g1, mutari, output);
			dezalocGr(&g1);
                        break;
                }
                insertS(&s1, (*s) -> info, sizeof(gru));
                deleteS(s);
        }
        while(s1) {
                insertS(s, s1 -> info, sizeof(gru));
                deleteS(&s1);
        }
}
