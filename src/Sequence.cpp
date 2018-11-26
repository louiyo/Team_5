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
{
	vector<array <double,4>> newMat(matrix_size,{0.25,0.25,0.25,0.25});
	matrix_ = newMat;
}


double Sequence::score_fow() const {

	if(matrix_.size() != sequence_.size()) {
	 	/*throw std::runtime_error("MATRIXSIZE");*/
	 	return 0;
	}

	double res(0);
	size_t seq_size = sequence_.size();

	for (size_t i(0) ; i < seq_size ; ++i) {
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


double Sequence::score_rev() const {

	if(matrix_.size() != sequence_.size()) {
	 	/*throw std::runtime_error("MATRIXSIZE");*/
	 	return 0;
	}

	double res(0);
	size_t seq_size = sequence_.size();

	for (size_t i(seq_size) ; i > 0 ; --i) {
		switch(sequence_[i-1]) {
			case ('A') : res += 2 + log2(matrix_[seq_size - i][3]);
						break;

			case ('C') : res += 2 + log2(matrix_[seq_size - i][2]);
						break;

			case ('G') : res += 2 + log2(matrix_[seq_size - i][1]);
						break;

			case ('T') : res += 2 + log2(matrix_[seq_size - i][0]);
						break;

			case ('N') : break;

			default : /*throw std::runtime_error("NUCLEOTIDE");*/ break; //A VOIR LORS DE LA GESTION D'ERREUR
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



void Sequence::write_matrix(std::ofstream& output) const{
	
	if(output.is_open()){
	for (size_t i(0); i< matrix_size(); i++){
		for (size_t j(0); j<4 ; j++){
		output >> matrix_ [i][j]<< "    ";
			} outp>> endl;
		}
	}
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



void count_nucleotides(size_t taille){
	
	int nbdecoupe((sequence_.size()-taille)+1); // Indique le nb de sequence possible si la taille de la sequence est differente de la taille demandee
	
	if(sequence_.size()<taille){throw std::invalid_argument("sequence trop petite");}//VERIFIER le type d'erreur
	
	if(sequence_.size()>taille){
		for(int i(0);i<nbdecoupe;++i){
		rempli_matrice(sequence_.substr(i,taille),nbdecoupe);}
	}	
	
	else { rempli_matrice(sequence_,nbdecoupe);}

	}
	
void rempli_matrice(string seq, double nbdecoupes) 
{
	for (size_t i(0) ; i < sequence_.size() ; ++i)
	{
		switch(sequence_[i]) {
			case ('A') : matrix_[i][0]+=(1/(nbdecoupes));
						break;

			case ('C') : matrix_[i][1]+=(1/(nbdecoupes));
						break;

			case ('G') : matrix_[i][2]+=(1/(nbdecoupes));
						break;

			case ('T') :matrix_[i][3]+=(1/(nbdecoupes));
						break;
						
			//A completer Case('N')

			default : /*throw std::runtime_error("NUCLEOTIDE");*/ break; //A VOIR LORS DE LA GESTION D'ERREUR
		}
	}

}


void matrice_en_freq(){
	//Faire un trow si compteurseq=0
	//compteur_seq  est un compteur de genome analyzer ou sequence qui compte le nombrede seq extraites
	for(auto& ligne: matrix_){
		for(auto& element: ligne){
			element/= compteur_seq;} // ATTENTION compteur seq doit etre un double et verifer qu'il soit non nul
	}
	
	}

