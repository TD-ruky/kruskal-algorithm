#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Arc dans un graphe non orienté => sens unique d'une arête
 *
 * Un arc est représenté par :
 * un int sommet_dep qui est le sommet duquel part l'arc
 * un int sommet_arr qui est le sommet vers lequel se dirige l'arc 
 * un double poids qui est le poids de l'arc considéré
 */
typedef struct arc{
    int sommet_dep;
    int sommet_arr;
    double poids;
}arc;

/** \brief crée en mémoire et initialise un arc dont l'adresse est retournée(NULL en cas d'échec d'allocation mémoire)
 * \param dep sommet_dep de l'arc
 * \param arr sommet_arr de l'arc
 * \param poids le poids de l'arc
 */
arc* construire_arc(int dep, int arr, double poids);

/** \brief libère la mémoire occupée par un arc
 * \param a adresse de l'arc
 * \return NULL
 *
 * \ doit être soit NULL, soit l'adresse d'un arc alloué dynamiquement
 */
arc* detruire_arc(arc *a);

/** \brief retourne le sommet de départ de l'arc considéré
 * \param a adresse de l'arc à lire
 */
int get_som_dep(arc *a);
/** \brief retourne le sommet d'arrivée de l'arc considéré
 * \param a adresse de l'arc à lire
 */
int get_som_arr(arc *a);
/** \brief retourne le poids de l'arc considéré
 * \param a adresse de l'arc à lire
 */
double get_poids(arc *a);


