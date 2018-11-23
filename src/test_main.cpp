#include "Genome_analyser.h"
#include "Sequence.hpp"
#include <gtest/gtest.h>

using namespace std;


Genome_analyser analyser("promoters.fasta", "DBP.mat", 0.11);

TEST(Genome_anaylserTest, sequence_handling) {

analyser.extract_seq("ATTGCCAT", 7);
EXPECT_EQ("ATTGCCA", analyser.get_seq());
EXPECT_EQ("TGGCAAT", analyser.revert_seq("ATTGCCA"));
	
}

TEST(Genome_analyserTest, read_write) {
	
	analyser.reader(); //est ce qu'on est obligé de le faire
	//utiliser la fonction qui lit le bed pour comparer notre output a celui demandé

}

Sequence seq("DBP.mat");

TEST(SequenceTest, matrix_construction)
{
	vector<array<double, 4>> matrix_test = {{0.991265586410457, 0.00188241672188422, 0.00438979579543401, 0.00246220107222457},
													  {0.00454038913318475, 0.00308716342389013, 0.961116800192759, 0.0312556472501656},
													  {0.00319260279955123, 0.991529060968172, 0.00188243089596181, 0.0033959053363151},
													  {0.891738449490994, 0.00188241672188422, 0.00883982892596831, 0.0975393048611529},
													  {0.624171736642371, 0.251091801698693, 0.00595596650804169, 0.118780495150895},
													  {0.728886814047346, 0.10454942473345, 0.0115881573399193, 0.154975603879284},
													  {0.304793385940606, 0.491122522739594, 0.00446509246430938, 0.199618998855491}};
	for (int i=0; i<7; ++i) {
		for (int j=0; j<4; ++j) {
			EXPECT_EQ(seq.get_matrix()[i][j], matrix_test[i][j]);
		}
	}
}
