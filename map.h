#include "math.h"

typedef struct b {
    int sol;
    int serpent;
} Block;

typedef struct s {
    int coordonne[3];
    struct s *preced;
} Serpent, *Tete;

typedef struct m {
    int coter;
    int hauteur;
    Tete tete;
    int nombre;
    int direction[2];
    int pomme[3];
    Block matrice[3][20][20];
} Maps;


int initialise_map(Maps *map, char nom[]);


int avance(Maps *map, int *descendu);


int ajoute(Maps *map);


void popomme(Maps *map);


void afficheserpent(Maps *map);


void libereserpent(Maps *map);


void litmap(char *lien, Maps *map);


void decompose(Maps *map, Block regard[3][20][20]);
