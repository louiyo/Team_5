#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <vector>
#include <array>


using namespace std;




class Sequence {
	
	public:

			//CONSTRUCTEUR
		Sequence(const std::string& file); //Construit la matrice

			//METHODE	
		double score_fow() const; //Calcul du score foward de la séquence
		double score_rev() const; //Calcul du score reverse de la séquence
		
		void ConstructMatrix ();

			//GETTERS
		int get_size() const;
		std::string get_sequence() const;
		
			//SETTER
		void set_sequence(std::string newSeq);
	

	private:

			//ATTRIBUTS	
		std::string sequence_;
		std::string myfilename;
		vector< array<double,4>> matrix_ ;
	
};



#endif
