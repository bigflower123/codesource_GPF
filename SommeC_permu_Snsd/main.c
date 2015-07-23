#include "head/readsrc.h"
#include "head/ILS.h"
#include "head/varglobal.h"
#include "head/f3setupcbarre.h"

int main(int argc, char **argv)
{
	int i;
	int * M;
	int * resultat;
  
	char *nomfichier;    // Fichier à charger
	if(argc < 2)
	{
	    printf("syntaxe : %s data/...\n", argv[0]);
	    return -1;
	}
	nomfichier = argv[1];
	if(lecture_fichier(nomfichier) != 0)
	{
		printf("Erreur ouverture fichier %s\n",nomfichier);
		return -1;
	}
	
	// print_pb_info();                 // Affichage de tableau de données
	
	M=Tab_jobtoM();                  // table de durée d'opération M[]

	// ILS
	resultat=ILS(M, nbjobs, nbmachines);
	printf("ILS la séquence de Jobs est: \n");
	for(i=0;i<nbjobs;i++)	
		printf("%-4d",resultat[i]);
	printf("\nILS Cbarre avec Setuptime est:  %d\n",calculer_cbarre(resultat));

	// IGA
	resultat=IGA(M, nbjobs, nbmachines);
	printf("IGA la séquence de Jobs est: \n");
	for(i=0;i<nbjobs;i++)	
		printf("%-4d",resultat[i]);	
	printf("\nIGA Cbarre avec Setuptime est:  %d\n",calculer_cbarre(resultat));
	
	free_tab_job();
	free(resultat);
	freeM(M);

	return 1;
}
