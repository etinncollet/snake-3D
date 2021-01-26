#include "map.h"
#include <stdio.h>
#include <stdlib.h>

/*telechare la maps et initialise le serpent*/
/*map est l'addresse de l'objet a remplir*/
/*nom donne le nom du fichier a ouvrir*/
int initialise_map(Maps *map, char nom[]){
    int un;
    Serpent *prem;
    /*dimention*/
    map->coter = 10;
    map->hauteur = 2;

    /*decort*/
    litmap(nom, map);

    /*tete serpent*/
    prem = malloc(sizeof(Serpent));
    if(prem == NULL){
        fprintf(stderr, "erreure alocation");
        return 0;
    }
    map->tete = prem;
    map->tete->preced = NULL;
    map->nombre = 1;

    for(un = 0; un < 3; un++){
        map->tete->coordonne[un] = 1;
    }

    map->tete->coordonne[0] = 0;

    map->matrice[0][1][1].serpent = 1;
    map->direction[0] = 1;
    map->direction[1] = 0;

    /*premiere pomme*/
    popomme(map);
    return 1;
}


/*verifie que l'escalier est bien prit dans le bon sens*/
/*nbr donne l'escalier a verifier*/
/*donne la direction*/
/*renvoi 0 si c'est mauvaut et -1 si c'est bon*/
int verif_escalier(int nbr, int direction[2]){
    int direun[4] = {1, 0, -1, 0}, diredeux[4] = {0, -1, 0, 1};
    if(nbr == 1){
        /*c'est du sol*/
        return -1;
    }
    if(direun[nbr - 3] == direction[0] && diredeux[nbr - 3] == direction[1]){
        /*la direction est mauvause*/
        return 0;
    }
    if(direun[nbr - 3] == -direction[0] && diredeux[nbr - 3] == -direction[1]){
        /*l'escalier est dans le bon sens*/
        return -1;
    }
    return 1;
}


/*fait affancer recurcivement tout le corp du  serpent*/
/*map structure de tout*/
/*actuel donne l'adresse l'element du serpent*/
/*preced donne l'adresse de l'element precedent*/
int avance_corp(Maps *map, Serpent *actuel, Serpent *preced){
    /*parcour la liste chainer jusqu'a la fin*/
    if(actuel->preced != NULL){
        avance_corp(map, actuel->preced, actuel);
    }else{

        map->matrice[actuel->coordonne[0]][actuel->coordonne[1]][actuel->coordonne[2]].serpent = 0;
    }
    /*donne les coordonnée d'apres a l'element*/
    actuel->coordonne[0] = preced->coordonne[0];
    actuel->coordonne[1] = preced->coordonne[1];
    actuel->coordonne[2] = preced->coordonne[2];
    return 1;
}


/*permet de se deplacer dans la maps*/
/*map structure de tout*/
/*donne l'information si le serpent est descendu*/
int avance(Maps *map, int *descendu){
    int ajpomme = 0;
    Serpent *corp = map->tete , prem = {{corp->coordonne[0], corp->coordonne[1], corp->coordonne[2]}, map->tete->preced};
    /*si il n'y a qu'un element dans le serpent*/
    if(corp->preced == NULL){
        map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent = 0;
        /*si ont peut descendre*/
        if(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol == 7){
            if(verif_escalier(map->matrice[corp->coordonne[0] - 1][corp->coordonne[1]][corp->coordonne[2]].sol, map->direction) == -1){
                corp->coordonne[0] = corp->coordonne[0] - 1;
                *descendu = 1;
                map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent = 1;
                return 1;
            }
        /*si il y a un escalier*/
        }else if(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol > 2
            && map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol < 7){
            if((*descendu) == 0){
                if(verif_escalier(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol, map->direction)){
                    fprintf(stderr, "erreur1");
                    return 0;
                }
                corp->coordonne[0] = corp->coordonne[0] + 1;

                map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent = 1;
                *descendu = 0;
                return 1;
            }
            *descendu = 0;
        }
        /*si il y a un obstacle ou si ont sort de la maps*/
        if(corp->coordonne[1] + map->direction[0] <= -1 || corp->coordonne[1] + map->direction[0] >= map->coter ||
            corp->coordonne[2] + map->direction[1] <= -1 || corp->coordonne[2] + map->direction[1] >= map->coter ||
            map->matrice[corp->coordonne[0]][corp->coordonne[1] + map->direction[0]][corp->coordonne[2] + map->direction[1]].sol == 2 ||
            map->matrice[corp->coordonne[0]][corp->coordonne[1] + map->direction[0]][corp->coordonne[2] + map->direction[1]].sol == 0){
            fprintf(stderr, "erreur2");
            return 0;
        }

        corp->coordonne[1] = corp->coordonne[1] + map->direction[0];
        corp->coordonne[2] = corp->coordonne[2] + map->direction[1];

        /*teste les pomme*/
        if(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent == 2){
            if(ajoute(map) == 0){fprintf(stderr, "erreur10");return 0;}
            ajpomme = 1;
        }
        map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent = 1;
        if(ajpomme){
            popomme(map);
        }
        return 1;
    }
    /*si il y a plusieur element*/
    if(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol == 7){
        /*si il faut descendre ^^*/
        if(verif_escalier(map->matrice[corp->coordonne[0] - 1][corp->coordonne[1]][corp->coordonne[2]].sol, map->direction) == -1){

            corp->coordonne[0] = corp->coordonne[0] - 1;

            map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent = 1;
            avance_corp(map, corp->preced, &prem);
            *descendu = 1;
            return 1;
        }
    /*si il faut monter avec un escalier*/
    }else if(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol > 2
        && map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol < 7){
        if((*descendu) == 0){
            if(verif_escalier(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].sol, map->direction)){
                fprintf(stderr, "erreur3");
                return 0;
            }
            corp->coordonne[0] = corp->coordonne[0] + 1;

            map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent = 1;
            avance_corp(map, corp->preced, &prem);
            *descendu = 0;
            return 1;
        }

    }
    *descendu = 0;
    /*teste si il y a un obstacle ou si l'on sort de maps*/
    if(corp->coordonne[1] + map->direction[0] <= -1 || corp->coordonne[1] + map->direction[0] >= map->coter ||
        corp->coordonne[2] + map->direction[1] <= -1 || corp->coordonne[2] + map->direction[1] >= map->coter ||
        map->matrice[corp->coordonne[0]][corp->coordonne[1] + map->direction[0]][corp->coordonne[2] + map->direction[1]].serpent == 1 ||
        map->matrice[corp->coordonne[0]][corp->coordonne[1] + map->direction[0]][corp->coordonne[2] + map->direction[1]].sol == 2 ||
        map->matrice[corp->coordonne[0]][corp->coordonne[1] + map->direction[0]][corp->coordonne[2] + map->direction[1]].sol == 0){
        fprintf(stderr, "erreur4");
        return 0;
    }

    corp->coordonne[1] = corp->coordonne[1] + map->direction[0];
    corp->coordonne[2] = corp->coordonne[2] + map->direction[1];

    /*teste les pomme*/
    if(map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent == 2){
        if(ajoute(map) == 0){fprintf(stderr, "erreur5");return 0;}
        ajpomme = 1;
    }
    map->matrice[corp->coordonne[0]][corp->coordonne[1]][corp->coordonne[2]].serpent = 1;

    avance_corp(map, corp->preced, &prem);
    if(ajpomme){
        popomme(map);
    }
    return 1;
}


/*ajoute un bout du serpent*/
/*maps structure avec toute les information*/
/*renvoi 0 en cas d'erreur d'alocation sinon 1*/
int ajoute(Maps *map){
    Serpent *corp = map->tete, *queu = map->tete, *ajout;
    int xcoef, ycoef;
    ajout = malloc(sizeof(Serpent));
    /*teste l'allocation*/
    if(ajout == NULL){
        return 0;
    }
    /*si il n'y a qu'un element*/
    if(queu->preced == NULL){
        ajout->preced = NULL;
        queu->preced = ajout;
        ajout->coordonne[0] = queu->coordonne[0];
        ajout->coordonne[1] = queu->coordonne[1] - map->direction[0];
        ajout->coordonne[2] = queu->coordonne[2] - map->direction[1];
        map->nombre += 1;
        return 1;
    }
    /*sinon ont parcour le serpent pour allez a la fin*/
    while(queu->preced !=NULL){
        corp = queu;
        queu = queu->preced;
    }

    xcoef = corp->coordonne[1] - queu->coordonne[1];
    ycoef = corp->coordonne[2] - queu->coordonne[2];
    /*si l'ajout ne pause pas de probleme*/
    if((queu->coordonne[1] - xcoef) >= 0 && (map->coter) > (queu->coordonne[1] - xcoef)
        && (queu->coordonne[2] - ycoef) >= 0 && (map->coter) > (queu->coordonne[2] - ycoef)){

        ajout->coordonne[0] = queu->coordonne[0];
        ajout->coordonne[1] = queu->coordonne[1] - xcoef;
        ajout->coordonne[2] = queu->coordonne[2] - ycoef;

        ajout->preced = NULL;
        queu->preced = ajout;

        map->nombre += 1;
    }
    return 1;
}


/*cree une pomme et la place dans la maps*/
/*map structure tout info*/
void popomme(Maps *map){
    do{
        map->pomme[2] = rand()%(map->coter);
        map->pomme[1] = rand()%(map->coter);
        map->pomme[0] = rand()%(map->hauteur);
    }while(map->matrice[map->pomme[0]][map->pomme[1]][map->pomme[2]].serpent == 1 ||
        map->matrice[map->pomme[0]][map->pomme[1]][map->pomme[2]].sol != 1);
    /*teste que la pomme ne gene rien ^^*/
    map->matrice[map->pomme[0]][map->pomme[1]][map->pomme[2]].serpent = 2;
}


/*affiche la liste chaine qui caracterise le serpent dans le terminal*/
/*map structure tout info*/
void afficheserpent(Maps *map){
    Serpent *regarde = map->tete;
    if(regarde == NULL){
        fprintf(stderr, "liste vide");
    }
    while(regarde != NULL){
        fprintf(stderr, "%d, %d, %d / ", regarde->coordonne[0], regarde->coordonne[1], regarde->coordonne[2]);
        regarde = regarde->preced;
    }
    fprintf(stderr, "\n");
}


/*libere la memoir occuper par la liste chainnee du serpent*/
/*map structure tout info*/
void libereserpent(Maps *map){
    Serpent *suiv = map->tete;
    while(map->tete != NULL){
        suiv = map->tete->preced;
        free(map->tete);
        map->tete = suiv;
    }
}


/*lit le fichier qui donne la map et le retourne dans la matrice en paramettre*/
/*la chaine de caractere qui donne le lien*/
/*map structure tout info*/
void litmap(char *lien, Maps *map){
    int hauteur = 0, longueur = 0, et, un, de;
    char lettre;
    FILE *carte = fopen(lien, "r");
    lettre = fgetc(carte);
    longueur += (lettre - '0')*10;
    lettre = fgetc(carte);
    longueur += lettre - '0';
    lettre = fgetc(carte);
    lettre = fgetc(carte);
    hauteur += lettre - '0';
    lettre = fgetc(carte);
    map->hauteur = hauteur;
    map->coter = longueur;

    for(et = 0; et < hauteur; et++){
        for(un = 0; un < longueur; un++){
            for(de = 0; de < longueur; de++){
                lettre = fgetc(carte);
                map->matrice[et][un][de].sol = lettre - '0';
                map->matrice[et][un][de].serpent = 0;
            }
            lettre = fgetc(carte);
        }
        lettre = fgetc(carte);
        lettre = fgetc(carte);
    }
}


/*decompose la matrice quand le serpent monte*/
/*map structure tout info*/
/*regade est la matrice qui vas etre renvoyer*/
/*donne les coordonnée de depart*/
void decompose_monte(Maps *map, Block regard[3][20][20], int departx, int departy){
    int et, y, x, plus_x = 1, plus_y = -1, finx = map->coter, finy = 0;

    for(et = 0; et < map->hauteur; et++){
        for(y = -departy; y >= finy; y += plus_y){
            for(x = -departx; x < finx; x += plus_x){
                regard[et][y][x].sol = map->matrice[et][-departy - y][departx + x].sol;
                regard[et][y][x].serpent = map->matrice[et][-departy - y][departx + x].serpent;
            }
        }
    }
}


/*decompose la matrice quand le serpent vas a gauche*/
/*map structure tout info*/
/*regade est la matrice qui vas etre renvoyer*/
/*donne les coordonnée de depart*/
void decompose_gauche(Maps *map, Block regard[3][20][20], int departx, int departy){
    int et, y, x, plus_x = -1, plus_y = 1, finy = map->coter, finx = 0;

    for(et = 0; et < map->hauteur; et++){
        for(y = -departy; y < finy; y += plus_y){
            for(x = -departx; x >= finx; x += plus_x){
                regard[et][y][x].sol = map->matrice[et][departy + y][-departx - x].sol;
                regard[et][y][x].serpent = map->matrice[et][departy + y][-departx - x].serpent;
            }
        }
    }
}


/*decompose la matrice seont la direction*/
/*map structure tout info*/
/*regade est la matrice qui vas etre renvoyer*/
void decompose(Maps *map, Block regard[3][20][20]){
    int departx = map->tete->coordonne[2] * map->direction[1], departy = map->tete->coordonne[1] * map->direction[0];
    int et, y, x;
    if(departx >= 0 && departy >= 0 && map->direction[1] >= 0 && map->direction[0] >= 0){

        for(et = 0; et < map->hauteur; et++){
            for(y = 0; y < (map->coter - departy); y++){
                for(x = 0; x < (map->coter - departx); x++){

                    regard[et][y][x].sol = map->matrice[et][departy + y][departx + x].sol;
                    regard[et][y][x].serpent = map->matrice[et][departy + y][departx + x].serpent;

                }
            }
        }
    }else{
        if(departx == 0 && map->direction[0] < 0){
            decompose_monte(map, regard, departx, departy);
        }else{
            decompose_gauche(map, regard, departx, departy);
        }
    }
}
