#include <string>
#include <cstdlib>

#include "Boat.h"

namespace
{
  size_t provided_test_01()
  {
    std::cout << "Test case 1 target: 25" << '\n';
    Boat boat{"day_12_01_test.data"};
    return boat.get_manhattan_distance();
  }
} // namespace

int main()
{

  {
    size_t res{provided_test_01()};
    std::cout << "Test case 1 result: " << res << '\n';
  }

  {
    std::string fname{"day_12_01.data"};
    Boat boat{fname};
    std::cout << "Stable travel distance from: " << fname << " is " << boat.get_manhattan_distance() << '\n';
  }
  return EXIT_SUCCESS;
}