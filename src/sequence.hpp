#include <iostream>
#include <string>


class Sequence {
	
	public:

//CONSTRUCTEUR
	
	Sequence(); //Initialisé par readerwriter


//FONCTIONS	
	
	/*! Initialise le nom du chromosome,lorsqu'un nouveau chromosome est rencontré au cours de la lecture*/
	void change_chromosome(const string& name);
	
	/*! Met à jour la position courante */
	int change_position();
	
	/*! Met à jour la séquence lue */
	void change_sequence(const string& seq);

//GETTERS

	/*! Retourne sequence_ */
	string getSequence();
	
	/*! donne la position du nucleotide dans la séquence */
	int getPosition();
	
	private:

//ATTRIBUTS	
	string chromosome_;
	int position_; 
	string sequence_;
	
	};
