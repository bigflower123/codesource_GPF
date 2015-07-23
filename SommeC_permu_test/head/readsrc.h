#ifndef READSRC_H_INCLUDED
#define READSRC_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

typedef struct src{
	int **Tab;
	int m;
	int n;
}source;

source * readsrc(const char *);
void aff_source(source *);
void freeSource(source *);
int *TabtoM(source * );
void aff_M(int *,int ,int );
void freeM(int *);
//int *ILS(int *M, int n, int m);
//int *IGA(int *M, int n, int m);

#endif // READSRC_H_INCLUDED
