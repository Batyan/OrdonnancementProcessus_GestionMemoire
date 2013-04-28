

#ifndef GESTIONMEMOIRE_H
#define GESTIONMEMOIRE_H

#include "glob.h"

void preparationMemoire();

int reserveMemoire(int pid, int* memoire);

void demandeMemoire(int ecriture);

void placeProcessusMemoire(int pid, int empMem, int* memoire);

int estDansMemoireVive(int pid);

void ajouteDansMemoireVive(int pid, int numAPlacer);

void placeProcessusMemoireTaille(int pid, int empMem, int* memoire);


int tailleMemoireVive;
int tailleMemoireVirtuelle;
int tailleCadresPages;

int* memoireVive;
int* memoireVirtuelle;

int* memoireViveTemps;
int* memoireViveReference;

int numCadresVive;
int numCadresVirtuelle;

#endif /*GESTIONMEMOIRE_H*/
