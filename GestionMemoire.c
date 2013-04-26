
#include "GestionMemoire.h"

void preparationMemoire()
{
	printf("Debut initialisation de la memoire...\n");
	
	printf("Calcul du nombre de cadres de page...\n");
	numCadresVive = tailleMemoireVive / tailleCadresPages;
	numCadresVirtuelle = tailleMemoireVirtuelle / tailleCadresPages;
	
	printf("Creation de la memoire vive... %d cadres", numCadresVive);
	memoireVive = (int*) malloc (sizeof(int) * numCadresVive);
	// Initialisation de la memoire vive
	int i = 0;
	for (; i<numCadresVive; ++i)
	{
		memoireVive[i] = -1;
	}
	
	printf("Creation de la memoire virtuelle... %d cadres", numCadresVirtuelle);
	memoireVirtuelle = (int*) malloc (sizeof(int) * numCadresVirtuelle);
	// Initialisation de la memoire virtuelle
	int i = 0;
	for (; i<numCadresVirtuelle; ++i)
	{
		memoireVirtuelle[i] = -1;
	}
	
}