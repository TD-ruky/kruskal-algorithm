/**
 * \file graphe-4.c
 * \brief Représentation des graphes par liste de successeurs
 * \version 2 : maillons et listes de sommets externalisées (pour les parcours)
 * \date jeudi 7 novembre 2021
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 
 * \version 3 : fonctions Kruskal, tri_fusion, fusion, find, union
 * \authors Saint Aubin Elodie, Derivaux Thomas
 * TP : partie 4
*/
#include "graphe-4.h"

#include <stdio.h>
#include <stdlib.h>

#define TRACE 0

/* __________________________________ Initialisation / Destruction */
int graphe_stable(graphe* g, int n, int est_or) {
	int stat =0;	/* tout se passe bien jusqu'à preuve du contraire */
	
	/* on vérifie que la valeur donnée pour n est correcte */
	if(n <= 0)
		stat =-2;
	else {
		/* allocation d'un tableau de n pointeurs tous initialisés à NULL */
		g->tab_sucs =calloc(n, sizeof(msuc*));
		if(! g->tab_sucs)
			stat =-1;
		else {
			/* initialisation des champs atomiques */
			g->n =n;
			g->est_or =est_or;
			g->m =0;
		}
	}

    /* on retourne le statut de réussite de la fonction */
    return stat;
}

void graphe_detruire(graphe *g) {
	int v;
	msuc *suiv, *m;
	
	if(g->tab_sucs) {
		/* __ parcours & destruction des listes d'adjacence */
		/* parcours des sommets du graphe */
		for(v =0 ; v < g->n ; v ++) {
			/* destruction 1 à 1 des maillons de la liste d'adjacence du sommet v */
			m =g->tab_sucs[v];
			while(m != NULL) {
				suiv =msuc_suivant(m);
				m =msuc_detruire(m);
				m =suiv;
			}
		}

		/* __ libération de la mémoire liée au tableau */
		free(g->tab_sucs);
	}
}

/* __________________________________ Ajout / Suppression d'arêtes */
/* Attention :
 * Si le graphe est orienté, utiliser les fonctions _arc
 * Si le graphe est non orienté, utiliser les fonction _arete
 */

int graphe_ajouter_arc(graphe *g, int v, int w, double val) {
	int stat =0;
	msuc *nv_vois;
	
	/* __ mise à jour de la liste d'adjacence */

	/* création & initialisation d'un nouveau maillon */
	nv_vois =msuc_construire(w, val);
	if(! nv_vois)
		stat =-1;
	else {
		/* son insertion (en tête) dans la liste */
		msuc_set_suivant(nv_vois, g->tab_sucs[v]);
		g->tab_sucs[v] =nv_vois;

		/* __ mise à jour du nombre d'arcs */
		(g->m)++;
	}

    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_ajouter_arete(graphe* g, int v, int w, double val) {
	int stat;

	/* insertion de w dans la liste de voisins de v */
	stat =graphe_ajouter_arc(g, v, w, val);
	if(!stat && v != w) {
		/* insertion de v dans la liste de voisins de w */
		stat =graphe_ajouter_arc(g, w, v, val);
		if(!stat)
			/* en cas de succès, l'arête aura été comptée 2 fois par graphe_ajouter_arc */
			(g->m) --;
		else
			/* en cas d'échec, on revient à la situation initiale */
			graphe_supprimer_arc(g, w, v, val);
	}
	
    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_supprimer_arc(graphe *g, int v, int w, double val) {
	int stat =-1;
	msuc *m =g->tab_sucs[v], *mprec =NULL, *msuiv;

	while(m != NULL) {
		/* mémorisation du successeur de m */
		msuiv =msuc_suivant(m);
		
		/* le cas échéant, on supprime l'arête */
		if (msuc_sommet(m) == w && msuc_valeur(m) == val) {
			stat =0;
			m =msuc_detruire(m);
			if(mprec)
				msuc_set_suivant(mprec, msuiv);
			else
				g->tab_sucs[v] =msuiv;
			(g->m) --;
		}
		/* sinon, on met simplement à jour du prédécesseur */
		else
			mprec =m;

		/* mise à jour de m */
		m =msuiv;
		
	}
	
    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_supprimer_arete(graphe* g, int v, int w, double val) {
	int stat =graphe_supprimer_arc(g, v, w, val), m =g->m;
	if(!stat && v != w) {
		stat =graphe_supprimer_arc(g, w, v, val);
		if(! stat)	/* les 2 appels à graphe_supprimer_arc ont diminué g->m de 2 pour chaque arête supprimée */
			g->m =g->m +(m -g->m)/2;	
	}
	
    /* on retourne le statut de réussite de la fonction */
	return stat;
}

/* ______________________________________ Accesseurs en lecture */
int graphe_est_or(graphe *g) {
	return g->est_or;
}

int graphe_get_n(graphe* g) {
	return g->n;
}

int graphe_get_m(graphe* g) {
	return g->m;
}

msuc *graphe_get_prem_msuc(graphe *g, int v) {
	return g->tab_sucs[v];
}

/* NE PAS ACCÉDER DIRECTEMENT AUX CHAMPS EN-DESSOUS DE CETTE LIGNE */

/* Complexité : au plus, le plus grand degré (sortant : Delta_max) dans le graphe */
int graphe_get_multiplicite_arc(graphe* g, int v, int w) {
	int mult =0;
	msuc* m;
	for(m =graphe_get_prem_msuc(g, v) ; m != NULL ; m =msuc_suivant(m)) 
		if (msuc_sommet(m) == w)
			mult ++;
	
	return mult;
}

/* Complexité : au plus, le plus grand degré (Delta) dans le graphe */
int graphe_get_multiplicite_arete(graphe* g, int v, int w) {
	int mult =graphe_get_multiplicite_arc(g, v, w);

	if(v != w && graphe_est_or(g))
		mult =mult +graphe_get_multiplicite_arc(g, w, v);
	
	return mult;
}

/* Complexité : cas identique à celui de graphe_get_multiplicite_arc 
	attention, si cette fonction n'a pas vocation à être appelée sur les graphes non orientés, 
		elle est pour ces graphes utilisée comme sous-routine de graphe_get_degre */
int graphe_get_degre_sortant(graphe* g, int v) {
	int deg =0;
	msuc* m;
	for(m =graphe_get_prem_msuc(g, v) ; m != NULL ; m =msuc_suivant(m))
		if(msuc_sommet(m) == v && !graphe_est_or(g))
			deg =deg +2;	/* NB sinon dans graphe_get_degre on peut ajouter la multiplicité de la boucle sur v */
		else
			deg ++;
	
	return deg;
}

/* Complexité : la somme des degrés sortants, soit le nombre d'arêtes (m) du graphe */
int graphe_get_degre_entrant(graphe* g, int w) {
	int deg =0, v;
	for(v =0 ; v < graphe_get_n(g) ; v ++) 
		deg =deg +graphe_get_multiplicite_arc(g, v, w);
	
	return deg;
}

/* Complexité : 
	cas identique à celui de graphe_get_degre_sortant dans le cas non orienté
	cas identique à celui de graphe_get_degre_entrant (facteur dominant de m sur Delta_max) dans le cas orienté
*/
int graphe_get_degre(graphe *g, int v) {
	int deg =graphe_get_degre_sortant(g, v);
	if(graphe_est_or(g))
		deg =deg +graphe_get_degre_entrant(g, v);

    return deg;
}

/* ______________________________________ Entrées / Sorties */
void graphe_afficher(graphe* g) {
	int v, w;
	msuc *m;
	int n = graphe_get_n(g);
	printf("graphe %s d'ordre %d à %d aretes :\n",
		graphe_est_or(g) ? "orienté" : "non orienté",
		graphe_get_n(g), graphe_get_m(g));
	for (v = 0; v < n; ++v) {
		puts("successeurs de v : ");
		for (m = graphe_get_prem_msuc(g, v); m; m = msuc_suivant(m)) {
			w = msuc_sommet(m);
			printf("%2d, ", w);
		}
		puts("");
	}
}

int graphe_ecrire_dot(graphe *g, char *nom_fichier, int ecrire_valeurs) {
	int stat =-1;
	int u, v, n = graphe_get_n(g), est_or = graphe_est_or(g);
	msuc *m;
	double val;
	FILE *f;

	/* ouverture du fichier */
	f = fopen(nom_fichier, "w");
	if (!f)
		perror("fopen"); 
	else {
		stat =0;

		/* __ écriture du fichier */

		/* entête */
		if (est_or)
			fputs("digraph {\n", f);
		else
			fputs("graph {\n", f);

		/* sommets */
		for (u = 0; u < n; ++u)
			fprintf(f, "\t%d;\n", u);
		fputs("\n", f);

		/* arêtes (ou arcs) */
		for (u =0; u <n; ++u)
			for (m =graphe_get_prem_msuc(g, u); m; m =msuc_suivant(m)) {
				v =msuc_sommet(m);
				val =msuc_valeur(m);
				if (!est_or && v <u) /* arête déjà rencontrée */
					continue;
				fprintf(f, "\t%d -%c %d ", u, est_or ? '>' : '-', v);
				if (ecrire_valeurs)
					fprintf(f, " [label = %.2f]", val);
				fprintf(f, ";\n");
			}
		fputs("}\n", f);

		/* fermeture du fichier */
		fclose(f);
	}

    /* on retourne le statut de réussite de la fonction */
	return stat;
}

/* ______________________________________ Autres fonctions d'initialisation */
int graphe_complet(graphe* g, int n) {
	int stat =-1;
	int v, w;

	stat =graphe_stable(g, n, 0);
	if(! stat) {
		for (v =0 ; v <graphe_get_n(g) -1 && !stat ; ++v)
			for (w =v +1 ; w <graphe_get_n(g)  && !stat ; ++w)
				stat =graphe_ajouter_arete(g, v, w, 1.);
			
		if(stat)
			graphe_detruire(g);
	}

    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_aleatoire(graphe* g, int n, double p, int est_or) {
	int v, w;
	if (n < 0)
		return -2;
	if (p < 0 || p > 1)
		return -3;
	if (graphe_stable(g, n, est_or) < 0)
		return -1;
	if (!est_or) {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = v; w < graphe_get_n(g); ++w)
				if ((double) rand()/RAND_MAX < p)
					if (graphe_ajouter_arete(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	} 
	else {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = 0; w < graphe_get_n(g); ++w)
				if ((double) rand()/RAND_MAX < p)
					if ( graphe_ajouter_arc(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	}
	return 0;
}

int graphe_aleatoire_multi(graphe* g, int n, double p, int est_or) {
	int v, w;
	if (n < 0)
		return -2;
	if (p < 0 || p >= 1)
		return -3;
	if (graphe_stable(g, n, est_or) < 0)
		return -1;
	if (!est_or) {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = v; w < graphe_get_n(g); ++w)
				while ((double) rand()/RAND_MAX < p)
					if (graphe_ajouter_arete(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	} 
	else {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = 0; w < graphe_get_n(g); ++w)
				while ((double) rand()/RAND_MAX < p)
					if (graphe_ajouter_arc(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	}
	return 0;
}



/*Fonctions du devoir d'optimisation*/





arc* fusion(arc left_tab[], arc right_tab[], int len_left_tab, int len_right_tab){
      int len = len_left_tab + len_right_tab;
      arc *ordonned_tab = malloc(sizeof(arc) * len);
      int i_left_tab = 0;
      int i_right_tab = 0;
      //Parcours entier des deux tableaux
      for(int i=0; i<len; i++){
            //left_tab vide
            if(i_left_tab == len_left_tab){
                ordonned_tab[i]=right_tab[i_right_tab];
                i_right_tab++;
            }
            //right_tab vide
            else if(i_right_tab == len_right_tab){
                ordonned_tab[i]=left_tab[i_left_tab];
                i_left_tab++;
            }
            /*l'arc de plus petit poids de right_tab a un plus petit poids que l'arc de plus 
            petit poids de left_tab*/
            else if (get_poids(&(right_tab[i_right_tab]))<=get_poids(&(left_tab[i_left_tab]))){
                ordonned_tab[i]=right_tab[i_right_tab];
                i_right_tab++;
            }
            /*l'arc de plus petit poids de left_tab a un plus petit poids que l'arc de plus 
            petit poids de right_tab*/
            else{
                ordonned_tab[i]=left_tab[i_left_tab];
                i_left_tab++;
            }
      }
      return ordonned_tab;
}

arc* tri_fusion(arc* tab, int len){
    //Tant que les tableaux contiennent plus d'un arc
    if (len >=2){
        arc* left_tab[len/2];
        arc* right_tab[len-(len/2)];
        //On remplit un premier de taille longueur du tableau d'origine divisé par 2
        for(int i=0; i<len/2; i++){
            left_tab[i] = &(tab[i]);
        }
        //On remplit un second tableau du reste des arcs
        for(int i=0; i<len-(len/2); i++){
            right_tab[i] = &(tab[i+(len/2)]);
        }
        //On fait une récursivité pour contrôler de nouveau la taille des tableaux
        arc* ordonned_left_tab = tri_fusion(*left_tab, len/2);
        arc* ordonned_right_tab = tri_fusion(*right_tab, len-(len/2));
        //Les tableaux auront ici les arcs rangés par poids croissant, on les fusionne donc
        arc* ordonned_tab = fusion(ordonned_left_tab, ordonned_right_tab, len/2, len-(len/2));
        return ordonned_tab;
    }
    return tab;
}


int uf_find(union_find* uf_sommet_tab, int uf_sommet){

    //Si le sommet n'est pas son propre parent = n'est pas racine
    if(uf_parent(&(uf_sommet_tab[uf_sommet]))!=uf_sommet){
    
        /*On lui set comme parent le parent de son parent par fonction récursive : 
        tous les descendants de la racine auront directement pour parent la racine*/
        uf_set_parent(&(uf_sommet_tab[uf_sommet]), uf_find(uf_sommet_tab, uf_parent(&(uf_sommet_tab[uf_sommet]))));
    }
    
    //Sinon, on retourne son parent (donc lui-même)
    return uf_parent(&(uf_sommet_tab[uf_sommet]));
}

int uf_union(union_find* uf_sommet_tab,int sommet_depart, int sommet_arrivee){

    //Recherche des deux parents racines des deux sommets
    int racine_sommet_depart = uf_find(uf_sommet_tab, sommet_depart);
    int racine_sommet_arrivee = uf_find(uf_sommet_tab, sommet_arrivee);
    
    //Si ces parents sont différents
    if (racine_sommet_depart!=racine_sommet_arrivee){
    
        //modification des parents pour lier les sommets
        if ( uf_rang(&(uf_sommet_tab[racine_sommet_depart])) < uf_rang(&(uf_sommet_tab[racine_sommet_arrivee]))){
            uf_set_parent(&(uf_sommet_tab[racine_sommet_depart]), racine_sommet_arrivee);
        }
        else{
            uf_set_parent(&(uf_sommet_tab[racine_sommet_arrivee]), racine_sommet_depart);
            if(uf_rang(&(uf_sommet_tab[racine_sommet_depart])) == uf_rang(&(uf_sommet_tab[racine_sommet_arrivee]))){
                uf_set_rang(&(uf_sommet_tab[racine_sommet_depart]), uf_rang(&(uf_sommet_tab[racine_sommet_arrivee])+1));
            }
        }
    //Les deux sommets ont leur parent racine qui est different, ils ne sont donc pas liés, et l'arrête doit être selectionnée
    	return 1;
    }
    return -1;
}


double kruskal(graphe* g, graphe* acm){
    double poids_acm = 0.00;
    arc* tab_arc = (arc*) malloc(graphe_get_m(g)*sizeof(arc));
    int n = 0;
    int i = 0;
    int nmb_aretes = 2*graphe_get_m(g);
    msuc *maillon_actuel = g->tab_sucs[n];
    
    /*parcours des maillons de successeurs pour mettre toutes aretes (sous forme d'arcs) dans
    un tableau*/
    while (n < graphe_get_n(g)){
        tab_arc[i] = *construire_arc(n,msuc_sommet(maillon_actuel),msuc_valeur(maillon_actuel));
        if (msuc_suivant(maillon_actuel)==NULL){
            n++;
            maillon_actuel = g->tab_sucs[n];
            i++;
        }
        else{
            maillon_actuel = msuc_suivant(maillon_actuel);
            i++;
        }
    }
    
    /*tri des aretes (sous forme d'arcs) du tableau*/
    arc* ordonned_tab_arc = tri_fusion(tab_arc, 2*graphe_get_m(g));
    
    printf("\narcs ordonnés par poids : \n\n");
    
    for (int i = 0; i<2*graphe_get_m(g); i++){
        printf("arc %d-%d de poids %f \n", get_som_dep(&(ordonned_tab_arc[i])),get_som_arr(&(ordonned_tab_arc[i])),get_poids(&(ordonned_tab_arc[i])));
    }
    
    //Création tableau de structures union_find, une par sommet du graphe
   
    union_find* tab_uf_sommets = (union_find*) malloc(graphe_get_n(g)*sizeof(union_find));
    for (int i = 0; i<graphe_get_n(g); i++){
        tab_uf_sommets[i] = *makeset_som(i);
    }
    
    // Choix des aretes de l'arbre couvrant de poids minimal
    for (int i = 0; i<nmb_aretes; i++){
        int garder_arete = uf_union(tab_uf_sommets , get_som_dep(&(ordonned_tab_arc[i])), get_som_arr(&(ordonned_tab_arc[i])));
        if (garder_arete == 1){
            poids_acm += get_poids(&(ordonned_tab_arc[i]));
            graphe_ajouter_arete(acm,get_som_dep(&(ordonned_tab_arc[i])), get_som_arr(&(ordonned_tab_arc[i])), get_poids(&(ordonned_tab_arc[i])));
        }
    }

    printf("\n Le poids final de l'acm est de : %f \n\n", poids_acm);
    free(tab_arc);
    free(ordonned_tab_arc);
    free(tab_uf_sommets);
    return poids_acm;
}

