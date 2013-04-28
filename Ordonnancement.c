/*
 * Ordonnancement.c
 * Auteurs : Battista Yann, Mohamed Hilali
 */


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
	
	printf("Initialisation des files de priorité...\n");
	initFile(tabFiles[0]);
	initFile(tabFiles[1]);
	initFile(tabFiles[2]);
	initFile(tabFiles[3]);
	initFile(tabFiles[4]);
}

void initFile(struct File f)
/*
 * Initialisation de la file de priorité f
 */
{
	// Debut et fin de la file mises a zero
	f.beg = 0;
	f.end = 0;
}

int addProcessTable(struct Processus* p)
/*
 * Ajoute le processus dans la table des processus
 * Retourne la position dans la table, ou -1 si echoué
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
		tableProcessus[place].pid = place;
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
		fprintf(stderr, "File de priorite pleine, aucun nouveau processus ne pourra etre ajouté...\n");
	}
	printf("Ajout du processus dans la file... pid: %d\n", f->file[f->end-1].pid);
	return f->end;
}

int newProcessus(int duree, int taille)
/*
 * Créé un processus et l'ajoute dans la table des processus
 * Retourne le pid du processus (-1 s'il n'a pas pu etre créé)
 */
{
	struct Processus p;
	p.duree = duree;
	p.dureeRestante = duree;
	p.taille = (taille + tailleCadresPages - 1) / tailleCadresPages;
	
	int pid = addProcessTable(&p);
	p.pid = pid;
	p.nombreAccesProc = 0;
	
	if (pid >= 0)
	{
		addProcessFile(&tabFiles[0], &p);
		if (reserveMemoire(pid, memoireVirtuelle) == -1)
		{
			enleverProcessus(pid);
		}
	}
	
	return pid;
}

void supprimerProcessusFile(int pid, struct File* file)
{
	int i = file->beg;
	//printf("Debut file: %d.\nFin file: %d.\n", file->beg, file->end);
	while (i != file->end)
	{
		printf("Analyse de %d... pid=%d.\n", i, file->file[i].pid);
		if (file->file[i].pid == pid)
		{
			file->file[i].pid = -1;
			break;
		}
		i = (i+1) % TAILLEFILE;
	}
	if (i == file->end)
		printf("Impossible de trouver le processus dans la file.\n");
}

void enleverProcessus(int pid)
{
	supprimerProcessusFile(pid, &tabFiles[0]);
	supprimerProcessusFile(pid, &tabFiles[1]);
	supprimerProcessusFile(pid, &tabFiles[2]);
	supprimerProcessusFile(pid, &tabFiles[3]);
	supprimerProcessusFile(pid, &tabFiles[4]);
	
	supprimerProcessusTable(pid);
}

void supprimerProcessusTable(int pid)
{
	tableProcessus[pid].pid = -1;
}

void reordonnancement()
{
	int i;
	for (i = 0; i < TAILLETABLEPROCESS; ++i)
	{
		
	}
}

void createNewProcessus()
{
	printf("Entrez la duree du processus: ");
	int dureeProc;
	scanf("%d", &dureeProc);
	printf("Entrez la taille du processus: ");
	int tailleProc;
	scanf("%d", &tailleProc);
	newProcessus(dureeProc, tailleProc);
}

int processTime()
/*
 * Gere le deroulement du temps, l'exucution des processus et la mise en memoire vive de ceux-ci
 * retourne 0 si aucun processus dans les files, -1 en cas d'erreur, sinon 1
 */
{
	/*if (processFile(&tabFiles[0]) == 0)
		if (processFile(&tabFiles[1]) == 0)
			if (processFile(&tabFiles[2]) == 0)
				if (processFile(&tabFiles[3]) == 0)
					if(processFile(&tabFiles[4]) == 0)
						return 0;*/
	int i;
	for (i = 0; i < NUMFILES; ++i)
	{
		int r = processFile(&tabFiles[i]);
		if (r == 1)
			return 1;
		else if (r == -1)
			return -1;
	}
	return 0;
}

int processFile(struct File* file)
/*
 * Execute le processus
 * Retourne 0, ou 1 si le processus est termine
 * -1 si aucun processus n'a ete execute
 */
{
	int valReturn = 0;
	struct Processus* p = &tableProcessus[file->beg];
	
	//printf("Processus %d...\nid %d...\n", p->pid, file->beg);
	if (execute(tableProcessus[file->beg].pid) == -1)
	{
		//printf("Aucun processus a executer...\n");
		return -1;
	}
	
	tableProcessus[file->beg].nombreAccesProc += 1;
	if (tableProcessus[file->beg].dureeRestante > 0)
	{
		//printf("Execution processus...\n");
		addProcessFile(file, &tableProcessus[file->beg]);
	}
	else
	{
		valReturn = 1;
		//printf("Processus termine...\n");
	}
	file->beg = file->beg+1;
	return valReturn;
}

int execute(int pid)
{
	if (pid == -1)
		return -1;
	//printf("Execute pid %d...\n", pid);
	int difference = estDansMemoireVive(pid);
	if (difference <= 0)
	{
		printf("Processus %d est deja en memoire, execution...\n", pid);
	}
	else
	{
		printf("Processus pas entierement en memoire...\n%d pages restantes.\n", difference);
		ajouteDansMemoireVive(pid, difference);
	}
	tableProcessus[pid].dureeRestante -= 1;
	return 0;
}
