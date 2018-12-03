#include "Sequence.h"
#include <cmath>
#include <iostream>
#include <sstream> 
#include <fstream>

using namespace std;


Sequence::Sequence(const string& file)
	: sequence_("None"), myfilename(file)
{
	ConstructMatrix();
}


Sequence::Sequence (const size_t & matrix_size)
{
	vector<array <double,4>> newMat(matrix_size,{0.25,0.25,0.25,0.25});
	matrix_ = newMat;
}


double Sequence::score_fow() const
{
	if(matrix_.size() != sequence_.size()) {
	 	/*throw std::runtime_error("MATRIXSIZE");*/
	 	return 0;
	}

	double res(0);
	size_t seq_size = sequence_.size();

	for (size_t i(0) ; i < seq_size ; ++i) {
		switch(sequence_[i]) {
			case ('a') :
			case ('A') : res += 2 + log2(matrix_[i][0]);
						break;

			case ('c') :
			case ('C') : res += 2 + log2(matrix_[i][1]);
						break;

			case ('g') :
			case ('G') : res += 2 + log2(matrix_[i][2]);
						break;

			case ('t') :
			case ('T') : res += 2 + log2(matrix_[i][3]);
						break;

			case ('n') :
			case ('N') : break;

			default : /*throw std::runtime_error("NUCLEOTIDE");*/ break; //A VOIR LORS DE LA GESTION D'ERREUR
		}
	}

	return res;
}


double Sequence::score_rev() const
{
	if(matrix_.size() != sequence_.size()) {
	 	/*throw std::runtime_error("MATRIXSIZE");*/
	 	return 0;
	}

	double res(0);
	size_t seq_size = sequence_.size();

	for (size_t i(seq_size) ; i > 0 ; --i) {
		switch(sequence_[i-1]) {
			case ('a') :
			case ('A') : res += 2 + log2(matrix_[seq_size - i][3]);
						break;

			case ('c') :
			case ('C') : res += 2 + log2(matrix_[seq_size - i][2]);
						break;

			case ('g') :
			case ('G') : res += 2 + log2(matrix_[seq_size - i][1]);
						break;

			case ('t') :
			case ('T') : res += 2 + log2(matrix_[seq_size - i][0]);
						break;

			case ('n') :
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

        myfile.close();
    } /*else {
        throw(std::runtime_error("MATRIX_FILE")); //A VOIR LORS DE LA GESTION D'ERREUR
    }*/
}





int Sequence::get_size() const
{
	return matrix_.size();
}


std::string Sequence::get_sequence() const
{
	return sequence_;
}


void Sequence::set_sequence(std::string newSeq)
{
	sequence_ = newSeq;
}

vector< array<double,4>> Sequence::get_matrix() const
{
	return matrix_;
}





void Sequence::write_matrix(std::ofstream& output, double compteur_seq) 
{
	
	if(compteur_seq>1){ //verifie qu'on a au moins extrait une sequence
	for(auto& ligne: matrix_){
		for(auto& element: ligne){element/= compteur_seq;}
	}
	}
	if(output.is_open()){
		for (size_t i(0); i< matrix_.size(); i++){
			for (size_t j(0); j<4 ; j++){
			output <<matrix_[i][j]<< "    ";
			} output<<endl;
		}
	}
}





void Sequence::count_nucleotides(size_t taille)
{
	//Si la séquence extrait est plus petite que la taille demandée on la complete avec des nucleotides N
	while(sequence_.size()<taille){
		sequence_+="N";
		}
	
	int nbdecoupe((sequence_.size()-taille)+1); // Indique le nb de sequence possible si la taille de la sequence est differente de la taille demandee
	
	if(sequence_.size()>taille){
		for(int i(0);i<nbdecoupe;++i){
			
		rempli_matrice(sequence_.substr(i,taille),nbdecoupe);
		}
	}	
	
	else { rempli_matrice(sequence_,nbdecoupe);}
}


	
void Sequence::rempli_matrice(string seq, double nbdecoupes) 
{
	for (size_t i(0) ; i < seq.size() ; ++i)
	{
		switch(seq[i]) {
			case ('a') :
			case ('A') : matrix_[i][0]+=(1/(nbdecoupes));
						break;

			case ('c') :
			case ('C') : matrix_[i][1]+=(1/(nbdecoupes));
						break;

			case ('g') :
			case ('G') : matrix_[i][2]+=(1/(nbdecoupes));
						break;

			case ('t') :
			case ('T') :matrix_[i][3]+=(1/(nbdecoupes));
						break;
						
			case ('n') :
			case ('N') : break;

			default : throw std::runtime_error("NUCLEOTIDE"); break; //A VOIR LORS DE LA GESTION D'ERREUR
		}
	}

}





