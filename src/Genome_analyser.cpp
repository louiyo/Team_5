#include "Genome_analyser.h"
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;


Genome_analyser::Genome_analyser(const std::string & file_input, const std::string & matrix_file, const double & thrs)
	: current_seq(matrix_file),
	threshold(thrs),
	//chromosome_number??
	current_pos_in_chr(0),
	file_in(file_input),
	current_pos_in_line(0),
	seq_size(current_seq.get_size())
	//positions??
	//nb_of_sequences_to_analyze?? 
{}


//~ Genome_analyser::Genome_analyser(const std::string & genome_file, const size_t & size, const std::string & pos_file)
	//~ : current_seq(size),
	//~ threshold(0),
	//~ //chromosome_number??
	//~ current_pos_in_chr(0),
	//~ file_in(genome_file),
	//~ current_pos_in_chr(0),
	//~ seq_size(size)
	//~ //nb_of_sequences_to_analyze??
//~ {
	//~ ConstructPositions(pos_file);
//~ }


void Genome_analyser::revert_seq()
{
	std::string reverse;
	std::string seq(current_seq.get_sequence());
	
	for(int i(seq.size()-1);i>=0;--i)
	{
		switch(seq[i]) {
			case ('a') :
			case ('A') : reverse+="T";
						break;

			case ('c') :
			case ('C') : reverse+="G";
						break;

			case ('g') :
			case ('G') : reverse+="C";
						break;

			case ('t') :
			case ('T') : reverse+="A";
						break;
			
			case ('n') :
			case ('N') : reverse+='N';
						break;
			
					}
				}
	current_seq.set_sequence(reverse);
}


std::string Genome_analyser::get_seq() const
{
	return current_seq.get_sequence();
}


void Genome_analyser::extract_seq(std::string chromoseq, int length)
{
	if(chromoseq.size() >= (current_pos_in_line + length) )
	{
		current_seq.set_sequence (chromoseq.substr(current_pos_in_line,length)); 
		current_pos_in_chr+=1;
		current_pos_in_line +=1;
	}
}


void Genome_analyser::writer(std::ofstream& output, bool forward) const
{
	if(output.is_open()) {
		if (forward) { 
		    output<< chromosome_number<<" "<<current_pos_in_chr<<" "<<"+"<<" " <<current_seq.get_sequence()<<" "<<current_seq.score_fow()<<std::endl;
	    }else {
		    output<< chromosome_number<<" "<<current_pos_in_chr<<" "<<"-" << " " <<current_seq.get_sequence()<<" "<<current_seq.score_rev()<<std::endl;
	    }
	}
}





void Genome_analyser::reader_1()
{
    std::ifstream file_input(file_in.c_str());
    std::ofstream file_output("output_file.txt");
    
    std::string chromo_seq, line, last;

        if(!file_input.eof()) {
		size_t counter (0);
		
            while(std::getline(file_input, line)) {

                if(line[0] == '>') {

                    chromosome_number = line;
                    chromosome_number.erase(0,1);
                    current_pos_in_chr = 0;
                    last = "";
                    current_pos_in_line = 0;

                } else {

                    counter += 1;
                    chromo_seq = last;
                    chromo_seq += line;
                    current_pos_in_line = 0;

                    if(chromo_seq.size() >= seq_size) {

                        last = line.substr(line.size()-seq_size + 1, seq_size);
                        
                        while(current_pos_in_line <= (chromo_seq.size()- seq_size) ) {

                            extract_seq(chromo_seq, seq_size);

							if(current_seq.score_fow() > threshold) {
								writer(file_output);
							}
                        

							if(current_seq.score_rev() > threshold) {
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


//regroupe toutes les séquences d'intérêt dans un chromosome donné et les ajoute a la matrice
void Genome_analyser::cut_positions(const Range& range, std::ifstream& genome_input, size_t pos_0)
{
	//local variables
	std::string seq;
	char c;
	
	//goes through different positions in chromosome
	for(auto struc : range)
	{
		//extract sequence of interest char per char
		size_t start_seq(pos_0 + struc.start);
		genome_input.seekg(start_seq);
		for(size_t i(struc.start); i < struc.end; ++i)
			{
				genome_input.get(c);
				if(c != '\n')
					{seq += c;} 
			}
		/*if(!struc.forward)
		{
			//add to matrix
			current_seq.set_sequence(seq);
			revert_seq();
			current_seq.count_nucleotides(seq_size);
			seq = "";
		}
		else
		{
			//add to matrix
			current_seq.set_sequence(seq);
			current_seq.count_nucleotides(seq_size);
			seq = "";
		}*/
	}
	
}

void Genome_analyser::reader_2()
{
    std::ifstream genome_input(file_in.c_str());
    std::ofstream file_output("output_file_Matrix.txt");
    
    std::string line, chrom_nbr;
    bool in_chromo(false);
    size_t pos_0(0);
    
    //goes through positions map
    Positions::iterator it(positions.begin());
    chrom_nbr = it->first;
    
    //while it isn't at the end of positions
    while(!genome_input.eof())
    {
		while(it != positions.end())
		{
			std::getline(genome_input, line);
			
			//if we are in the chromosome of interest
			if(in_chromo)
			{
				cut_positions(it->second, genome_input, pos_0);
				//initialize iterator on map element
				in_chromo = false;
				++ it;
				chrom_nbr = it->first;
			}
			
			
			//right chromo
			if(line.compare(chrom_nbr) == 0)
			{
				in_chromo = true;
				//set start_seq index
				pos_0 = (genome_input.tellg());
			}
			
		}
		
		//last range
		std::getline(genome_input, line);
		//if we are in the chromosome of interest
			if(in_chromo)
			{
				cut_positions(it->second, genome_input, pos_0);
				in_chromo = false;
			}	
			
			//right chromo
			if(line.compare(">chr" + chrom_nbr) == 0)
			{
				in_chromo = true;
				//set start_seq index
				pos_0 = (genome_input.tellg());
			}
		
	}
	
	//ecrit la matrice
	//current_seq.write_matrix(file_output);
	
	genome_input.close();
	file_output.close();
	
}


void Genome_analyser::ConstructPositions (const std::string & file)
{
	
	std::ifstream myfile(file);
	
	if ( myfile.is_open() ) {
		std::string chrom;
		std::size_t start, end;
		char info;
		while (myfile >> chrom >> start >> end) {
			bool forward(true);
			chrom.erase(0,3);
			size_t chrom_num = std::stoul(chrom);
			if ( myfile.peek() != '\n' ) {
				myfile >> info;
				if ( info == '-' ) forward = false;
			}
			if ( myfile.peek() != '\n' ) {
				myfile >> info;
				if ( info == '-' ) forward = false;
			}
			if ( myfile.peek() != '\n' ) {
				myfile >> info;
				if ( info == '-' ) forward = false;
			}
			
			Position newPos = {start, end, forward};

			if(chromoAlreadyMapped(chrom_num)) {
				//ajoute la nouvelle information (ie structure) dans le vector déjà existant
				//du chromosome en le plaçant au bon endroit
				if (sortPosition(positions[chrom_num], newPos) == false) {
					positions[chrom_num].push_back(newPos);
				} 
			} else {
				//ajoute une nouvelle key avec nouveau vector dans la map
				positions.insert(chrom_num, newPos);
			}	
		}
		myfile.close();
	} /*else {
		throw(std::runtime_error("BED_FILE")); //A VOIR LORS DE LA GESTION D'ERREUR
	}*/
} 



bool Genome_analyser::chromoAlreadyMapped(size_t chromo) const
{
	for ( auto p : positions){
		if (p.first == chromo) return true; 
	}
	return false;
}


bool Genome_analyser::sortPosition (std::vector pos, Position newPos)
{
	size_t i(0);

	while (i < pos.size())
	{
		if (newPos.start < pos[i].start) {
			pos.insert(i, newPos);
			return true;
		} else ++i;

		return false;
	}
}
