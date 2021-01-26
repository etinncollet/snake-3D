#include "main.h"
#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>

/*est le main du jeu*/
int main(){
    Maps carte_jeu;
    int un, descente = 0, nbdirection = 2, a, nbr_coul = 2, nbr_map = 0;
    Couleur choix[4] = {{255, 0, 0}, {255, 255, 255}, {255,255,0}, {153,50,204}};
    char lst_map[10][15] = {"map0.txt", "map1.txt", "map2.txt", "maplionel.txt"};
    /*a = 1611301609;*/

    ouvre_fenetre();
    /*boucle pricipale*/
    while(1){
        a = time(NULL);
        srand(a);
        menu(&nbr_coul, choix, &nbr_map, lst_map, 4);
        initialise_map(&carte_jeu, lst_map[nbr_map]);
        affiche_devant(carte_jeu, choix[nbr_coul], 1);
        /*boucle du jeu*/
        while(1){
            affiche_devant(carte_jeu, choix[nbr_coul], 0);
            if(demande_bouton(carte_jeu.direction, &nbdirection) == 0){
                break;
            }

            un = avance(&carte_jeu, &descente);
            if(un == 0){
                affiche_message("perdu");
                break;
            }
        }

    }
    libereserpent(&carte_jeu);
    MLV_free_window();
    return 0;
}
