Simulateur d'ordonnancement et de gestion de memoire
Battista Yann
Mohamed Hilali

Compilation:
------------
Le simulateur comporte un fichier makefile pour pouvoir compiler ais�ment.
Il suffit de se placer avec un terminal dans le dossier du simulateur et d'executer la commande 'make all'
Le compilation se fera d'elle m�me par la suite.

S'il est necessaire de nettoyer le repertoire (suppression des fichier .o et de l'executable) il est possible d'executer la commande 'make clean'

Description du simulateur:
--------------------------
Le simulateur permet de simuler l'ordonnancement de processus et la gestion de la memoire.
Il permet de voir les changements effectu�s lors de l'ajout e nouveaux processus et lors de l'execution de ceux-ci.

Utilisation:
------------
Une fois le simullateur compil�, un fichier executable sera cr�� dans le repertoire du simulateur.
Il aura comme nom Simulateur.run.
Pour l'executer, il faut avec un terminal demander l'execution du programme. Une methode pour le faire et de taper la commande './Simulateur.run'.

Une fois le simulateur lanc�, il sera demand� a l'utilisateur de rentrer des variables utilis�s pour le simulateur.
Ces variables sont: 
- La taille de la memoire vive		: Qui est utilis� pour determiner le nombre d'octets allou�s a la memoire vive.
- La taille de la memoire virtuelle	: Qui de la meme maniere est utilis� pour allouer un certain nombre d'octets a la memoire virtuelle. 
									  La memoire virtuelle doit etre plus grande que la memoire vive.
- Le taille du cadre de page		: La memoire est divis�e en 'cadres' ces cadres sont utilis�s pour allouer la memoire plus facilement. 
									  La taille du cadre de page doit etre plus petit que la taille de la memoire vive.
- Le quantum						: Le quantum est l'unit� de temps entre chaque r�ordonnancement. 
									  Une valeur faible entraine une actualisation plus frequente.

Une fois ces quatres valeurs rentr�es, le programme propose a l'utilisateur quatres choix.
Il propose de terminer le programme, de rentrer un nouveau processus, d'afficher les files d'attente des processus et d'afficher la memoire.
Chaque option est associ� a un numero, en entrant ce numero, l'utilisateur demande au programme d'effectuer l'action.

Si l'utilisateur venait a entrer un numero alors que le quantum est elev�, il se pourrai que le programme parraise fig�.
Il ne l'est pas, le programme se met a jour en fonction du quantum choisi. Plus le quantum est grand plus le programme semblera lent.

Implementation:
---------------
Nous avons choisi pour effectuer ce simulateur de travailler avec deux principales parties:
Nous avons la partie ordonnancement. Contenant tout ce qui est necessaire au fonctionnement des processus. 
Ceux-ci n'etant pas directement stock�s en memoire, cette partie est presque independante.
Les processus sont g�r�s sous forme de struct, ils contiennent toutes les informations dont nous avons besoin.
Les files d'attente sont aussi sous forme de struct. Elles contiennent un tableau, contenant l'identifiant du processus dans la file, d'un debut, et d'une fin.
La file n'�tant pas infinie, nous utilisons un modulo, pour donner l'impression que celle ci est infinie.
Nous veillons tout de m�me � v�rifier que la fin de file ne rejoigne pas le d�but.

Nous avons ensuite la partie gestion de la m�moire. Ou la m�moire est repr�sent� par deux tableaux. Un pour la m�moire vive, l'autre pour la m�moire virtuelle.
La m�moire vive �tant sp�ciale, nous avons ajout� deux autres tableaux contenant des information suppl�mentaire sur la m�moire.
Ces informations sont le tableau de r�f�rencement pour l'algorithme de la derni�re chance.
Et le tableau du temps avant la derni�re mise � jour de cet emplacement m�moire, il nous est utilis� pour le r�ordonnancement.

Finalement nous avons une derni�re partie, qui n'est pas une partie majeure du simulateur, il correspond � la communicatio entre les deux processus du simulateur.
En effet le processus destin� au dialogue avec l'utilisateur n'est pas celui qui effectue l'ordonnancement et la gestion de la m�moire.
Cela nous permet d'avoir un programme qui continu de travailler m�me si l'utilisateur est lent pour choisir des options.
La seule exception est lors de la cr�ation d'un nouveau processus pour le simulateur, car c'est le processus de gestion qui fait cet �change, pour des raisons de simplicit�.
