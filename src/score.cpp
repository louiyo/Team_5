// utilise les attributs threshold_, seqSize_, score_ et matrix_ de la classe Matrix

#include <cmath>
#include <string>
#include <array>

bool fwdscore (std::string seq);
bool revscore (std::string seq);



bool fwdscore (std::string seq)
{
	double res(0);

	for (size_t i(0); i < seqSize_; ++i)
	{
		switch(seq[i]) {
			case ('A') : res += 2 + log2(matrix_[i][0]);
						break;

			case ('C') : res += 2 + log2(matrix_[i][1]);
						break;

			case ('G') : res += 2 + log2(matrix_[i][2]);
						break;

			case ('T') : res += 2 + log2(matrix_[i][3]);
						break;

			default : /*throw std::runtime_error("NUCLEOTIDE");*/ break;
		}
	}
	
	if (res >= threshold_)
		{
			score_ = res;
			return true;
		}
	else return false;
}



bool revscore (std::string seq)
{
	double res(0);

	for (size_t i(seqSizq_ -1 ); i >= 0; --i)
	{
		switch(seq[i]) {
			case ('A') : res += 2 + log2(matrix_[i][3]);
						break;

			case ('C') : res += 2 + log2(matrix_[i][2]);
						break;

			case ('G') : res += 2 + log2(matrix_[i][1]);
						break;

			case ('T') : res += 2 + log2(matrix_[i][0]);
						break;

			default : /*throw std::runtime_error("NUCLEOTIDE");*/ break;
		}
	}

	if (res >= threshold_)
		{
			score_ = res;
			return true;
		}
	else return false;
}
