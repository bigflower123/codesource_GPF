#include "head/ILS.h" 

#define ILS_GAMMA 5
#define ILS_LAMDA 4.0  
#define ILS_TIME 30

int *ILS(int *M, int n, int m){
	int i,sumP=0;
	int nbr_itr_resulat=0;
	int nbr_itr=0;
	int * dupPI0,*PI,*PIetoile,*PI1,*PI11;
	TypeCellule * U=NULL;    //U est une liste pour les jobs dont l'ordre est pas encore déterminé
	TypeCellule * PI0=NULL;    //PI est une liste pour les jobs dont l'ordre est déterminé
	TypeCellule * p;	
	struct timeval tpstart,tpend;
    float timeuse=0.0;
	int result_p,result_p11,result_pe;
	double Temperature;
	srand(time(0));

	// LR(n/m)
	LR(M, m, n, &U, &PI0, 0, n); //MODIF ICI     1: un séquence
	
	dupPI0 = (int*)calloc(n, sizeof(int));
	PI11=(int*)calloc(n, sizeof(int));
	PI=(int*)calloc(n, sizeof(int));
	PIetoile=(int*)calloc(n, sizeof(int));
	p=PI0;
	for(i=0;i<(n-1);i++)
	{
		*(dupPI0+i)=p->job[0];
		p=p->suivant;
	}
	*(dupPI0+i)=p->job[0];
	/*
	printf("LR la séquence de Jobs est: \n");
	for(i=0;i<n;i++)	
		printf("%-4d",dupPI0[i]);
	printf("\nLR la somme de date de fin est:  %d\n",calculateCbarre(M, m,n, dupPI0, n));*/
	// iRZ(PI0)
	for(i=0;i<n;i++){
		PI[i]=dupPI0[i];
	}	
	PI=RZ( M,  m,  n, PI);
	/*printf("iRZ la séquence de Jobs est: \n");
	for(i=0;i<n;i++)	
		printf("%-4d",dupPI0[i]);
	printf("\niRZ la somme de date de fin est:  %d\n",calculateCbarre(M, m,n, dupPI0, n));
	*/
	// PIetoile <-PI	
	for(i=0;i<n;i++){
		PIetoile[i]=PI[i];
	}
	//calculer temperature
	for(i=0;i<n*m;i++){
		sumP+=M[i];
	}
	Temperature=(double)ILS_LAMDA*(double)sumP/(double)(10.0*m*n);
	gettimeofday(&tpstart,NULL);
	//time_t start, finish;
    //double  duration;
    //start=clock();
	while(timeuse<=ILS_TIME*n*m*0.001){
		// perturbation
		PI1=perturbation(PI,n);  // il faut free PI1
		// RZ
		for(i=0;i<n;i++){
			PI11[i]=PI1[i];
		}
		PI11=RZ(M, m, n, PI11);  // free PI11
		result_p11=calculateCbarre(M, m, n, PI11, n);
		result_p=calculateCbarre(M, m, n, PI, n);
		result_pe=calculateCbarre(M, m, n, PIetoile, n);
		
		if(result_p11<result_p){
			for(i=0;i<n;i++){
			    PI[i]=PI11[i];
			}
			if(result_p11<result_pe){
			    for(i=0;i<n;i++){
			        PIetoile[i]=PI11[i];
			    }
			    nbr_itr_resulat=nbr_itr;
			}
		}
		else if(((double)rand()/(double)RAND_MAX)<=exp((double)result_p-(double)result_p11)/Temperature){
			for(i=0;i<n;i++){
			    PI[i]=PI11[i];
			}	
		}
	    nbr_itr++;
        //finish=clock();
        //duration = (double)(finish - start) / CLOCKS_PER_SEC;
		gettimeofday(&tpend,NULL);
		timeuse=(tpend.tv_sec-tpstart.tv_sec)+(tpend.tv_usec-tpstart.tv_usec)/1000000.0;
	}
	printf("ILS solution trouvée dans irération:%d/%d\n",nbr_itr_resulat,nbr_itr);
	printf("ILS runtime:%f\n",timeuse);
	Liveration(&PI0);
	PI0=NULL;
	free(PI1);
	free(PI11);
	free(dupPI0);
	free(PI);
	return PIetoile;	
}

/**
  * perturbation la séquence de jobs
  * return la nouvelle séquence de jobs sur le tas
*/
int *perturbation(int *PI,int n){
	int *PI1;
    int valSelection;
	PI1=(int *)calloc(n,sizeof(int));
	int i,j,posSelection,posInsertion;
	for(i=0;i<ILS_GAMMA;i++){
		posSelection=rand()%n;
		while((posInsertion=rand()%n)==posSelection)	
			posInsertion=rand()%n;
		// construire PI1
		valSelection=PI[posSelection];
		for(j=0;j<posSelection;j++){
		    PI1[j]=PI[j];
		}
	    for(j=posSelection;j<n-1;j++){
		    PI1[j]=PI[j+1];
		}
		for(j=n-1;j>posInsertion;j--){
		    PI1[j]=PI1[j-1];
		}
		PI1[posInsertion]=valSelection;
	}
	return PI1;
}
