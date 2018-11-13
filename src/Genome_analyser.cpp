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
    //on ouvre le fichier file_in qui est un attribut de la Grosse classe
    std::ifstream file_input(file_in.c_str());

    //se crée tout seul
    std::ofstream file_output("name_output_file");


      std::string chromo_name, chromo_seq, line;

        if(file_input.is_open())
        {
            while(std::getline(file_input, line)) //modifier 
            {

                // si la ligne est un nom de chromosome, on stocke le nom dans l'attribut chromosome_name
                //on traite la séquence chromosique complète qui vient d'être extraite
                if(line[0] == '>')
                {

                    //si on a déjà une chromo_seq et qu'on est retourné à '>', alors c'est la fin du chromosome :
                    //on peut commencer a découper la ligne extraite
                    if(chromo_seq.size() != 0)
                    {
						if(chromo_seq.size() >= seq_size)
						{
                        //tant qu'on n'est pas à la fin du chromosome ATTENTION CAR IL SE PEUT QUIL Y AIT UNE COMPARAISON AVEC UN NB NEGATIF
                        while(current_pos_in_chr <= (chromo_seq.size()- seq_size) )
						{
                            //on extrait une séquence d'une longueur donnée (attribut se(la fonction extract_seq la stocke dans l'objet Sequence,
                            //initialise la position courant ++1)
                            extract_seq(chromo_seq, seq_size);

                        //on regarde si la séquence et ses paramètres peuvent être écrits dans le fichier de sortie
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

                    //on passe au chromosome suivant et on change le chromosome courant (en ayant au préalable supprimé le signe '>')
                    chromo_name = line;
                    chromo_name.erase(0,1);
                    chromosome_name = chromo_name;
                    current_pos_in_chr = 0;

                    //on remet à 0 la séquence courante de chromosome
                    chromo_seq = "";
                }

                    //si c'est une encore séquence, on l'ajoute (dans le cas ou la séq chromosomique est écrite sur plusieurs lignes)
                else
                {
                    chromo_seq += line;
                }


            }
            //pour prendre la dernière ligne du fichier
			
			if(chromo_seq.size() >= seq_size)
			{
            //tant qu'on n'est pas à la fin du chromosome ATTENTION CAR IL SE PEUT QUIL Y AIT UNE COMPARAISON AVEC UN NB NEGATIF
            while(current_pos_in_chr <= (chromo_seq.size()- seq_size) )
            
            {

                            //on extrait une séquence d'une longueur donnée (attribut se(la fonction extract_seq la stocke dans l'objet Sequence,
                            //initialise la position courant ++1)
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
        //on ferme les fichiers
        file_input.close();
        file_output.close();
   
}
