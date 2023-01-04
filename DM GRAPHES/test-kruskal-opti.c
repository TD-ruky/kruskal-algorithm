/**
 * \file test-kruskal-opti.c
 * fonctions testées
 * - kruskal
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe-4.h"

/* sous-routine du programme test */
void test_kruskal(graphe* g, graphe* acm, char *nom_fichier, char *nom_fichier2);

/* ____ programme test */
int main() {
    graphe g;
    graphe acm;
    int n = 8;
    if(graphe_stable(&acm, n, 0)){
		puts("une erreur est survenue lors du deroulement de la fonction graphe_stable\n");
    }
	if(graphe_stable(&g, n, 0))
		puts("une erreur est survenue lors du deroulement de la fonction graphe_stable\n");
	else {
		/* __ premier test: graphe kruskal */
		graphe_ajouter_arete(&g, 0, 1, 8.00);
		graphe_ajouter_arete(&g, 1, 3, 16.30);
		graphe_ajouter_arete(&g, 1, 4, 58.20);
		graphe_ajouter_arete(&g, 2, 5, 20.00);
		graphe_ajouter_arete(&g, 0, 2, 1.90);
		graphe_ajouter_arete(&g, 3, 6, 3.40);
		graphe_ajouter_arete(&g, 2, 6, 3.60);
		graphe_ajouter_arete(&g, 3, 2, 4.07);
		graphe_ajouter_arete(&g, 7, 5, 11.40);
		graphe_ajouter_arete(&g, 5, 1, 8.07);
		graphe_ajouter_arete(&g, 6, 7, 5.16);
		graphe_ajouter_arete(&g, 6, 6, 4.76);
		graphe_ajouter_arete(&g, 1, 2, 4.25);
		graphe_ajouter_arete(&g, 1, 5, 5.16);
		graphe_ajouter_arete(&g, 2, 3, 2.04);
		graphe_ajouter_arete(&g, 2, 2, 2.04);
		graphe_ajouter_arete(&g, 2, 6, 17.48);
		graphe_ajouter_arete(&g, 3, 7, 35.06);
		graphe_ajouter_arete(&g, 3, 4, 25.16);
		graphe_ajouter_arete(&g, 3, 1, 9.00);
		test_kruskal(&g, &acm, "kruskal.dot","acm-kruskal.dot");

	}
    graphe_detruire(&g);
    graphe_detruire(&acm);
    return EXIT_SUCCESS;
}
void test_kruskal(graphe* g, graphe* acm, char *nom_fichier, char *nom_fichier2){
    char cmd[100] = "dot -Tx11";
    graphe_ecrire_dot(g, nom_fichier, 1);
    sprintf(cmd, "dot -Tx11 %s", nom_fichier);
    system(cmd);
    kruskal(g, acm);
    graphe_ecrire_dot(acm, nom_fichier2, 1);
    sprintf(cmd, "dot -Tx11 %s", nom_fichier2);
    system(cmd);
}

