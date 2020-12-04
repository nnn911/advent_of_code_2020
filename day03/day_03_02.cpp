#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include "Tree_map.h"

namespace
{
  struct slope
  {
    int right;
    int down;
  };

  int provided_test_01()
  {
    auto map = std::make_unique<Tree_map>("day_03_01_test.data");
    std::cout << "Test case 1 target: 7" << '\n';
    return map->accumulate_path(1, 3);
  }

  int provided_test_02()
  {
    std::vector<slope> slopes{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    auto map = std::make_unique<Tree_map>("day_03_01_test.data");
    std::cout << "Test case 2 target: 336" << '\n';
    size_t product{1};
    for (auto &s : slopes)
      product *= map->accumulate_path(s.down, s.right);
    return product;
  }
} // namespace

int main()
{
  {
    auto result{provided_test_01()};
    std::cout << "Test case 1 result: " << result << '\n';
  }

  {
    std::string fname{"day_03_01.data"};
    auto map = std::make_unique<Tree_map>(fname);
    std::cout << "Total trees hit in 1: " << fname << " is " << map->accumulate_path(1, 3) << '\n';
  }

  {
    auto result{provided_test_02()};
    std::cout << "Test case 2 result: " << result << '\n';
  }

  {
    std::vector<slope> slopes{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    std::string fname{"day_03_01.data"};
    auto map = std::make_unique<Tree_map>(fname);
    size_t product{1};
    for (auto &s : slopes)
      product *= map->accumulate_path(s.down, s.right);
    std::cout << "Total trees hit in 2: " << fname << " is " << product << '\n';
  }
  return EXIT_SUCCESS;
}