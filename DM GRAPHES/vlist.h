#ifndef VLIST_H
#define VLIST_H

#include "msuc.h"

/**
 * \brief Liste de sommets d'un graphe.
 *
 * Une liste de sommets est représentée par l'adresse \a pm 
 * de son premier maillon (NULL si la liste est vide), l'adresse \a dm 
 * de son dernier maillon (NULL si la liste est vide) et son nombre \a card
 * de maillons
 */
typedef struct vlist {
	int card; /**< taille de la liste */
    struct msuc *pm; /**< pointeur vers le premier maillon de la liste (NULL si la liste est vide) */
    struct msuc *dm; /**< pointeur vers le dernier maillon de la liste (NULL si la liste est vide) */
} vlist;

/** \brief crée en mémoire une liste vide dont l'adresse est retournée
 * \return l'adresse de la liste construite (NULL en cas d'échec d'allocation mémoire).
 *
 * Le champ \a card est initialisé à 0.
 * Les champs \a pm et \a dm sont initialisés à NULL.
 */
vlist* vlist_construire();

/** \brief libère la mémoire occupée par une liste et ses maillons, et retourne NULL
 * \param l adresse de la liste
 * \return NULL
 *
 * \a l doit être soit NULL, soit l'adresse d'une liste allouée dynamiquement
 *
 * les maillons de l sont tous détruits
 */
vlist* vlist_detruire(vlist *l);

/** \brief crée un maillon de sommet \a v et valeur \a val, et l'insère en début de liste
 * \param l adresse de la liste
 * \param v sommet contenu dans le maillon
 * \param val valeur associée au maillon
 * \return la taille actualisée de la liste en cas de succès, -1 en cas d'échec (allocation mémoire)
 *
 * Cette fonction est à utiliser pour manipuler \a l comme une pile
 */
int vlist_ajouter_deb(vlist *l, int v, double val);

/** \brief crée un maillon de sommet \a v et valeur \a val, et l'insère en fin de liste
 * \param l adresse de la liste
 * \param v sommet contenu dans le maillon
 * \param val valeur associée au maillon
 *
 * Cette fonction est à utiliser pour manipuler \a l comme une file
 */
int vlist_ajouter_fin(vlist *l, int v, double val);

/** \brief supprime le premier maillon d'une liste
 * \param l adresse de la liste
 * \return la taille actualisée de la liste
 *
 * Cette fonction est à utiliser pour manipuler \a l comme une pile ou comme une file
 */
int vlist_supprimer_deb(vlist *l);

/** \brief retourne, s'il existe, le sommet de tête d'une liste
 * \param l adresse de la liste
 * \return le sommet du premier maillon de la liste si celle-ci est non vide, -1 sinon.
 */
int vlist_get_sommet(vlist *l);

/** \brief retourne la taille d'une liste
 * \param l adresse de la liste
 * \return le champ \a card de la liste considérée.
 */
int vlist_get_card(vlist *l);

#endif
