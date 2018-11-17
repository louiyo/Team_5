#ifndef GENOME_ANALYSER
#define GENOME_ANALYSER

#include <iostream>

class Genome_analyser{
public:

    /*
     * @brief Constructeur
     */
    Genome_analyser();

    /*
     * @brief Extrait séquence par séquence à partir de la séquence chromosomique entière
     *
     *  @param
     *  @param
     */
        void reader();
	
	string revert_seq(string seq);



    void extract_seq(std::string, int length);

    /*
     * @brief Ecrit dans le fichier de sortie les infos relatives à une séquence à afficher
     *
     * @param output (un std::ofstream) : le fichier de sortie dans lequel on écrit
     * @param forward (un bool) indiquant le sens de lecture de la séquence
     */
    void writer(std::ofstream & output, bool forward=true);

private :
	
	Sequence current_seq; // Type à créer
    double threshold; //Genome_analyser s'occupe de savoir si le score est au dessus du seuil ou non
    string chromosome_name;
    int seq_size; //longueur de la séquence à couper
    int current_pos_in_chr; //position courante dans la séquence chromosomique
    std::string file_in; //nom du fichier du génôme

    //nom fichier entrée ? string file_in;
};

#endif
