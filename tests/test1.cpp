#include <Point.h>
#include <Contender.h>
#include <DataLog.h>
#include <iostream>
#include <string>
#include <gtest/gtest.h>


class ContenderTest : public ::testing::Test
{
protected:

	void SetUp() override {
		pop_size = 4;
		std::string TestData = "C:\\dev\\cppTSP\\Resources\\DataSets\\circ100.txt";
		Contender::Points = ReadDataFile(TestData);
		
		for (int i = 0; i < pop_size; i++)
		{
			population.push_back(Contender());
		}
		
	}

	std::vector<Contender> population;
	int pop_size;

	void PerfectTwo()
	{
		for (int i = 0; i < population[2].GetSize(); i++)
			population[2].SetPriority(i, i);
		population[2].CalcFitness();
	}

};

/// <summary>
/// This test is for the facets of Evaluations
///		1. Able to retrieve value
///		2. Goes up each time Path_length is calculated
///		3. Goes up whenver ANY contender evaluates path length
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST_F(ContenderTest, EvalCount)
{
	// Able to retrieve evaluations value
	ASSERT_EQ(Contender::GetEvalCount(), pop_size);
	//for(int i < )

	// Goes up each time Path_Length is calculated
	for (int i = 0; i < 10; i++)
		population[0].CalcFitness();
	ASSERT_EQ(Contender::GetEvalCount(), pop_size + 10);

	for (int i = 0; i < pop_size; i++)
		population[i].CalcFitness();
	ASSERT_EQ(Contender::GetEvalCount(), 2 * pop_size + 10);
}


TEST_F(ContenderTest, CopyConstructor)
{
	population[0] = population[1];

	// Track priorities
	for (int i = 0; i < population[0].GetSize(); i++)
		ASSERT_EQ(population[0].GetPriority(i), population[1].GetPriority(i)) << "Priorities failed to copy";
	
	// Copied Fitness
	ASSERT_EQ(population[0].GetFitness(), population[1].GetFitness()) << "Fitness failed to copy";

	// Verify not pointing to the same object
	ASSERT_NE(&population[0], &population[1]) << "Not different pointers";

}


TEST_F(ContenderTest, ComparisonOperator)
{
	PerfectTwo();
	EXPECT_TRUE(population[1].GetFitness() > population[2].GetFitness()) << Contender::Points.size() << " " << population[1].GetFitness() << " " << population[2].GetFitness();

}


TEST_F(ContenderTest, RandomRouteGenerator)
{
	PerfectTwo();

	int count = 0;
	for (int i = 0; i < population[0].GetSize(); i++)
		if (population[0].GetPriority(i) == population[2].GetPriority(i))
			count++;
	ASSERT_TRUE(count < population[0].GetSize());
}

TEST_F(ContenderTest, CalcFitness)
{
	PerfectTwo();
	ASSERT_EQ(3.8265130362463426, population[2].GetFitness());
}

TEST_F(ContenderTest, Crossover)
{
	Contender::Crossover(population[0], population[1], population[2], population[3]);

	for (int i = 0; i < Contender::Points.size(); i++)
	{
		if (population[0].GetPriority(i) != population[2].GetPriority(i))
		{
			ASSERT_EQ(population[0].GetPriority(i), population[3].GetPriority(i)) << "Pareent A did not get copied at " << i;
			ASSERT_EQ(population[1].GetPriority(i), population[2].GetPriority(i)) << "Pareent B did not get copied at "  << i;
		}
		else
		{
			//std::cout << "0:" << population[0].GetPriority(i) << " 2:" << population[2].GetPriority(i) << " 1:" << population[1].GetPriority(i) << " 3:" << population[3].GetPriority(i) << std::endl;
			ASSERT_EQ(population[1].GetPriority(i), population[3].GetPriority(i)) << "Parent B did not get copied at " << i;
		}
	}

}
