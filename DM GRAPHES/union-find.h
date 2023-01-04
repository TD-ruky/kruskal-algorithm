#include <stdio.h>	/* perror */
#include <stdlib.h>	/* calloc */

/**
 * \brief union_find est un sommet à qui l'on attribue un parent et un rang
 *
 * Un union-find est représenté par :
 * un int parent qui est un sommet parent duquel provient le sommet 
 * un int rang qui permet de comparer la hauteur des arbres de deux sommets
 */
 
typedef struct union_find{
    int parent;
    int rang;
}union_find;

/** \brief crée en mémoire et initialise un union_find dont l'adresse est retournée(NULL en cas d'échec d'allocation mémoire)
 * \param node le numéro du sommet visé
 * \initialise le parent à lui-même, le rang à 0 
 */
union_find* makeset_som(int node);

/** \brief libère la mémoire occupée par un union_find
 * \param uf adresse de l'union_find
 * \return NULL
 *
 * \doit être soit NULL, soit l'adresse d'un union_find alloué dynamiquement
 */
union_find* uf_detruire(union_find *uf);

/** \brief retourne le parent du sommet considéré
 * \param uf adresse de l'union_find
 */
int uf_parent(union_find* uf);

/** \brief retourne le rang du sommet considéré
 * \param uf adresse de l'union_find
 */
int uf_rang(union_find* uf);

/** \brief affecte à un union_find un parent
 * \param uf adresse du union_find à définir
 * \param parent le sommet parent qui doit être affecté à l'union_find
 */
void uf_set_parent(union_find *uf, int parent);
/** \brief affecte à un union_find un rang
 * \param uf adresse du union_find à définir
 * \param rang le rang du sommet qui doit être affecté à l'union_find
 */
void uf_set_rang(union_find *uf, int rang);

