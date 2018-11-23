#include "Sequence.h"

#include <cmath>
#include <iostream>
#include <sstream> 
#include <fstream>

using namespace std;


Sequence::Sequence(const string& file): sequence_("None"), myfilename(file) {
	ConstructMatrix();
}


Sequence::Sequence (const size_t & matrix_size)
: matrix_( vector<array <double,4>, double> (matrix_size , 0.25))
{}


double Sequence::score_fow() const {

	double res(0);
	size_t sequence_size = sequence_.size();

	for (size_t i(0) ; i < sequence_size ; ++i) {
		switch(sequence_[i]) {
			case ('A') : res += 2 + log2(matrix_[i][0]);
						break;

			case ('C') : res += 2 + log2(matrix_[i][1]);
						break;

			case ('G') : res += 2 + log2(matrix_[i][2]);
						break;

			case ('T') : res += 2 + log2(matrix_[i][3]);
						break;

			//default : /*throw std::runtime_error("NUCLEOTIDE");*/ break; //A VOIR LORS DE LA GESTION D'ERREUR
		}
	}

	return res;
}


double Sequence::score_rev() const {

	double res(0);
	size_t matrice_size = sequence_.size() - 1;
	size_t sequence_size = matrice_size + 1;

	for (size_t i(0) ; i < sequence_size ; ++i) {
		switch(sequence_[i]) {
			case ('A') : res += 2 + log2(matrix_[matrice_size - i][3]);
						break;

			case ('C') : res += 2 + log2(matrix_[matrice_size - i][2]);
						break;

			case ('G') : res += 2 + log2(matrix_[matrice_size - i][1]);
						break;

			case ('T') : res += 2 + log2(matrix_[matrice_size - i][0]);
						break;

			//default : /*throw std::runtime_error("NUCLEOTIDE");*/ break; //A VOIR LORS DE LA GESTION D'ERREUR
		}
	}

	return res;
}


void Sequence::ConstructMatrix (){

    ifstream myfile(myfilename);
    string line;
		
    if (myfile.is_open() ) {

        double valueA, valueC, valueG, valueT;

        while ( myfile >> valueA >> valueC >> valueG >> valueT){

            array <double,4> values {valueA, valueC, valueG, valueT};
            matrix_.push_back(values);
        }

        for (size_t i(0); i<matrix_.size(); i++){
            for (size_t j(0); j< matrix_[i].size(); j++){
                cout << matrix_[i][j] << "   ";
            }
            cout << endl;
        }

        myfile.close();
    } /*else {
        throw(std::runtime_error("MATRIX_FILE")); //A VOIR LORS DE LA GESTION D'ERREUR
    }*/
}


int Sequence::get_size() const {
	return matrix_.size();
}


std::string Sequence::get_sequence() const {
	return sequence_;
}


void Sequence::set_sequence(std::string newSeq) {
	sequence_ = newSeq;
}

vector< array<double,4>> Sequence::get_matrix() const {
	return matrix_;
}
