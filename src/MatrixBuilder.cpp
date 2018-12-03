//
// Created by William Astier on 02/12/2018.
//

#include "MatrixBuilder.h"

MatrixBuilder::MatrixBuilder (const size_t& size, const std::string & pos_file):
	Builder (size), total_seq_nb(1)
	
{
	ConstructPositions(pos_file);
	}


void MatrixBuilder::reader(const std::string& file)
{
    std::ifstream genome_input(file.c_str());
    std::ofstream file_output("output_file_Matrix.txt");
    
    std::string line;
    bool in_chromo(false);
    size_t pos_0(0);
    Range value;
   
    //tant que c'est pas la fin du fichier
    while(!genome_input.eof())
    {
			std::getline(genome_input, line);
		
			//si on est dans le chromo qui nous intéresse
			if(in_chromo)
			{
			
			for (auto struc : value )
					{
						
						add_to_matrix(struc, cut_positions(struc, genome_input, pos_0));
					}
				in_chromo = false;
			}
			
			//header chromo name
			if(line[0] == '>')
			{
					line.erase(0,1);
					value = positions[line];
					in_chromo = true;
					//initialise la position 0 (début d'un chromosome au nucléotide 0)
					pos_0 = (genome_input.tellg());
				}
	
			
	}
	
	//ecrit la matrice
	cout<<total_seq_nb<<endl;
	current_seq.write_matrix(file_output, total_seq_nb);
	
	genome_input.close();
	file_output.close();
	
}


 //ajoute les séquences extraites a la matrice

void MatrixBuilder::add_to_matrix(const Position& struc, std::string seq)
	{
				current_seq.set_sequence(seq);
				std::cout<< current_seq.get_sequence() <<endl;
				if(struc.forward)
				{
					current_seq.count_nucleotides(seq_size);
					
				}
				else
				{
					revert_current_seq();
					current_seq.count_nucleotides(seq_size);	
				}

	}

void MatrixBuilder::revert_current_seq()
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


//regroupe toutes les séquences d'intérêt dans un chromosome donné

std::string MatrixBuilder::cut_positions(const Position& struc, std::ifstream& genome_input, size_t pos_0)
{
	//variables locales
	std::string seq;
	char c;
	
	//extracts sequence of interest char per char a partir de la position 0 (relative à une ligne de chr)+ start
		size_t start_seq(pos_0 + struc.start);
		genome_input.seekg(start_seq);
		for(size_t i(struc.start); i < struc.end; ++i)
			{
				genome_input.get(c);
				
				if(c == '\n')
					{ genome_input.get(c);}
				seq += c;

			}
		
		//incrémente le nb total de séquences analysees (pour diviser ensuite   la matrrrice aveccccccc)
		++total_seq_nb;
	
	return seq;
	
}

void MatrixBuilder::ConstructPositions (const std::string& file)
{
	
	std::ifstream myfile(file);
	
	if ( myfile.is_open() ) {
		std::string chrom;
		std::size_t start, end;

		while (myfile >> chrom >> start >> end) {
			bool forward(true);
			
			string line;
			getline(myfile,line);
			
		forward = not std::count(line.begin(), line.end(), '-');
				
			
			
			Position newPos {start, end, forward, ""};

			if(chromoAlreadyMapped(chrom)) {
				//ajoute la nouvelle information (ie structure) dans le vector déjà existant
				//du chromosome en le plaçant au bon endroit
				if (not sortPosition(positions[chrom], newPos)) {
					positions[chrom].push_back(newPos);
				} 
			} else {
				//ajoute une nouvelle key avec nouveau vector dans la map
				std::vector<Position> newVec;
				newVec.push_back(newPos);
				positions[chrom] = newVec;
			}	
		}
		myfile.close();
	} /*else {
		throw(std::runtime_error("BED_FILE")); //A VOIR LORS DE LA GESTION D'ERREUR
	}*/
} 


bool MatrixBuilder::chromoAlreadyMapped(string chromo) const
{
	for ( auto p : positions){
		if (p.first == chromo) return true; 
	}
	return false;
}



bool MatrixBuilder::sortPosition (std::vector<Position>& pos, Position newPos)
{
	std::vector<Position>::iterator it;
	it = pos.begin();

	while (it != pos.end())
	{
		if (newPos.start < it->start) {
			pos.insert(it, 1, newPos);
			return true;
		} else ++it;
	}
	return false;
}


