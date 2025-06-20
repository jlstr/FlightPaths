#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "./../headers/data_loader.h"
using namespace std;
namespace fs = filesystem;

class DataLoaderTest: public ::testing::Test {
protected:
  string test_root;

  void SetUp() override {
    test_root = fs::temp_directory_path() / "data_loader_test";
    fs::create_directory(test_root);
  }

  void TearDown() override {
    fs::remove_all(test_root);
  }

  void writeFile(const string& relative_path, const string& content) {
    fs::path full_path = fs::path(test_root) / relative_path;
    fs::create_directories(full_path.parent_path());

    ofstream file(full_path);
    file << content;
  }
};

TEST_F(DataLoaderTest, LoadsValidCitiesAndCostsCorrectly) {
  writeFile("test_data/cities.csv", "Alpha,Beta,Gamma");
  writeFile("test_data/costs.csv",
    "0,1,2\n"
    "0,0,4\n"
    "0,0,0"
  );

  DataLoader loader(test_root);
  vector<string> cities = loader.loadCities();
  vector<vector<int>> costs = loader.loadCosts();

  EXPECT_EQ(cities, vector<string>({ "Alpha", "Beta", "Gamma" }));

  ASSERT_EQ(costs.size(), 3);
  EXPECT_EQ(costs[0], vector<int>({ 0, 1, 2 }));
  EXPECT_EQ(costs[1], vector<int>({ 0, 0, 4 }));
  EXPECT_EQ(costs[2], vector<int>({ 0, 0, 0 }));
}

TEST_F(DataLoaderTest, ThrowsIfCityFileMissing) {
  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCities(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfCostsFileMissing) {
  writeFile("test_data/cities.csv", "A,B");
  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCosts(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfCitiesFileIsEmpty) {
  writeFile("test_data/cities.csv", "");
  writeFile("test_data/costs.csv",
    "0,1,2\n"
    "0,0,3\n"
    "0,0,0"
  );

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCities(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfCostsFileIsEmpty) {
  writeFile("test_data/cities.csv", "A,B,C");
  writeFile("test_data/costs.csv", "");

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCosts(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfCostFileContainsNonNumericData) {
  writeFile("test_data/cities.csv", "A,B,C");
  writeFile("test_data/costs.csv",
    "0,1,X\n"
    "0,0,2\n"
    "0,0,0"
  );

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCosts(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfRowsAreDifferentLengths) {
  writeFile("test_data/cities.csv", "A,B,C");
  writeFile("test_data/costs.csv",
    "0,1,2\n"
    "0,0\n"
    "0,0,0"
  );

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCosts(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfMatrixIsNotSquare) {
  writeFile("test_data/cities.csv", "A,B,C");
  writeFile("test_data/costs.csv",
    "0,1,2\n"
    "0,0,4"
  );

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCosts(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfMatrixIsBiggerThan8x8) {
  writeFile("test_data/cities.csv", "A,B,C,D,E,F,G,H,I");
  writeFile("test_data/costs.csv",
  "0,1,1,1,1,1,1,1,1\n"
  "0,0,1,1,1,1,1,1,1\n"
  "0,0,0,1,1,1,1,1,1\n"
  "0,0,0,0,1,1,1,1,1\n"
  "0,0,0,0,0,1,1,1,1\n"
  "0,0,0,0,0,0,1,1,1\n"
  "0,0,0,0,0,0,0,1,1\n"
  "0,0,0,0,0,0,0,0,1\n"
  "0,0,0,0,0,0,0,0,0"
);

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCosts(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfCitiesAreNotUnique) {
  writeFile("test_data/cities.csv", "Bogota,Medellin,Bogota");
  writeFile("test_data/costs.csv",
    "0,1,2\n"
    "0,0,3\n"
    "0,0,0"
  );

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCities(), runtime_error);
}

TEST_F(DataLoaderTest, ThrowsIfCitiesAreNotUniqueIgnoringCase) {
  writeFile("test_data/cities.csv", "Medellin,Bogota,medellin");
  writeFile("test_data/costs.csv",
    "0,1,2\n"
    "0,0,3\n"
    "0,0,0"
  );

  DataLoader loader(test_root);
  EXPECT_THROW(loader.loadCities(), runtime_error);
}

TEST_F(DataLoaderTest, LoadsUniqueCitiesWithDifferentNames) {
  writeFile("test_data/cities.csv", "Bogota,Medellin,Cali");
  writeFile("test_data/costs.csv",
    "0,1,2\n"
    "0,0,4\n"
    "0,0,0"
  );

  DataLoader loader(test_root);
  EXPECT_NO_THROW(loader.loadCities());
}