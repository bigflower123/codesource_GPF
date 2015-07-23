/**
 * F3 || permu,Snsd || Cbarre.
 * PSE sur un fichier.
 */
#include "head/f3setupcbarre.h"


/**
 * PROCEDURES
 */

/**
 * int lecture_fichier(nomfichier)
 *
 * Cette procédure permet la lecture du fichier de données.
 * Les données sont enregistrées dans le tableau Tab_job[].
 *
 * E:     nomfichier : nom du fichier de données à ouvrir.
 * PrecC: Néant.
 * 
 * S:     Entier.
 * PostC: La lecture a réussi et la fonction renvoie 0, ou la lecture a échoué et la fonction renvoie -1.
 */
int lecture_fichier(char *nomfichier){
	int i,j;
	/* Fichier de données. */
	FILE *f;
	
	f = fopen(nomfichier, "rt");
	if(f == NULL) return -1;
	
	/* Lecture. */
	fscanf(f, "%d", &nbmachines);
	fscanf(f, "%d", &nbjobs);
	
	/* Allocation mémoire */
	Tab_job = (Job *)malloc(sizeof(Job)*nbjobs);
	for(j = 0; j < nbjobs; j++)
	{
		Tab_job[j].s = (int *)malloc(sizeof(int)*nbmachines);
		Tab_job[j].p = (int *)malloc(sizeof(int)*nbmachines);
	}
	
	/* Lecture tableau. */
	for(i = 0; i < nbmachines; i++)
	{
		for(j = 0; j < nbjobs; j++)
		{
			fscanf(f,"%d,%d ",&Tab_job[j].s[i],&Tab_job[j].p[i]);
		}
	}
	
	return 0;
}

/**
 * void free_tab_job(void)
 *
 * Cette procédure permet de désallouer l'espace mémoire de Tab_job[].
 *
 */
void free_tab_job(void){
	int j;
	for(j = 0; j < nbjobs; j++)
	{
		free(Tab_job[j].s);
		free(Tab_job[j].p);
	}
	free(Tab_job);
}
 
/**
 * void print_pb_info(void)
 *
 * Cette procédure permet d'affichier les informations du problème à résoudre.
 *
 */
void print_pb_info(void){
	int i,j;
	
	printf("--------Problème à résoudre:--------\n");
	printf("nbmachines=%d, nbjobs=%d\n",nbmachines,nbjobs);
	/* Affichage de tableau de job */
	for(i = 0; i < nbmachines; i++)
	{
		for(j = 0; j < nbjobs; j++)
		{
			printf("%d,%d\t",Tab_job[j].s[i], Tab_job[j].p[i]);
		}
		printf("\n");
	}
}

/**
 * void print_node_info(void)
 *
 * Cette procédure permet d'affichier les informations d'un noeud.
 * 
 * E:     noeud : un noeud.
 * PrecC: Néant.
 * 
 * S:     Néant.
 * PostC: Néant.
 */
void print_node_info(Node *noeud){
	int i;
	
	if(noeud != NULL)
	{
		printf("---------------------------------------------\n");
		if(noeud->Seq != NULL)
		{
			printf("Jobs Traités %d: ", noeud->tailleSeq);
			for(i = 0; i < noeud->tailleSeq; i++)
				printf("J%d ",noeud->Seq[i]);
			printf("\n");
		}
		if(noeud->AFaire != NULL)
		{
			printf("Jobs à Traiter %d: ", noeud->tailleAFaire);
			for(i = 0; i < noeud->tailleAFaire; i++)
				printf("J%d ",noeud->AFaire[i]);
			printf("\n");
		}
		printf("LB = %d\n",noeud->LB);
	}
}

/**
 * void pse(node)
 *
 * Cette procédure permet de trouver la solution optimale du problème.
 *
 * E:     node : un noeud de l'arbre de recherche
 * PrecC: Néant.
 * 
 * S:     Néant.
 * PostC: La solution optimale est trouvée et enrigistrée.
 */
 
void pse(Node *noeud){
	int i,cbarre;
	Node *fils;
	
	if(noeud == NULL) return;
	
	/* Evaluation d'un noeud */
	nbexplore++;
	//print_node_info(noeud);
	
	if(noeud->tailleAFaire == 0) // un noeud feuille
	{
		cbarre = calculer_cbarre(noeud->Seq);
		//printf("cbarre = %d\n",cbarre);
		if(UB > cbarre) // mise à jour UB
		{
			UB = cbarre;
			for(i = 0; i < nbjobs; i++) // mise à jour la séquence
				bestseq[i] = noeud->Seq[i];
		}
	}
	else // un noeud non feuille
	{
		noeud->LB = calculer_LB(noeud->Seq);
		if(noeud->LB > UB) /* Supprimmer ce noeud */
		{
			nbsupprime++;
			free_node(noeud);
			return;
		}
		else /* Continuer à explorer ce noeud */
		{
			for(i = 0; i < noeud->tailleAFaire; i++)
			{
				/* Création d'un noeud fils */
				fils = create_node(noeud,i);
				/* Explorer ce noeud */
				pse(fils);
			}
		}
	}
}

/**
 * Node* create_node(parent,pos)
 *
 * Cette procédure permet de créer un noeud fils par ajouter le job pos dans la séquence traité.
 *
 * E:     parent : un noeud de l'arbre de recherche
 *          pos: un entier indiquer la position dans la séquence AFaire
 * PrecC: parent n'est pas vide, pos inférieure à tailleAFaire de parent.
 * 
 * S:     fils: un noeud fils.
 * PostC: Retourner un noeud de l'arbre de recherche.
 */
Node * create_node(Node *parent, int pos)
{
	Node * fils;
	int i,indice;
	
	if(parent->tailleAFaire == 0) return NULL;
	
	/* Allocations */
	fils = (Node *) malloc (sizeof(Node));
	fils->LB = 0;
	fils->tailleSeq = parent->tailleSeq + 1;
	fils->tailleAFaire = parent->tailleAFaire -1;
	if(fils->tailleSeq > 0)	fils->Seq = (int *) malloc (sizeof(int)*fils->tailleSeq);
	if(fils->tailleAFaire > 0)	fils->AFaire = (int *) malloc (sizeof(int)*fils->tailleAFaire);
	
	/* Traitement de séquence de job déjà traité */
	for(i = 0; i < parent->tailleSeq; i++)
		fils->Seq[i] = parent->Seq[i];
	fils->Seq[fils->tailleSeq-1] = parent->AFaire[pos];
	
	/* Traitement de séquence de job déjà traité */
	indice = 0;
	for(i = 0; i < parent->tailleAFaire; i++)
	{
		if(i != pos)
		{
			fils->AFaire[indice] = parent->AFaire[i];
			indice++;
		}
	}
	return fils;
}

/**
 * void free_node(noeud)
 *
 * Cette procédure permet de désallouer la mémoire.
 *
 * E:     un noeud de l'arbre de recherche
 * PrecC: Néant.
 * 
 * S:     Néant
 * PostC: Désallouer la mémoire.
 */
void free_node(Node *noeud)
{
	if(noeud != NULL)
	{
		if(noeud->Seq != NULL) free(noeud->Seq);
		if(noeud->AFaire != NULL) free(noeud->AFaire);
		free(noeud);
	}
}

/**
 * int calculer_cbarre_cpt(sequence)
 *
 * Cette procédure permet de calculer le temps de complétion totale à partir d'une séquence de job.
 *
 * E:     sequence: une séquence complète de job
 *        jobcount: jobs qu'on va traiter
 * PrecC: Néant.
 * 
 * S:     cbarre: le temps de complétion totale
 * PostC: Retourner la valeur de cbarre
 */
int calculer_cbarre_cpt(int *sequence, int jobcount)
{
	int *C1, *C2, *C3; // Date de fin sur les trois machines
	int cbarre = 0; // Le temps de complétion totale
	int j,indice_job;
	
	/* Allocations */
	C1 = (int *) malloc (sizeof(int)*jobcount);
	C2 = (int *) malloc (sizeof(int)*jobcount);
	C3 = (int *) malloc (sizeof(int)*jobcount);
	
	/* Calcul de C1 */
	indice_job = sequence[0]; 
	C1[0] = Tab_job[indice_job].s[0] + Tab_job[indice_job].p[0];
	for(j = 1; j < jobcount; j++) // pour tous les jobs
	{
		indice_job = sequence[j]; // obtenir l'indice de jème job dans la séquence
		C1[j] = C1[j-1] + Tab_job[indice_job].s[0] + Tab_job[indice_job].p[0]; // pour la machine 1
	}
	
	/* Calcul de C2 */
	indice_job = sequence[0]; 
	C2[0] = max(C1[0], Tab_job[indice_job].s[1]) + Tab_job[indice_job].p[1];
	for(j = 1; j < jobcount; j++) // pour tous les jobs
	{
		indice_job = sequence[j]; // obtenir l'indice de jème job dans la séquence
		C2[j] = max(C1[j], C2[j-1] + Tab_job[indice_job].s[1]) + Tab_job[indice_job].p[1]; // pour la machine 2
	}
	
	/* Calcul de C3 */
	indice_job = sequence[0]; 
	C3[0] = max(C2[0], Tab_job[indice_job].s[2]) + Tab_job[indice_job].p[2];
	for(j = 1; j < jobcount; j++) // pour tous les jobs
	{
		indice_job = sequence[j]; // obtenir l'indice de jème job dans la séquence
		C3[j] = max(C2[j], C3[j-1] + Tab_job[indice_job].s[2]) + Tab_job[indice_job].p[2]; // pour la machine 3
	}
	
	/* Affichage de C 
	printf("\n**************************\n");
	for(j = 0; j < nbjobs; j++) printf("%d ", C1[j]);
	printf("\n**************************\n");
	for(j = 0; j < nbjobs; j++) printf("%d ", C2[j]);
	printf("\n**************************\n");
	for(j = 0; j < nbjobs; j++) printf("%d ", C3[j]);
	printf("\n**************************\n");*/
	
	/* Calcul de Cbarre */
	for(j = 0; j < jobcount; j++) // pour tous les jobs
	{
		cbarre = cbarre + C3[j];
	}
	/* Désallocations */
	free(C1);
	free(C2);
	free(C3);
	
	return cbarre;
}

int calculer_cbarre(int *sequence)
{
	int *C1, *C2, *C3; // Date de fin sur les trois machines
	int cbarre = 0; // Le temps de complétion totale
	int j,indice_job;
	
	/* Allocations */
	C1 = (int *) malloc (sizeof(int)*nbjobs);
	C2 = (int *) malloc (sizeof(int)*nbjobs);
	C3 = (int *) malloc (sizeof(int)*nbjobs);
	
	/* Calcul de C1 */
	indice_job = sequence[0]; 
	C1[0] = Tab_job[indice_job].s[0] + Tab_job[indice_job].p[0];
	for(j = 1; j < nbjobs; j++) // pour tous les jobs
	{
		indice_job = sequence[j]; // obtenir l'indice de jème job dans la séquence
		C1[j] = C1[j-1] + Tab_job[indice_job].s[0] + Tab_job[indice_job].p[0]; // pour la machine 1
	}
	
	/* Calcul de C2 */
	indice_job = sequence[0]; 
	C2[0] = max(C1[0], Tab_job[indice_job].s[1]) + Tab_job[indice_job].p[1];
	for(j = 1; j < nbjobs; j++) // pour tous les jobs
	{
		indice_job = sequence[j]; // obtenir l'indice de jème job dans la séquence
		C2[j] = max(C1[j], C2[j-1] + Tab_job[indice_job].s[1]) + Tab_job[indice_job].p[1]; // pour la machine 2
	}
	
	/* Calcul de C3 */
	indice_job = sequence[0]; 
	C3[0] = max(C2[0], Tab_job[indice_job].s[2]) + Tab_job[indice_job].p[2];
	for(j = 1; j < nbjobs; j++) // pour tous les jobs
	{
		indice_job = sequence[j]; // obtenir l'indice de jème job dans la séquence
		C3[j] = max(C2[j], C3[j-1] + Tab_job[indice_job].s[2]) + Tab_job[indice_job].p[2]; // pour la machine 3
	}
	
	/* Affichage de C 
	printf("\n**************************\n");
	for(j = 0; j < nbjobs; j++) printf("%d ", C1[j]);
	printf("\n**************************\n");
	for(j = 0; j < nbjobs; j++) printf("%d ", C2[j]);
	printf("\n**************************\n");
	for(j = 0; j < nbjobs; j++) printf("%d ", C3[j]);
	printf("\n**************************\n");*/
	
	/* Calcul de Cbarre */
	for(j = 0; j < nbjobs; j++) // pour tous les jobs
	{
		cbarre = cbarre + C3[j];
	}
	/* Désallocations */
	free(C1);
	free(C2);
	free(C3);
	
	return cbarre;
}

/**
 * int calculer_cbarre(sequence)
 *
 * Cette procédure permet de calculer le temps de complétion totale à partir d'une séquence de job.
 *
 * E:     sequence: une séquence complète de job
 * PrecC: Néant.
 * 
 * S:     cbarre: le temps de complétion totale
 * PostC: Retourner la valeur de cbarre
 */
int calculer_LB(int *sequence)
{
	return 63;
}


int min(int a, int b)
{
	if(a < b) return a;
	return b;
}
int max(int a, int b)
{
	if(a < b) return b;
	return a;
}
int calculer_nb_node_total(int n)
{
	int i,choixlayer = n,res = 1;
	for(i = 1; i <= n; i++) // layer i, n-i choix
	{
		res += choixlayer;
		choixlayer = choixlayer * (n-i);
	}
	return res;
}
