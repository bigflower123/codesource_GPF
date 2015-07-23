#ifndef _VAR_GLOBAL_H
#define _VAR_GLOBAL_H

typedef struct job
{
	int *s; // temps de montage
	int *p; // durée opératoire
}Job;

typedef struct node
{
	int LB; // borne inf
	int *Seq; // tableau de job déjà traité
	int *AFaire; // tableau de job à traiter
	int tailleSeq; // taille de tableau Seq, nb de job déjà traité
	int tailleAFaire; // taille de tableau AFaire, nb de job à traiter
}Node;

/**
 * VARIABLES GLOBALES
 */
/* Nombre de machines. */
int nbmachines;
/* Nombre de travaux. */
int nbjobs;
/* Tableau des travaux du problème. */
Job *Tab_job;

/* Meilleur Cbarre */
int bestcbarre;
/* Meilleure séquence */
int *bestseq;

/* Nombre de noeud exploré */
int nbexplore;
/* Nombre de noeud supprimé */
int nbsupprime;

/* Borne supérieure */
int UB;

#endif
