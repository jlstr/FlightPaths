#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./../headers/graph_builder.h"
using namespace std;
using ::testing::ElementsAre;
using ::testing::UnorderedElementsAre;

class GraphBuilderTest: public ::testing::Test {
protected:
  vector<vector<int>> cost_matrix;
  vector<string> cities;

  void SetUp() override {
    cost_matrix = {
      { 0, 15, 80, 90 },
      { 0,  0, 40, 50 },
      { 0,  0,  0, 70 },
      { 0,  0,  0,  0 },
    };

    cities = { "Castle Black", "Winterfell", "Riverrun", "King's Landing" };
  }

  Graph assemble() {
    return GraphBuilder::assemble(cost_matrix, cities);
  }
};

TEST_F(GraphBuilderTest, AssemblesCorrectGraphWithFourCities) {
  Graph graph = assemble();

  ASSERT_EQ(graph.size(), 3);

  EXPECT_THAT(graph["Castle Black"], ElementsAre(
    make_pair(string("Winterfell"), 15),
    make_pair(string("Riverrun"), 80),
    make_pair(string("King's Landing"), 90)
  ));

  EXPECT_THAT(graph["Winterfell"], ElementsAre(
    make_pair(string("Riverrun"), 40),
    make_pair(string("King's Landing"), 50)
  ));

  EXPECT_THAT(graph["Riverrun"], ElementsAre(
    make_pair(string("King's Landing"), 70)
  ));

  EXPECT_EQ(graph.count("King's Landing"), 0);
}

TEST_F(GraphBuilderTest, EmptyInputProducesEmptyGraph) {
  cost_matrix.clear();
  cities.clear();

  Graph graph = assemble();
  EXPECT_TRUE(graph.empty());
}

TEST_F(GraphBuilderTest, SingleCityProducesEmptyGraph) {
  cost_matrix = { { 0 } };
  cities = { "Tokyo" };

  Graph graph = assemble();
  EXPECT_TRUE(graph.empty());
}

TEST_F(GraphBuilderTest, NoEdgesWhenMatrixIsZeroExceptDiagonal) {
  cost_matrix = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 }
  };

  cities = { "Paris", "New York", "London" };

  Graph graph = assemble();
  EXPECT_TRUE(graph.empty());
}

TEST_F(GraphBuilderTest, ThrowsWhenMatrixRowsDoNotMatchCityCount) {
  cost_matrix = {
    { 0, 10, 20 }, 
    { 0,  0, 30 }
  };

  cities = { "Bogotá", "Medellín" };

  EXPECT_THROW({
    assemble();
  }, runtime_error);
}