/*
 * DialoguePereFils.c
 * Auteurs : Battista Yann, Mohamed Hilali
 */

#include "DialoguesPereFils.h"

void analyseReponse(int lecture)
/*
 * Analyse les données envoyées dans le tube
 */
{
	char a[256];
	if (read(lecture, a, 256) != 0)
	{
		if (a[0] == '1')
		{
			if (a[1] == 'p')
				reponseFileAttenteProcessus();
			else if (a[1] == 'm')
				reponseMemoire();
			else if (a[1] == 'n')
				createNewProcessus();
			kill(getppid(), SIGUSR1);
		}
	}
}

void reponseMemoire()
{
	
	//printf("Memoire vive : %d cadres de page\n", numCadresVive);
	//printf("Cadre de page: pid du processus, taille du processus\n");
	int i;
	for (i = 0; i < numCadresVive / 5; ++i)
	{
		int j;
		for (j = 0; j < 5; ++j)
		{
			if (tableProcessus[memoireVive[i*5+j]].pid != -1)
			{
				printf("%d : %d, %d\t", i*5+j, /*tableProcessus[*/memoireVive[i*5+j]/*].pid*/, tableProcessus[memoireVive[i*5+j]].taille);
			}
			else
			{
				printf("%d : \t\t", i*5+j);
			}
		}
		printf("\n");
	}
	for (i = i*5; i < numCadresVive; ++i)
	{
		printf("%d : %d, %d\t", i, tableProcessus[memoireVive[i]].pid, tableProcessus[memoireVive[i]].taille);
	}
	
	//printf("\nMemoire virtuelle : %d cadres de page\n", numCadresVirtuelle);
	//printf("Cadre de page: pid du processus, taille du processus\n");
	for (i = 0; i < numCadresVirtuelle / 5; ++i)
	{
		int j;
		for (j = 0; j < 5; ++j)
		{
			if (tableProcessus[memoireVirtuelle[i*5+j]].pid != -1)
			{
				printf("%d : %d, %d\t", i*5+j, /*tableProcessus[*/memoireVirtuelle[i*5+j]/*].pid*/, tableProcessus[memoireVirtuelle[i*5+j]].taille);
			}
			else
			{
				printf("%d : \t\t", i*5+j);
			}
		}
		printf("\n");
	}
	for (i = i*5; i < numCadresVirtuelle; ++i)
	{
		if (tableProcessus[memoireVirtuelle[i]].pid != -1)
		{
			printf("%d : %d, %d\t", i, tableProcessus[memoireVirtuelle[i]].pid, tableProcessus[memoireVirtuelle[i]].taille);
		}
		else
		{
			printf("%d: \t\t", i);
		}
	}
	
	printf("\n\n");
}


void demandeFileAttenteProcessus(int ecriture)
{
	char buff[] = "1p";
	write(ecriture, buff, sizeof(buff));
}

void reponseFileAttenteProcessus()
{
	//printf("Priorite\t\tFile d'attente\n");
	int f;
	for(f = 0; f < NUMFILES; ++f)
	{
		printf("%c", ('0' + f));
		printf("       \t\t");
		int i = tabFiles[f].beg;
		if (i == tabFiles[f].end)
		{
			printf("File vide...");
		}
		else
		{
			if (tabFiles[f].file[i].pid != -1)
				printf("%c", ('0' + tabFiles[f].file[i].pid));
			++i;
			for(; i != tabFiles[f].end; ++i)
			{
				if (tabFiles[f].file[i].pid != -1)
					printf(", %c", ('0' + tabFiles[f].file[i].pid));
			}
			
			
		}
		printf("\n");
	}
}

void demandeAjoutProcessus(int ecriture)
{
	char buff[] = "1n";
	write(ecriture, buff, sizeof(buff));
}

