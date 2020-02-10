/*Musat Mihai-Robert - 313CB*/

#include <stdio.h>
#include "structuri.h"

void initS(stiva *s);
void insertS(stiva *s, void *info, int size);
int esteG(stiva s);
void deleteS(stiva *s);
void dezalocSInt(stiva *s);
void addOrdS(stiva *s, void *info, int size);
void showS(stiva *s, char *culoare, int stack, FILE *output);
void initGr(gru *g, char *nume);
void insertGr(gru *g, void *info, int size);
void dezalocGr(gru *g);
void dezalocSGr(stiva *s);
void showGr(gru *g, FILE *output);
int addSGr(stiva *s, char *nume, int disc);
int showCul(stiva *s, char *nume, FILE *output);
int legalMove(stiva *a, stiva *b);
int nextMove(gru *g);
void playGr(gru *g, int mutari);
void playGr1(gru *g, int mutari, FILE *output);
void playG(stiva *s, char *nume, int mutari);
void copyS(stiva *s1, stiva *s2);
void copyG(gru *g1, gru *g2);
void showMoves(stiva *s, char *nume, int mutari, FILE *output);











 
