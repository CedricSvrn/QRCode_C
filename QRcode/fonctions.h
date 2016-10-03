#include <stdio.h>
#include <stdlib.h>
#include <math.h>


////////////////////////////////////////    ENCODAGE    /////////////////////////////////////


    // Création de la fonction qui va donner la taille en binaire du décimal
    int taille_tableau_du_decimal(int a);

    // Convertit un tableau de bits en une décimal
    int convertisseur_binaire_decimal (int tableau[15], int k);

    // Fonction qui prend en arguments le niveau de correction et le masque
    void encodage_bits_de_format (int correction, int masque, int tableau[15]);

    // Place les Parties fixes dans le tableau
    void affichageCarreTableau (int taille,int tableau[21][21], int departLigne, int departColone, int carre);    // AFFICHAGE D'UN CARE FIXE

    /********************** Définit la lecture des octets du QRcode (encodage) ***********************/

    void octetMontant (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8]);


    void octetDescendant (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8]);


    void octetHaut (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8]);


    void octetBas (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8]);


    /*************************************************************************************/

    // Affiche le tableau final dans la console
    void affichageCarreDansFichier (int taille,int multiplicateur,FILE *image,int tableau[21][21], int tableauFinal[taille][taille]);
    // Place le mode

    void affichageMode(int tableau[21][21]);
    // Place la longueur du message

    void affichageLongeurMessage(int tableau[21][21],int nombreDeCaracteres,int tableauOctet[8]);


    void convertisseur_caracteres_binaire (char caractere, int tableauOctet[8]);


    void convertisseur_entier_binaire (int caractere, int tableauOctet[8]);


    void convertisseur_entier_binaire2 (int caractere, int tableau[15]);

    // Place les bits de formats le long des carrés fixes
    void affichageBitsDeFormat (int tableau[21][21], int Formats[15]);

    // Place le texte
    void affichageTexteTableau (int tableau[21][21], char chaineCaracteres[20], int tableauOctet[8],int nombreDeCaracteres);

    // Code les octets restant (ceux ne contenant le message
    void affichageFinTableau (int tableau[21][21], int tableauOctet[8],int nombreDeCaracteres,int k);

    // Place le carré END
    void affichageEnd(int tableau[21][21]);




////////////////////////////////////////    DECODAGE    /////////////////////////////////////


    /********************** Définit la lecture des octets du QRcode (décodage) ***********************/

    void octetMontantDecodage (int tableau[21][21], int departLigne,int departColone, int tableauOctet[8]);


    void octetDescendantDecodage (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8]);


    void octetBasDecodage (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8]);


    void octetHautDecodage (int tableau[21][21], int departLigne, int departColone,int tableauOctet[8]);


    /*************************************************************************************/


    void determinationMode(int tableau[21][21]);


    int convertisseurBinaireDecimal(int tableauOctet[8],int nombre);


    void determinationLongueurMessage(int tableau[21][21]);


    void decodageLettres(int tableau[21][21],int tableauOctet[8],int nombre);


    void decodageBitsDeFormat (int tableau[21][21], int BitsDeFormat[15], int correction, int masque);


    void lectureDuFichier(int tableauDecodage[21][21]);


    //void tableau_SDL(int tab[21][21]);
