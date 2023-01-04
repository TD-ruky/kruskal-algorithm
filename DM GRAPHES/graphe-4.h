/**
 * \file graphe-4.h
 * \brief Représentation des graphes par liste de successeurs
 * \version 2 : maillons et listes de sommets externalisées
 * \date jeudi 28 octobre 2021
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 
 * \version 3 : fonctions Kruskal, tri_fusion, fusion, find, union
 * \authors Saint Aubin Elodie, Derivaux Thomas
*/

#ifndef GRAPHE_H
#define GRAPHE_H
#include <stdlib.h> /* rand */

/* ______________________________________ Structure de données */
#include "vlist.h"
#include "union-find.h"
#include "arc.h"
/**
 * \brief Graphe orienté ou non orienté représenté par sa liste de successeurs.
 *
 * Un graphe est ici représenté par son nombre de sommets \a n
 * et un tableau de pointeurs vers des maillons de successeurs (tableau dynamique de n pointeurs) \a tab_sucs.
 *
 * L'ensemble des sommets du graphe est alors \f$\{0, 1, 2, \ldots, n-1\}\f$.
 *
 * Le champ \a m est le nombre d'arêtes et est mis à jour par les fonctions de
 * manipulation.
 *
 * Le champ \a est_or vaut 0 si le graphe n'est pas orienté, autre chose sinon.
 */
struct s_graphe {
	int n;/**< nombre de sommets du graphes (doit être >=0) */
	int m;/**< nombre d'arêtes du graphes */
	msuc **tab_sucs; /* tableau de pointeurs vers les listes de successeurs du graphe */
	int est_or;/** <0 si le graphe n'est pas orienté, autre chose sinon. */
};
typedef struct s_graphe graphe;

/* ______________________________________ Constructeur et destructeur */

/**
 * \brief ALLOUE de la mémoire pour le tableau des listes de successeurs
 * \a n, et l'initialise le graphe en un graphe sans arc ou arête.
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \param est_or 0 si le graphe n'est pas orienté, autre chose sinon
 * \return -1 si l'allocation de mémoire pour le tableau des listes de
 * successeurs a échoué, -2 si \a n est négatif, 0 sinon.
*/
int graphe_stable(graphe* g, int n, int est_or);

/**
 * \brief Libère la zone mémoire occupée par un graphe.
 * \param g pointeur vers un graphe
 *
 * Si g->tab_sucs est le pointeur NULL, ne fait rien.
 */
void graphe_detruire(graphe *g);

/* ______________________________________ Ajout / Suppression d'arêtes */

/**
 * \brief Ajoute un arc entre deux sommets dans le graphe orienté
 * \param g adresse de la variable graphe à modifier
 * \param v une extrémité de l'arête (entre 0 et n -1)
 * \param w une extrémité de l'arête (entre 0 et n -1)
 * \param val valeur de l'arc ajouté
 * \return 0 en cas de succès, -1 si l'allocation du nouveau maillon a échoué.
 *
 * En dehors des fonctions internes à la bibliothèque, cette fonction ne devrait
 * pas être utilisée sur des graphes non orientés.
 */
int graphe_ajouter_arc(graphe *g, int v, int w, double val);

/**
 * \brief Ajoute une arête entre deux sommets dans le graphe non orienté
 * \param g adresse de la variable graphe à modifier
 * \param v une extrémité de l'arête (entre 0 et n -1)
 * \param w une extrémité de l'arête (entre 0 et n -1)
 * \param val valeur de l'arc ajouté
 * \return 0 en cas de succès, -1 si l'allocation du ou des nouveau(x)
 * maillon(s) a échoué.
 *
 * Ne devrait pas être utilisée sur des graphes orientés.
 */
int graphe_ajouter_arete(graphe* g, int v, int w, double val);

/**
 * \brief Supprime un arc entre deux sommets dans le graphe orienté
 * \param g adresse de la variable graphe à modifier
 * \param v extrémité initiale de l'arête (entre 0 et n -1)
 * \param w extrémité terminale de l'arête (entre 0 et n -1)
 * \param val valeur de l'arc à supprimer
 * \return -1 si l'arc ne peut être supprimé (n'existe pas), 0 sinon
 *
 * En dehors des fonctions internes à la bibliothèque, cette fonction ne devrait
 * pas être utilisée sur des graphes non orientés.
 */
int graphe_supprimer_arc(graphe *g, int v, int w, double val);

/**
 * \brief Supprime une arête entre deux sommets dans le graphe non orienté
 * \param g adresse de la variable graphe à modifier
 * \param v une extrémité de l'arête (entre 0 et n -1)
 * \param w une extrémité de l'arête (entre 0 et n -1)
 * \param val valeur de l'arete à supprimer
 * \return -1 si l'arête ne peut être supprimée (n'existe pas), 0 sinon
 *
 * Ne devrait pas être utilisée sur des graphes orientés.
 */
int graphe_supprimer_arete(graphe* g, int v, int w, double val);

/* ______________________________________ Accesseurs en lecture */


/**
 * \brief Retourne 1 si le graphe est orienté, 0 sinon
 * \param g adresse de la variable graphe à lire
 * \return 1 si le graphe est orienté, 0 sinon
 */
int graphe_est_or(graphe *g);

/**
 * \brief Retourne l'ordre du graphe.
 * \param g adresse de la variable graphe à lire
 * \return le nombre de sommets du graphe
 */
int graphe_get_n(graphe* g);

/**
 * \brief Retourne le nombre d'arêtes du graphe.
 * \param g adresse de la variable graphe à lire
 * \return le nombre d'arêtes du graphe
 */
int graphe_get_m(graphe* g);

/** \brief retourne l'adresse du premier maillon de successeur de la liste de
 * successeurs du sommet \a v dans le graphe d'adresse \a g
 * \param g adresse de la variable graphe à modifier
 * \param v sommet (entre 0 et n -1) dont on veut parcourir la liste des
 * successeurs
 * \return l'adresse du premier maillon de successeur de la liste de
 * successeurs du sommet \a v dans le graphe d'adresse \a g
 */
msuc *graphe_get_prem_msuc(graphe *g, int v);


/* NE PAS ACCÉDER DIRECTEMENT AUX CHAMPS EN-DESSOUS DE CETTE LIGNE */

/**
 * \brief Retourne le nombre de fois qu'un arc est présente entre deux
 * sommets donnés.
 * \param g adresse de la variable graphe à lire
 * \param v extrémité initiale de l'arête (entre 0 et n -1)
 * \param w extrémité terminale de l'arête (entre 0 et n -1)
 * \return le nombre d'arêtes entre les sommets \a v et \a w
 *
 * En dehors des fonctions internes à la bibliothèque, cette fonction ne devrait
 * pas être utilisée sur des graphes non orientés.
 */
int graphe_get_multiplicite_arc(graphe* g, int v, int w);

/**
 * \brief Retourne le nombre de fois qu'une arete est présente entre deux
 * sommets donnés.
 * \param g adresse de la variable graphe à lire
 * \param v une extrémité de l'arête (entre 0 et n -1)
 * \param w une extrémité de l'arête (entre 0 et n -1)
 * \return le nombre d'arêtes entre les sommets \a v et \a w
 */
int graphe_get_multiplicite_arete(graphe* g, int v, int w);

/**
 * \brief Retourne le degré sortant d'un sommet 
 * \param g adresse de la variable graphe à lire
 * \param v sommet du graphe
 * \return le nombre d'arcs ou arêtes d'extrémité initiale \a v.
 *
 * En dehors des fonctions internes à la bibliothèque, cette fonction ne devrait
 * pas être utilisée sur des graphes non orientés.
 */
int graphe_get_degre_sortant(graphe* g, int v);

/**
 * \brief Retourne le degré entrant d'un sommet 
 * \param g adresse de la variable graphe à lire
 * \param v sommet du graphe
 * \return le nombre d'arcs ou arêtes d'extrémité terminale \a v.
 *
 * Ne devrait pas être utilisée sur des graphes non orientés.
 */
int graphe_get_degre_entrant(graphe* g, int v);

/**
 * \brief Retourne le degré d'un sommet.
 * \param g adresse de la variable graphe à lire
 * \param v sommet du graphe (entre 0 et n -1)
 * \return le degré du sommet v dans le graphe
 */
int graphe_get_degre(graphe* g, int v);

/* ______________________________________ Entrées / Sorties */

/**
 * \brief Affiche sur la sortie standard les données d'un graphe
 * \param g adresse de la variable graphe à lire
 *
 * Affiche le nombre de sommets, d'arêtes, le caractère orienté ou non et les
 * listes de successeurs dans le graphe d'adresse \a g
 */
void graphe_afficher(graphe* g);

/**
 * \brief Écrit le graphe au format dot dans un fichier.
 * \param g adresse de la variable graphe à lire
 * \param nom_fichier nom du fichier à écrire
 * \param ecrire_valeurs 0 si l'on ne veut pas de l'affichage des valeurs des
 * arcs ou arêtes, autre chose sinon
 * \return 0 si l'écriture du fichier a réussi, -1 sinon
 */
int graphe_ecrire_dot(graphe *g, char *nom_fichier, int ecrire_valeurs);

/* ______________________________________ Autres fonctions d'initialisation */
/**
 * \brief ALLOUE de la mémoire pour un graphe d'ordre
 * \a n, et l'initialise en un graphe simple complet 
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \return -1 si l'allocation de mémoire pour le graphe a échoué,
 * 	-2 si \a n est négatif, 0 sinon.
 *
 * Cette fonction ne devrait pas être utilisée sur des graphes orientés.
*/
int graphe_complet(graphe* g, int n);

/**
 * \brief ALLOUE de la mémoire pour un graphe d'ordre
 * \a n, et l'initialise en un graphe simple aléatoire d'ordre \a n, où chaque
 * arc ou arête
 * est, de façon indépendante, présente avec probabilité \a p.
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \param p probabilité de présence de chaque arête
 * \param est_or caractère orienté ou non du graphe
 * \return -1 si l'allocation de mémoire pour la matrice d'adjacence a échoué,
 * 	-2 si \a n est négatif, -3 si \a p n'est pas compris entre 0 et 1 et
 * 	0 sinon.
*/
int graphe_aleatoire(graphe* g, int n, double p, int est_or);

/**
 * \brief ALLOUE de la mémoire pour un graphe d'ordre
 * \a n, et l'initialise en un graphe aléatoire d'ordre \a n, où, pour chaque
 * couple (paire dans le cas non-orienté) de sommets, il y a un nombre aléatoire
 * géométrique de paramètre \a p d'arcs ou arêtes entre ces sommets, ceci
 * valant aussi pour les boucles.
 *
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \param p paramètre de la loi géométrique
 * \param est_or caractère orienté ou non du graphe
 * \return -1 si l'allocation de mémoire pour la matrice d'adjacence a échoué,
 * 	-2 si \a n est négatif, -3 si \a p n'est pas compris entre 0 et 1
 * 	strictement et
 * 	0 sinon.
*/
int graphe_aleatoire_multi(graphe* g, int n, double p, int est_or);

/* ______________________________________ Autres fonctions de manipulation (application des parcours) */
/**
 * \brief Teste si un graphe est biparti
 * \param g adresse d'une variable de type graphe *existante*
 * \return -1 si la fonction ne s'est pas terminée normalement (ex. erreur d'allocation mémoire),
 * 1 si le graphe est biparti, 0 s'il ne l'est pas.
*/
int graphe_est_biparti(graphe* g);


//fonctions du devoir d'optimisation

/**
 * \Applique l'algorithme de Kruskal pour trouver un arbre couvrant de poids minimal dans un 
 * graphe connexe et non orienté
 * \param g adresse d'une variable de type graphe 
 * \param acm adresse d'une variable de type graphe (celui-ci étant un graphe stable)
 * \return le poids de l'acm du graphe et remplit le graphe stable acm pour en faire un arbre
 * couvrant de poids minimal
*\
*/
double kruskal(graphe* g, graphe* acm);

/**
 * \fusionne deux tableaux ordonnés par poids croissant pour en créer un unique de poids
 * croissants
 * \prend en paramètres deux tableaux de type arc ainsi que deux int qui sont respectivement la 
 * longueur des deux tableaux
 * \return un tableau de type arc
*/

arc* fusion(arc left_tab[], arc right_tab[], int len_left_tab, int len_right_tab);

/**
 * \divise un tableau jusqu'à en avoir de taille 1 (de façon récursive) puis ordonne ceux-ci par 
 * fusion grâce à la fonction fusion();
 * \prend en paramètre un tableau de type arc et un int len, longueur du tableau
 * \return un tableau de type arc ordonné en fonction du poids des arcs
*/
arc* tri_fusion(arc* tab, int len);

/**
 * \cherche le parent racine d'un sommet
 * \prend en paramètre un tableau de structures union_find, et un int correspondant au numéro
 * du sommet recherché
 * \si le parent direct du sommet que l'on prend en paramètre n'est pas racine, celui-ci
 * verra aussi la donnée de son parent modifiée
 * \return le numéro du parent du sommet en paramètre
*/
int uf_find(union_find* uf_sommet_tab, int uf_sommet);

/**
 * \crée une union entre deux sommets s'ils ne sont pas déjà reliés (= si ils ont des parents
 * racines différents)
 * \prend en paramère un tableau de structures union find et deux int qui correspondent aux deux
 * sommets de l'arrête testée
 * \return 1 si une union a été faite (= l'arrête est rajoutée dans l'arbre couvrant de poids
 * minimal), -1 sinon
*/
int uf_union(union_find* uf_sommet_tab,int sommet_depart, int sommet_arrive);
#endif
