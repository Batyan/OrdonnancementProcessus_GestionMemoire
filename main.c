/*
 * main.c
 * Auteurs : Battista Yann, Mohamed Hilali
 */

#include "glob.h"

#include "GestionMemoire.h"
#include "Ordonnancement.h"
#include "DialoguesPereFils.h"

#define MAXORDONNANCEMENT 10

void finProgramme(int signum)
/*
 * Termine le programme proprement en liberant la memoire allou�
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

void reveil(int signum)
{
	return;
}

int main(int argc, char** argv)
{
	struct sigaction quitAction;
	quitAction.sa_handler = finProgramme;
	quitAction.sa_flags = 0;
	sigaction(SIGINT, &quitAction, NULL);
	sigaction(SIGQUIT, &quitAction, NULL);
	// sigaction(, &quitAction, NULL);
	
	int pereFils[2];
	int filsPere[2];
	
	if(pipe(pereFils) == -1 || pipe(filsPere) == -1)
	{
		fprintf(stderr, "Erreur pipe() impossible...\nArret du programme...\n");
		finProgramme(1);
	}
	
	int pid = fork();
	if (pid == -1)
	{
		fprintf(stderr, "Erreur fork() impossible...\nArret du programme...\n");
		finProgramme(1);
	}
	else if(pid == 0) // fils traitement
	{
	
		
		close(filsPere[0]); // Fermeture de la lecture sur filsPere
		close(pereFils[1]); // Fermeture de l'ecriture sur pereFils
		
		fcntl(pereFils[0], F_SETFL, O_NONBLOCK); // Lecture non bloquante
		
		do
		{
			printf("Entrez la taille de la m�moire vive :\t");
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
		} while (tailleCadresPages > tailleMemoireVive || tailleCadresPages < 1);
	
		do
		{
			printf("Entrez le quantum pour l'ordonnancement :\t");
			scanf("%d", &quantum);
			if (quantum < 1)
				fprintf(stderr, "Le quantum doit avoir une valeur strictement positive!\n");
		} while (quantum < 1);
		
		preparationMemoire();
		preparationOrdonnanceur();
		
		/*
		newProcessus(10, 10);
		newProcessus(10, 10);
		newProcessus(10, 10);
		*/
		
		kill(getppid(), SIGUSR1);
		
		while(0 == 0)
		{
			int numOrdonnancement = 0;
			while(numOrdonnancement < MAXORDONNANCEMENT)
			{
				processTime();
				//printf("Lecture de %s\n", a);
				analyseReponse(pereFils[0]);
				sleep(quantum);
			}
			reordonnancement();
		}
	}
	else // pere
	{
		close(filsPere[1]); // Fermeture de l'ecriture sur filsPere
		close(pereFils[0]); // Fermeture de la lecture sur pereFils
		struct sigaction reveilAct;
		reveilAct.sa_handler = reveil;
		reveilAct.sa_flags = 0;
		sigemptyset(&reveilAct.sa_mask);
		sigaction(SIGUSR1, &reveilAct, NULL);
		// Le pere entre en sommeil jusqu'a ce que le fils ait fini son initialisation
		sleep(60);
		
		printf("Initialisation termin�e,\nvous pouvez maintenant utiliser le simulateur d'ordonnancement et de gestion de la m�moire.\n\n");
		
		int action, end;
		end = 0;
		
		while (end == 0)
		{
			printf("Entrez une action a effectuer parmis les suivantes en entrant le numero correspondant:\n");
			printf("0: Fin du simulateur.\n");
			printf("1: Ajout d'un nouveau processus.\n");
			printf("2: Affichage de la file d'attente des processus.\n");
			printf("3: Affichage de la memoire.\n");
		
			scanf("%d", &action);
			switch (action)
			{
				case 1:
					demandeAjoutProcessus(pereFils[1]);
					sleep(100);
					break;
				case 2:
					demandeFileAttenteProcessus(pereFils[1]);
					sleep(100);
					break;
				case 3:
					demandeMemoire(pereFils[1]);
					sleep(100);
					break;
				case 0:
					end = 1;
					break;
			}
		}
	}
	
	finProgramme(0);
	return 1;
}
