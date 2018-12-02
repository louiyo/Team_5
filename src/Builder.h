#ifndef BUILDER
#define BUILDER

#include "Sequence.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>

class Builder {

public:

    /**
     * @brief constructeur (sans arguments, la current_seq est laissée vide)
     */
    Builder();

    /**
     * @brief Génère la séquence complémentaire à une séquence donnée
     *
     * @param seq (un std::string) : la séquence dont on veut générer le brin complémentaire
     *
     * @return la séquence complémentaire à seq
     */
    std::string revert_seq (std::string seq);

    /**
     * @brief getteur des nucléotides de la current_seq
     *
     * @return les nucléotides de la current_seq (de longueur seq_size)
     */
    std::string get_seq () const;

    /**
     * @brief Reader de fichiers virtuel, qui sera adapté (défini) dans chaque sous-classe Builder
     */
    virtual void reader(const std::string & file) = 0;

private:

    Sequence current_seq;
    size_t seq_size;

};


#endif
