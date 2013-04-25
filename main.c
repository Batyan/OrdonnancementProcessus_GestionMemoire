/*
 * 
 *
 * 
 */

#include "glob.h"

int main(int argc, char* argv)
{
	do
	{
		printf("Entrez la taille de la mémoire vive :\t");
		scanf("%d", &tailleMemoireVive);
		
		printf("Entrez la taille de la memoire virtuelle :\t");
		scanf("%d", &tailleMemoireVirtuelle);
		if (tailleMemoireVive > tailleMemoireVirtuelle)
		{
			fprintf(stderr, "La memoire vive ne peut pas avoir une plus grande taille que le memoire virtuelle!");
		}
	} while (tailleMemoireVive > tailleMemoireVirtuelle);
	
	printf("Entrez la taille des cadres de pages :\t");
	scanf("%d", &tailleCadresPages);
	
	printf("Entrez le quantum pour l’ordonnancement :\t");
	scanf("%d", &quantum);
	
	struct sigaction quitAction;
	quitHandler.sa_handler = finProgramme;
	quitHandler.sa_flags = 0;
	sigaction(SIGINT, &quitHandler, NULL);
	sigaction(SIGQUIT, &quitHandler, NULL);
	// sigaction(, &quitHandler, NULL);
	
	preparationMemoire();
	preparationOrdonnanceur();
	
	
}

void finProgramme(int signum)
/*
 * Termine le programme proprement en liberant la memoire alloué
 */
{
	free(memoireVive);
	free(memoireVirtuelle);
	
	if (signum == 0)
	// Terminaison normale
		exit(EXIT_SUCCES);
	else
	// Terminaison par signaux ou par erreur
		exit(EXIT_FAILURE);
}