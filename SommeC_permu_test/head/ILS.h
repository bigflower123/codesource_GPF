#ifndef ILS_H_INCLUDED
#define ILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define RZ_INT_MAX 99999999

typedef struct Cell
{
    int job[2];
    struct Cell *suivant;
}TypeCellule;



void insert(int* joblist, int length, int p, int j);
int calculateCbarre(int * M, int m, int n, int* joblist, int jobcount);
//int calculateSommeC(int *M, int m, int n, int* joblist, int jobcount);
int * RZ(int *M, int m, int n,int *PI);

int Affichage(TypeCellule* L);
TypeCellule * Append(TypeCellule *L, int jobnumero, int cm);
TypeCellule * Supprime(TypeCellule *L,int jobnumero);
void Liveration(TypeCellule **pL);
TypeCellule *Tri (TypeCellule *L);
TypeCellule * InsereElement(TypeCellule *L, int jobnumero, int xi);

void LR(int *M, int m, int n, TypeCellule ** U, TypeCellule** PI,int l, int d);

int *ILS(int *M, int n, int m, int *,int *);
int *perturbation(int *,int );
int *IGA(int *M, int n, int m,int *,int *);
int *destruction_construction(int *M,int *PI,int n,int m);
void releverRamdomJobs(int *PI1,int *PIr,int n,int d);


#endif // ILS_H_INCLUDED
