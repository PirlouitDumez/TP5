#include <stdlib.h>
#include <stdio.h>
#include "tab.h"
#define TAILLEINITIALE 10

TABLEAU newArray() {
	TABLEAU tab;
	tab.elt = (int*)malloc(sizeof(int) * TAILLEINITIALE);  //on allloue une taille de TAILLEINITIALE * taille d'un entier en m�moire
	if (tab.elt != NULL) { // si malloc a fonctionn� on initialise le tableau avec des 0
		for (int i = 0; i < TAILLEINITIALE; i++) {
			*(tab.elt + i) = 0;
		}
	}
		tab.size = TAILLEINITIALE;
		tab.eltsCount = 0;
		return(tab);
}

int incrementArraySize(TABLEAU* tab, int incrementValue) {
	if ((incrementValue < 0) || ((*tab).elt == NULL)) {
		return(-1);
	}
	else {
		int* tmp = tab->elt; // sauvegarde du pointeur actuel
		tab->elt = (int*)realloc((*tab).elt, sizeof(int) * (tab->size  + incrementValue));
		if (tab->elt == NULL) { // �chec de la r�allocation
			tab->elt = tmp;    // restitution du pointeur pr�c�dent
			return(-1);         // Cela permet d'�viter que la valeur de tab soit modifi�e si le realloc ne fonctionne pas 
		}
		else {
			tab->size += incrementValue;
		}
	}
	return(tab->size);
}

int setElement(TABLEAU* tab, int pos, int element) {
	printf("\nOn insere %d a la position %d", element, pos);
	int ancienneTaille = tab->size;
	if (pos <= tab->size) {
		//printf("\n L'element est dans le tableau");
		if (*(tab->elt + pos - 1) == 0) {
			tab->eltsCount++;
		}
		*(tab->elt + pos - 1) = element;
		return(pos);
	}
	else {
	//	printf("\ntableau agrandi");
		if (incrementArraySize(tab, pos - tab->size) == -1) { // on agrandit le tableau et si l'agrandissement du tableau �choue, on retourne 0
			return(0);
		}
		for (int i = 0; i < pos - ancienneTaille; i++) {  //remplit les nouvelles cases du tableau de 0
			*(tab->elt + ancienneTaille + i) = 0;
		}
		*(tab->elt + pos - 1) = element; //agrandissement r�ussi, on insere le nouvel element et on augmente le nombre d'�l�ments
		tab->eltsCount++;                // la taille est mis � jour dans la fonction incrementArraySize
		return(pos);
	}
}

int displayElements(TABLEAU* tab, int startPos, int endPos) {
	printf("\nVoici le tableau\n");
	if (((startPos < 1) || (endPos < 1)) || (startPos > tab->size) || (endPos > tab->size) || (tab==NULL)) { //erreur si position plus petite que 1 ou en dehors de la taille du tableau
		return(-1);
	}
	else {
		if (startPos > endPos) { // si l'utilisateur a entr� une valeur de d�part> valeur d'arriv�e, on inverse les deux pour ne pas renvoyer d'erreur
			int tmp = startPos;
			startPos = endPos;
			endPos = tmp;
		}
		for (int i = startPos-1; i <endPos; i++) {  //on affiche les elements du tableau de startPos-1 � endPos ( le premier element est a la position 1)
			printf("%d ", *(tab->elt + i));
		}
		printf("\n");
		return(0);
	}
}

int deleteElements(TABLEAU* tab, int startPos, int endPos) {
	if (((startPos < 0) || (endPos < 0)) || (startPos > tab->size) || (endPos > tab->size)) { //erreur si position n�gative ou en dehors de la taille du tableau
		return(-1);
	}
	else {
		if (startPos > endPos) { // si l'utilisateur a entr� une valeur de d�part> valeur d'arriv�e, on inverse les deux pour ne pas renvoyer d'erreur
			int tmp = startPos;
			startPos = endPos;
			endPos = tmp;
		}
		printf("On supprime les elements du tableau entre la position %d et la position %d", startPos, endPos);
		int nbElementsSuppr = endPos - startPos + 1; //on calcule le nombre d'�l�ments � supprimer
		for (int i = 0; i < nbElementsSuppr; i++) {
			if (*(tab->elt + startPos - 1 + i) != 0) { // si on supprime un �l�ment diff�rent de 0
				tab->eltsCount--;                      // on a supprim� un �lement du tableau donc on d�cr�mente tab.eltsCount
			}
		}
		for (int i = 0; i < tab->size - endPos; i++) {
			// printf(" On supprime %d", *(tab->elt + startPos - 1 + i));
			*(tab->elt + startPos - 1 +i) = *(tab->elt + startPos - 1 + nbElementsSuppr+i); // on decale les valeurs de nbElementsSuppr vers la gauche
		}
		int* tmp = tab->elt; // sauvegarde du pointeur actuel
		tab->elt = (int*)realloc((*tab).elt, sizeof(int) * (tab->size - nbElementsSuppr));
		if (tab->elt == NULL) { // �chec de la r�allocation
			tab->elt = tmp;     // restitution du pointeur pr�c�dent
			return(-1);         // Cela permet d'�viter que la valeur de tab soit modifi�e si le realloc ne fonctionne pas 
		}
		else {
			tab->size = tab->size - nbElementsSuppr;  // on met la taille � jour
		}
		return(tab->size);
	}
}