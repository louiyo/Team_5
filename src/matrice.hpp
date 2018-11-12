#include <iostream>
#include <string>
#include <fstream>

/*! La matrice represente la probabilité de présence d'un nucléotide,
 * dans une sequence consensus, selon sa position.
 * Score = taux d'affinité entre la proteine et une sequence de nucleotides*/

class Matrice {
	
	public:

//CONSTRUCTEUR	
	/*!Appel la fonction create_matrix */
	Matrice(std::ifstream& file, double seuil);
	
//FONCTIONS
	/*! Lit la matrice donnée et initialise notre attribut matrice_*/
	void create_matrix(std::ifstream& file);
	
	/*! Calcul le score d'une sequence lu de 5'à 3' et attribue à score_ 
	 la valeur obtenue*/
	bool reverse_score(const string& sequence);
	
	/*! Calcul le score d'une sequence lu de 3'à 5'et attribue à score_ 
	 la valeur obtenue*/
	bool forward_score(const string& sequence);

//GETTERS	
	/*! Retourne la taille de la sequence à extraire */
	int getSeqLength() const;
	
	/*! Retourne la valeur du score */
	double getScore() const;
	
	private:
	
//ATTRIBUTS	
	vector<vector<double>> matrice_;
	double score_;
	double seuil_;
	
	};
