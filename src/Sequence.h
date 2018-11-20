#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <vector>
#include <array>

using namespace std;

class Sequence {
public:

    /*
     * @brief constructeur (input 1)
     *
     * @param file (un std::string) : le nom du fichier qui contient la matrice
     */
    Sequence (const std::string & file);

    /*
     * @brief constructeur (input 2)
     *
     * @param matrix_size (un int) : la taille de la matrice (initialisée avec des valeurs 0.25 pour chaque coordonée)
     */
    Sequence (const size_t & matrix_size);

    /*
     * @brief calcule le score de la séquence (dans son sens 5'-3' dit "forward")
     *
     *  @return le score
     */
    double score_fow() const;

    /*
     * A SUPPRIMER SI PAS UTILISEE
     */
    double score_rev() const;

    /*
     * @brief construit la matrice (en utilisant le fichier qui la contient)
     */
    void ConstructMatrix ();

    /*
     * @brief getteur de la taille de la séquence
     *
     * @return la taille de sequence_
     */
    int get_size() const;

    /*
     * @brief getteur de la séquence de nucléotides
     *
     * @return la std::string sequence_
     */
    std::string get_sequence() const;

    /*
     * @brief setteur de sequence_
     *
     * @param newSeq (un std::string) : la nouvelle séquence de nucléotides
     */
    void set_sequence(std::string newSeq);


private:

    //ATTRIBUTS
    std::string sequence_;
    std::string myfilename;
    vector< array<double,4>> matrix_ ;
};

#endif
