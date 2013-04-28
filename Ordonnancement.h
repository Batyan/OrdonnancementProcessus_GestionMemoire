#ifndef ORDONNANCEMENT_H
#define ORDONNANCEMENT_H

#include "glob.h"

#define TAILLEFILE 64

#define TAILLETABLEPROCESS 100

#define NUMFILES 5

int quantum;

struct File fileP0;
struct File fileP1;
struct File fileP2;
struct File fileP3;
struct File fileP4;

struct Processus* tableProcessus;

void preparationOrdonnanceur();

void initFile(struct File f);

int addProcessTable(struct Processus *p);

int addProcessFile(struct File* f, struct Processus *p);

int newProcessus(int duree, int taille);

void supprimerProcessusFile(int pid, struct File* file);

void enleverProcessus(int pid);

void supprimerProcessusTable(int pid);

void reordonnancement();

void createNewProcessus();

int processTime();

int processFile(struct File* file);

int execute(int pid);

struct Processus{
	int pid;
	int duree;
	int dureeRestante;
	int taille;
	int emplacementMemoire;
	int nombreAccesProc;
};

struct File
{
	struct Processus file[TAILLEFILE];
	int beg;
	int end;
};


struct File tabFiles[NUMFILES];

#endif /*ORDONNANCEMENT_H*/
