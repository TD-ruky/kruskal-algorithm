# ___________________________________________________ Rappels Makefile
# ____ Principes :
# Un fichier Makefile est un ensemble de cibles
# Pour chaque cible, il faut donner ses règles de génération (i.e., la succession de commandes permettant de produire la cible)
# Pour chaque cible, on indique ses dépendances (ce sont les fichiers, sources ou cibles, dont la mise à jour impacte potentiellement la cible)
#
# ____ Éléments de syntaxe :
# Marque de commentaires : 
#	caractère # précédant la ligne à commenter
#
# Macros :
#       définition :            MACRO = valeur
#       utilisation :           $(MACRO)
#
# Cibles :
#
# cible: dépendances                    #liste des dependances separées par un caractère d'espacement
#       regle1 de génération            #attention, chaque commande nécessite un passage à la ligne suivi d'une tabulation
#       regle2 de génération
#       ...
#
# ____ Variables génériques :
# $@            :       cible courante
# $<            :       première dépendance de la cible courante
# $^            :       toutes les dépendances de la cible courante
#
# ____________________________________________________
PROG=test-kruskal-opti

CC=gcc
CFLAGS=-Wall -Wfatal-errors -g -Wincompatible-pointer-types -Werror -pedantic

SOURCES=$(wildcard *.c *.h)
ALLOBJS=$(patsubst %.c,%.o,$(wildcard *.c))
OBJS=$(filter-out $(patsubst %,%.o,$(PROG)) main-test-1.o,$(ALLOBJS))

# exécutables
all: $(PROG)

test-kruskal-opti: test-kruskal-opti.o graphe-4.o vlist.o msuc.o union-find.o arc.o
	$(CC) $^ -o $@

# programmes test
test-kruskal-opti.o: test-kruskal-opti.c graphe-4.h
	$(CC) -c $(CFLAGS) $< -o $@

# modèle
graphe-4.o:	graphe-4.c graphe-4.h vlist.h msuc.h union-find.h arc.h
	$(CC) -c $(CFLAGS) $< -o $@

vlist.o: vlist.c vlist.h msuc.h
	$(CC) -c $(CFLAGS) $< -o $@

msuc.o:	msuc.c msuc.h
	$(CC) -c $(CFLAGS) $< -o $@

arc.o: arc.c arc.h
	$(CC) -c $(CFLAGS) $< -o $@

union-find.o: union-find.c union-find.h
	$(CC) -c $(CFLAGS) $< -o $@

# lancement du programme test
launch:
	./test-kruskal-opti

# nettoyage
OUTPUT=kruskal.dot acm-kruskal.dot
clean:
	@rm -f *.o $(OUTPUT)
distclean: clean
	@rm -f $(PROG) *~
