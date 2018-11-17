#include "Genome_analyser.h"
#include "Sequence.h"
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

TEST(SequenceTest, /* ...*/)
{
}
