/*
 * 
 *
 * 
 */

#include "glob.h"

void finProgramme(int signum)
/*
 * Termine le programme proprement en liberant la memoire alloué
 */
{
	printf("Fin du programme... Au revoir :)\n");
	free(memoireVive);
	free(memoireVirtuelle);
	
	free(tableProcessus);
	
	if (signum == 0)
	// Terminaison normale
		exit(EXIT_SUCCESS);
	else
	// Terminaison par signaux ou par erreur
		exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
	do
	{
		printf("Entrez la taille de la mémoire vive :\t");
		scanf("%d", &tailleMemoireVive);
		
		printf("Entrez la taille de la memoire virtuelle :\t");
		scanf("%d", &tailleMemoireVirtuelle);
		if (tailleMemoireVive > tailleMemoireVirtuelle)
		{
			fprintf(stderr, "La memoire vive ne peut pas avoir une plus grande taille que le memoire virtuelle!\n");
		}
	} while (tailleMemoireVive > tailleMemoireVirtuelle);
	
	do
	{
		printf("Entrez la taille des cadres de pages :\t");
		scanf("%d", &tailleCadresPages);
		if (tailleCadresPages > tailleMemoireVive || tailleCadresPages < 1)
			fprintf(stderr, "La taille du cadre des pages doit etre une valeur strictement positive, inferieure a la taille de la memoire vive!\n");
	{ while (tailleCadresPages > tailleMemoireVive || tailleCadresPages < 1);
	
	do
	{
		printf("Entrez le quantum pour l’ordonnancement :\t");
		scanf("%d", &quantum);
		if (quantum < 1)
			fprintf(stderr, "Le quantum doit avoir une valeur strictement positive!\n");
	} while (quantum < 1);
	
	struct sigaction quitAction;
	quitAction.sa_handler = finProgramme;
	quitAction.sa_flags = 0;
	sigaction(SIGINT, &quitAction, NULL);
	sigaction(SIGQUIT, &quitAction, NULL);
	// sigaction(, &quitAction, NULL);
	
	preparationMemoire();
	preparationOrdonnanceur();
	
	
}