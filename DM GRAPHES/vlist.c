#include "vlist.h"

#include <stdio.h>	/* perror */
#include <stdlib.h>	/* calloc */

/* __________________________________ Construction / destruction de liste */
vlist* vlist_construire() {
	vlist* l = calloc(1, sizeof(*l));
	/* en cas de succès les champs (l->card, l->pm, l->dm) sont initialisés à (0, NULL, NULL) */

	if (!l)
		perror("calloc");

	return l;
}

vlist* vlist_detruire(vlist *l) {
	if(l) {
		while(l->card)
			vlist_supprimer_deb(l);

		free(l);
	}
	
	return NULL;
}

/* __________________________________ Ajout / suppression dans une liste */
int vlist_ajouter_deb(vlist *l, int v, double val) {
	int card =-1;
	
	/* __ construction du maillon */
	msuc* m =msuc_construire(v, val);
	if (m) {
		/* __ son insertion en début de liste */
		msuc_set_suivant(m, l->pm);	
		l->pm =m;
		if(! l->card)	/* si la liste était vide, le nouveau maillon est aussi le dernier de la liste */
			l->dm =m;

		/* __ mise à jour de la taille de la liste */
		card =++(l->card);
	}
	
	return card;
}

int vlist_ajouter_fin(vlist *l, int v, double val) {
	int card =-1;
	
	/* __ construction du maillon */
	msuc* m =msuc_construire(v, val);
	if (m) {
		/* __ son insertion en fin de liste */
		if(! l->card)
			l->pm =m;	/* si la liste était vide, le nouveau maillon est aussi le premier de la liste */
		else
			msuc_set_suivant(l->dm, m);	/* sinon, le nouveau maillon succède au dernier maillon de la liste */
		l->dm =m;	/* dans tous les cas, le nouveau maillon devient le dernier de la liste */

		/* __ mise à jour de la taille de la liste */
		card =++(l->card);
	}
	
	return card;
}

int vlist_supprimer_deb(vlist *l) {
	msuc* msuiv;
	if(l->card) {
		msuiv =msuc_suivant(l->pm);

		/* __ suppression du premier maillon de la liste */
		l->pm =msuc_detruire(l->pm);

		l->pm =msuiv;	/* le nouveau premier maillon devient l'éventuel successeur du maillon supprimé */
		if(! msuiv)	/* si la liste ne contenait qu'un maillon, le dernier maillon de la liste est inexistant */
			l->dm =NULL;

		l->card --;	/* mise à jour de la taille de la liste */
	}
	
	return l->card;
}

/* __________________________________ Accesseurs en lecture */
int vlist_get_sommet(vlist *l) {
	return (l->card ? msuc_sommet(l->pm) : -1);
}

int vlist_get_card(vlist *l) {
	return l->card;
}
