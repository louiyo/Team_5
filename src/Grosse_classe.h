#ifndef GROSSE_CLASSE
#define GROSSE_CLASSE

#include <iostream>

class Grosse_Classe {
public:

    /*
     * @brief Constructeur
     */
    Grosse_Classe();

    /*
     * @brief Extrait séquence par séquence à partir de la séquence chromosomique entière
     *
     *  @param
     *  @param
     */
    void /*Grosse_Classe::*/ extract_seq(std::string, int length);

    // Commentaire de @William :
    // extract_seq correspond-elle à extract qui est implémentée ? Ou est-ce une autre fonction ?

    /*
     * @brief Ecrit dans le fichier de sortie les infos relatives à une séquence à afficher
     *
     * @param output (un std::ofstream) : le fichier de sortie dans lequel on écrit
     * @param forward (un bool) indiquant le sens de lecture de la séquence
     */
    void /*Grosse_Classe::*/ write_seq(std::ofstream & output, bool forward=true);

private:
    Sequence seq; // Type à créer
    Matrice mat; // Type à créer

    // Commentaire de @William :
    // Contrairement à ce qui est écrit dans le compte-rendu 2, il ne me semble pas bon d'avoir des attributs
    // Correspondants aux fichiers de input et de output, on se contenterai plutôt de les lire sans les "charger"
    // dans la mémoire
};

#endif
