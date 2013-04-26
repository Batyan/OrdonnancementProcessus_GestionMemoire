

#ifndef GESTIONMEMOIRE_H
#define GESTIONMEMOIRE_H

void preparationMemoire();

int tailleMemoireVive;
int tailleMemoireVirtuelle;
int tailleCadresPages;

int* memoireVive;
int* memoireVirtuelle;

#endif GESTIONMEMOIRE_H