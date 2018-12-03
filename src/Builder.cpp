#include "Builder.h"


Builder::Builder(const std::string & matrix_file):
  current_seq(matrix_file), seq_size(current_seq.get_size()) {}
  
 Builder::Builder(const size_t& size):
  current_seq(size), seq_size(size) {}
  
  
  
std::string Builder::revert_seq()
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
	return reverse;
}

std::string Builder::get_seq() const
{
	return current_seq.get_sequence();
}


