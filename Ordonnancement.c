#include "Ordonnancement.h"

void preparationOrdonnanceur()
{
	printf("Debut de la preparation de l'ordonnanceur...\n");
	
	printf("Generation de la table des processus...\n");
	tableProcessus = (struct Processus*) malloc(sizeof(struct Processus)* TAILLETABLEPROCESS);
	
	printf("Initialisation des files de priorité...\n");
	initFile(&fileP0);
	initFile(&fileP1);
	initFile(&fileP2);
	initFile(&fileP3);
	initFile(&fileP4);
	
	
}

void initFile(struct File* f)
/*
 * Initialisation de la file de priorité f
 */
{
	int i;
	for (i = 0; i < TAILLEFILE; ++i)
	{
		// Mise a NULL de chaque element
		f[i]->file = NULL;
	}
	// Debut et fin de la file mises a zero
	f->beg = 0;
	f->end = 0;
}

int addProcessTable(struct Processus* p)
/*
 * Ajoute le processus dans la table des processus
 * Retourne la position dans la table, ou -1 si echoué
 */
{
	int place = 0;
	while(tableProcessus[place] != -1 && place < TAILLETABLEPROCESS)
	{
		++place;
	}
	if (place == TAILLETABLEPROCESS)
	{
		fprintf(stderr, "Impossible d'ajouter le processus car la table de processus est pleine!\n");
		printf("Voulez vous terminer le programme? (O: Oui N: Non) ");
		char finP;
		scanf("%c", finP);
		if (finP == 'O' || finP == 'o')
			finProgramme(1);
		else
			place = -1;
	}
	else
	{
		tableProcessus[place] = p;
	}
	return place;
}

int addProcessFile(struct File f*, struct Processus p)
/*
 * Ajoute le processus p dans la file de priorite f
 * Retourne la position dans la file
 */
{
	f->file[f->end] = p;
	end = (end + 1) % TAILLEFILE;
	if (end == beg)
	{
		fprintf(stderr, "File de priorite pleine, aucun nouveau processus ne pourra etre ajouté...\n");
	}
}

int newProcessus(int duree, int taille)
{
	struct Processus p;
	p.duree = duree;
	p.taille = taille;
	
	
}