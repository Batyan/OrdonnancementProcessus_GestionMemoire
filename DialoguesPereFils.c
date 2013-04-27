#include "DialoguesPereFils.h"

void analyseReponse(int lecture)
/*
 * Analyse les données envoyées dans le tube
 */
{
	char a[256];
	read(lecture, a, 256);
	
	if (a[0] == '1')
	{
		if (a[1] == 'p')
			reponseFileAttenteProcessus();
		else if (a[1] == 'm')
			reponseMemoire();
	}
}

void reponseMemoire()
{
	
	//printf("%s", buff);
	kill(getppid(), SIGUSR1);
}


void demandeFileAttenteProcessus(int ecriture)
{
	char buff[] = "1p";
	write(ecriture, buff, sizeof(buff));
}

void reponseFileAttenteProcessus()
{
	//char buff[256];
	printf("Priorite\t\tFile d'attente\n");
	int f;
	for(f = 0; f < NUMFILES; ++f)
	{
		printf("%c", ('0' + f));
		/*char tempChar[2];
		tempChar[1] = '\0';
		tempChar[0] = '0' + f;
		strcat(buff, tempChar);*/
		//strcat(buff, "       \t\t");
		printf("       \t\t");
		int i = tabFiles[f].beg;
		if (i == tabFiles[f].end)
		{
			printf("File vide...");
		}
		else
		{
			printf("%c", ('0' + tabFiles[f].file[i].pid));
			//tempChar[0] = '0' + tabFiles[f].file[i].pid;
			//strcat(buff, tempChar);
			++i;
			for(; i != tabFiles[f].end; ++i)
			{
				//strcat(buff, ", ");
				printf(", %c", ('0' + tabFiles[f].file[i].pid));
				//tempChar[0] = ('0' + tabFiles[f].file[i].pid);
				//strcat(buff, tempChar);
			}
			
			
		}
		//strcat(buff, "\n");
		printf("\n");
	}
	//printf("%s", buff);
	kill(getppid(), SIGUSR1);
}

void demandeAjoutProcessus(int dureeProc, int tailleProc)
{
	newProcessus(dureeProc, tailleProc);
	kill(getppid(), SIGUSR1);
}

