#ifndef GENOME_ANALYSER_H
#define GENOME_ANALYSER_H

#include "Sequence.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Position
{
	size_t start;
	size_t end;
	bool forward;
};

struct Seq
{
	std::string seq;
	bool forward;
};

typedef std::vector<Position> Range;
typedef std::map <size_t, std::vector<Position> > Positions;


class Genome_analyser {
public:

    /*
     * @brief constructeur (input 1)
     *
     * @param file_input (un std::string)  : le nom du fichier qui contient le génome
     * @param matrix_file (un std::string) : le nom du fichier qui contient la matrice
     * @param thrs (un double) : le seuil de validité du score d'une séquence
     */
	Genome_analyser (const std::string & matrix_file, const double & thrs);

	/*
	 * @brief constructeur (input 2)
	 *
	 * @param genome_file (un std::string)  : le nom du fichier qui contient le génome
	 * @param size (un double) : la longueur du motif des séquences
     * @param pos_file (un std::string) : le nom du fichier qui continet les coordonnées des séquences
	 */
	Genome_analyser (const size_t & size, const std::string & pos_file);

    /*
     * @brief Extrait séquence par séquence à partir de la séquence chromosomique entière
     */
    void reader_1 (std::string file);
    
    //input 2
    void reader_2 (bool one_file, std::string file); // extrait les séquences dans le génome a partir de positions données (via la multimap)
    std::vector<Seq> cut_positions(const Range& range, std::ifstream& genome_input, size_t pos_0); //coupe toutes les séquences données sur un chrom et les met avec leur signe dans un vecteur
    void add_to_matrix(std::vector<Seq> s); //ecrit dans la matrice les séquences extraites
	
	void ConstructPositions (const std::string & file);
    
    
    //FONCTIONS UTILITAIRES DE READ_POSITIONS_FILE
    bool chromoAlreadyMapped(size_t chromo) const;
    bool sortPosition (std::vector<Position>& pos, Position newPos);

    /*
     * @brief génère la séquence de nucléotides complémentaire à une séquence donnée
     *
     * @param seq (un std::string) : la séquence de nucléotides de la séquence à inverser
     *
     * @return la séquence complémentaire à seq (de même direction 5'-3')
     */
	void revert_seq ();

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
    
    std::vector< std::array<double,4>> get_matrix() const
		{ 
			return current_seq.get_matrix();
		}
    
    
    

private :
	
	Sequence current_seq;
    double threshold;
    std::string chromosome_number;
    size_t current_pos_in_chr; //position courante dans la séquence chromosomique
    size_t current_pos_in_line;
    size_t seq_size; //longueur de la séquence à couper

    Positions positions;        //tableau des positions à aller chercher dans le génome
    int total_seq_nb;
    
};

#endif
