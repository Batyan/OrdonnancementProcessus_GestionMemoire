/*
 * glob.h
 * Auteurs : Battista Yann, Mohamed Hilali
 */

#ifndef GLOB_H
#define GLOB_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void finProgramme(int signum);

void reveil(int signum);

#endif /*GLOB_H*/
