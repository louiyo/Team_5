#include "Genome_analyser.h"

#include <string>
#include <fstream>


//constructeur
Genome_analyser::Genome_analyser(std::string file_input, std::string matrix_file, double thrs)
	: current_seq(matrix_file), threshold(thrs), seq_size(current_seq.get_size()), current_pos_in_chr(0), file_in(file_input)
		
		{ }

//extrait séquence par séqeunce à partir de la séquence chromosique entière
void extract_seq(std::string chromoseq, int length)
	{
	
		current_seq.set_sequence (chromoseq.substr(current_pos_in_chr,length)); 
		currentpos_+=1
	
	}			

//ecrit dans le fichier de sortie. le booléen sert a savoir dans quel sens la séquence a un score le plus haut
void write_seq_for(std::ofstream& output, bool forward=true){
	
	if(sortie.is_open()){
		output<<chromo_name<<"  "<<currentpos_<<" + "<<Sequence.getSequence()<<" "<<Matrice.getScore()<<endl;
		}
	}


void write_seq_rev(std::ofstream& output, bool forward=true){
	
	string reverse("");

	for(int i(Sequence.size()-1);i>=0;--i)
	{
		if(seq[i]=='A') {reverse+="T";}
		if(seq[i]=='T') {reverse+="A";}
		if(seq[i]=='G') {reverse+="C";}
		if(seq[i]=='C') {reverse+="G";}
	}
	
	if(output.is_open()){
		
		output<<chromo_name<<"  "<<currentpos_<<" - "<<reverse<<" "<<Matrice.getScore()<<endl;
		
		}
		
	}




void reader(std::string file_in)
{
    std::ifstream file_input(file_in.c_str());
    std::ofstream file_output("name_output_file");
    
    std::string chromo_seq, line, last;

        if(!file.eof())
        {
            while(std::getline(file_input, line)) 
            {
                if(line[0] == '>')
                {
                    chromosome_name = line;
                    chromosome_name.erase(0,1);
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
                        
							set_sequence(revert_seq());

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
