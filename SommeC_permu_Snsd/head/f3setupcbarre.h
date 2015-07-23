#ifndef _F3SETUPCBARRE_H
#define _F3SETUPCBARRE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "varglobal.h"

/**
 * DECLARATION FONCTION
 */
int lecture_fichier(char *nomfichier);

void print_pb_info(void);
void print_node_info(Node *noeud);

void free_tab_job(void);
void free_node(Node *noeud);

int min(int a, int b);
int max(int a, int b);
int calculer_nb_node_total(int n);

int calculer_cbarre(int *sequence);
int calculer_cbarre_cpt(int *sequence, int jobcount);
int calculer_LB(int *sequence);

void pse(Node *noeud);
Node * create_node(Node *parent, int pos); // création d'un noeud fils

#endif
