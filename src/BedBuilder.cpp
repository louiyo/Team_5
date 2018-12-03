#include "BedBuilder.h"
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;


BedBuilder::BedBuilder(const std::string & matrix_file, const double & thrs)
	: 
	Builder (matrix_file),
	threshold(thrs),
	current_pos_in_chr(0),
	current_pos_in_line(0),
	chromosome_number("None")
{}


void BedBuilder::reader(const std::string & file)
{
    std::ifstream file_input(file.c_str());
    std::ofstream file_output("output_file.txt");
    
    std::string chromo_seq, line, last;

        if(!file_input.eof()) {
		
            while(std::getline(file_input, line)) {

                if(line[0] == '>') {

                    chromosome_number = line;
                    chromosome_number.erase(0,1);
                    current_pos_in_chr = 0;
                    last = "";
                    current_pos_in_line = 0;

                } else {

                    chromo_seq = last;
                    chromo_seq += line;
                    current_pos_in_line = 0;
					
					if((chromo_seq.size() < seq_size))
						{
							last = chromo_seq;
						}
					
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


void BedBuilder::extract_seq (std::string chromoseq, int length)
{
	if(chromoseq.size() >= (current_pos_in_line + length) )
	{
		current_seq.set_sequence (chromoseq.substr(current_pos_in_line,length)); 
		current_pos_in_chr+=1;
		current_pos_in_line +=1;
	}
}

void BedBuilder::writer(std::ofstream & output, bool forward) const
{
	if(output.is_open()) {
		if (forward) { 
		    output<< chromosome_number<<" "<<current_pos_in_chr<<" "<<"+"<<" " <<current_seq.get_sequence()<<" "<<current_seq.score_fow()<<std::endl;
	    }else {
		    output<< chromosome_number<<" "<<current_pos_in_chr<<" "<<"-" << " " <<current_seq.get_sequence()<<" "<<current_seq.score_rev()<<std::endl;
	    }
	}
}

