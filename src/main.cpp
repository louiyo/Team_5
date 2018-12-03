#include <tclap/CmdLine.h>
#include <string>
#include "BedBuilder.h"
#include "MatrixBuilder.h"


using namespace TCLAP; 

int main(int argc, char **argv) { 
 CmdLine cmd("Projet Programmation Team 5"); 
 
	ValueArg< std::string > argNameofGenome("G", "Genome", "Enter the name of the file that contains your genome of interest",  true, "NoName", "string"); 
    cmd.add(argNameofGenome);
    
    ValueArg< std::string > argListofPos("L", "List", "Enter the name of the file that contains your list of position",  true, "NoName", "string"); 
    cmd.add(argListofPos);
    
    ValueArg< size_t > argSize("s", "size", "Enter the size of sequence of interest to build matrice",  true, 0, "size_t"); 
    cmd.add(argSize);
    
    
    /* POUR LA PARTIE 1 
    ValueArg< std::string > argMatrice ("M", "Matrice", "Enter the name of the file that contains your matrice of interest", true, "NoName", "string"); 
    cmd.add(argMatrice); 
    
    ValueArg< double > argSeuil("S", "Seuil", "Enter the seuil of likelihood tolerance (double)", false, 10.0, "double"); 
    cmd.add(argSeuil);
    
*/
    
cmd.parse(argc, argv);

MatrixBuilder Analyser(argSize.getValue(), argListofPos.getValue());
Analyser.reader(argNameofGenome.getValue());
//BedBuilder Analyser (argMatrice.getValue(), argSeuil.getValue());
//Analyser.reader(argNameofGenome.getValue());
 
}
