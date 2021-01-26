#include "graphique2d.h"

/*structure qui caracterise un objet*/
typedef struct o {
    int type;/*0 mur 1 pomme 2 serpent 3 eslcaler*/
    int base_de_x[4];
    int base_de_y[4];
    int ydess;
    int rang;
    int i;
    int y_du_centre;
} Objet;

/*structure qui caracterise la liste chaine d'objet*/
typedef struct l {
    Objet info;
    int distance;
    struct l *suivant;
} *Liste, Element;

/*affiche la vision du serpent avec tout les objets*/
void affiche_devant(Maps map, Couleur couleur_serp, int entier);
