#ifndef BEDBUILDER
#define BEDBUILDER

#include "Builder.h"

class BedBuilder : public Builder {

public:

    /**
     * @brief Constructeur
     *
     * @param matrix_file (un std::string) : le nom du fichier de la matrice à partir duquel on calcule les scores
     * @param thrs (un double) : le seuil de validité d'une séquence
     */
    BedBuilder(const std::string & matrix_file, const double & thrs);

    /**
     * @brief Lis un fichier de génome et analyse les séquences d'intérêt
     *
     * @param file (un std::string) : le nom du fichier du génome
     */
    void reader(const std::string & file) override;

    /**
	 * @brief Extrait séquence par séquence à partir d'un brin entier d'ADN (en changeant current_seq et les positions liées)
	 *
	 * @param chromoseq (un std::string) : la séquence de chromosome à découper
	 * @param length (un int) : la longueur des séquences à découper
	 */
    void extract_seq (std::string chromoseq, int length);

    /**
     * @brief Ecrit dans le fichier de sortie les infos relatives à une séquence à afficher
     *
     * @param output (un std::ofstream) : le fichier de sortie dans lequel on écrit
     * @param forward (un bool) indiquant le sens de lecture de la séquence (dans le sens + par défaut)
     */
    void writer (std::ofstream & output, bool forward=true) const;

private:

    double threshold;
    size_t current_pos_in_chr;
    size_t current_pos_in_line;

};


#endif
