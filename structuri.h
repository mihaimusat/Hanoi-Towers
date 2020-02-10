/*Musat Mihai-Robet - 313CB*/

#ifndef _LISTA_H_
#define _LISTA_H_

//structura pentru liste si stive
typedef struct celulag {
	void *info;
	struct celulag *urm;
} nod, *lista, *stiva;

//structura pentru un grup format din trei stive : culoare, dimensiunea grupului si numarul de mutari disponibile
typedef struct grup {
	char *culoare;
	int size;
	int mutari;
	stiva a, b, c;
} gru;

#endif

