#include "head/ILS.h" 
#include "head/varglobal.h"
#include "head/f3setupcbarre.h"

#define IGA_D 8
#define IGA_LAMDA 2.0  
#define IGA_TIME 30

int *IGA(int *M, int n, int m){
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
	// iRZ(PI0)
	for(i=0;i<n;i++){
		PI[i]=dupPI0[i];
	}	
	PI=RZ( M,  m,  n, PI);
	// PIetoile <-PI	
	for(i=0;i<n;i++){
		PIetoile[i]=PI[i];
	}
	
	//calculer temperature
	for(i=0;i<n*m;i++){
		sumP+=M[i];
	}
	Temperature=(double)IGA_LAMDA*(double)sumP/(double)(10.0*m*n);
	gettimeofday(&tpstart,NULL);
	//time_t start, finish;
    //double  duration;
    //start=clock();
	while(timeuse<=IGA_TIME*n*m*0.001){
		// destruction_construction
		PI1=destruction_construction(M,PI,n,m);  // il faut free PI1
		// RZ
		for(i=0;i<n;i++){
			PI11[i]=PI1[i];
		}
		PI11=RZ(M, m, n, PI11);  // free PI11
		
		result_p11=calculer_cbarre(PI11);
		result_p=calculer_cbarre(PI);
		result_pe=calculer_cbarre(PIetoile);
		
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
	printf("\nIGA solution trouvée dans irération:%d/%d\n",nbr_itr_resulat,nbr_itr);
	printf("IGA runtime:%f\n",timeuse);
	Liveration(&PI0);
	PI0=NULL;
	free(PI1);
	free(PI11);
	free(dupPI0);
	free(PI);
	return PIetoile;	
}

/**
  * relever IGA_D jobs de PI au hasard, et refaire insertion dans le nouvelle PI1 
  * return la nouvelle séquence de jobs sur le tas
*/
int *destruction_construction(int *M,int *PI,int n,int m){
	int d=IGA_D;
	int *PI1,*PIr,*resDup;
        
	PI1=(int *)calloc(n,sizeof(int));
	PIr=(int *)calloc(d,sizeof(int));
	resDup = (int*)calloc(n,sizeof(int));
	int i,j,k,tmp,sommeC;
	int pos; //La position de l'insersion au final
	// PI1<-PI
	for(i=0;i<n;i++){
	    PI1[i]=PI[i];
	}
	// destrution
	releverRamdomJobs(PI1,PIr,n,d);  //PI1 rest n-d jobs, PIr contient d jobs
	// costruction
	for(k=0;k<d;k++)   // d jobs
	{
	    sommeC=RZ_INT_MAX;
	    for(j=0; j<=n-d; j++)//j est la position de l'insersion
	    {
		    memcpy(resDup, PI1, (n-d+k)*sizeof(int));
		    insert(resDup, n-d+k, j, PIr[k]);
		    tmp=calculer_cbarre_cpt(resDup, n-d+k+1);
		    if(tmp<sommeC)
		    {
		        sommeC=tmp;
		        pos=j;
		    }
	    }
	    insert(PI1,n-d+k ,pos, PIr[k]);
	}
	
	free(resDup);
	free(PIr);
	return PI1;
}
/**
  *  relever d jobs de PI, et les mettre dans PIr
*/
void releverRamdomJobs(int *PI1,int *PIr,int n,int d){
	int i,j,posRel;
	for(i=0;i<d;i++){
		posRel=rand()%(n--);
		PIr[i]=PI1[posRel];
		for(j=posRel;j<n;j++){
		    PI1[j]=PI1[j+1];
		}	
	}
}
