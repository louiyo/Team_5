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

analyser.extract_seq("ATTNCCATTAGATCCAGATCNNATG", 7);
EXPECT_EQ(analyser.get_seq(), "ATTNCCA");
analyser.extract_seq("ATTNCCATTAGATCCAGATCNNATG", 7);
EXPECT_EQ(analyser.get_seq(), "TTNCCAT");
analyser.revert_seq();
EXPECT_EQ(analyser.get_seq(),"ATGGNAA");
analyser.revert_seq();
EXPECT_EQ(analyser.get_seq(),"TTNCCAT");
	
}

Range range = {{1,4,true},{4,7, false}};
std::vector<Seq> seq; //idem
std::vector<Seq> test_seq = {{"NNG", true},{"CTA", false}};

//Genome_analyser analyser_2 nouveau constructeur
TEST(Genome_analyser, reading) {
	
	seq = analyser.cut_positions(range, gen, 5); 
	EXPECT_EQ(seq, test_seq);
	
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

	seq.set_sequence("ATGCTCC");	//random sequence 1
	EXPECT_NEAR(seq.score_fow(), -16.4759996073, 0.0000000002);

	seq.set_sequence("AtgCTcC");	//random seq 1 w/ lower case nucleotides
	EXPECT_NEAR(seq.score_fow(), -16.4759996073, 0.0000000002);

	seq.set_sequence("atGCtCc");
	EXPECT_NEAR(seq.score_fow(), -16.4759996073, 0.0000000002);

	seq.set_sequence("atgctcc");
	EXPECT_NEAR(seq.score_fow(), -16.4759996073, 0.0000000002);

	seq.set_sequence("GTACTAT");	//random sequence 2
	EXPECT_NEAR(seq.score_fow(), -22.0301617141, 0.0000000002);

	seq.set_sequence("gtActAT");	//random seq 2 w/ lower case nucleotides
	EXPECT_NEAR(seq.score_fow(), -22.0301617141, 0.0000000002);

	seq.set_sequence("NTACTAT");	//seq w/ undetermined nucl(N) in first pos
	EXPECT_NEAR(seq.score_fow(), -16.1985312594, 0.0000000002);

	seq.set_sequence("nTACTAT");	//seq w/ lower case n
	EXPECT_NEAR(seq.score_fow(), -16.1985312594, 0.0000000002);

	seq.set_sequence("nTacTat");
	EXPECT_NEAR(seq.score_fow(), -16.1985312594, 0.0000000002);

	seq.set_sequence("GTANTAT");	//seq w/ N in other random pos
	EXPECT_NEAR(seq.score_fow(), -14.9769634709, 0.0000000002);

	seq.set_sequence("GTACTAN");
	EXPECT_NEAR(seq.score_fow(), -21.7054826557, 0.0000000002);

	seq.set_sequence("GTNNTAN");	//seq w/ multiple Ns
	EXPECT_NEAR(seq.score_fow(), -8.36123320232, 0.0000000002);
	
	seq.set_sequence("AAAAAAA");	//seq w/ 1 type of nucl only
	EXPECT_NEAR(seq.score_fow(), -5.10229832163, 0.0000000002);

	seq.set_sequence("aAaaaAA");
	EXPECT_NEAR(seq.score_fow(), -5.10229832163, 0.0000000002);

	seq.set_sequence("NNNNNNN");	//seq w/ Ns only
	EXPECT_EQ(seq.score_fow(),0);

	seq.set_sequence("ATGCT");		//seq too short
	EXPECT_EQ(seq.score_fow(),0);

	seq.set_sequence("GTACTNTCT");	//seq too long
	EXPECT_EQ(seq.score_fow(),0);

	seq.set_sequence("");			//empty seq
	EXPECT_EQ(seq.score_fow(),0);
}


TEST(test_score_rev, calcul)
{
	Sequence seq("DBP.mat");

	seq.set_sequence("ATGCTCC");
	EXPECT_NEAR(seq.score_rev(), -13.7762893507, 0.0000000002);

	seq.set_sequence("atgCtCC");
	EXPECT_NEAR(seq.score_rev(), -13.7762893507, 0.0000000002);

	seq.set_sequence("AtGCtCc");
	EXPECT_NEAR(seq.score_rev(), -13.7762893507, 0.0000000002);

	seq.set_sequence("CGTAGTC");
	EXPECT_NEAR(seq.score_rev(), -16.729566595, 0.0000000002);

	seq.set_sequence("CGTAGTN");
	EXPECT_NEAR(seq.score_rev(), -10.8979361404, 0.0000000002);

	seq.set_sequence("NGTAGTC");
	EXPECT_NEAR(seq.score_rev(), -10.9224723617, 0.0000000002);

	seq.set_sequence("CGNAGTC");
	EXPECT_NEAR(seq.score_rev(), -18.0495815316, 0.0000000002);

	seq.set_sequence("CNTAGNN");
	EXPECT_NEAR(seq.score_rev(), -3.8572248333, 0.0000000002);

	seq.set_sequence("CNtAgnN");
	EXPECT_NEAR(seq.score_rev(), -3.8572248333, 0.0000000002);

	seq.set_sequence("TTTTTTT");
	EXPECT_NEAR(seq.score_rev(), -5.10229832163, 0.0000000002);

	seq.set_sequence("ttttttt");
	EXPECT_NEAR(seq.score_rev(), -5.10229832163, 0.0000000002);

	seq.set_sequence("NNNNNNN");
	EXPECT_EQ(seq.score_rev(),0);

	seq.set_sequence("CGTA");
	EXPECT_EQ(seq.score_rev(),0);

	seq.set_sequence("TGACTANA");
	EXPECT_EQ(seq.score_rev(),0);

	seq.set_sequence("");
	EXPECT_EQ(seq.score_rev(),0);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
