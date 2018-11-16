#include <string>
#include <vector>
#include <array>


typedef std::vector<std::array<double, 4>> Matrice;


class Sequence {
	
	public:

			//CONSTRUCTEUR
		Sequence(const std::string& file); //Construit la matrice

			//METHODE	
		double score() const; //Calcul du score de la séquence

			//GETTERS
		int get_size() const;
		std::string get_sequence() const;
		
			//SETTER
		void set_sequence(std::string newSeq);
	

	private:

			//ATTRIBUTS	
		std::string sequence_;
		static Matrice matrix_;
	
};
