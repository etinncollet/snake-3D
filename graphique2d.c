#include "graphique2d.h"
#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#define LONG 1350
#define HAUT 750

/*MLV_rgba(255-i , i , 0, 255)*/



/*ouvre la fenetre*/
void ouvre_fenetre(){
    MLV_create_window ("snake", "a", LONG, HAUT);
}


/*dessine le serpent pour le choix*/
/*x et y de la tete normalement(ceci n'est pas encore fait)*/
void serpent_choix_couleur(int x, int y, Couleur coul_choix){

    int xserpun[10] = {928, 926, 1104, 1080}, yserpun[10] = {458, 315, 261, 340};
    int xserpde[10] = {1146, 1078, 1078,  1146}, yserpde[10] = {275, 271, 340,  346};
    int xserptr[10] = {926, 863, 1042,  1103}, yserptr[10] = {315, 289, 259,  262};
    int xserpqu[10] = {1193, 1193, 1146, 1146}, yserpqu[10] = {252, 290, 344, 275};
    int xserpci[10] = {1142, 1078, 1146, 1193}, yserpci[10] = {248, 271, 275, 252};

    MLV_draw_filled_circle(878, 380, 91, MLV_rgba(coul_choix.r, coul_choix.v, coul_choix.b, 255));
    MLV_draw_circle(878, 380, 91, MLV_COLOR_BLACK);

    MLV_draw_filled_polygon(xserpun, yserpun, 4, MLV_rgba(coul_choix.r, coul_choix.v, coul_choix.b, 255));
    MLV_draw_polygon(xserpun, yserpun, 4, MLV_COLOR_BLACK);

    MLV_draw_filled_polygon(xserpde, yserpde, 4, MLV_rgba(coul_choix.r, coul_choix.v, coul_choix.b, 255));
    MLV_draw_polygon(xserpde, yserpde, 4, MLV_COLOR_BLACK);

    MLV_draw_filled_polygon(xserptr, yserptr, 4, MLV_rgba(coul_choix.r, coul_choix.v, coul_choix.b, 255));
    MLV_draw_polygon(xserptr, yserptr, 4, MLV_COLOR_BLACK);

    MLV_draw_filled_polygon(xserpqu, yserpqu, 4, MLV_rgba(coul_choix.r, coul_choix.v, coul_choix.b, 255));
    MLV_draw_polygon(xserpqu, yserpqu, 4, MLV_COLOR_BLACK);

    MLV_draw_filled_polygon(xserpci, yserpci, 4, MLV_rgba(coul_choix.r, coul_choix.v, coul_choix.b, 255));
    MLV_draw_polygon(xserpci, yserpci, 4, MLV_COLOR_BLACK);

    MLV_draw_filled_circle(879, 380, 91, MLV_rgba(coul_choix.r, coul_choix.v, coul_choix.b, 255));
    /*MLV_draw_filled_polygon(xserp, yserp, 4, MLV_COLOR_GREEN);*/
}


/*affiche le choix de la map*/
/*donne le nom du fichier qui comptien la map*/
/*donne le numero de la map*/
void affiche_choix_map(char nom[], int nbr){
   MLV_Font *font = MLV_load_font("font.ttf", 250);
   char nbre_a[2] = {'0'+ nbr, '\0'};
   MLV_draw_text_with_font(250, 200, nbre_a, font, MLV_COLOR_BLACK);
   MLV_free_font(font);
   font = MLV_load_font("font.ttf", 50);
   MLV_draw_text_with_font(200, 470, nom, font, MLV_COLOR_BLACK);
   MLV_free_font(font);
}


/*affiche un fond blanc pour faire un choix*/
/*coordonnée du coin en haut a gauche*/
void affiche_fond_choix(int x, int y){
    MLV_Font *font = MLV_load_font("font.ttf", 75);
    MLV_draw_filled_rectangle(x, y, 560, 460, MLV_COLOR_GREY50);
    MLV_draw_filled_rectangle(x+5, y+5, 550, 450, MLV_COLOR_WHITE);

    MLV_draw_text_with_font(x+520, 300, ">", font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(x+20, 300, "<", font, MLV_COLOR_BLACK);
    MLV_free_font(font);
}

/*affiche en gros le texte rentrer en parametre*/
void affiche_message(char message[20]){
    MLV_Font *font = MLV_load_font("font.ttf", 205);
    MLV_clear_window(MLV_COLOR_SADDLEBROWN);
    MLV_draw_text_with_font(200, 100, message, font, MLV_COLOR_BLACK);
    MLV_free_font(font);
    MLV_update_window();
    MLV_wait_seconds(3);
}


/*affiche le menu et capte les click*/
/*couleu donne le numero de la couleur choisie*/
/*coul transmet la liste des couleur*/
/*nummap donne le numero de la map choisi*/
/*lst_nom_map la liste des nom de map*/
/*le nombre max de map*/
int menu(int *couleu, Couleur coul[], int *nummap, char lst_nom_map[][15], int nbmax){
    int x, y;
    MLV_Font *font = MLV_load_font("font.ttf", 75);
    /*affiche le fond et les element qui ne vont pas bouger*/
    MLV_clear_window(MLV_COLOR_SADDLEBROWN);

    MLV_draw_text_with_font(450, -10, "SNAKE'S HOUSE", font, MLV_COLOR_BLACK);

    MLV_draw_filled_rectangle(950, 625, 350, 100, MLV_COLOR_GREY50);
    MLV_draw_text_with_font(1000, 620, "JOUER", font, MLV_COLOR_BLACK);

    MLV_free_font(font);
    font = MLV_load_font("font.ttf", 50);
    /*boucle pour l'entrer des click*/
    while(1){

        affiche_fond_choix(745, 120);

        affiche_fond_choix(45, 120);

        MLV_draw_text_with_font(920, 125, "SERPENT", font, MLV_COLOR_BLACK);

        MLV_draw_text_with_font(220, 125, "MAPS", font, MLV_COLOR_BLACK);

        serpent_choix_couleur(10, 20, coul[(*couleu)]);
        affiche_choix_map(lst_nom_map[absolut(*nummap)], absolut(*nummap));
        MLV_update_window();
        MLV_wait_mouse(&x, &y);
        if(x < 1300 && 950 < x && y < 725 && 625 < y){
            return 1;
        }else if(x < 600 && 550 < x && y < 575 && 125 < y){
            (*nummap) = ((*nummap) + 1)%nbmax;
        }else if(x < 85 && 45 < x && y < 575 && 125 < y){
            (*nummap) = ((*nummap) - 1)%nbmax;
        }else if(x < 1300 && 1260 < x && y < 575 && 125 < y){
            (*couleu) = ((*couleu) + 1)%4;
        }else if(x < 785 && 745 < x && y < 575 && 125 < y){
            (*couleu) = ((*couleu) - 1)%4;
        }
    }
    MLV_wait_seconds(1);
    MLV_free_font(font);
}


/*affiche deux case de couleur et de transparence differente selont le paramettre verf*/
/*(x, y) donne les coordonnée du de la mini map*/
/*donne la taille de celui ci*/
/* un deux donne l'emplacement du bloc dans la mini map*/
/*etage et tete permete les condition sur les etage*/
/*defini les couleur et les transparance utiliser*/
void verifetage_block(int x, int y, int taille, int un, int deux, int etage, int tete, int coul1, int coul2, int trans1, int trans2){
    if(tete == etage){
        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(coul1 , coul1 , coul1,  trans1));
    }else if(tete > etage){
        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(coul2 , coul2 , coul2,  200));
    }else{
        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(coul2 , coul2 , coul2, trans2));
    }
}


/*affiche sur la mini map le serpent en fonction de sont etage*/
/*fait comme la fonction precedente mais pour le corp du serpent*/
void verifetage_serpent(int x, int y, int taille, int un, int deux, int etage, int tete,
    int coul1, int coul2, int coul3, int trans1, int trans2){
    if(tete == etage){
        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(coul1 , coul2 , coul3,  trans1));
    }else if(tete > etage){
        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(coul1 , coul2 , coul3,  trans1));
    }else{
        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(coul1 , coul2 , coul3, trans2));
    }
}


/*je ne sait plus*/
void dessine_choix(int tabx[], int taby[], int transpa, int etage, int tete){
    MLV_draw_filled_polygon(tabx, taby, 4, MLV_rgba(210 , 210 , 210,  255));
    /*if(tete == etage || tete == (etage - 1)){
        MLV_draw_filled_polygon(tabx, taby, 4, MLV_rgba(200 , 200 , 200,  255));
    }else{
        MLV_draw_filled_polygon(tabx, taby, 4, MLV_rgba(200, 200 , 200,  transpa));
    }*/
}


/*affiche les escalier sur la mini map*/
/*suit le meme schema que pour les block et le serpent*/
void escalier(int x, int y, int taille, int un, int deux, int nbr, int etage, int tete){
    int escax3[4] = {x + deux*taille , (x + deux*taille) + (taille/6), (x + deux*taille) + (taille*5/6), x + (deux+1)*taille},
        escay3[4] = {y + (un+1)*taille, y + un*taille, y + un*taille, y + (un+1)*taille},

        escax4[4] = {x + deux*taille, x + (deux+1)*taille, x + (deux+1)*taille, x + deux*taille},
        escay4[4] = {y + un*taille , (y + un*taille) + (taille/6), (y + un*taille) + (taille*5/6), y + (un+1)*taille},

        escax5[4] = {x + deux*taille , (x + deux*taille) + (taille/6), (x + deux*taille) + (taille*5/6), x + (deux+1)*taille},
        escay5[4] = {y + un*taille, y + (un+1)*taille, y + (un+1)*taille, y + un*taille},

        escax6[4] = {x + deux*taille, x + (deux+1)*taille, x + (deux+1)*taille, x + deux*taille},
        escay6[4] = {(y + un*taille) + (taille/4), y + un*taille, y + (un+1)*taille, (y + un*taille) + (taille*3/4)};

    verifetage_block(x, y, taille, un, deux, etage, tete, 35, 145, 255, 100);
    switch(nbr){
        case(3):
            dessine_choix(escax3, escay3, 100, etage, tete);
            break;
        case(4):
            dessine_choix(escax4, escay4, 100, etage, tete);
            break;
        case(5):
            dessine_choix(escax5, escay5, 100, etage, tete);
            break;
        case(6):
            dessine_choix(escax6, escay6, 100, etage, tete);
            break;
        default:
            fprintf(stderr, "erreur escalier");
    }
}


/*affiche la petite carte*/
/*(x,y) donne les coordonner de la map */
/*taille donne la taille de chaque block qui la constitue*/
/*transmet la structure qui comptient toute les information*/
/*la couleur du serpent*/
void carte(int x, int y, int taille, Maps plan, Couleur couleur){
    int un, deux, etage;
    MLV_draw_filled_rectangle(x-2, y-2, taille*plan.coter +4, taille*plan.coter+4, MLV_COLOR_GREEN);

    for(etage = 0; etage < plan.hauteur; etage++){
        for(un = 0; un < plan.coter; un++){
            for(deux = 0; deux < plan.coter; deux++){

                if(plan.matrice[etage][un][deux].sol == 0){
                    /*MLV_draw_rectangle(x + un*taille, y + deux*taille, taille, taille, MLV_COLOR_WHITE);*/
                }else if(plan.matrice[etage][un][deux].sol == 7 ){
                    if(plan.matrice[etage][un][deux].serpent == 1){
                        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(couleur.r, couleur.v, couleur.b, 255));
                    }
                }else if(plan.matrice[etage][un][deux].sol == 2){
                    verifetage_block(x, y, taille, un, deux, etage, plan.tete->coordonne[0], 0, 75, 255, 100);
                }else if(plan.matrice[etage][un][deux].sol > 2 && plan.matrice[etage][un][deux].sol < 7){
                    escalier(x, y, taille, un, deux, plan.matrice[etage][un][deux].sol, etage, plan.tete->coordonne[0]);
                    if(plan.matrice[etage][un][deux].serpent == 1){
                        MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, MLV_rgba(couleur.r, couleur.v, couleur.b, 255));
                    }
                }else{
                    if(plan.matrice[etage][un][deux].serpent == 0){
                        verifetage_block(x, y, taille, un, deux, etage, plan.tete->coordonne[0], 35, 145, 255, 100);
                    }else if(plan.matrice[etage][un][deux].serpent == 2){
                        verifetage_block(x, y, taille, un, deux, etage, plan.tete->coordonne[0], 255, 255, 255, 100);
                    }else{
                        /*MLV_draw_filled_rectangle(x + deux*taille, y + un*taille, taille, taille, couleur);*/
                        verifetage_serpent(x, y, taille, un, deux, etage, plan.tete->coordonne[0], couleur.r, couleur.v, couleur.b, 255, 100);
                    }

                }

            }
        }
    }
    MLV_update_window();
}


/*demande les touche et remplie direction en consequence*/
/*renvoi la nouvel direction*/
int demande_bouton(int direction[2], int *nbrdirec){
    int code, retour;
    MLV_Keyboard_button bout;
    retour = MLV_wait_keyboard_or_seconds(&bout, NULL, &code, 1);
    /*fprintf(stderr, "%d, %d, %d", retour, code, bout);*/
    if(retour){
        return 2;
    }
    switch(bout){
        case 275:
            (*nbrdirec) += 1;
            break;
        case 276:
            (*nbrdirec) += 3;
            break;
        case 109:
            return 0;
        default:
            return 2;
    }

    (*nbrdirec) = (*nbrdirec)%4;

    switch((*nbrdirec)){
        case 0:
            direction[0] = -1;
            direction[1] = 0;
            break;
        case 2:
            direction[0] = 1;
            direction[1] = 0;
            break;
        case 1:
            direction[0] = 0;
            direction[1] = 1;
            break;
        case 3:
            direction[0] = 0;
            direction[1] = -1;
            break;
    }
    return 1;
}
