#include "molecules.h"
#define NB_MOLECULES 90130

#define taille 1000



int main(int argc, char *argv[])
{
	
	
	if( argc != 3 )
	{
		fprintf(stdout,"Missing arguments (nombre de molecules ) et taille min des cycles \n");
		exit(20);
	}
	//on recupère le chebi de la molécule passée en parametre
	int MAX = atoi(argv[1]);
	int MIN = atoi(argv[2]);
	
	srandom(getpid() + time(NULL));
	
	char src[64];
	sprintf(src,"tailles_cycles.data");
	
	FILE *F = fopen(src,"r");

	if( F == NULL)
	{
		fprintf(stdout,"Cannot read the file %s\n",src);
		exit(87);
	}
	
	sprintf(src,"molecules.data");
	FILE *G = fopen(src,"w");

	if( G == NULL)
	{
		fprintf(stdout,"Cannot read the file %s\n",src);
		exit(88);
	}
	
	sprintf(src,"distribution_echantillon.data");
	FILE *H = fopen(src,"w");

	if( H == NULL)
	{
		fprintf(stdout,"Cannot read the file %s\n",src);
		exit(89);
	}
	
	
	
	
	int mol,i, cycles;
	
	int tab[NB_MOLECULES];
	int molecules[NB_MOLECULES];
	int distri[taille];
	int cycle[NB_MOLECULES];
	
	for( i = 0; i < NB_MOLECULES; i++) tab[i] = 0;
	for( i = 0; i < taille; i++) distri[i] = 0;
	for( i = 0; i < NB_MOLECULES; i++)
	{
		fscanf(F,"%d",&mol);
		fscanf(F,"%d",&cycles);
		molecules[i] = mol;
		cycle[i] = cycles;
		if( cycles > 0)
			tab[i] = 1;
	}
	
	i = 0;
	int num;
	while( i < MAX)
	{
		num = (int)(((double)random()/RAND_MAX) * NB_MOLECULES);
		
		if ( tab[num] == 1 && cycle[num] >= MIN )
		{
			tab[num] = 2;
			distri[cycle[num]]++;
			fprintf(G, "%d\n",molecules[num]);
			i++;
		}
	}
	
	int somme = 0;
	
	for( i = 0; i < taille; i++)
	{
		somme += distri[i];
		fprintf(H, "%d %d\n",i, distri[i]);
		//printf("%d\n",somme);
		if(somme == MAX)
			break;
	}
	
	
	
	
	fclose(F);
	fclose(G);
	fclose(H);
	
	
	system("gnuplot ./distribution.gplt");
	
	
	exit(0);
}

