#include "head/readsrc.h"
#include "head/ILS.h"

int main(int argc, char **argv)
{
	source * src;
	int i;
	int * M;
	int * resultat;
       
	if(argc < 2)
	{
	    printf("syntaxe : %s benchmarks_Taillard/...\n", argv[0]);
	    return -1;
	}
	src=readsrc(argv[1]);          // table de durée d'opération Tab[][]
	M=TabtoM(src);                 // table de durée d'opération M[]
    //aff_source(src);
	//aff_M(M,src->n,src->m);

	// ILS
	resultat=ILS(M, src->n, src->m);
	printf("ILS la séquence de Jobs est: \n");
	for(i=0;i<src->n;i++)	
		printf("%-4d",resultat[i]);
	printf("\nILS la somme de date de fin est:  %d\n",calculateCbarre(M, src->m, src->n, resultat, src->n));

	// IGA
	resultat=IGA(M, src->n, src->m);
	printf("IGA la séquence de Jobs est: \n");
	for(i=0;i<src->n;i++)	
		printf("%-4d",resultat[i]);	
	printf("\nIGA la somme de date de fin est:  %d\n",calculateCbarre(M, src->m, src->n, resultat, src->n));
	
	free(resultat);
	freeSource(src);
	freeM(M);

	return 1;
}
