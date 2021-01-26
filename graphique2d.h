#include "map.h"
#include <MLV/MLV_all.h>

typedef struct c {
    int b;
    int r;
    int v;
} Couleur;


void ouvre_fenetre();


void escalier(int x, int y, int taille, int un, int deux, int nbr, int etage, int tete);


void carte(int x, int y, int taille, Maps plan, Couleur couleur);


int demande_bouton(int direction[2], int *nbrdirec);


int menu(int *couleu, Couleur coul[], int *nummap, char lst_nom_map[][15], int nbmax);


void affiche_message(char message[20]);
