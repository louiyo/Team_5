
/*La classe Matrix doit avoir les attributs :
 * std::string file_;
 * int length_;
 * std::vector< std::array<double,4> > matrix_;
 * 
 * et une fonction void creatMatrix();*/
 
//inclure le fichier .h
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>

//Constructeur de la classe Matrix :

Matrix::Matrix (std::string file)
	:file_(file), length_(0) // + autres attributs
	{
		this->creatMatrix();
	}

//Fonction creatMatrix :

void Matrix::creatMatrix()
{
	std::ifstream myfile(file_);
	std::string line;
	
	if ( myfile.is_open() ) {
		while ( std::getline(myfile,line).good() ) {
			double valueA, valueC, valueG, valueT;
			myfile >> valueA >> valueC >> valueG >> valueT;
			std::array<double, 4> values = {valueA, valueC, valueG, valueT};
			matrix_.push_back(values);
			++length;
		}
		myfile.close();
	} else {
		throw(std::runtime_error("MatrixFile"));
	}
}

//A DEMANDER : autre facon de faire pour remplacer le getline et le array intermédiaire values, mieux de faire ++length ou length = matrix_.size() à la fin, est ce qu'il faut fermer le fichier après
