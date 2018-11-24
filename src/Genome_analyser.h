#ifndef GENOME_ANALYSER_H
#define GENOME_ANALYSER_H

#include "Sequence.h"

#include <iostream>
#include <map>
#include <utility>

using namespace std;

typedef std::multimap <size_t, std::pair <size_t, size_t> > Positions;
typedef std::pair <Positions::iterator, Positions::iterator> Range;

class Genome_analyser {
public:

    /*
     * @brief constructeur (input 1)
     *
     * @param file_input (un std::string)  : le nom du fichier qui contient le génome
     * @param matrix_file (un std::string) : le nom du fichier qui contient la matrice
     * @param thrs (un double) : le seuil de validité du score d'une séquence
     */
	Genome_analyser (const std::string & file_input, const std::string & matrix_file, const double & thrs);

	/*
	 * @brief constructeur (input 2)
	 *
	 * @param genome_file (un std::string)  : le nom du fichier qui contient le génome
	 * @param size (un double) : la longueur du motif des séquences
     * @param pos_file (un std::string) : le nom du fichier qui continet les coordonnées des séquences
	 */
	Genome_analyser (const std::string & genome_file, const size_t & size, const std::string & pos_file);

    /*
     * @brief Extrait séquence par séquence à partir de la séquence chromosomique entière
     */
    void reader ();
    
    void read_genome  (); // extrait les séquences dans le génome a partir de positions données (via la multimap)
    void read_positions_file (); //A VOIR COMMENT ON S'ORGANISE, POUR LE MOMENT CETTE FONCTION EXTRAIT SEULEMENT LES INFOS DU FICHIER.
						  //IL FAUT PAR LA SUITE REMPLIR LA MULTIMAP AVEC CES INFOS.

    /*
     * @brief génère la séquence de nucléotides complémentaire à une séquence donnée
     *
     * @param seq (un std::string) : la séquence de nucléotides de la séquence à inverser
     *
     * @return la séquence complémentaire à seq (de même direction 5'-3')
     */
	std::string revert_seq (std::string seq) const;

	/*
	 * @brief extrait séquence par séquence à partir d'un brin entier d'ADN (en changeant current_seq et les positions liées)
	 *
	 * @param chromoseq (un std::string) : la séquence de chromosome à découper
	 * @param length (un int) : la longueur des séquences à découper
	 */
    void extract_seq (std::string chromoseq, int length);

    /*
     * @brief Ecrit dans le fichier de sortie les infos relatives à une séquence à afficher
     *
     * @param output (un std::ofstream) : le fichier de sortie dans lequel on écrit
     * @param forward (un bool) indiquant le sens de lecture de la séquence (dans le sens + par défaut)
     */
    void writer (std::ofstream & output, bool forward=true) const;

    /*
     * @brief getteur des nucléotides de la current_seq
     *
     * @return les nucléotides de la current_seq (de longueur seq_size)
     */
    std::string get_seq () const;

private :
	
	Sequence current_seq;
    double threshold;
    std::string chromosome_number;
    size_t current_pos_in_chr = 0; //position courante dans la séquence chromosomique
    std::string file_in; //nom du fichier du génôme
    size_t current_pos_in_chr_in_line = 0;
    size_t seq_size; //longueur de la séquence à couper

    std::string positions_file;
    std::multimap <size_t, std::pair <size_t, size_t> > positions;
    int nb_of_sequences_to_analyze;
};

#endif
