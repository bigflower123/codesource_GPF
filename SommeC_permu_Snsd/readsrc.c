#include "head/readsrc.h"
#include "head/varglobal.h"

/** lire le source dans les fichiers
  * return un structure de tableau de int Tab[n][m] contient les durée d'opération 
  * dans le fichers de durée d'opération, chaque data a besoin de 3 espases pour séparer
*/
source * readsrc(const char *path){
	int i,j;	
	char buf[4];
	source * tempSrc;
	tempSrc=(source *)malloc(sizeof(source));
	FILE * src;
	src=fopen(path,"r");
	// lire le nbr de machines et jobs
	fgets(buf,4,src);
	tempSrc->m=atoi(buf);
	fgets(buf,4,src);
	tempSrc->n=atoi(buf);
	fgets(buf,4,src);
	
	tempSrc->Tab=(int **)malloc(tempSrc->n*sizeof(int*));
	for(i=0; i<tempSrc->n; i++){
		tempSrc->Tab[i]=(int *)malloc(tempSrc->m*sizeof(int));
	}
	// lire les durées d'opération
	for(i=0; i<tempSrc->n; i++){
		for(j=0; j<tempSrc->m; j++){
			fgets(buf,4,src);
			tempSrc->Tab[i][j]=atoi(buf);
		}	
		fgets(buf,4,src);
	}
	fclose(src);
	return tempSrc;
}

/**
  *  changer le Tab[n][m] à la format de int *M pour stocker tous les éléments
  *  return un pointeur de M 
*/
int *TabtoM(source * src){
	int i,j;
	int *tempM;
	tempM=(int *)calloc(src->n*src->m,sizeof(int));
	for(i=0;i<src->m;i++){
		for(j=0;j<src->n;j++){
			tempM[i*src->n+j]=src->Tab[j][i];		
		}
	}
	return tempM;
} 
/**
  *  changer le Job *Tab_job à la format de int *M pour stocker tous les éléments
  *  return un pointeur de M 
*/
int *Tab_jobtoM(){
	int i,j;
	int *tempM;
	tempM=(int *)calloc(nbmachines*nbjobs,sizeof(int));
	for(i=0;i<nbmachines;i++){
		for(j=0;j<nbjobs;j++){
			tempM[i*nbjobs+j]=Tab_job[j].p[i];		
		}
	}
	return tempM;
} 

void freeSource(source * src){
	int i;
	for(i=0;i<src->n;i++){
		free(src->Tab[i]);
	}
	free(src->Tab);
	free(src);
}

void freeM(int *M){
	free(M);
}

void aff_source(source * src){
	int i,j;
	printf("nombre de Jobs est: %d\n",src->n);
	printf("nombre de Machines est: %d\n",src->m);
	for(i=0;i<src->n;i++){
		for(j=0;j<src->m;j++){
			printf("%-4d",src->Tab[i][j]);		
		}
		printf("\n");
	}
}

void aff_M(int *M,int n,int m){
	int i,j;
	printf("nombre de Jobs est: %d\n",n);
	printf("nombre de Machines est: %d\n",m);
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%-4d",M[j*n+i]);		
		}
		printf("\n");
	}
}
