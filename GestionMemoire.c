
#include "GestionMemoire.h"
#include "Ordonnancement.h"

void preparationMemoire()
/*
 * Initialisation des variables utilisees pour la memoire
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

int reserveMemoire(int pid, int* memoire)
/*
 * Reserve la memoire pour un processus (memoire vive ou virtuelle)
 * Retourne 0, ou -1 si memoire non allouee
 */
{
	printf("Reservation de la memoire...\n");
	struct Processus p = tableProcessus[pid];
	int tailleMemoire;
	if (memoire == memoireVive)
		tailleMemoire = tailleMemoireVive;
	else
		tailleMemoire = tailleMemoireVirtuelle;
	int i = 0;
	while (i < tailleMemoire - p.taille)
	{
		if (memoire[i] == -1)
		{
			int j = i;
			for (; j < p.taille + i; ++j)
			{
				if (memoire[j] != -1)
					break;
			}
			if (j == p.taille + i)
			{
				placeProcessusMemoire(pid, i, memoire);
				return 0;
			}
			i = j;
		}
		++i;
	}
	printf("Memoire pleine, reservation memoire impossible suppression du nouveau processus...\n");
	return -1;
}

void demandeMemoire(int ecriture)
{
	char buff[] = "1m";
	write(ecriture, buff, sizeof(buff));
}

void placeProcessusMemoire(int pid, int empMem, int* memoire)
/*
 * Place le processus d'identifiant pid dans la memoire memoire (vive ou virtuelle) a partir de empMem
 * Ne retourne rien, on doit s'assurer avant d'appeler cette fonction que la memoire est libre,
 * sinon, elle sera ecrasee
 * Peut etre utilise pour liberer la memoire si pid est mis a -1
 */
{
	printf("Le processus %d est place en memoire. Pages %d a %d.\n", pid, empMem, empMem + tableProcessus[pid].taille);
	int i = empMem;
	for (; i < tableProcessus[pid].taille + empMem; ++i)
	{
		memoire[i] = pid;
	}
}


