#include "graphique3d.h"
#include <stdlib.h>

#define LONG 1350
#define HAUT 750
#define GAUCHE LONG*3/10
#define DROITE LONG*7/10
#define SOUS 200


/*affiche dans le terminal la liste des objet retrer en paramettre*/
void affiche_terminal_liste_element(Liste lst){
    Element *affiche = lst;
    int compte = 0;
    while(affiche != NULL && compte < 20){
        compte += 1;
        fprintf(stderr, " %d / %d / (%d, %d) ->", affiche->info.type, affiche->distance, affiche->info.i, affiche->info.rang);
        affiche = affiche->suivant;
    }
    fprintf(stderr, "\n");
}


/*dessine une pomme au centre de la case a la quel elle appartient*/
/*donne la liste des x de la case*/
/*donne la liste des y de la case*/
/*donne le y de la base des point*/
/*donne la ranger du bloc*/
/*donne le y du centre de l'image*/
/*donne la profoindeur*/
void dessine_pomme(int x_base[], int y_base[], int y_debut_dessus, int ranger, int centre_y, int i){
    int xbas, ybas, rayon = (x_base[3] - x_base[0])/4;
    int tige_x[3], tige_y[3];
    calcule_milleux_quatre(x_base, y_base, &xbas, &ybas);
    MLV_draw_filled_polygon(x_base, y_base, 4, MLV_COLOR_GREEN);
    MLV_draw_polygon(x_base, y_base, 4, MLV_COLOR_BLACK);

    tige_x[0] = xbas;
    tige_x[1] = xbas-rayon/10;
    tige_x[2] = xbas+rayon/10;

    tige_y[0] = ybas-rayon-((rayon * 9)/10);
    tige_y[1] = ybas-(rayon*2) - rayon/3;
    tige_y[2] = ybas-(rayon*2) - rayon/5;

    MLV_draw_filled_circle(xbas, ybas - rayon, rayon, MLV_COLOR_RED3);
    MLV_draw_filled_circle(xbas, ybas - rayon, (rayon*5)/7, MLV_COLOR_RED2);
    MLV_draw_filled_polygon(tige_x, tige_y, 3, MLV_COLOR_DARK_GREEN);
}


/*calcule les point droite et gauche en fonction de nbr et les renvoie en parametre*/
void suite_coter(int nbr, int *deb_d, int *deb_g, int signe, int plg, int pld){
    int i2, longueur;

    (*deb_g) = GAUCHE;
    (*deb_d) = DROITE;
    longueur = DROITE - GAUCHE;
    for(i2 = 0; i2 < nbr; i2++){

        (*deb_g) += signe * ((longueur * puissance(6, i2 + plg)) / puissance(7, i2 + plg));
        (*deb_d) += signe * ((longueur * puissance(6, i2 + pld)) / puissance(7, i2 + pld));

    }
}


/*dessine le corp du serpent*/
/*donne la liste des x de la case puis des y*/
/*donne le y de la base des point*/
/*donne la ranger du bloc*/
/*donne le y du centre de l'image*/
/*donne la profoindeur*/
/*donne la coumeur du serpent*/
void dessine_corp_serpent(int x_base[], int y_base[], int y_debut_dessus, int ranger, int centre_y, int i, Couleur serpcoul){
    int depart_d = LONG*6/9, depart_g = LONG*3/9;
    int coef_1, coef_2, ordo;
    int coef_3, coef_4, ordo_2;
    int centre_x = LONG/2;
    int blocixe[4] = {506, depart_g, depart_d, 844}, blocigrec[4] = {650, y_debut_dessus, y_debut_dessus, 650};
    int xmur[4], ymur[4], i4;

    y_debut_dessus += 200;
    if(ranger == 0){
        depart_d = DROITE;
        depart_g = GAUCHE;
    }else if(ranger < 0){
        suite_coter(absolut(ranger), &depart_d, &depart_g, -1, 1, 0);
    }else{
        suite_coter(ranger, &depart_d, &depart_g, 1, 0, 1);
    }

    blocixe[1] = depart_g; blocixe[2] = depart_d;
    /*calcule les equation de droite*/
    point_ver_equa(centre_x, centre_y, depart_g, y_debut_dessus, &coef_1, &coef_2, &ordo);
    point_ver_equa(centre_x, centre_y, depart_d, y_debut_dessus, &coef_3, &coef_4, &ordo_2);

    blocigrec[0] = calcule_x(x_base[0], coef_1, coef_2, ordo);
    blocigrec[1] = calcule_x(x_base[1], coef_1, coef_2, ordo);
    blocigrec[2] = calcule_x(x_base[2], coef_3, coef_4, ordo_2);
    blocigrec[3] = calcule_x(x_base[3], coef_3, coef_4, ordo_2);

    blocixe[0] = x_base[0];
    blocixe[1] = x_base[1];
    blocixe[2] = x_base[2];
    blocixe[3] = x_base[3];
    /*affiche les coter du serpent*/
    for(i4 = 0; i4 < 4; i4++){
        xmur[0] = blocixe[i4];
        xmur[1] = blocixe[(i4 + 1)%4];
        xmur[2] = blocixe[(i4 + 1)%4];
        xmur[3] = blocixe[i4];
        ymur[0] = blocigrec[i4];
        ymur[1] = blocigrec[(i4+1)%4];
        ymur[2] = y_base[(i4+1)%4];
        ymur[3] = y_base[i4];
        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_rgba(serpcoul.r, serpcoul.v, serpcoul.b, 255));
    }
}


/*dessine un mur*/
void dessine_mur(int x_base[], int y_base[], int y_debut_dessus, int ranger, int centre_y, int i){
    int depart_d = LONG*6/9, depart_g = LONG*3/9;
    int coef_1, coef_2, ordo;
    int coef_3, coef_4, ordo_2;
    int centre_x = LONG/2;
    int blocixe[4] = {506, depart_g, depart_d, 844}, blocigrec[4] = {650, y_debut_dessus, y_debut_dessus, 650};
    int xmur[4], ymur[4], i4;

    if(ranger == 0){
        depart_d = DROITE;
        depart_g = GAUCHE;
    }else if(ranger < 0){
        suite_coter(absolut(ranger), &depart_d, &depart_g, -1, 1, 0);
    }else{
        suite_coter(ranger, &depart_d, &depart_g, 1, 0, 1);
    }

    blocixe[1] = depart_g; blocixe[2] = depart_d;

    point_ver_equa(centre_x, centre_y, depart_g, y_debut_dessus, &coef_1, &coef_2, &ordo);
    point_ver_equa(centre_x, centre_y, depart_d, y_debut_dessus, &coef_3, &coef_4, &ordo_2);

    blocigrec[0] = calcule_x(x_base[0], coef_1, coef_2, ordo);
    blocigrec[1] = calcule_x(x_base[1], coef_1, coef_2, ordo);
    blocigrec[2] = calcule_x(x_base[2], coef_3, coef_4, ordo_2);
    blocigrec[3] = calcule_x(x_base[3], coef_3, coef_4, ordo_2);

    blocixe[0] = x_base[0];
    blocixe[1] = x_base[1];
    blocixe[2] = x_base[2];
    blocixe[3] = x_base[3];

    for(i4 = 0; i4 < 4; i4++){
        xmur[0] = blocixe[i4];
        xmur[1] = blocixe[(i4 + 1)%4];
        xmur[2] = blocixe[(i4 + 1)%4];
        xmur[3] = blocixe[i4];
        ymur[0] = blocigrec[i4];
        ymur[1] = blocigrec[(i4+1)%4];
        ymur[2] = y_base[(i4+1)%4];
        ymur[3] = y_base[i4];
        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_COLOR_BLACK);
    }

}


/*dessine le toit des case devant toi*/
void dessine_toit(int x_base[], int y_base[], int y_debut_dessus, int ranger, int centre_y, int i){
    int depart_d = LONG*6/9, depart_g = LONG*3/9;
    int coef_1, coef_2, ordo;
    int coef_3, coef_4, ordo_2;
    int centre_x = LONG/2;
    int blocixe[4] = {506, depart_g, depart_d, 844}, blocigrec[4] = {650, y_debut_dessus, y_debut_dessus, 650};
    if(ranger == 0){
        depart_d = DROITE;
        depart_g = GAUCHE;
    }else if(ranger < 0){
        suite_coter(absolut(ranger), &depart_d, &depart_g, -1, 1, 0);
    }else{
        suite_coter(ranger, &depart_d, &depart_g, 1, 0, 1);
    }

    blocixe[1] = depart_g; blocixe[2] = depart_d;

    point_ver_equa(centre_x, centre_y, depart_g, y_debut_dessus, &coef_1, &coef_2, &ordo);
    point_ver_equa(centre_x, centre_y, depart_d, y_debut_dessus, &coef_3, &coef_4, &ordo_2);

    blocigrec[0] = calcule_x(x_base[0], coef_1, coef_2, ordo);
    blocigrec[1] = calcule_x(x_base[1], coef_1, coef_2, ordo);
    blocigrec[2] = calcule_x(x_base[2], coef_3, coef_4, ordo_2);
    blocigrec[3] = calcule_x(x_base[3], coef_3, coef_4, ordo_2);

    blocixe[0] = x_base[0];
    blocixe[1] = x_base[1];
    blocixe[2] = x_base[2];
    blocixe[3] = x_base[3];

    MLV_draw_filled_polygon(blocixe, blocigrec, 4, MLV_COLOR_GREEN);
    MLV_draw_polygon(blocixe, blocigrec, 4, MLV_COLOR_BLACK);
}


/*dessine les escalier*/
void dessine_escalier(int type, int x_base[], int y_base[], int y_debut_dessus, int ranger, int centre_y, int i, int direction[]){
    int depart_d = LONG*6/9, depart_g = LONG*3/9;
    int coef_1, coef_2, ordo;
    int coef_3, coef_4, ordo_2;
    int centre_x = LONG/2;
    int blocixe[4] = {506, depart_g, depart_d, 844}, blocigrec[4] = {650, y_debut_dessus, y_debut_dessus, 650};
    int xmur[4], ymur[4];

    if(ranger == 0){
        depart_d = DROITE;
        depart_g = GAUCHE;
    }else if(ranger < 0){
        suite_coter(absolut(ranger), &depart_d, &depart_g, -1, 1, 0);
    }else{
        suite_coter(ranger, &depart_d, &depart_g, 1, 0, 1);
    }

    blocixe[1] = depart_g; blocixe[2] = depart_d;

    point_ver_equa(centre_x, centre_y, depart_g, y_debut_dessus, &coef_1, &coef_2, &ordo);
    point_ver_equa(centre_x, centre_y, depart_d, y_debut_dessus, &coef_3, &coef_4, &ordo_2);

    blocigrec[0] = calcule_x(x_base[0], coef_1, coef_2, ordo);
    blocigrec[1] = calcule_x(x_base[1], coef_1, coef_2, ordo);
    blocigrec[2] = calcule_x(x_base[2], coef_3, coef_4, ordo_2);
    blocigrec[3] = calcule_x(x_base[3], coef_3, coef_4, ordo_2);

    blocixe[0] = x_base[0];
    blocixe[1] = x_base[1];
    blocixe[2] = x_base[2];
    blocixe[3] = x_base[3];

    if((type == 4 && direction[1] == -1) || (type == 3 && direction[0] == 1) || (type == 5 && direction[0] == -1) || (type == 6 && direction[1] == 1)){
        /*face*/
        xmur[0] = blocixe[3];
        xmur[1] = x_base[2];
        xmur[2] = x_base[3];

        ymur[0] = blocigrec[3];
        ymur[1] = y_base[2];
        ymur[2] = y_base[3];

        MLV_draw_filled_polygon(xmur, ymur, 3, MLV_COLOR_GREY20);

        xmur[0] = blocixe[0];
        xmur[1] = x_base[1];
        xmur[2] = x_base[0];

        ymur[0] = blocigrec[0];
        ymur[1] = y_base[1];
        ymur[2] = y_base[0];

        MLV_draw_filled_polygon(xmur, ymur, 3, MLV_COLOR_GREY20);

        xmur[0] = blocixe[0];
        xmur[1] = blocixe[3];
        xmur[2] = x_base[2];
        xmur[3] = x_base[1];

        ymur[0] = blocigrec[0];
        ymur[1] = blocigrec[3];
        ymur[2] = y_base[2];
        ymur[3] = y_base[1];

        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_COLOR_GREY);


    }else if((type == 4 && direction[1] == 1) || (type == 3 && direction[0] == -1) || (type == 5 && direction[0] == 1) || (type == 6 && direction[1] == -1)){
        /*dos*/
        xmur[0] = blocixe[2];
        xmur[1] = x_base[3];
        xmur[2] = x_base[2];

        ymur[0] = blocigrec[2];
        ymur[1] = y_base[3];
        ymur[2] = y_base[2];

        MLV_draw_filled_polygon(xmur, ymur, 3, MLV_COLOR_GREY20);

        xmur[0] = blocixe[1];
        xmur[1] = x_base[0];
        xmur[2] = x_base[1];

        ymur[0] = blocigrec[1];
        ymur[1] = y_base[0];
        ymur[2] = y_base[1];

        MLV_draw_filled_polygon(xmur, ymur, 3, MLV_COLOR_GREY20);

        xmur[0] = blocixe[1];
        xmur[1] = blocixe[2];
        xmur[2] = x_base[2];
        xmur[3] = x_base[1];

        ymur[0] = blocigrec[1];
        ymur[1] = blocigrec[2];
        ymur[2] = y_base[2];
        ymur[3] = y_base[1];

        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_COLOR_BLACK);

    }else if((type == 4 && direction[0] == 1) || (type == 3 && direction[1] == 1) || (type == 5 && direction[1] == -1) || (type == 6 && direction[0] == -1)){
        /*profil 1*/
        xmur[0] = blocixe[3];
        xmur[1] = blocixe[2];
        xmur[2] = x_base[2];
        xmur[3] = x_base[3];

        ymur[0] = blocigrec[3];
        ymur[1] = blocigrec[2];
        ymur[2] = y_base[2];
        ymur[3] = y_base[3];

        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_COLOR_BLACK);

        xmur[0] = blocixe[3];
        xmur[1] = blocixe[2];
        xmur[2] = x_base[1];
        xmur[3] = x_base[0];

        ymur[0] = blocigrec[3];
        ymur[1] = blocigrec[2];
        ymur[2] = y_base[1];
        ymur[3] = y_base[0];

        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_COLOR_GREY);

        xmur[0] = blocixe[2];
        xmur[1] = x_base[1];
        xmur[2] = x_base[2];

        ymur[0] = blocigrec[2];
        ymur[1] = y_base[1];
        ymur[2] = y_base[2];

        MLV_draw_filled_polygon(xmur, ymur, 3, MLV_COLOR_GREY20);

    }else if((type == 4 && direction[0] == -1) || (type == 3 && direction[1] == -1) || (type == 5 && direction[1] == 1) || (type == 6 && direction[0] == 1)){
        /*profil 2*/
        xmur[0] = blocixe[0];
        xmur[1] = blocixe[1];
        xmur[2] = x_base[1];
        xmur[3] = x_base[0];

        ymur[0] = blocigrec[0];
        ymur[1] = blocigrec[1];
        ymur[2] = y_base[1];
        ymur[3] = y_base[0];

        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_COLOR_BLACK);

        xmur[0] = blocixe[0];
        xmur[1] = blocixe[1];
        xmur[2] = x_base[2];
        xmur[3] = x_base[3];

        ymur[0] = blocigrec[0];
        ymur[1] = blocigrec[1];
        ymur[2] = y_base[2];
        ymur[3] = y_base[3];

        MLV_draw_filled_polygon(xmur, ymur, 4, MLV_COLOR_GREY);

        xmur[0] = blocixe[1];
        xmur[1] = x_base[2];
        xmur[2] = x_base[1];

        ymur[0] = blocigrec[1];
        ymur[1] = y_base[2];
        ymur[2] = y_base[1];

        MLV_draw_filled_polygon(xmur, ymur, 3, MLV_COLOR_GREY20);
    }
}


/*remplie en triant la liste chaine d'objet avec un objet qui se caracterise par les parametre*/
int rentre_objet(int type_o, int x_base[], int y_base[], int y_debut_dessus, int ranger, int centre_y, int id, Liste *num){
    int i;
    Element *ajout = (Element *)malloc(sizeof(Element)), *parcour = (*num), *preced = (*num);
    /*teste l'allocation*/
    if(ajout == NULL){
        fprintf(stderr, "erreur allocation decort");
        return 0;
    }

    for(i = 0; i < 4; i++){
        ajout->info.base_de_x[i] = x_base[i];
        ajout->info.base_de_y[i] = y_base[i];
    }

    ajout->info.ydess = y_debut_dessus;
    ajout->info.rang = ranger;
    ajout->info.i = id;
    ajout->info.y_du_centre = centre_y;
    ajout->info.type = type_o;

    ajout->distance = distance_point_origine(id, ranger);

    if((*num) == NULL){
        ajout->suivant = NULL;
        (*num) = ajout;
        return 1;
    }
    /*trie la liste chainer par distance*/
    while(parcour != NULL){
        if(parcour->suivant == NULL){
            if(parcour->distance < ajout->distance){
                if(preced == parcour){
                    ajout->suivant = parcour;
                    (*num) = ajout;
                    return 1;
                }
                ajout->suivant = parcour;
                preced->suivant = ajout;
                return 1;
            }
            ajout->suivant = NULL;
            parcour->suivant = ajout;
            return 1;
        }
        if(parcour->distance < ajout->distance){
            if(parcour == (*num)){
                ajout->suivant = parcour;
                (*num) = ajout;
                return 1;
            }
            ajout->suivant = parcour;
            preced->suivant = ajout;
            return 1;
        }
        preced = parcour;
        parcour = parcour -> suivant;
    }
    fprintf(stderr,"lol");
    return 0;
}


/*dessine tout les objet qui sont dans les deux liste en paramettre*/
void dessine_tout_objet(Liste droite, Liste gauche, Couleur couleur_s, int dir[]){
    Element *parc = gauche;
    while(parc != NULL){
        switch(parc->info.type){
            case 2:
                dessine_mur(parc->info.base_de_x, parc->info.base_de_y, parc->info.ydess, parc->info.rang, parc->info.y_du_centre, parc->info.i);
                break;
            case 1:
                dessine_pomme(parc->info.base_de_x, parc->info.base_de_y, parc->info.ydess, parc->info.rang, parc->info.y_du_centre, parc->info.i);
                break;
            case 0:
                dessine_corp_serpent(parc->info.base_de_x, parc->info.base_de_y, parc->info.ydess, parc->info.rang, parc->info.y_du_centre, parc->info.i, couleur_s);
                break;
            default:
                if(parc->info.type < 7 && parc->info.type > 2){
                    dessine_escalier(parc->info.type, parc->info.base_de_x, parc->info.base_de_y,
                        parc->info.ydess, parc->info.rang, parc->info.y_du_centre, parc->info.i, dir);
                    break;
                }
        }
        parc = parc->suivant;
    }
}


/*vide et remmet a null la liste rentrer en paramettre*/
void vide_objet(Liste *lst){
    Element *suprime;
    while((*lst) != NULL){
        suprime = (*lst);
        (*lst) = (*lst)->suivant;
        free(suprime);
    }
}


/*teste si au coordonnée x,y,z de la matrice il y a un objet*/
int test_objet(int x, int y, int z, int *mur, int *pomme, int *serpent, int *vide, Block matrice[][20][20]){
    if(matrice[z][y][x].sol == 0 || matrice[z][y][x].sol == 7){
        *vide = 1;
        return 0;
    }
    if(matrice[z][y][x].sol != 1){
        *mur = matrice[z][y][x].sol;
        return 0;
    }else if(matrice[z][y][x].serpent == 2){
        *pomme = 1;
        return 0;
    }else if(matrice[z][y][x].serpent == 1){
        *serpent = 1;
        return 0;
    }
    return 1;
}


/*desinne le decort qui est devant nous*/
int dessine_coter(int nombre_coter, int nombre_devant, Block matrice[3][20][20], int commence, int direct[2],
    int yctr, int ydebut, int yctr_dessus, int ydebut_dessus, int etage, int toit, Couleur coul_du_serp, int avance){
    Liste tab_gc = NULL;
    int mur, pomme, serpent, vide;
    int i, i3, a1, a2, somme, somme_plus;
    int coef_1, coef_2, ordo;
    int coef_3, coef_4, ordo_2;

    int centre_y = (HAUT + yctr)/2, centre_x = LONG/2;
    int depart_d = LONG*6/9, depart_g = LONG*3/9;
    int blocixe[4] = {506, depart_g, depart_d, 844}, blocigrec[4] = {650, ydebut, ydebut, 650};

    for(i3 = commence+1; i3 < nombre_coter+1; i3++){
        if(i3 == 0){
            depart_d = DROITE;
            depart_g = GAUCHE;
        }else if(i3 < 0){
            suite_coter(absolut(i3), &depart_d, &depart_g, -1, 1, 0);
        }else{
            suite_coter(i3, &depart_d, &depart_g, 1, 0, 1);
        }

        point_ver_equa(centre_x, centre_y, depart_g, ydebut, &coef_1, &coef_2, &ordo);
        point_ver_equa(centre_x, centre_y, depart_d, ydebut, &coef_3, &coef_4, &ordo_2);

        for(i=0; i < nombre_devant; i++){
            vide = 0;
            mur = 0;
            pomme = 0;
            serpent = 0;
            somme_plus = 0;
            somme = suite_devant(i);
            a1 = puissance(4, i);
            a2 = puissance(5, i);
            somme_plus = somme + ((100 * a1) / a2);

            blocixe[3] = calcule_y(ydebut - somme_plus, coef_3, coef_4, ordo_2);
            blocixe[2] = calcule_y(ydebut - somme, coef_3, coef_4, ordo_2);
            blocixe[1] = calcule_y(ydebut - somme, coef_1, coef_2, ordo);
            blocixe[0] = calcule_y(ydebut - somme_plus, coef_1, coef_2, ordo);

            blocigrec[0] = ydebut - somme_plus;
            blocigrec[1] = ydebut - somme;
            blocigrec[2] = ydebut - somme;
            blocigrec[3] = ydebut - somme_plus;

            /*departage en fonction des direction*/
            if(direct[1] == 1 && direct[0] == 0){

                if(toit && matrice[etage + 1][i3 - commence - 1][i+direct[1]].sol < 7 && matrice[etage + 1][i3 - commence - 1][i+direct[1]].sol > 0 && toit){
                    dessine_toit(blocixe, blocigrec, ydebut_dessus , i3, (HAUT + yctr_dessus)/2, i);
                }
                if(test_objet(i+direct[1], i3 - commence - 1, etage, &mur, &pomme, &serpent, &vide, matrice)){
                    MLV_draw_filled_polygon(blocixe, blocigrec, 4, MLV_COLOR_GREEN);
                }
            }else if(direct[1] == -1 && direct[0] == 0){

                if(toit && matrice[etage + 1][-i3 + nombre_coter][i+absolut(direct[1])].sol < 7 && matrice[etage + 1][-i3 + nombre_coter][i+absolut(direct[1])].sol > 0 && toit){
                    dessine_toit(blocixe, blocigrec, ydebut_dessus, i3, (HAUT + yctr_dessus)/2, i);
                }

                if(test_objet(i+absolut(direct[1]), -i3 + nombre_coter, etage, &mur, &pomme, &serpent, &vide, matrice)){
                    MLV_draw_filled_polygon(blocixe, blocigrec, 4, MLV_COLOR_GREEN);
                }
            }else if(direct[1] == 0 && direct[0] == 1){

                if(toit && matrice[etage + 1][i + direct[0]][(-i3) + nombre_coter].sol < 7 && matrice[etage + 1][i + direct[0]][(-i3) + nombre_coter].sol > 0 && toit){
                    dessine_toit(blocixe, blocigrec, ydebut_dessus , i3, (HAUT + yctr_dessus)/2, i);
                }
                if(test_objet((-i3) + nombre_coter, i + direct[0], etage, &mur, &pomme, &serpent, &vide, matrice)){
                    MLV_draw_filled_polygon(blocixe, blocigrec, 4, MLV_COLOR_GREEN);
                }
            }else if(direct[1] == 0 && direct[0] == -1){

                if(toit && matrice[etage + 1][i + absolut(direct[0])][i3 - commence - 1].sol < 7 && matrice[etage + 1][i + absolut(direct[0])][i3 - commence - 1].sol > 0 && toit){
                    dessine_toit(blocixe, blocigrec, ydebut_dessus , i3, (HAUT + yctr_dessus)/2, i);
                }
                if(test_objet(i3 - commence - 1, i + absolut(direct[0]), etage, &mur, &pomme, &serpent, &vide, matrice)){
                    MLV_draw_filled_polygon(blocixe, blocigrec, 4, MLV_COLOR_GREEN);
                }
            }

            if(mur != 0){
                if(rentre_objet(mur, blocixe, blocigrec, ydebut_dessus, i3, (HAUT + yctr_dessus)/2, i, &tab_gc) == 0){
                    return 0;
                }
            }else if(pomme){
                if(rentre_objet(1, blocixe, blocigrec, ydebut_dessus, i3, (HAUT + yctr_dessus)/2, i, &tab_gc) == 0){
                    return 0;
                }
            }else if(serpent){
                if(rentre_objet(0, blocixe, blocigrec, ydebut_dessus, i3, (HAUT + yctr_dessus)/2, i, &tab_gc) == 0){
                    return 0;
                }
            }
            if(vide == 0){
                MLV_draw_polygon(blocixe, blocigrec, 4, MLV_COLOR_BLACK);
            }
        }
        dessine_tout_objet(tab_gc, tab_gc, coul_du_serp, direct);

    }

    vide_objet(&tab_gc);
    return 1;
}


/*affiche le decort*/
/*donne les information sur la map*/
/*donne la couleure du serpent*/
void affiche_devant(Maps map, Couleur couleur_serp, int entier){
    Block partie[3][20][20];
    int longueur = 0, largeur = 0, y_dep;

    decompose(&map, partie);

    MLV_clear_window(MLV_COLOR_WHITE);

    y_dep = HAUT;
    /*si le serpent descend*/
    if(map.direction[0] == 1 && map.direction[1] == 0){

        longueur = map.coter - map.tete->coordonne[2];
        largeur = map.coter - (map.direction[0] * (map.tete->coordonne[1] + 1));

        /*si il y a un etage en dessous*/
        if(map.tete->coordonne[0] > 0){
            dessine_coter(map.tete->coordonne[2], largeur, partie, -longueur, map.direction, -400, y_dep+SOUS, -400, HAUT, map.tete->coordonne[0]-1, 0, couleur_serp, entier);
        }
        /*teste si il y a un etage au dessus*/
        if(map.tete->coordonne[0] < map.hauteur - 1){
            dessine_coter(map.tete->coordonne[2], largeur, partie, -longueur, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 1, couleur_serp, entier);
        }else{
            dessine_coter(map.tete->coordonne[2], largeur, partie, -longueur, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 0, couleur_serp, entier);
        }
    /*si le serpent vas a droite*/
    }else if(map.direction[0] == 0 && map.direction[1] == 1){

        longueur = map.coter - map.tete->coordonne[1];
        largeur = map.coter - (map.direction[1] * (map.tete->coordonne[2] + 1));

        /*si il y a un etage en dessous*/
        if(map.tete->coordonne[0] > 0){
            dessine_coter(longueur - 1, largeur, partie, -map.tete->coordonne[1]-1, map.direction, -400, y_dep+SOUS, -400, y_dep, map.tete->coordonne[0]-1, 0, couleur_serp, entier);
        }
        /*teste si il y a un etage au dessus*/
        if(map.tete->coordonne[0] < map.hauteur - 1){
            dessine_coter(longueur - 1, largeur, partie, -map.tete->coordonne[1]-1, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 1, couleur_serp, entier);
        }else{
            dessine_coter(longueur - 1, largeur, partie, -map.tete->coordonne[1]-1, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 0, couleur_serp, entier);
        }
    /*si le serpent monte*/
    }else if(map.direction[0] == -1 && map.direction[1] == 0){
        /*si il y a un etage en dessous*/
        if(map.tete->coordonne[0] > 0){
            dessine_coter(map.coter-map.tete->coordonne[2]-1, map.tete->coordonne[1], partie, -map.tete->coordonne[2]-1, map.direction, -400, y_dep+SOUS, -400, y_dep, map.tete->coordonne[0]-1, 0, couleur_serp, entier);
        }
        /*teste si il y a un etage au dessus*/
        if(map.tete->coordonne[0] < map.hauteur - 1){
            dessine_coter(map.coter-map.tete->coordonne[2]-1, map.tete->coordonne[1], partie, -map.tete->coordonne[2]-1, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 1, couleur_serp, entier);
        }else{
            dessine_coter(map.coter-map.tete->coordonne[2]-1, map.tete->coordonne[1], partie, -map.tete->coordonne[2]-1, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 0, couleur_serp, entier);
        }
    /*si le serpent vas a gauche*/
    }else if(map.direction[0] == 0 && map.direction[1] == -1){

        longueur = map.coter - map.tete->coordonne[1];
        largeur = map.coter + (map.direction[1] * (map.tete->coordonne[2]));

        /*si il y a un etage en dessous*/
        if(map.tete->coordonne[0] > 0){
            dessine_coter(map.tete->coordonne[1], map.tete->coordonne[2], partie, -longueur, map.direction, -400, y_dep+SOUS, -400, y_dep, map.tete->coordonne[0]-1, 0, couleur_serp, entier);
        }
        /*teste si il y a un etage au dessus*/
        if(map.tete->coordonne[0] < (map.hauteur - 1)){
            dessine_coter(map.tete->coordonne[1], map.tete->coordonne[2], partie, -longueur, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 1, couleur_serp, entier);
        }else{
            dessine_coter(map.tete->coordonne[1], map.tete->coordonne[2], partie, -longueur, map.direction, -400, y_dep, -200, -30, map.tete->coordonne[0], 0, couleur_serp, entier);
        }
    }

    carte(1100, 500, 200/map.coter, map, couleur_serp);
}
