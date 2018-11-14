#include "Sequence.h"

#include <cmath>




//CONSTRUCTEUR (Elodie)

Sequence::Sequence();



//METHODE

double Sequence::score() const
{
	double res(0);

	for (size_t i(0) ; i < sequence_.size() ; ++i)
	{
		switch(sequence_[i]) {
			case ('A') : res += 2 + log2(matrix_[i][0]);
						break;

			case ('C') : res += 2 + log2(matrix_[i][1]);
						break;

			case ('G') : res += 2 + log2(matrix_[i][2]);
						break;

			case ('T') : res += 2 + log2(matrix_[i][3]);
						break;

			default : /*throw std::runtime_error("NUCLEOTIDE");*/ break; //A VOIR LORS DE LA GESTION D'ERREUR
		}
	}

	return res;
}




//GETTERS

int Sequence::get_size() const
{
	return sequence_.size();
}


std::string Sequence::get_sequence() const
{
	return sequence_;
}




//SETTER

void Sequence::set_sequence(std::string newSeq)
{
	sequence_ = newSeq;
}