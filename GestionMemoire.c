
#include "GestionMemoire.h"
#include "Ordonnancement.h"

void preparationMemoire()
/*
 * Initialisation des variables utilises pour la memoire
 */
{
	printf("Debut initialisation de la memoire...\n");
	
	printf("Calcul du nombre de cadres de page...\n");
	numCadresVive = tailleMemoireVive / tailleCadresPages;
	numCadresVirtuelle = tailleMemoireVirtuelle / tailleCadresPages;
	
	printf("Creation de la memoire vive... %d cadres\n", numCadresVive);
	memoireVive = (int*) malloc (sizeof(int) * numCadresVive);
	// Initialisation de la memoire vive
	int i = 0;
	for (; i<numCadresVive; ++i)
	{
		memoireVive[i] = -1;
	}
	
	printf("Creation de la memoire virtuelle... %d cadres\n", numCadresVirtuelle);
	memoireVirtuelle = (int*) malloc (sizeof(int) * numCadresVirtuelle);
	// Initialisation de la memoire virtuelle
	i = 0;
	for (; i<numCadresVirtuelle; ++i)
	{
		memoireVirtuelle[i] = -1;
	}
	
}

int reserveMemoire(int pid)
/*
 * Reserve la memoire pour un processus
 * Retourne 0, ou -1 si memoire non allouee
 */
{
	struct Processus p = tableProcessus[pid];
	int i = 0;
	while (i < tailleMemoireVirtuelle - p.taille)
	{
		if (memoireVive[i] == -1)
		{
			int j = i;
			for (; j < p.taille + i; ++j)
			{
				if (memoireVive[j] != -1)
					break;
			}
			if (j == p.taille + i)
			{
				placeProcessusMemoire(pid, i);
				return 0;
			}
			i = j;
		}
		++i;
	}
	return -1;
}

void demandeMemoire(int ecriture)
{
	printf("Memoire vive: %d cadres de page\n", numCadresVive);
	printf("Cadre de page: pid du processus, taille du processus\n");
	int i;
	for (i = 0; i < numCadresVive / 5; ++i)
	{
		int j;
		for (j = 0; j < 5; ++j)
		{
			printf("%d: %d, %d\t", i*5+j, tableProcessus[memoireVive[i*5+j]].pid, tableProcessus[memoireVive[i*5+j]].taille);
		}
	}
	for (i = i*5; i < numCadresVive; ++i)
	{
		printf("%d: %d, %d\t", i, tableProcessus[memoireVive[i]].pid, tableProcessus[memoireVive[i]].taille);
	}
	
	printf("Memoire virtuelle: %d cadres de page\n", numCadresVirtuelle);
	printf("Cadre de page: pid du processus, taille du processus\n");
	for (i = 0; i < numCadresVirtuelle / 5; ++i)
	{
		int j;
		for (j = 0; j < 5; ++j)
		{
			printf("%d: %d, %d\t", i*5+j, tableProcessus[memoireVirtuelle[i*5+j]].pid, tableProcessus[memoireVirtuelle[i*5+j]].taille);
		}
	}
	for (i = i*5; i < numCadresVirtuelle; ++i)
	{
		printf("%d: %d, %d\t", i, tableProcessus[memoireVirtuelle[i]].pid, tableProcessus[memoireVirtuelle[i]].taille);
	}
}

void placeProcessusMemoire(int pid, int mem)
/*
 * Place le processus d'identifiant pid dans la memoire
 * Ne retourne rien, on doit s'assurer avant d'appeler cette fonction que la memoire est libre,
 * sinon, elle sera ecrasee
 */
{
	int i = mem;
	for (; i < tableProcessus[pid].taille; ++i)
	{
		memoireVirtuelle[i] = pid;
	}
}

