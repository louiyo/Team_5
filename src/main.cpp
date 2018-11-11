#include <tclap/CmdLine.h>

#include <string>

//#include "Grosse_classe.h"


using namespace TCLAP; 

int main(int argc, char **argv) { 
 CmdLine cmd("Projet Programmation Team 5"); 
 
	ValueArg< std::string > argNameofGenome("G", "Genome", "Enter the name of the file that contains your genome of interest",  true, "NoName", "string"); 
    cmd.add(argNameofGenome);
    
    ValueArg< std::string > argMatrice ("M", "Matrice", "Enter the name of the file that contains your matrice of interest", true, "NoName", "string"); 
    cmd.add(argMatrice); 
    
    ValueArg< double > argSeuil("S", "Seuil", "Enter the seuil of likelihood tolerance (double)", false, 10.0, "double"); 
    cmd.add(argSeuil);
    
    /*
    ValueArg<int> argFirstPos("F","FirstPos", "Enter the first position in your genome to create a matrice", true, "int");
    cmd.add(argFirstPos);
    
    ValueArg<int> argLastPos( "L", "LastPos", "Enter the last position in your genome to create a matrice", true, "int");
    cmd.add(argLastPos);
    
    */
    
cmd.parse(argc, argv);
 
}
