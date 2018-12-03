#ifndef MATRIXBUILDER
#define MATRIXBUILDER

#include "Builder.h"
#include <sstream> 
#include <fstream> 
#include <algorithm>

struct Position {
    size_t start;
    size_t end;
    bool forward;
    string seq;
};



typedef std::vector<Position> Range;

typedef std::map <string, Range > Positions;

class MatrixBuilder : public Builder  {

public:

    /**
	 * @brief Constructeur
	 *
	 * @param size (un double) : la longueur du motif des séquences
     * @param pos_file (un std::string) : le nom du fichier qui continet les coordonnées des séquences
	 */
    MatrixBuilder (const size_t & size, const std::string & pos_file);

    /**
     * @brief extrait les séquences dans le génome a partir de positions données (via la multimap)
     *
     * @param one_file
     * @param file
     */
    virtual  void reader (const std::string & file) override;

    /**
     * @brief Change la current_seq par la séquence qui lui est complémentaire
     */
    void revert_current_seq ();

    /**
     * @brief
     *
     * @param range (un Range) :
     * @param genome_input (un std::ifstream) :
     * @param pos_0  (un size_t) :
     * @param size  (un size_t) :
     *
     * @return
     */
   std::string cut_positions(const Position& struc, std::ifstream& genome_input, size_t pos_0);

    /**
     * @brief
     *
     * @param file (un std::string) :
     */
    void ConstructPositions (const std::string & file);

    /**
     * @brief
     *
     * @param chromo (un size_t
     *
     * @return
     */
    bool chromoAlreadyMapped(string chromo) const;

    /**
     * @brief
     *
     * @param pos (un std::vector<Position>) :
     * @param newPos (une Position)
     *
     * @return
     */
    bool sortPosition (std::vector<Position>& pos, Position newPos);
    
   void add_to_matrix(const Position& struc, std::string seq);

private:

    Positions positions; //tableau des positions à aller chercher dans le génome
    double total_seq_nb; //nombre de séquences d'intérêt ayant été analysées

};


#endif
