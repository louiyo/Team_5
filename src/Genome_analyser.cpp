#include "Genome_analyser.h"
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;


Genome_analyser::Genome_analyser(const std::string & file_input, const std::string & matrix_file, const double & thrs)
: current_seq(matrix_file), threshold(thrs), seq_size(current_seq.get_size()), current_pos_in_chr(0), file_in(file_input)
{}


Genome_analyser::Genome_analyser (const std::string & genome_file, const size_t & size, const std::string & pos_file)
: file_in (genome_file), seq_size(size), positions_file(pos_file)
{}


std::string Genome_analyser::revert_seq(std::string seq) const {
	
	std::string reverse; //string reverse(current_seq.get_sequence();
	
	for(int i(seq.size()-1);i>=0;--i)
	{
		switch(seq[i]) {
			case ('A') : reverse+="T";
						break;

			case ('C') : reverse+="G";
						break;

			case ('G') : reverse+="C";
						break;

			case ('T') : reverse+="A";
						break;
					}
				}
	return reverse; //current_seq.set_sequence(reverse);
}


std::string Genome_analyser::get_seq() const {
		return current_seq.get_sequence();
	}


void Genome_analyser::extract_seq(std::string chromoseq, int length) {
		current_seq.set_sequence (chromoseq.substr(current_pos_in_chr_in_line,length)); 
		current_pos_in_chr+=1;
		current_pos_in_chr_in_line +=1;
}


void Genome_analyser::writer(std::ofstream& output, bool forward) const{

	if(output.is_open()) {
		if (forward) { 
		    output<< chromosome_number<<" "<<current_pos_in_chr<<" "<<"+"<<" " <<current_seq.get_sequence()<<" "<<current_seq.score_fow()<<std::endl;
	    }else {
		    output<< chromosome_number<<" "<<current_pos_in_chr<<" "<<"-" << " " <<current_seq.get_sequence()<<" "<<current_seq.score_rev()<<std::endl;
	    }
	}

}

void Genome_analyser::reader() {

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
                    current_pos_in_chr_in_line = 0;

                } else {

                    counter += 1;
                    chromo_seq = last;
                    chromo_seq += line;
                    current_pos_in_chr_in_line = 0;

                    if(chromo_seq.size() >= seq_size) {

                        last = line.substr(line.size()-seq_size + 1, seq_size);
                        
                        while(current_pos_in_chr_in_line <= (chromo_seq.size()- seq_size) ) {

                            extract_seq(chromo_seq, seq_size);

							if(current_seq.score_fow() > threshold) {
								writer(file_output);
							}
                        

							if(current_seq.score_rev() > threshold) {
								//Pas cool ecrit la séquence à l'envers, c'est mieux si ça ecrit dans le bon sens et après + ou - 
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

void Genome_analyser::cut_positions(const Range& range, std::ifstream& genome_input, size_t pos_0)
{
	//local variables
	std::string seq;
	char c;
	
	//goes through different positions in chromosome
	for(Positions::iterator ref=range.first; ref!=range.second; ++ref)
	{
		//extract sequence of interest char per char
		size_t start_seq(pos_0 + ref->second.first);
		genome_input.seekg(start_seq);
		for(size_t i(ref->second.first); i < ref->second.second; ++i)
			{
				genome_input.get(c);
				if(c != '\n')
					{seq += c;} 
			}
		
		//add to matrix
		current_seq.set_seq(seq),
		current_seq.add_points_to_matrix();
		seq = "";
	}
	
}

void Genome_analyser::read_genome()
{
    std::ifstream genome_input(file_in.c_str());
    
    std::string line, chrom_nbr;
    bool in_chromo(false);
    size_t pos_0(0);
    
    //goes through positions multimap
    Positions::iterator it(positions.begin());
    
    //range
    Range range(positions.equal_range(it->first));
    chrom_nbr = std::to_string(it->first);
    it = range.second;
    
    //while it isn't at the end of positions
    while(!genome_input.eof())
    {
		while(it != positions.end())
		{
			std::getline(genome_input, line);
			
			//if we are in the chromosome of interest
			if(in_chromo)
			{
				cut_positions(range, genome_input, pos_0);
				//initialize range
				in_chromo = false;
				range = positions.equal_range(it->first);
				chrom_nbr = std::to_string(it->first);
				it = range.second;
			}
		
				
			
			//right chromo
			if(line.compare(">chr" + chrom_nbr) == 0)
			{
				in_chromo = true;
				//set start_seq index
				pos_0 = (genome_input.tellg());
			}
		}
		
		std::getline(genome_input, line);
		//if we are in the chromosome of interest
			if(in_chromo)
			{
				cut_positions(range, genome_input, pos_0);
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
	genome_input.close();
	write_matrix();
}


void Genome_analyser::read_positions_file ()
{
	
	std::ifstream myfile(positions_file);
	std::string line;
	
	if ( myfile.is_open() ) {
		while ( std::getline(myfile,line).good() ) {
			std::string chrom;
			size_t start, end;
			myfile >> chrom >> start >> end; //récupère un string et 2 size_t du fichier.
			chrom.erase(0,3); //enlève les lettres "chr".
			size_t chrom_num = stoul(chrom); //convertit en unsigned long (size_t).
			
			if(this->chromoAlreadyMapped(chrom_num)){

				//ajoute la nouvelle information dans le vecteur déjà existant dans la map	
				(positions[chrom_num]).push_back(std::make_pair(start, end));


				std::sort(positions[chrom_num].begin(), positions[chrom_num].end(), 
													[](auto &left, auto &right){
					return left.second < right.second;
				});

			}else{ std::vector<std::pair<size_t, size_t>> newVec = {{start, end}};
				positions[chrom_num] = newVec;; //ajoute un nouveau vecteur dans la map
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
