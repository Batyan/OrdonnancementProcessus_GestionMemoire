#indef ORDONNANCEMENT_H
#define ORDONNANCEMENT_H

#define TAILLEFILE 64

#define TAILLETABLEPROCESS 100

int quantum;

struct File fileP0;
struct File fileP1;
struct File fileP2;
struct File fileP3;
struct File fileP4;

struct Processus* tableProcessus;

void preparationOrdonnanceur();

struct Processus{
	int duree;
	int taille;
};

struct File
{
	struct Processus* file[TAILLEFILE];
	int beg;
	int end;
};

#endif ORDONNANCEMENT_H