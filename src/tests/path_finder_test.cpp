#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./../headers/path_finder.h"
using namespace std;

class PathFinderTest : public ::testing::Test {
protected:
  Graph graph;

  void SetUp() override {
    graph = {
      { "Castle Black", { { "Winterfell", 15 }, { "Riverrun", 80 } } },
      { "Winterfell", { { "Riverrun", 40 }, { "King's Landing", 50 } } },
      { "Riverrun", { { "King's Landing", 70 } } },
      { "King's Landing", {} }
    };
  }
};

TEST_F(PathFinderTest, FindsAllPathsBetweenTwoCities) {
  PathFinder finder(graph);
  auto paths = finder.solve("Castle Black", "King's Landing");

  std::vector<std::pair<std::string, int>> expected = {
    { "Castle Black -> Winterfell -> King's Landing", 65 },
    { "Castle Black -> Winterfell -> Riverrun -> King's Landing", 125 },
    { "Castle Black -> Riverrun -> King's Landing", 150 }
  };

  auto sort_fn = [](const auto& a, const auto& b) {
    return a.first < b.first || (a.first == b.first && a.second < b.second);
  };

  std::sort(paths.begin(), paths.end(), sort_fn);
  std::sort(expected.begin(), expected.end(), sort_fn);

  EXPECT_EQ(paths, expected);
}


TEST_F(PathFinderTest, HandlesCaseInsensitivityInCityNames) {
  PathFinder finder(graph);
  auto paths = finder.solve("castle black", "king's landing");

  EXPECT_FALSE(paths.empty()); // Just ensuring case-insensitivity works
}

TEST_F(PathFinderTest, ReturnsSinglePathWhenOnlyOneExists) {
  Graph g = {
    { "A", { { "B", 1 } } },
    { "B", { { "C", 2 } } },
    { "C", {} }
  };

  PathFinder finder(g);
  auto paths = finder.solve("A", "C");

  ASSERT_EQ(paths.size(), 1);
  EXPECT_EQ(paths[0], make_pair(string("A -> B -> C"), 3));
}

TEST_F(PathFinderTest, ReturnsEmptyWhenNoPathExists) {
  Graph g = {
    { "A", { { "B", 1 } } },
    { "B", {} },
    { "C", {} }
  };

  PathFinder finder(g);
  auto paths = finder.solve("A", "C");

  EXPECT_TRUE(paths.empty());
}

TEST_F(PathFinderTest, ThrowsWhenCityNotFound) {
  PathFinder finder(graph);

  EXPECT_THROW(finder.solve("Atlantis", "Winterfell"), runtime_error);
  EXPECT_THROW(finder.solve("Castle Black", "El Dorado"), runtime_error);
}
