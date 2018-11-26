#include "Genome_analyser.h"
#include "Sequence.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>

using namespace std;

bool reader(std::string in, std::string out)
	{
		std::ifstream input(in.c_str());
		std::ifstream output(out.c_str());
		
		std::string line_in, line_out;
		
		while(std::getline(input, line_in) && std::getline(output, line_out))
			{
				if(line_in.compare(line_out) != 0)
					{ return false; }
			}
		
		return true;
		
	}

Genome_analyser analyser("test.fa", "test.mat", 0.11);

TEST(Genome_anaylserTest, sequence_handling) {

analyser.extract_seq("ATTGCCAT", 7);
EXPECT_EQ(analyser.get_seq(), "ATTGCCA");
analyser.extract_seq("ATTG", 7);
EXPECT_EQ(analyser.get_seq(), "ATTGCCA");
analyser.revert_seq("AtTGCCA");
EXPECT_EQ(analyser.get_seq(),"TGGCAAT");
analyser.revert_seq("ATTGCCN");
EXPECT_EQ(analyser.get_seq(),"NGGCAAT");
	
}

Range range; //a initialiser en fonction du type de structure
vector< array<double,4>> test_mat; //idem

TEST(Genome_analyser, reading) {
	
	//tester le output file d'abord
	analyser.reader_1();
	EXPECT_TRUE(reader("output_file.txt", "test_out.txt"));
	
	analyser.cut_positions(range, "test.fa", 5);
	EXPECT_EQ(test_mat, analyser.get_matrix());
	
	analyser.reader_2();
	EXPECT_TRUE(); //a completer
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

TEST(test_score_fow, calcul)
{
	Sequence seq("DBP.mat");

	seq.set_sequence("ATGCTCC");
	double score = seq.score_fow();
	EXPECT_NEAR(score, -16.4759996073, 0.0000000002);
	
	seq.set_sequence("AAAAAAA");
	score = seq.score_fow();
	EXPECT_NEAR(score, -5.10229832163, 0.0000000002);

	seq.set_sequence("NNNNNNN");
	EXPECT_EQ(seq.score_fow(),0);

	seq.set_sequence("");
	EXPECT_EQ(seq.score_fow(),0);
}


TEST(test_score_rev, calcul)
{
	Sequence seq("DBP.mat");

	seq.set_sequence("ATGCTCC");
	double score = seq.score_rev();
	EXPECT_NEAR(score, -13.7762893507, 0.0000000002);
	
	seq.set_sequence("TTTTTTT");
	score = seq.score_rev();
	EXPECT_NEAR(score, -5.10229832163, 0.0000000002);

	seq.set_sequence("NNNNNNN");
	EXPECT_EQ(seq.score_rev(),0);

	seq.set_sequence("");
	EXPECT_EQ(seq.score_rev(),0);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
