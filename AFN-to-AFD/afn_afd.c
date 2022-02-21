#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct AFN_Entree {
    int final;
    char symb1[4];
    char symb2[4];
}
//representation de fichier d'enttrée (les etats et transitions)
AFN_Entree;
AFN_Entree Automate_N[128];

char Etat_Actuel[4] = {'0'};

int this_etat(int etransition, char Etat_AFD[]);//retourne l'etat qui suive

int
main() {
    FILE * fich;
    fich = fopen("./fichentree.txt", "r"); //automate non deterministe
    FILE * fich_sortie;
    fich_sortie = fopen("./fichsortie.txt", "w+"); //sortie : automate deterministe
    char Automate_D[50][4][4]; //pour enregistrer les valeurs de l'automate deterministe
    int pnt = 1, pntf = 0;//pnt : pointe vers l'etat qui suive et pntf: ponte vers l'etat final
    for (int i = 0; i < 5; i++) {
        Etat_Actuel[i] = '0';
    }
    int pos = 0;
    strcpy(Automate_D[0][0], "10000");   //initialisation
    while (fscanf(fich, "%s %s %d", Automate_N[pos].symb1, Automate_N[pos].symb2, &
            Automate_N[pos].final) != EOF && pos != 128) {
        pos++; // importation de l'automate non deterministe
    } 

    
    
    for (int j = 0; j < 49 && !pntf; j++) {
        for (int k = 1; k <= 2; k++) {
            for (int l = 0; l < 5; l++) {
                Etat_Actuel[l] = '0';
            }
            pntf = this_etat(k, Automate_D[j][0]);
            pnt = 1;
            for (int m = 0; m <= j; m++) {
                if (!strcmp(Automate_D[m][0], Etat_Actuel)) {
                    snprintf(Automate_D[j][k], 5, "%d", m);
                    pnt = 0;
                }
            }
            if (pnt) {
                strcpy(Automate_D[j + 1][0], Etat_Actuel);
                snprintf(Automate_D[j][k], 5, "%d", j + 1);
            }
        }
        fprintf(fich_sortie, "%d : %s    %s      %s\n", j, Automate_D[j][0],
            Automate_D[j][1], Automate_D[j][2]);
    }
    fclose(fich);
    fclose(fich_sortie);
}



int this_etat(int etransition, char Etat_AFD[]) {
    int fin;
    if (etransition == 1) {
        for (int i = 0; i < 5; i++) {
            if (Etat_AFD[i] == '1') {
                fin = Automate_N[i].final;
                for (int j = 0; j < 5; j++) {
                    if (Automate_N[i].symb1[j] == '1') {
                        Etat_Actuel[j] = '1';
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < 5; i++) {
            if (Etat_AFD[i] == '1') {
                fin = Automate_N[i].final;
                for (int j = 0; j < 5; j++) {
                    if (Automate_N[i].symb2[j] == '1') {
                        Etat_Actuel[j] = '1';
                    }
                }
            }
        }
    }
    return fin;
}
