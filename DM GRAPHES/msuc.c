#include"msuc.h"

#include <stdio.h>	/* perror */
#include <stdlib.h>	/* calloc */

/* __________________________________ Construction / destruction */
msuc* msuc_construire(int v, double val) {
	msuc* m = (msuc*)malloc(sizeof(*m));
	if (!m)
		perror("malloc");
	else {
		m->sommet = v;
		m->valeur = val;
		m->suivant = NULL;
	}

	return m;
}

msuc* msuc_detruire(msuc *m) {
	if(m)
		free(m);
	
	return NULL;
}

/* __________________________________ Accesseurs en écriture */
void msuc_set_suivant(msuc *m, msuc *msuiv) {
	m->suivant =msuiv;
} 

/* __________________________________ Accesseurs en lecture */
msuc *msuc_suivant(msuc *m) {
	return m->suivant;
}

int msuc_sommet(msuc *m) {
	return m->sommet;
}

double msuc_valeur(msuc *m) {
	return m->valeur;
}
