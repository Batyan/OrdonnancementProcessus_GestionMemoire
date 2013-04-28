/*
 * DialoguePereFile.h
 * Auteurs : Battista Yann, Mohamed Hilali
 */

#ifndef DIALOGUESPEREFILS_H
#define DIALOGUESPEREFILS_H

#include "glob.h"

#include "Ordonnancement.h"
#include "GestionMemoire.h"

void analyseReponse(int lecture);

void reponseMemoire();

void reponseFileAttenteProcessus();

void demandeFileAttenteProcessus(int ecriture);

void demandeAjoutProcessus(int ecriture);

#endif /*DIALOGUESPEREFILS_H*/
