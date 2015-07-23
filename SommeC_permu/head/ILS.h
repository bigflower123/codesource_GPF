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


/* intertion une tâche dans la séquence des tâches qui est */
void insert(int* joblist, int length, int p, int j);
/* pour calculer la somme des dates de fin d'une séquence */
int calculateCbarre(int * M, int m, int n, int* joblist, int jobcount);
/* alogrithme RZ(pi) pour nous donner une séquence des tâche assez bien */
int * RZ(int *M, int m, int n,int *PI);
/* affichage la liste des tâches */
int Affichage(TypeCellule* L);
/* mettre une tâche à la fin de la liste des tâches */
TypeCellule * Append(TypeCellule *L, int jobnumero, int cm);
/* suprimer une tâche dans la liste des tâches */
TypeCellule * Supprime(TypeCellule *L,int jobnumero);
/* free tous les sources de la liste */
void Liveration(TypeCellule **pL);
/* trier les tâche par la fonction d'indice */
TypeCellule *Tri (TypeCellule *L);
/* insertion dans la liste les tâches */
TypeCellule * InsereElement(TypeCellule *L, int jobnumero, int xi);
/* algorithme LR(n/m) pour nous donner une séquence des tâches assez bien.*/
void LR(int *M, int m, int n, TypeCellule ** U, TypeCellule** PI,int l, int d);

int *ILS(int *M, int n, int m);
int *perturbation(int *,int );
int *IGA(int *M, int n, int m);
int *destruction_construction(int *M,int *PI,int n,int m);
void releverRamdomJobs(int *PI1,int *PIr,int n,int d);

#endif // ILS_H_INCLUDED
