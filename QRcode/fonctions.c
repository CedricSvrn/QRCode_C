#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Détermine le nombre de bits du décimal
int taille_tableau_du_decimal(int a) // Création de la fonction qui va donner la taille en binaire du décimal
{
    int n=0;
    int b;
    b = pow(2, n);
    while(a>b) // Détermine la 1ère valeur 2^n dépassant la variable
    {
        n++;
        b = pow(2, n);
    }
    return n;
}

// Convertit un tableau de bits en une décimal
int convertisseur_binaire_decimal (int tableau[15], int k)
{
    int n, i, S=0;
    for (i=0; i<k; i++) // fais la somme des 2^n du tableau de bits de 0 à k
    {
        n = tableau[i];
        S = S + (n*(pow(2,i)));
    }
    return S;
}

// Fonction qui prend en arguments le niveau de correction et le masque
void encodage_bits_de_format (int correction, int masque, int tableau[15])
{
    // Déclaration des variables

    int BitsDeFormat[5];
    int a_1; // Mot binaire entrée
    int a; // Mot binaire modifiée<br/>
    int b; // Polynome générateur
    int c; // Polynome générateur modifiée (étape 3 et 4)
    int t_a = 14; // Taille de a: ici, 14 pour le début du "do...while" pour le cas où le niveau de correction est M (soit où t_a<t_poly)
    int taille_polynome = 11; // De même que pour t_a
    int i;
    int Masque[15] = {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1}; // Qui est définie par le dossier (pour le OU final)
    int tab[15];
    int polynomeGenerateur[11] = {1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1}; // Qui est définie par le dossier


    // Début de la fonction

    switch (correction)
    {
    case 1:
        tab[3] = 1;
        tab[4] = 0;
        break;
    case 2:
        tab[3] = 0;
        tab[4] = 0;
        break;
    case 3:
        tab[3] = 1;
        tab[4] = 1;
        break;
    case 4:
        tab[3] = 1;
        tab[4] = 0;
        break;
    }

    switch (masque)
    {
    case 0:
        tab[0] = 0;
        tab[1] = 0;
        tab[2] = 0;
        break;
    case 1:
        tab[0] = 1;
        tab[1] = 0;
        tab[2] = 0;
        break;
    case 2:
        tab[0] = 0;
        tab[1] = 1;
        tab[2] = 0;
        break;
    case 3:
        tab[0] = 1;
        tab[1] = 1;
        tab[2] = 0;
        break;
    case 4:
        tab[0] = 0;
        tab[1] = 0;
        tab[2] = 1;
        break;
    case 5:
        tab[0] = 1;
        tab[1] = 0;
        tab[2] = 1;
        break;
    case 6:
        tab[0] = 0;
        tab[1] = 1;
        tab[2] = 1;
        break;
    case 7:
        tab[0] = 1;
        tab[1] = 1;
        tab[2] = 1;
        break;
    }


/******Etape 1 et 2: Modification du mot binaire(début)*****/
    a_1 = convertisseur_binaire_decimal(tab, 5); // Passe du binaire en décimal
    a = a_1<<10; // Etape 1 et 2: on ajoute 10 zéros à droite et on enlève les zéros à gauche(cela se faire automatiquement
    convertisseur_entier_binaire2 (a, tab);

    b = convertisseur_binaire_decimal(polynomeGenerateur, 11);

/*******Etape 3 à 5**********/
    do{
    c = b<<(t_a-taille_polynome); // Polynome générateur modifiée (étape 3 et 4)
    a = a^c; //Etape 4
    t_a = taille_tableau_du_decimal(a);
    }while(t_a>10);

    if(t_a<10)
    {
        a = a<<(10-t_a);
    }
    convertisseur_entier_binaire2 (a, tableau);

/***********OU final***********/

    c = convertisseur_binaire_decimal(Masque, 15); // c contient maintenant le masque (définie)
    a = a + (a_1<<10); // On ajoute aux 10 bits obtenues les 5 bits de format du départ
    convertisseur_entier_binaire2 (a, tableau);
    b = a^c; // b contient maintenant le résultat en décimal des bits de format

    convertisseur_entier_binaire2 (b, tableau);

    return 0;
}


// Place les Parties fixes dans le tableau
void affichageCarreTableau (int taille,int tableau[21][21], int departLigne, int departColone, int carre)    // AFFICHAGE D'UN CARE FIXE
{
  int ligne,colone;    // creation des compteurs

// INITIALISATION PARTIE FIXE **********
    for(ligne = departLigne  ; ligne < departLigne + 7 ; ligne++)    // Initialisation du carré en blanc
    {
        for(colone = departColone  ; colone < departColone + 7 ; colone++)
        {
            tableau[colone][ligne]=0;
        }
    }


    // --------------------- COLONE GAUCHE --------------------
    for(ligne=departLigne ; ligne<departLigne+7; ligne++)   // ON CODE LA COLONE DE GAUCHE AVEC DES 1
    {
        for(colone=departColone ; colone<departColone + 1 ; colone++)
        {
            tableau[colone][ligne]=1;
        }
    }

    // --------------------- COLONE DROITE--------------------
    for(ligne=departLigne ; ligne<departLigne+7; ligne++)   // ON CODE LA COLONE DE DROIE AVEC DES 1
    {
     for(colone=departColone+6 ; colone<departColone+7 ; colone++)
        {
            tableau[colone][ligne]=1;
        }

    }


    // --------------------- LIGNE HAUT --------------------
    for(ligne=departLigne ; ligne< departLigne+1 ; ligne++) // ON CODE LA LIGNE DU HAUT AVEC DES 1
    {
        for(colone=departColone ; colone<departColone+7 ; colone++)
        {
            tableau[colone][ligne]=1;
        }
    }

    // --------------------- LIGNE BAS --------------------
    for(ligne = departLigne + 6  ; ligne < departLigne+7 ; ligne++) // ON CODE LA LIGNE DU AS AVEC DES 1
    {
        for(colone=departColone ; colone<departColone+7 ; colone++)
        {
            tableau[colone][ligne]=1;

        }
    }

    // ------------------------ PETIT CARRE ----------------------
    for(ligne=departLigne + 2; ligne<departLigne + 5 ; ligne++) // CODAGE DU PEI CARE INTERIEUR AVEC DES 1
    {
        for(colone=departColone + 2 ; colone<departColone + 5 ; colone++)
        {
            tableau[colone][ligne]=1;
        }
    }

    if (carre == 1) // SI CARRE=1 ON CODE LES PARTIES FIXES DE LA LIGNE 6 ET DE LA COLONE 6
        {
            // -------- PARTIES FIXE DE LA LIGNE 6 --------------
                for(ligne=6 ; ligne<7 ; ligne++)    // PREMIER PETIT CARRE
                    {
                        for(colone=8 ; colone<9 ; colone++)
                        {
                           tableau[colone][ligne]=1;
                        }
                    }

                for(ligne=6 ; ligne<7 ; ligne++)    // DEUXIEME PETIT CARRE
                    {
                        for(colone=10 ; colone<11 ; colone++)
                        {
                           tableau[colone][ligne]=1;
                        }
                    }

                for(ligne=6 ; ligne<7 ; ligne++) // TROISIEME PETIT CARRE
                    {
                        for(colone=12 ; colone<13 ; colone++)
                        {
                           tableau[colone][ligne]=1;
                        }
                    }

                // -------- PARTIES FIXE DE LA COLONE 6 --------------
                for(ligne=8 ; ligne<9 ; ligne++)    // PREMIER PETIT CARRE
                    {
                        for(colone=6 ; colone<7 ; colone++)
                        {
                           tableau[colone][ligne]=1;
                        }
                    }

                for(ligne=10 ; ligne<11 ; ligne++)  // DEUXIEME PETIT CARRE
                    {
                        for(colone=6 ; colone<7 ; colone++)
                        {
                           tableau[colone][ligne]=1;
                        }
                    }

                for(ligne=12 ; ligne<13 ; ligne++)  // TROISIEME PETIT CARRE
                    {
                        for(colone=6 ; colone<7 ; colone++)
                        {
                           tableau[colone][ligne]=1;
                        }
                    }


            // -------- LE PIXEL PERDU  --------------
                for(ligne=13 ; ligne<14 ; ligne++)  // CODAGE DU PIXEL QUI EST TOUT SEUL
                    {
                        for(colone=8 ; colone<9 ; colone++)
                        {
                           tableau[colone][ligne]=1;
                        }
                    }

        }

}

/********************** Définit la lecture des octets du QRcode***********************/
void octetMontant (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8])
{
    int ligne,colone;
    int i=0, j;

    for(ligne = departLigne ; ligne > departLigne-4 ; ligne--)
    {
        for (colone = departColone ; colone > departColone-2 ; colone--)
        {
            tableau[colone][ligne] = tableauOctet[i];
            i++;
        }
    }

    return 0;
}

void octetDescendant (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8])
{
    int ligne,colone;
    int i=0;

    for(ligne = departLigne ; ligne < departLigne+4 ; ligne++)
    {
        for (colone = departColone ; colone > departColone-2 ; colone--)
        {
            tableau[colone][ligne] = tableauOctet[i];
            i++;
        }
    }

    return 0;
}

void octetHaut (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8])
{
    tableau[departColone][departLigne] = tableauOctet[0];
    tableau[departColone-1][departLigne] = tableauOctet[1];
    tableau[departColone][departLigne-1] = tableauOctet[2];
    tableau[departColone-1][departLigne-1] = tableauOctet[3];
    tableau[departColone-2][departLigne-1] = tableauOctet[4];
    tableau[departColone-3][departLigne-1] = tableauOctet[5];
    tableau[departColone-2][departLigne] = tableauOctet[6];
    tableau[departColone-3][departLigne] = tableauOctet[7];

    return 0;
}

void octetBas (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8])
{
    tableau[departColone][departLigne] = tableauOctet[0];
    tableau[departColone-1][departLigne] = tableauOctet[1];
    tableau[departColone][departLigne+1] = tableauOctet[2];
    tableau[departColone-1][departLigne+1] = tableauOctet[3];
    tableau[departColone-2][departLigne+1] = tableauOctet[4];
    tableau[departColone-3][departLigne+1] = tableauOctet[5];
    tableau[departColone-2][departLigne] = tableauOctet[6];
    tableau[departColone-3][departLigne] = tableauOctet[7];

    return 0;
}
/*************************************************************************************/

// Affiche le tableau final dans la console
void affichageCarreDansFichier (int taille,int multiplicateur,FILE *image,int tableau[21][21], int tableauFinal[taille][taille])
{
    // ******************************* FONCTION AFFICHAGE DE SORTIE DU CARRE **************************
    // ** TRANSFORME LE TABLEAU 21*21 AVEC LE TABLEAU DEMANDE
    int ligne,colone;
    int i,j;

    printf("\n");
    printf("\n");
    printf("\n");
    printf("TABLEAU TRAVAIL :\n\n");

    for(ligne=0 ; ligne<21 ; ligne++)   // AFFICHAGE DU TABLEAU TRAVAIL
    {
        for(colone=0 ; colone<21 ; colone++)
        {
            printf("%d",tableau[colone][ligne]);
        }
        printf("\n");
    }

    for(ligne=0 ; ligne<taille ; ligne++)   // Initialisation du tableau Final
    {
        for(colone=0 ; colone<taille ; colone++)
        {
            tableauFinal[colone][ligne]=0;
        }
    }

    for(ligne=0 ; ligne<21 ; ligne++)   // boucles ligne du trableau de travail
    {
        for(colone=0 ; colone<21 ; colone++)// boucles colone du trableau de travail
            {
                for(i = ligne*multiplicateur; i<(ligne*multiplicateur)+multiplicateur ; i++)   // boucles transfert du tableau dans le tableau final
                {
                    for(j = colone*multiplicateur ; j<(colone*multiplicateur)+multiplicateur ; j++)
                    {
                        tableauFinal[j][i] = tableau[colone][ligne] ;   // Transfert des données
                    }
                }
            }
    }
    printf("\n\n\n");


    printf("TABLEAU FINAL :\n\n");

    for(ligne=0 ; ligne<taille ; ligne++)   // boucles transfert du tableau dans le fichier
    {
        for(colone=0 ; colone<taille ; colone++)
        {
            printf("%d",tableauFinal[colone][ligne]);
        }
        printf("\n");
    }

    fprintf(image,"P1\n");  // Ecritures des éléments de base du fichier pbm
    fprintf(image,"%d %d\n",taille,taille);

    for(ligne=0 ; ligne<taille ; ligne++)   // boucles transfert du tableau dans le fichier
    {
        for(colone=0 ; colone<taille ; colone++)
        {
            fprintf(image,"%d",tableauFinal[colone][ligne]);
        }
        fprintf(image,"\n");
    }

    return 0;
}

// Place le mode
void affichageMode(int tableau[21][21])
{
    int ligne,colone;

// ASCII DONC 0100 ***************************
    for (ligne = 19; ligne < 21 ; ligne++)  // GRAND CARRE BLANC
    {
        for (colone = 19 ; colone < 21 ; colone++)
        {
            tableau[colone][ligne] = 0;
        }
    }

    tableau[19][20] = 1;

    return 0;
}

// Place la longueur du message
void affichageLongeurMessage(int tableau[21][21],int nombreDeCaracteres,int tableauOctet[8])
{
    int departColone, departLigne;
    int tabl[4];
    convertisseur_entier_binaire(nombreDeCaracteres, tableauOctet);

    tabl[0] = tableauOctet[0];
    tabl[1] = tableauOctet[1];
    tabl[2] = tableauOctet[2];
    tabl[3] = tableauOctet[3];

    tableauOctet[0] = tableauOctet[7];
    tableauOctet[1] = tableauOctet[6];
    tableauOctet[2] = tableauOctet[5];
    tableauOctet[3] = tableauOctet[4];
    tableauOctet[4] = tabl[3];
    tableauOctet[5] = tabl[2];
    tableauOctet[6] = tabl[1];
    tableauOctet[7] = tabl[0];

    departColone = 20;
    departLigne = 18;
    octetMontant (tableau, departLigne, departColone, tableauOctet) ;

    return 0;
}

void convertisseur_caracteres_binaire (char caractere, int tableauOctet[8])
{
    int k;
    int i=7, j, reste;        //Les compteurs et le reste qui définira le tableau

    while(caractere!=0)              //Donne l'écriture en base 2 du caractere (qui est déjà en base 10)
    {
        reste = caractere%2;           //Détermine le reste de la décimal du caratere par 2
        caractere = (caractere-reste) / 2;         //Donne au caractere la valeur du caracterep par 2
        tableauOctet[i] = reste;            //On range le reste dans le tableau
        i--;
    }
    while(i>=0)                 //Complète le tableau de 0
    {
        tableauOctet[i] = 0;
        i--;
    }

    return 0;
}

void convertisseur_entier_binaire (int caractere, int tableauOctet[8])
{
    int k;
    int i=0, j, reste; //Les compteurs et le reste qui définira le tableau

    while(caractere!=0) //Donne l'écriture en base 2 du caractere (qui est déjà en base 10)
    {
        reste = caractere%2; //Détermine le reste de la décimal du caratere par 2
        caractere = (caractere-reste) / 2; //Donne au caractere la valeur du caracterep par 2
        tableauOctet[i] = reste; //On range le reste dans le tableau
        i++;
    }
    while(i<=7) //Complète le tableau de 0
    {
        tableauOctet[i] = 0;
        i++;
    }

    return 0;
}

void convertisseur_entier_binaire2 (int caractere, int tableau[15])
{
    int k;
    int i=0, j, reste; //Les compteurs et le reste qui définira le tableau

    while(caractere!=0) //Donne l'écriture en base 2 du caractere (qui est déjà en base 10)
    {
        reste = caractere%2; //Détermine le reste de la décimal du caratere par 2
        caractere = (caractere-reste) / 2; //Donne au caractere la valeur du caracterep par 2
        tableau[i] = reste; //On range le reste dans le tableau
        i++;
    }
    while(i<=14) //Complète le tableau de 0
    {
        tableau[i] = 0;
        i++;
    }

    return 0;
}

// Place les bits de formats le long des carrés fixes
void affichageBitsDeFormat (int tableau[21][21], int Formats[15])
{
    int colonne, ligne;
    int i;

    /********Carré Haut Gauche********/
    i=0;
    for(colonne=0; colonne<8; colonne++)
    {
        if(colonne==6)
        {
            colonne++;
        }
        tableau[colonne][8] = Formats[i];
        i++;
    }
    for (ligne=8; ligne>=0; ligne--)
    {
        if(ligne==6)
        {
            ligne--;
        }
        tableau[colonne][ligne] = Formats[i];
        i++;
    }

    /********Carré Bas Gauche*********/
    i=0;
    for(ligne=20; ligne>=14; ligne--)
    {
        tableau[8][ligne] = Formats[i];
        i++;
    }

    /*******Carré Haut Droit********/
    for(colonne=13; colonne<=20; colonne++)
    {
        tableau[colonne][8] = Formats[i];
        i++;
    }

    return 0;
}

// Place le texte
void affichageTexteTableau (int tableau[21][21], char chaineCaracteres[20], int tableauOctet[8],int nombreDeCaracteres)
{
    int tableauCorrection[8] = {1, 0, 1, 0, 1, 0, 1, 0};
    int departLigne,j,departColone,k;
    int i=0;

for( k=0 ; k<=nombreDeCaracteres ; k++ )
{
  switch (k)
  {
        case 1:
            departLigne = 14;
            departColone = 20;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetMontant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 2:
            departLigne = 10;
            departColone = 20;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetHaut(tableau,departLigne,departColone,tableauOctet);
            break;

        case 3:
            departLigne = 11;
            departColone = 18;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetDescendant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 4:
            departLigne = 15;
            departColone = 18;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetDescendant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 5:
            departLigne = 19;
            departColone = 18;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetBas(tableau,departLigne,departColone,tableauOctet);
            break;

        case 6:
            departLigne = 18;
            departColone = 16;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetMontant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 7:
            departLigne = 14;
            departColone = 16;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetMontant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 8:
            departLigne = 10;
            departColone = 16;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetHaut(tableau,departLigne,departColone,tableauOctet);
            break;

        case 9:
            departLigne = 11;
            departColone = 14;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetDescendant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 10:
            departLigne = 15;
            departColone = 14;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetDescendant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 11:
            departLigne = 19;
            departColone = 14;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetBas(tableau,departLigne,departColone,tableauOctet);
            break;

        case 12:
            departLigne = 18;
            departColone = 12;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetMontant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 13:
            departLigne = 14;
            departColone = 12;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetMontant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 14:
            departLigne = 10;
            departColone = 12;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetMontant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 15:
            departLigne = 5;
            departColone = 12;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetMontant(tableau,departLigne,departColone,tableauOctet);
            break;

        case 16:
            departLigne = 1;
            departColone = 12;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetHaut(tableau,departLigne,departColone,tableauOctet);
            break;

        case 17:
            departLigne = 2;
            departColone = 10;
            convertisseur_caracteres_binaire(chaineCaracteres[i],tableauOctet);
            i++;
            octetDescendant(tableau,departLigne,departColone,tableauOctet);
            break;

      }

}

/*********Tableau de correction***************/

   departLigne = 9;
   departColone = 10;
   octetDescendant(tableau,departLigne,departColone,tableauCorrection);

   departLigne = 13;
   departColone = 10;
   octetDescendant(tableau,departLigne,departColone,tableauCorrection);

   departLigne = 17;
   departColone = 10;
   octetDescendant(tableau,departLigne,departColone,tableauCorrection);

   departLigne = 12;
   departColone = 8;
   octetMontant(tableau,departLigne,departColone,tableauCorrection);

   departLigne = 9;
   departColone = 5;
   octetDescendant(tableau,departLigne,departColone,tableauCorrection);

   departLigne = 12;
   departColone = 3;
   octetMontant(tableau,departLigne,departColone,tableauCorrection);

   departLigne = 9;
   departColone = 1;
   octetDescendant(tableau,departLigne,departColone,tableauCorrection);

   return 0;
}

// Code les octets restant (ceux ne contenant le message
void affichageFinTableau (int tableau[21][21], int tableauOctet[8],int nombreDeCaracteres,int k)
{
    int departLigne, departColone;
    int i=0;
    k++;
    while ( k <= 17 )
    {
        if(i==0)
        {
            tableauOctet[0]=0;
            tableauOctet[1]=0;
            tableauOctet[2]=0;
            tableauOctet[3]=0;
            tableauOctet[4]=0;
            tableauOctet[5]=0;
            tableauOctet[6]=0;
            tableauOctet[7]=0;
            i++;
        }
        else if(i==1)    // Premier octet
        {
            tableauOctet[0]=1;
            tableauOctet[1]=1;
            tableauOctet[2]=1;
            tableauOctet[3]=0;
            tableauOctet[4]=1;
            tableauOctet[5]=1;
            tableauOctet[6]=0;
            tableauOctet[7]=0;
            i++;
        }
        else if(i==2)   // Deuxieme octet
        {
            tableauOctet[0]=0;
            tableauOctet[1]=0;
            tableauOctet[2]=0;
            tableauOctet[3]=1;
            tableauOctet[4]=0;
            tableauOctet[5]=0;
            tableauOctet[6]=0;
            tableauOctet[7]=1;
            i=1;
        }
              switch (k)
              {
            case 1:
                departLigne = 14;
                departColone = 20;
                octetMontant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 2:
                departLigne = 10;
                departColone = 20;
                octetHaut(tableau,departLigne,departColone,tableauOctet);
                break;

            case 3:
                departLigne = 11;
                departColone = 18;
                octetDescendant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 4:
                departLigne = 15;
                departColone = 18;
                octetDescendant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 5:
                departLigne = 19;
                departColone = 18;
                octetBas(tableau,departLigne,departColone,tableauOctet);
                break;

            case 6:
                departLigne = 18;
                departColone = 16;
                octetMontant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 7:
                departLigne = 14;
                departColone = 16;
                octetMontant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 8:
                departLigne = 10;
                departColone = 16;
                octetHaut(tableau,departLigne,departColone,tableauOctet);
                break;

            case 9:
                departLigne = 11;
                departColone = 14;
                octetDescendant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 10:
                departLigne = 15;
                departColone = 14;
                octetDescendant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 11:
                departLigne = 19;
                departColone = 14;
                octetBas(tableau,departLigne,departColone,tableauOctet);
                break;

            case 12:
                departLigne = 18;
                departColone = 12;
                octetMontant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 13:
                departLigne = 14;
                departColone = 12;
                octetMontant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 14:
                departLigne = 10;
                departColone = 12;
                octetMontant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 15:
                departLigne = 5;
                departColone = 12;
                octetMontant(tableau,departLigne,departColone,tableauOctet);
                break;

            case 16:
                departLigne = 1;
                departColone = 12;
                octetHaut(tableau,departLigne,departColone,tableauOctet);
                break;

            case 17:
                departLigne = 2;
                departColone = 10;
                octetDescendant(tableau,departLigne,departColone,tableauOctet);
                break;

                  }
                  k++;

    }
   return 0;
}

// Place le carré END
void affichageEnd(int tableau[21][21])
{
    tableau[9][7]=0;
    tableau[9][8]=0;
    tableau[10][7]=0;
    tableau[10][8]=0;

    return 0;
}

////////////////////////////////////////    DECODAGE    /////////////////////////////////////

void octetMontantDecodage (int tableau[21][21], int departLigne,int departColone, int tableauOctet[8])
{
    int ligne,colone;
    int i=0;

    for(ligne = departLigne ; ligne > departLigne-4 ; ligne--)
    {
        for (colone = departColone ; colone > departColone-2 ; colone--)
        {
            tableauOctet[i] = tableau[colone][ligne] ;
            i++;
        }
    }

    return 0;
}

void octetDescendantDecodage (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8])
{
    int ligne,colone;
    int i=0;

    for(ligne = departLigne ; ligne < departLigne+4 ; ligne++)
    {
        for (colone = departColone ; colone > departColone-2 ; colone--)
        {
            tableauOctet[i] = tableau[colone][ligne];
            i++;
        }
    }

    return 0;
}

void octetBasDecodage (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8])
{
    tableauOctet[0] = tableau[departColone][departLigne];
    tableauOctet[1] = tableau[departColone-1][departLigne];
    tableauOctet[2] = tableau[departColone][departLigne+1];
    tableauOctet[3] = tableau[departColone-1][departLigne+1];
    tableauOctet[4] = tableau[departColone-2][departLigne+1];
    tableauOctet[5] =  tableau[departColone-3][departLigne+1];
    tableauOctet[6] = tableau[departColone-2][departLigne];
    tableauOctet[7] = tableau[departColone-3][departLigne];

    return 0;
}

void octetHautDecodage (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8])
{
    tableauOctet[0] = tableau[departColone][departLigne];
    tableauOctet[1] = tableau[departColone-1][departLigne];
    tableauOctet[2] = tableau[departColone][departLigne-1];
    tableauOctet[3] = tableau[departColone-1][departLigne-1];
    tableauOctet[4] = tableau[departColone-2][departLigne-1];
    tableauOctet[5] = tableau[departColone-3][departLigne-1];
    tableauOctet[6] = tableau[departColone-2][departLigne];
    tableauOctet[7] = tableau[departColone-3][departLigne];

    return 0;
}

void determinationMode(int tableau[21][21])
{

    /*printf("%d",tableau[20][20]);   // AFFICHAGE DU MODE EN BINAIRE
    printf("%d",tableau[19][20]);
    printf("%d",tableau[19][19]);
    printf("%d",tableau[19][19]);
    printf("\n");*/

    if( tableau[20][20] == 0 && tableau[19][20] == 1 && tableau[19][19] == 0 && tableau[19][19] == 0 )  // VERIFICATION ASCII
    {
            printf("Le QRCODE est code avec le mode ASCII\n\n");
    }
    else if( tableau[20][20] == 0 && tableau[19][20] == 0 && tableau[19][19] == 0 && tableau[19][19] == 1 ) // VERIFICATION MODE NUMERIQUE
    {
            printf("Le QRCODE est code avec le mode NUMERIQUE\n\n");
    }
    else if( tableau[20][20] == 0 && tableau[19][20] == 0 && tableau[19][19] == 1 && tableau[19][19] == 0 ) // VERIFICATION MODE ALPHE-NUMERIQUE
    {
            printf("Le QRCODE est code avec le mode ALPHA-NUMERIQUE\n\n");
    }

    return 0;
}

int convertisseurBinaireDecimal(int tableauOctet[8],int nombre)
{
    nombre = (tableauOctet[0])*pow(2,7) + (tableauOctet[1])*pow(2,6) + (tableauOctet[2])*pow(2,5) + (tableauOctet[3])*pow(2,4) + (tableauOctet[4])*pow(2,3);
    nombre = nombre + (tableauOctet[5])*pow(2,2) + (tableauOctet[6])*pow(2,1) + (tableauOctet[7])*pow(2,0);

    return nombre;
}

void determinationLongueurMessage(int tableau[21][21])
{
    int longueur;

    /*printf("%d",tableau[19][15]);   // AFFICHAGE DU MODE EN BINAIRE
    printf("%d",tableau[20][15]);
    printf("%d",tableau[19][16]);
    printf("%d",tableau[20][16]);
    printf("%d",tableau[19][17]);
    printf("%d",tableau[20][17]);
    printf("%d",tableau[19][18]);
    printf("%d",tableau[20][18]);
    printf("\n");*/

    longueur = (tableau[20][18])*pow(2,7) + (tableau[19][18])*pow(2,6) + (tableau[20][17])*pow(2,5) + (tableau[19][17])*pow(2,4) + (tableau[20][16])*pow(2,3) + (tableau[19][16])*pow(2,2) + (tableau[20][15])*pow(2,1) + (tableau[19][15])*pow(2,0);

    printf("Le message contient %d caracteres:\n",longueur);
//longueur = (tableau[19][15])*pow(2,7) + (tableau[20][15])*pow(2,6) + (tableau[19][16])*pow(2,5) + (tableau[20][16])*pow(2,4) + (tableau[19][17])*pow(2,3) + (tableau[20][17])*pow(2,2) + (tableau[19][18])*pow(2,1) + (tableau[20][18])*pow(2,0);
    return 0;
}

void decodageLettres(int tableau[21][21],int tableauOctet[8],int nombre)
{
    int departLigne,departColone;
    int finTableau = 0;
    char c;
    int k=1;
    int i;

    while (finTableau == 0 )
    {   // PROBLEME SUR LE WHILE: CHANGER LE TABLEAU OCTET

        switch(k)
        {
            case 1:
            departLigne = 14;   // On annonce le depart de la ligne et de la colone voulu
            departColone = 20;
            octetMontantDecodage(tableau,departLigne,departColone,tableauOctet);    // On décode l'octet et on le range dans  tableauOctet
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);
            break;

        case 2:
            departLigne = 10;
            departColone = 20;
            octetHautDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 3:
            departLigne = 11;
            departColone = 18;
            octetDescendantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 4:
            departLigne = 15;
            departColone = 18;
            octetDescendantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 5:
            departLigne = 19;
            departColone = 18;
            octetBasDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 6:
            departLigne = 18;
            departColone = 16;
            octetMontantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);

            }
                       //printf("FIN TABLEAU : %d\n\n",finTableau);
            break;

        case 7:
            departLigne = 14;
            departColone = 16;
            octetMontantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 8:
            departLigne = 10;
            departColone = 16;
            octetHautDecodage(tableau,departLigne,departColone,tableauOctet);
          if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 9:
            departLigne = 11;
            departColone = 14;
            octetDescendantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 10:
            departLigne = 15;
            departColone = 14;
            octetDescendantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 11:
            departLigne = 19;
            departColone = 14;
            octetBasDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 12:
            departLigne = 18;
            departColone = 12;
            octetMontantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 13:
            departLigne = 14;
            departColone = 12;
            octetMontantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 14:
            departLigne = 10;
            departColone = 12;
            octetMontantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;
        case 15:
            departLigne = 5;
            departColone = 12;
            octetMontantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 16:
            departLigne = 1;
            departColone = 12;
            octetHautDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;

        case 17:
            departLigne = 2;
            departColone = 10;
            octetDescendantDecodage(tableau,departLigne,departColone,tableauOctet);
            if(tableauOctet[0] == 0 && tableauOctet[1] == 0 && tableauOctet[2] == 0 && tableauOctet[3] == 0 && tableauOctet[4] == 0 && tableauOctet[5] == 0 && tableauOctet[6] == 0 && tableauOctet[7] == 0)
            {
                finTableau = 1;
            }
            else
            {
                nombre = convertisseurBinaireDecimal(tableauOctet,nombre);   // On convertis le tableau binaire en décimal
                //printf("%d\n",nombre);
                printf("%c",nombre);
                finTableau = 1;
            }
                        //printf("FIN TABLEAU : %d\n\n",finTableau);

            break;


        }
    k++;
    }
printf("\n");
    return 0;
}

void decodageBitsDeFormat (int tableau[21][21], int BitsDeFormat[15], int correction, int masque)
{
    int colonne, ligne;
    int i;
    int Formats_1[15];
    int Formats_2[15];
    int a, b, c;
    int Masque[15] = {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1}; // Qui est définie par le dossier

    /********Carré Haut Gauche********/
    i=0;
    for(colonne=0; colonne<8; colonne++)
    {
        if(colonne==6)
        {
            colonne++;
        }
        Formats_1[i] = tableau[colonne][8];
        i++;
    }
    for (ligne=8; ligne>=0; ligne--)
    {
        if(ligne==6)
        {
            ligne--;
        }
        Formats_1[i] = tableau[colonne][ligne];
        i++;
    }

    /********Carré Bas Gauche*********/
    i=0;
    for(ligne=20; ligne>=14; ligne--)
    {
        Formats_2[i] = tableau[8][ligne];
        i++;
    }

    /*******Carré Haut Droit********/
    for(colonne=13; colonne<=20; colonne++)
    {
        Formats_2[i] = tableau[colonne][8];
        i++;
    }

    b = convertisseur_binaire_decimal (Formats_1, 15);
    c = convertisseur_binaire_decimal(Masque, 15);
    a = b^c; // b contient les bits de format lus en décimal PENSER A TRANSPOSER TABLEAU LUT DANS B

    convertisseur_entier_binaire2 (a, Formats_1);

    a = a>>10;
    convertisseur_entier_binaire2 (a, BitsDeFormat);

    masque = convertisseur_binaire_decimal (BitsDeFormat, 3);
    correction = a>>3;

    printf("\nLe niveau de correction est:  ");
    switch (correction)
    {
    case 0:
        printf("M");
        break;
    case 1:
        printf("L");
        break;
    case 2:
        printf("H");
        break;
    case 3:
        printf("Q");
        break;
    }
    printf("\n");
    printf("Le masque est le: %d", masque);
    printf("\n\n");

    return 0;
}

void lectureDuFichier(int tableauDecodage[21][21])
{
    char a;
    int c=0,d=0;
    int b=0, multiple=0;
    int colonne=0, ligne=0;
    int i, j=0, k=0;  // Compteurs
    int tab[3];
   // int tableauDecodage[21][21];
    int saut=0, l=0;
    int compteur =1;
//printf("1\n");
    FILE *image = fopen("qrcode.pbm","r");
    int var =1;
//printf("2\n");

    if(image != NULL)
    {
        for(i=0; i<=8; i++)
        {
           // printf("3\n");

            fscanf(image, "%c", &a);
           //printf("%c", a);
            if(a==32)
                j=0;
            if(j==1)
            {
                tab[k]=a-48;
                k++;
            }
            if(a==10)
                j=1;
        }

        while(a!=10) // boucle infinie
        {
            fscanf(image, "%c", &a);
           // printf("%c", a);
            i++;
            //printf("4\n");
        }

        for(j=0; j<3; j++)
        {
            printf("tab[%d] : %d\n",j,tab[j]);  // Transformation de la taille rangé dans le tableau en décimal
        }

printf("\n");

        for(j=0; j<k; j++)  // b = (pow(10,j) * tab[k-j-1]) + b;
        {
            c = (pow(10,j));
            if(j==2)    // problême sur la fonction pow
            {
                c=10*10;
            }
            else
            {
                c = (pow(10,j));
            }
            printf("b a %d : %d\n",j,c);  // Transformation de la taille rangé dans le tableau en décimal
            d = c * tab[k-j-1];
            printf("b a %d : %d\n",j,d);  // Transformation de la taille rangé dans le tableau en décimal
            b = b+d;
            printf("b a %d : %d\n",j,b);  // Transformation de la taille rangé dans le tableau en décimal
            printf("\n");
        }

        /*if(b>100)
        {
            b++;
        }*/

        multiple = b/21;

        colonne = 0, ligne = 0, l = 0;

        printf("\nmultiple : %d\n",multiple);

        while( i <= (21*multiple)*(21*multiple)+(21*multiple)+9 ) //461 *4 *2      //8 + (21*21)*2*multiple + 21*multiple        //(21*multiple)*(21*multiple)+(21*multiple)+9
        {
                if(compteur == multiple)
                {
                                fscanf(image, "%c", &a);
                                //printf("%c",a);
                                        if(a!=10)   // saut de ligne
                                        {
                                            tableauDecodage[colonne][ligne] = a-48;
                                            colonne++;
                                        }
                                        if(colonne==21) // bout de ligne
                                        {
                                            while (var<multiple)
                                            {
                                                     for (k=0;k<=b;k++)
                                                    {
                                                            fscanf(image, "%c", &a);
                                                            //printf("%c",a);
                                                        }
                                                        var++;
                                            }
                                            var=1;

                                                colonne=0;
                                                ligne++;
                                        }
                                        compteur=1;

                }

                else
                {
                                fscanf(image, "%c", &a);
                              // printf("%c",a);
                                compteur++;
                }
                        i++;
            }

    //printf("\n\n");

    printf("Taille du QR-Code : %dx%d\n\n", b,b);

    for(ligne=0 ; ligne<=20 ; ligne++)
    {
        for(colonne=0 ; colonne<=20 ; colonne++)
        {
            if(tableauDecodage[colonne][ligne]==1 ||  tableauDecodage[colonne][ligne]==0)
            {
                printf("%d",tableauDecodage[colonne][ligne]);
            }
        }
        printf("\n");
    }
    }
    getchar ();
    fclose(image);

 }

