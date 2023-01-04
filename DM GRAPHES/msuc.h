#ifndef MSUC_H
#define MSUC_H

/**
 * \brief Maillon de successeur dans un graphe arc/arête-valué
 *
 * Un maillon de successeur est représenté par :
 * un /a sommet (successeur du sommet considéré),
 * une /a valeur (valeur de l'arc ou arête allant du sommet considéré à ce
 * succeseur,
 * un pointeur /a suivant vers le maillon de successeur suivant (NULL s'il n'y
 * en a pas).
 */
typedef struct msuc {
	int sommet; /**< sommet successeur du sommet considéré */
    double valeur;/**< valeur de l'arc ou de l'arête menant du sommet considéré à
                    ce successeur */
    struct msuc *suivant;/**< pointeur vers le prochain successeur (NULL s'il
                           n'y en a pas). */
} msuc;

/** \brief crée en mémoire et initialise un maillon dont l'adresse est retournée
 * \param v sommet du maillon
 * \param val valeur associée
 * \return l'adresse du maillon construit (NULL en cas d'échec d'allocation mémoire).
 */
msuc* msuc_construire(int v, double val);

/** \brief libère la mémoire occupée par un maillon
 * \param m adresse du maillon
 * \return NULL
 *
 * \a m doit être soit NULL, soit l'adresse d'un maillon alloué dynamiquement
 */
msuc* msuc_detruire(msuc *m);

/** \brief affecte à un maillon son maillon suivant
 * \param m adresse du maillon de successeur à définir
 * \param msuiv adresse du maillon amené à succéder à m dans la liste
 */
void msuc_set_suivant(msuc *m, msuc *msuiv);

/** \brief retourne le pointeur vers le maillon suivant
 * \param m adresse du maillon de successeur à lire
 * \return l'adresse du prochain maillon de successeur (NULL s'il n'y a pas).
 */
msuc *msuc_suivant(msuc *m);

/** \brief retourne le sommet successeur du sommet considéré
 * \param m adresse du maillon de successeur à lire
 * \return le sommet successeur du sommet considéré.
 */
int msuc_sommet(msuc *m);

/** \brief retourne la valeur de l'arête ou de l'arc menant du sommet considéré
 * au sommet successeur.
 * \param m adresse du maillon de successeur à lire
 * \return la valeur de l'arête ou de l'arc menant du sommet considéré au sommet
 * successeur.
 */
double msuc_valeur(msuc *m);

#endif
