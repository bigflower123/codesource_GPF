#include "head/readsrc.h"
#include "head/ILS.h"
#include <sys/wait.h>
#include <unistd.h>

#define NBR_TEST 5


	
int main(int argc, char **argv)
{
	source * src;
	int i;
	int * M;
	int * resultatILS,*reusltatIGA;
    int pid;
    int ilssol=0;
    int igasol=0;  
	static int ils_itr;       // ILS compteur de nombre de l' itération
	static int ils_itr_sol;   // ILS compteur de la fois qu'on trouve la meilleur solution
	static int iga_itr;       // IGA compteur de nombre de l' itération
	static int iga_itr_sol;   // IGA compteur de la fois qu'on trouve la meilleur solution
		
	if(argc < 2)
	{
	    printf("syntaxe : %s benchmarks_Taillard/...\n", argv[0]);
	    return -1;
	}
	src=readsrc(argv[1]);          // table de durée d'opération Tab[][]
	M=TabtoM(src);                 // table de durée d'opération M[]
    //aff_source(src);
	//aff_M(M,src->n,src->m);
	pid=fork();
	if(pid==0){
		// ILS
		for(i=0;i<NBR_TEST;i++){
			resultatILS=ILS(M, src->n, src->m,&ils_itr,&ils_itr_sol);
			/*printf("ILS la séquence de Jobs est: \n");
			for(i=0;i<src->n;i++)	
			printf("%-4d",resultat[i]);*/
			//printf("ILS la somme de date de fin est:  %d\n",calculateCbarre(M, src->m, src->n, resultat, src->n));
			//printf("ILS solution trouvée dans irération:%d/%d\n",ils_itr_sol/NBR_TEST,ils_itr/NBR_TEST);
			ilssol+=calculateCbarre(M, src->m, src->n, resultatILS, src->n);
			free(resultatILS);
		}
		printf("ILS solution trouvée dans irération:   %d/%d\n",ils_itr_sol/NBR_TEST,ils_itr/NBR_TEST);
		printf("ILS la somme de date de fin est:  %d\n",ilssol/NBR_TEST);
	}else{
		// IGA
		for(i=0;i<NBR_TEST;i++){
			reusltatIGA=IGA(M, src->n, src->m, &iga_itr, &iga_itr_sol);
			/*printf("IGA la séquence de Jobs est: \n");
			for(i=0;i<src->n;i++)	
				printf("%-4d",resultat[i]);	*/
			//printf("IGA la somme de date de fin est:  %d\n",calculateCbarre(M, src->m, src->n, resultat, src->n));
			igasol+=calculateCbarre(M, src->m, src->n, reusltatIGA, src->n);
			//printf("\nIGA solution trouvée dans irération:%d/%d\n",iga_itr_sol/NBR_TEST,iga_itr/NBR_TEST);
			free(reusltatIGA);
		}
		printf("IGA solution trouvée dans irération:   %d/%d\n",iga_itr_sol/NBR_TEST,iga_itr/NBR_TEST);
		printf("IGA la somme de date de fin est:  %d\n",igasol/NBR_TEST);	
	}
	
	wait(NULL);
	
	
	freeSource(src);
	freeM(M);
    
	return 1;
}
