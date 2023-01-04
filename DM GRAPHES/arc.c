#include <stdio.h>
#include <stdlib.h>

#include "arc.h"

/* __________________________________ Construction / destruction */
arc* construire_arc(int dep, int arr, double poids){
    arc* a = (arc*) malloc(sizeof(*a));
    if (!a)
        perror("malloc");
    else {
        a -> sommet_dep = dep;
        a -> sommet_arr = arr;
        a -> poids = poids;
    }
    return a;
}
arc* detruire_arc(arc *a) {
	if(a)
		free(a);
	
	return NULL;
}
/* __________________________________ Accesseurs en lecture */
int get_som_dep(arc *a){
    return a-> sommet_dep;
}
int get_som_arr(arc *a){
    return a-> sommet_arr;
}
double get_poids(arc *a){
    return a-> poids;
}

