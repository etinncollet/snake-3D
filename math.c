#include <stdio.h>
/*calcule X en fonction du y en parametre sur la droite representer par les coeficient en paramettre*/
/*la droite est defini par y = a1/a2 X + b*/
int calcule_y(float y, int a1, int a2, float b){
    float result, deci;
    int neg;
    result = ((y - b)*(a2))/a1;
    neg = (int) result;
    deci = result - neg;
    /*fait l'arondit*/
    if(deci < 0.5)
        return neg;
    return neg + 1;
}


/*calcule Y en fonction du x en parametre sur la droite representer par les coeficient en paramettre*/
/*la droite est defini par y = a1/a2 X + b*/
int calcule_x(float x, int a1, int a2, float b){
    float result, deci;
    int neg;
    result = (a1 * x)/a2 + b;
    neg = (int) result;
    deci = result - neg;
    /*fait l'arondit*/
    if(deci < 0.5)
        return neg;
    return neg + 1;
}


/*calcule x a la puissance n*/
int puissance(int x, int n){
    int i, att = x;
    if(n == 0){
        return 1;
    }
    for(i = 1; i < n; i++){
        x = x * att;
    }
    return x;
}

/*renvoie en parametre les paramettre de la droite qui passe par les deux point en paramettre*/
/*point un (X1, Y1) */
/*point deux (X2, Y2)*/
/*la droite est defini par y = a_1/a_2 X + b*/
void point_ver_equa(int x1, int y1, int x2, int y2, int *a_1, int *a_2, int *b){
    float res;
    (*a_1) = y1 - y2;
    (*a_2) = x1 - x2;
    /*evite de diviser par 0*/
    if(*a_2 == 0){
        *a_2 = 1;
    }
    res = ((*a_1) * x1)/(*a_2);
    (*b) = y1 - res;
}


/*calcule l'intersection des deux droite des quatre point qui sont en parametre*/
/*donne une liste avec les quatre premier x*/
/*donne une liste avec les quatre premier y*/
/*valeur de x du millieux*/
/*valeur de y du millieux*/
void calcule_milleux_quatre(int listde_x[], int listede_y[], int *x, int *y){
    int coefficient_a_1, coefficient_a_2, coefficient_a_3, coefficient_a_4, ordonne_1, ordonne_2;
    float coef_fin, sustra, res;

    point_ver_equa(listde_x[1], listede_y[1], listde_x[3], listede_y[3], &coefficient_a_1, &coefficient_a_2, &ordonne_1);
    point_ver_equa(listde_x[0], listede_y[0], listde_x[2], listede_y[2], &coefficient_a_3, &coefficient_a_4, &ordonne_2);

    coefficient_a_1 = coefficient_a_1 * coefficient_a_4;
    coefficient_a_3 = coefficient_a_3 * coefficient_a_2;
    coefficient_a_2 = coefficient_a_2 * coefficient_a_4;

    coef_fin = ((float)coefficient_a_1 - (float)coefficient_a_3);
    sustra = ((float)ordonne_2 - (float)ordonne_1);

    res = (sustra * coefficient_a_2)/coef_fin;
    (*y) = calcule_x(res, coefficient_a_1, coefficient_a_2, (float) ordonne_1);
    (*x) = (int) res;
}


/*calcule la suite geometrique U de nbr ou U0 = 100 et q = 4/5 et aditionne les nbr premier terme*/
int suite_devant(int nbr){
    int somme = 0, i2, a1, a2;
    for(i2 = 0; i2 < nbr; i2++){
        a1 = puissance(4, i2);
        a2 = puissance(5, i2);
        somme += ((100 * a1) / a2);
    }
    return somme;
}


/*renvoi la distence entre le point en paramettre et l'origine*/
int distance_point_origine(int x, int y){return (x * x) + (y * y);}


/*donne la valeur absolurt d'un nombre*/
int absolut(int x){if(x<0){return -x;}return x;}
