#include "Grosse_classe.h"

#include <string>
#include <fstream>

void reader_writer()
{
    //on ouvre le fichier file_in qui est un attribut de la Grosse classe
    std::ifstream file_input(file_in.c_str());
    if(file_input.fail())
    { std::cerr << "Erreur d'ouverture du fichier"; }

    //on ouvre le fichier file_out qui est le fichier d'output
    std::ofstream file_output(file_out.c_str());
    if(file_output.fail())
    { std::cerr << "Erreur d'ouverture du fichier"; }


    else
    {
        std::string chromo_name, chromo_seq, line;

        if(file_input.is_open())
        {
            while(std::getline(file_input, line))
            {

                // si la ligne est un nom de chromosome, on stocke le nom dans l'attribut chromosome de l'attribut Sequence
                //on traite la séquence chromosique complète qui vient d'être extraite
                if(line[0] == '>')
                {

                    //si on a déjà une chromo_seq et qu'on est retourné à '>', alors c'est la fin du chromosome :
                    //on peut commencer a découper la ligne extraite
                    if(chromo_seq.size() != 0)
                    {
                        //tant qu'on n'est pas à la fin du chromosome -> PAULINE JAI MODIFIE LA CONDITION DE FIN DE LECTURE :)
                        while(seq.getPosition() < (chromo_seq.size()-mat.getSeqLength()) )

                            //on extrait une séquence d'une longueur donnée par celle stockée dans la matrice (la fonction extract_seq la stocke dans l'objet Sequence,
                            //initialise la position courant ++1)
                            extract_seq(chromo_seq, mat.getSeqLength());

                        //on discrimine si la séquence et ses paramètres peuvent être écrits dans le fichier de sortie
                        if(mat.reverse_score(seq.getSequence))
                        {
                            write_seq(file_output, false);
                        }

                        if(mat.forward_score(seq.getSequence))
                        {
                            write_seq(file_output);
                        }

                    }

                    //on passe au chromosome suivant et on change le chromosome courant (en ayant au préalable supprimé le signe '>')
                    chromo_name = line;
                    chromo_name.erase(0,1);
                    seq.change_chromosome(chromo_name);

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

            //tant qu'on n'est pas à la fin du chromosome
            while(seq.getPosition() < (chromo_seq.size()-mat.getSeqLength()) )

                //on extrait une séquence d'une longueur donnée par celle stockée dans la matrice (la fonction extract_seq la stocke dans l'objet Sequence,
                //initialise la position courant ++1)
                extract_seq(chromo_seq, mat.getSeqLength());

            //on discrimine si la séquence et ses paramètres peuvent être écrits dans le fichier de sortie
            if(mat.reverse_score(seq.getSequence))
            {
                write_seq(file_output, false);
            }

            if(mat.forward_score(seq.getSequence))
            {
                write_seq(file_output);
            }


        }
        //on ferme les fichiers
        file_input.close();
        file_output.close();
    }
}
