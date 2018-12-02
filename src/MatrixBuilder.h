#ifndef MATRIXBUILDER
#define MATRIXBUILDER

#include "Builder.h"
#include <string>

struct Position {
    size_t start;
    size_t end;
    bool forward;
};

// j'e ai besoin pour ma focntion cut position mais ça fait de la répet par rapport a la structure d'au dessus. d'autres idées ?
struct Seq {
	std::string seq;
	bool forward;
	
};

typedef std::vector<Position> Range;

typedef std::map <size_t, std::vector<Position> > Positions;

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
    void reader (const std::string & file) override;

    /**
     * @brief Change la current_seq par la séquence qui lui est complémentaire
     */
    void change_to_reverse ();

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
    std::vector<Seq> cut_positions(const Range& range, std::ifstream& genome_input, size_t pos_0, size_t size);

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
    bool chromoAlreadyMapped(size_t chromo) const;

    /**
     * @brief
     *
     * @param pos (un std::vector<Position>) :
     * @param newPos (une Position)
     *
     * @return
     */
    bool sortPosition (std::vector<Position>& pos, Position newPos);

private:

    Positions positions; //tableau des positions à aller chercher dans le génome
    int total_seq_nb; //nombre de séquences d'intérêt ayant été analysées

};


#endif
