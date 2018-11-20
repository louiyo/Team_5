#include "Genome_analyser.h"

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

//pas encore fonctionnelle
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

void Genome_analyser::read_genome(std::string output_file)
{
    std::ifstream genome_input(genome_in.c_str());
    std::ofstream file_output("DBP.mat");
    
    std::string line, seq;
    //get char from a file
    char c;
    bool in_chromo(false);
    size_t pos_inf(0);
    size_t pos_sup(0);
    int chrom_nbr(0);
    int start_seq(0);
    
    //goes through positions multimap
    multimap<size_t, size_t>::iterator it(positions.begin());
    
    //while it isn't at the end of positions
    while(it != positions.end())
    {
		//return range of all iterators with same key = all the different position ranges on the same chromosome 
		pair <std::multimap<std::string, std::pair <size_t, size_t> >::iterator, std::multimap<std::string, std::pair <size_t, size_t> >::iterator> range(positions.equal_range(it.first));
		
		//reinitializes it
		it = range.second;
		
		//goes through different position ranges
		for(std::multimap<std::string, std::pair <size_t, size_t> >::iterator ref=range.begin(); ref!=range.second; ++ref)
			{
				//store boundaries of extracted seq and chromosome number
				//CHECK IF WORKS WELL
				pos_inf = ref.second.first;
				pos_sup = ref.second.second;
				chrom_nbr = ref.first;
				
				
				while(!genome_input.eof())
				
				{
					//get line of file
					std::getline(genome_input, line);
					
					//if we are in the chromosome of interest
					if(in_chromo)
					{
						//extract sequence of interest char per char
						//WHAT HAPPENS IF CHAR = ENDL ??? WHAT HAPPENS IF SPACE OR TAB ?
						genome_input.seekg(start_seq + pos_inf);
						
						for(size_t i(pos_inf); i < pos_sup, ++i)
							{ seq += genome_input.get(c); }
						
						//add to matrix
						current_seq.set_seq(seq),
						current_seq.add_points_to_matrix();
					}
				
						
					//if line with chromosome nbr
					if( line[0] == '>')
					{
						//right chromo
						if(line.compare('>chr' + chrom_nbr) == 0)
						{
							in_chromo = true;
						
							//set start_seq index CAN I DO IT ???
							//CHECK
							start_seq = (genome_input.tellg() + 1);
						}
						
						//if we're not
						else
						{ in_chromo = false; }
					
					}
					
					
					
				} 
			}
            
           write_matrix();     
				
               
}
