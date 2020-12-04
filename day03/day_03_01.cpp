#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include "Tree_map.h"

namespace
{
  int provided_test_01()
  {
    auto map = std::make_unique<Tree_map>("day_03_01_test.data");
    std::cout << "Test case 1 target: 7" << '\n';
    return map->accumulate_path(1, 3);
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
    std::cout << "Total trees hit in: " << fname << " is " << map->accumulate_path(1, 3) << '\n';
  }
  return EXIT_SUCCESS;
}