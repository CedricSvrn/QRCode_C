#include <graphics.c>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include "fonctions.h"


void tableau_SDL(int tab[21][21])
{
    POINT P;
    COULEUR color;
    int ligne, colonne;
    int num_ligne=26, num_colonne=26;
    int val;

    P.x=40 ; P.y=50;


    init_graphics(600, 600); //Affiche la console
    affiche_auto_on();

    for(ligne=0 ; ligne<21  ; ligne++)   // boucles remplissage de tableau
    {
        for(colonne=20 ; colonne>=0 ; colonne--)
        {
            val = tab[ligne][colonne];

            if((colonne>12 && ligne<8)||(colonne<8 && ligne<8)||(colonne<8 && ligne>12) /*|| (colonne > 7 && colonne > 13 &&  ligne=6) || (colonne=8 && ligne=13)*/)
                aff_int(val, 20, P, white);

             else if((colonne > 5 && colonne < 7 && ligne < 13 ) || (colonne <13 &&  ligne > 5 && ligne < 7) || (ligne<9 && ligne > 7 && colonne >12 && colonne<14))    // Lignes et point fixe
                aff_int(val, 20, P, white);

            else if (( colonne > 7 && colonne < 9 && ligne > 12 && ligne < 21 ) || ( ligne > 7 && ligne < 9 && colonne > 13 && colonne < 21 ))   // bits de format
                aff_int(val, 20, P, red);

            else if ((colonne>7 && colonne < 9 && ligne >= 0 && ligne < 6) || (colonne > 7 && colonne < 9 && ligne >= 7 && ligne < 9))   // bits de format
                aff_int(val, 20, P, red);

            else if ((ligne>7 && ligne < 9 && colonne >= 0 && colonne < 6) || (ligne > 7 && ligne < 9 && colonne >= 7 && colonne < 9))   // bits de format
                aff_int(val, 20, P, red);

            else if(val==0)
                aff_int(0, 20, P, orange);

            else if(val==1)
                aff_int(1, 20, P, blue);

            P.y=P.y+num_colonne;
        }

        P.x=P.x+num_ligne ;
        P.y=50;
    }

    wait_escape();
}


int WinMain()
{

        /**********Déclaration des variables**********/


    int choix;
    int taille, multiplicateur, ligne, colone, departColone, departLigne;  // déclaration et initialisation des variables
    int nombre;
    // Taille de l'image voulue, nombre de fois de la taille du QR-Code de base
    // Variables de la ligne, colonne du tableau, et le départ de la ligne et de la colonne des différentes fonctions

    int carre = 0;  // Vaiable représentant le petit carré "perdu" pour l'initialisation du tableau

    int format, masque; // Représente le choix du format (taux de correction et masque)
    int BitsDeFormat[15];

    int i, j;    // Création des différents compteurs
    int correction; // Variable comptenant le nombre correspondant au type de corection choisis
    int nombreDeCaracteres;
    int tableauOctet[8];  // Création du tableau contenant les octets binaire

    char chaineCaracteres[20];  // Création du tableau de la chaine de caractere
    int k=0;    // Compteur de caracteres

    int tableau[21][21];    // Création du tableau de travail


    /************DEBUT DE L'ENCODAGE************/


    printf("Programme QRcode :      \n\n\n");

    printf("Que voulez vous faire ?\n");
    printf("1 - Coder un QRcode.\n");
    printf("2 - Decoder un QRcode.\n");
     scanf("%d",&choix);
    printf("\n\n");

     if(choix==1)
     {

// Enregistre les caractères dans un tableau
    printf("Entrez votre chaine de caracteres : ");
    while ((chaineCaracteres[k] = getchar()) != '\n')   // Boucle de tour à vide
    {k++;}
    k=0;
    //chaineCaracteres[k] = 'a'; // Demande d'entrée de la chaine
    while ((chaineCaracteres[k] = getchar()) != '\n')   // Boucle remplissage du tableau, tant qu'ENTRE n'est pas appuyé
    {
        k++;
    }

    if(k>17)
    {
        printf("\nIl y a plus de 17 caracteres, donc on ne prend que les 17 premiers\n");
        k = 17;
    }
    nombreDeCaracteres = k;
    chaineCaracteres[k] = '\0'; // 'FERMETURE' du tableau
    printf("\n");

// Gestion de la taille
    printf("Taille (multiple de 21) : ");   // Demande de la taille
    scanf("%d", &taille);
    int tableauFinal[taille][taille];   // céation du tableau final en foncion de la taille demandée
    printf("\n\n");

// Gestion du format
    printf("Choix du mode de correction :\n");  // Demande de la correction voulue, INUTILE POUR LE MOMENT
    printf("   1 - L (7 pourcent de recuperation et 17 caracteres max)\n");
    printf("   2 - M (15 pourcent de recuperation et 14 caracteres max)\n");
    printf("   3 - Q (25 pourcent de recuperation et 11 caracteres max)\n");
    printf("   4 - H (30 pourcent de recuperation et 7 caracteres max)\n");
    scanf("  %d", &correction);    // On sauvegarde le choix

    printf("\n\n");

    printf("Choix du masque :\n");
    printf("   0 \n");
    printf("   1 \n");
    printf("   2 \n");
    printf("   3 \n");
    printf("   4 \n");
    printf("   5 \n");
    printf("   6 \n");
    printf("   7 \n");
    scanf("  %d", &masque);

    printf("\n");

// Affiche ce à quoi correspondent les caractères
    printf("Voici votre chaine de caracteres : ");  // Affichage de la chaine de caractere
    for(k=0 ; chaineCaracteres[k] != '\0' ; k++)    // Boucle affichage de la chaine de caractere
    {
        putchar(chaineCaracteres[k]);   // Affichage des caracteres un par un
    }

    printf("\n\n");
    departLigne = 11;
    departColone = 14;
    printf("Voici votre chaine de caracteres en binaire : \n");  // Affichage de la chaine de caractere
    for (i=0; i<k; i++)   // Boucle qui effectue la convertion de chaque caractère
    {
        convertisseur_caracteres_binaire (chaineCaracteres[i], tableauOctet);    // On appelle la fonction qui convertit la lettre en binaire
        printf("\n");

        for (j=0;j<8;j++)   // Boucle affichage du code binaire
        {
            printf("%d",tableauOctet[j]);
        }
    }
     printf("\n");


    multiplicateur = taille/21; // Calcul du multiplicateur

    FILE *image;    // Création du fichiermorpion
    image = fopen("qrcode.pbm", "w+");

    for(ligne=0 ; ligne<21  ; ligne++)   // boucles remplissage de tableau
    {
        for(colone=0 ; colone<21 ; colone++)
            {
                tableau[colone][ligne] = 0 ;   // association du tableau de masque avec celui principal
            }
    }


// ------------------ CARRE HAUT GAUCHE -----------------------
    departColone = 0 ;      // on définit le départ de la colonne et de la ligne pour afficher la partie fixe
    departLigne = 0 ;
    affichageCarreTableau(taille,tableau,departLigne,departColone,carre);   // Affichage du carré fixe en fonction du point de départ

// ------------------ CARRE HAUT DROITE -----------------------
    departColone = 14 ;     // on définit le départ de la colonne et de la ligne pour afficher la partie fixe
    departLigne = 0 ;
    affichageCarreTableau(taille,tableau,departLigne,departColone,carre);// Affichage du carré fixe en fonction du point de départ

// ------------------ CARRE BAS GAUCHE ------------------------
    departColone = 0 ;      // on définit le départ de la colonne et de la ligne pour afficher la partie fixe
    departLigne = 14 ;
    carre = 1;  // On change cette variable pour afficher les bits fixes spéciaux
    affichageCarreTableau(taille,tableau,departLigne,departColone,carre);// Affichage du carré fixe en fonction du point de départ

// Affichage des bits de formats dans le tableau
    encodage_bits_de_format(correction, masque, BitsDeFormat);
    printf("\nTableau Bits de Formats obtenu :   \n");
    for (i=14; i>=0; i--)
    {
        printf("%d  ", BitsDeFormat[i]);
    }
    printf("\n\n");

// Fonctions d'encodage des bits dans le tableau QRcode
    affichageBitsDeFormat(tableau, BitsDeFormat);
    affichageMode(tableau); // AFFICAGE DU MODE CHOISIS, ICI C'EST ASCII
    affichageLongeurMessage(tableau,nombreDeCaracteres,tableauOctet);   // affichage longueur du message
    affichageTexteTableau(tableau, chaineCaracteres,tableauOctet,nombreDeCaracteres);
    affichageFinTableau (tableau,tableauOctet,nombreDeCaracteres,k);
    affichageEnd(tableau);
    affichageCarreDansFichier(taille,multiplicateur,image,tableau,tableauFinal); // affichage du tableau dans le fichier

    tableau_SDL(tableau);

    printf("\n\n\nFIN CODAGE DU QRCODE !\n\n\n\n\n");

    fclose(image); // fermeture de l'image
     }

    /***********FIN DE L'ENCODAGE***********/


 /***********DEBUT DU DECODAGE***********/
    else if(choix==2)
    {


    int tableauDecodage[21][21];

printf("DEBUT DU DECODAGE !\n\n\n\n");

    lectureDuFichier(tableauDecodage);
    determinationMode(tableauDecodage);
    determinationLongueurMessage(tableauDecodage);
    decodageLettres(tableauDecodage,tableauOctet,nombre);
    decodageBitsDeFormat (tableauDecodage, BitsDeFormat, correction, masque);

    tableau_SDL(tableauDecodage);


    }

    /***********FIN DU DECODAGE***********/


    /******************************************************
    */
    return 0;
}
