#include "union-find.h"

/* __________________________________ Construction / destruction */
union_find *makeset_som(int node){
    union_find* uf = (union_find*)malloc(sizeof(*uf));
	if (!uf)
		perror("malloc");
	else {
		uf->parent = node;
		uf->rang = 0;
	}
	return uf;
}

union_find* uf_detruire(union_find *uf) {
	if(uf)
		free(uf);
	
	return NULL;
}
/* __________________________________ Accesseurs en lecture */
int uf_parent(union_find* uf) {
	return uf->parent;
}
int uf_rang(union_find* uf) {
	return uf->rang;
}
/* __________________________________ Accesseurs en écriture */
void uf_set_parent(union_find *uf, int parent) {
	uf->parent =parent;
} 
void uf_set_rang(union_find *uf, int rang) {
	uf->rang =rang;
}

