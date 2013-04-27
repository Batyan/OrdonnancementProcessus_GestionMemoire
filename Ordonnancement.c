#include "Ordonnancement.h"
#include "GestionMemoire.h"

void preparationOrdonnanceur()
{
	printf("Debut de la preparation de l'ordonnanceur...\n");
	
	printf("Generation de la table des processus...\n");
	tableProcessus = (struct Processus*) malloc(sizeof(struct Processus)* TAILLETABLEPROCESS);
	
	int i;
	for (i = 0; i < TAILLETABLEPROCESS; ++i)
		tableProcessus[i].pid = -1;
	
	tabFiles[0] = fileP0;
	tabFiles[1] = fileP1;
	tabFiles[2] = fileP2;
	tabFiles[3] = fileP3;
	tabFiles[4] = fileP4;
	
	printf("Initialisation des files de priorit�...\n");
	initFile(tabFiles[0]);
	initFile(tabFiles[1]);
	initFile(tabFiles[2]);
	initFile(tabFiles[3]);
	initFile(tabFiles[4]);
}

void initFile(struct File f)
/*
 * Initialisation de la file de priorit� f
 */
{
	// Debut et fin de la file mises a zero
	f.beg = 0;
	f.end = 0;
}

int addProcessTable(struct Processus *p)
/*
 * Ajoute le processus dans la table des processus
 * Retourne la position dans la table, ou -1 si echou�
 */
{
	int place = 0;
	while(tableProcessus[place].pid != -1 && place < TAILLETABLEPROCESS)
	{
		++place;
	}
	if (place == TAILLETABLEPROCESS)
	{
		fprintf(stderr, "Impossible d'ajouter le processus car la table de processus est pleine!\n");
		printf("Voulez vous terminer le programme? (O: Oui N: Non) ");
		char finP;
		scanf("%d", (int*) &finP);
		if (finP == 'O' || finP == 'o')
			finProgramme(1);
		else
			place = -1;
	}
	else
	{
		tableProcessus[place] = *p;
	}
	printf("Ajout du processus dans la table... pid: %d\n", place);
	return place;
}

int addProcessFile(struct File* f, struct Processus *p)
/*
 * Ajoute le processus p a la fin de la file de priorite f (round robin)
 * Retourne la position dans la file
 */
{
	f->file[f->end] = *p;
	f->end = (f->end + 1) % TAILLEFILE;
	if (f->end == f->beg)
	{
		fprintf(stderr, "File de priorite pleine, aucun nouveau processus ne pourra etre ajout�...\n");
	}
	printf("Ajout du processus dans la file... pid: %d\n", f->file[f->end-1].pid);
	return f->end;
}

int newProcessus(int duree, int taille)
/*
 * Cr�� un processus et l'ajoute dans la table des processus
 * Retourne le pid du processus (-1 s'il n'a pas pu etre cr��)
 */
{
	struct Processus p;
	p.duree = duree;
	p.dureeRestante = duree;
	p.taille = taille;
	
	int pid = addProcessTable(&p);
	p.pid = pid;
	
	if (pid >= 0)
	{
		addProcessFile(&tabFiles[0], &p);
		if (reserveMemoire(pid) == -1)
		{
			
		}
	}
	
	return pid;
}

void reordonnancement()
{
	
}
