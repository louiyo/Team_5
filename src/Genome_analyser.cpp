#include "Genome_analyser.h"
#include <string>
#include <fstream>

using namespace std;


//constructeur
Genome_analyser::Genome_analyser(std::string file_input, std::string matrix_file, double thrs)
	: current_seq(matrix_file), threshold(thrs), seq_size(current_seq.get_size()), current_pos_in_chr(0), file_in(file_input)
		
		{}
		
//destructeur
Genome_analyser::~Genome_analyser()
	{}


void Genome_analyser::revert_seq(std::string seq) { //void sans paramètres
	
	std::string reverse; 
	
	for(int i(current_seq.size()-1);i>=0;--i)
	{
		if(current_seq[i]=='A') {reverse+="T";}
		if(current_seq[i]=='T') {reverse+="A";}
		if(current_seq[i]=='G') {reverse+="C";}
		if(current_seq[i]=='C') {reverse+="G";}
	}
	current_seq.set_sequence(reverse); 
	}


//fonction pour les tests... sinon changer paramètre de retour d'extract seq
std::string Genome_analyser::get_seq() const
	{
		return current_seq.get_sequence();
	}


//extrait séquence par séqeunce à partir de la séquence chromosique entière
void Genome_analyser::extract_seq(std::string chromoseq, int length)
	{
	
		current_seq.set_sequence (chromoseq.substr(current_pos_in_chr,length)); 
		current_pos_in_chr+=1;
	
	}			

//ecrit dans le fichier de sortie. le booléen sert a savoir dans quel sens la séquence a un score le plus haut
void Genome_analyser::writer(std::ofstream& output, bool forward) const{
	
	char direction;
	if (forward) { direction = '+'; }
	else { direction = '-'; }
	
	if(output.is_open())
	{
		output<<chromosome_number<<" "<<current_pos_in_chr<<" " << direction << " " <<current_seq.get_sequence()<<" "<<current_seq.score()<<std::endl;
	}
	
	}

//on rajoute la fin de la ligne d'avant à la ligne d'après pour analyser des séquences sur plusieurs lignes
void Genome_analyser::reader()
{
    std::ifstream file_input(file_in.c_str());
    std::ofstream file_output("output_file.txt");
    
    std::string chromo_seq, line, last;

        if(!file_input.eof())
        {
            while(std::getline(file_input, line)) 
            {
                if(line[0] == '>')
                {
                    chromosome_number = line;
                    chromosome_number.erase(0,1);
                    current_pos_in_chr = 0;
                    last = "";
					
                }

                else
                {
                    current_pos_in_chr = 0;
                    chromo_seq = last;
                    chromo_seq += line;
                    
                    if(chromo_seq.size() >= seq_size)
					{
                        last = line.substr(line.size()-seq_size + 1, seq_size);
                        
                        while(current_pos_in_chr <= (chromo_seq.size()- seq_size) )
						{
                            extract_seq(chromo_seq, seq_size);

							if(current_seq.score() > threshold)
							{
								writer(file_output);
							}
                        
							current_seq.set_sequence(revert_seq(current_seq.get_sequence())); //revert_seq();

							if(current_seq.score() > threshold)
							{
								writer(file_output, false);
							}
						}
					}   
                }


            }
        }
        //on ferme les fichiers
        file_input.close();
        file_output.close();
   
}

void Genome_analyser::search_and write(std::string output_file)
{
    std::ifstream genome_input(genome_in.c_str());
   
    std::ofstream file_output("DBP.mat");
    
    std::string seq, line;
    char c;
    bool in_chromo;
    //std::multimap <std::string, std::pair <size_t, size_t> > BED
    //use std::strcmp to compare two strings or compare

            
            //attention quand on aura plusieurs chromosomes sur mm file /un file per chromosome
            while(std::getline(file_input, line)) 
            {
                
				if(in_chromo)
					{
						//extraire la seq du genome
						genome_input.seekg(genome_input.tellg() - line.size() + pos_inf);
						while (nb de characters < length)
							{ seq += c.get(/*...*/); }
						
						//donner a manger a la matrice dépendant de la longueur
						current_seq.set_seq(seq),
						current_seq.add_to_matrix();
						
				
				if(line == ('>chr' + nbr_chromo))   //conparer le nber du chromosome
                {
                    //booléen dans la séquence voulue ?
					
                }

               
}
