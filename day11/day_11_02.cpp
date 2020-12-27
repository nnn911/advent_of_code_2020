#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <cstdlib>
#include <cassert>

#include "Floor_plan_02.h"

namespace
{
  size_t converge_seats(Floor_plan &floor_plan)
  {
    size_t prev{floor_plan.count_occupied()};
    size_t curr{0};
    do
    {
      floor_plan.apply_rules();
      prev = curr;
      curr = floor_plan.count_occupied();
    } while (prev != curr);
    return curr;
  }

  size_t provided_test_02()
  {
    std::cout << "Test case 2 target: 26" << '\n';
    Floor_plan floor_plan{"day_11_01_test.data"};
    return converge_seats(floor_plan);
  }
} // namespace

int main()
{

  {
    size_t res{provided_test_02()};
    std::cout << "Test case 2 result: " << res << '\n';
  }

  {
    std::string fname{"day_11_01.data"};
    Floor_plan floor_plan{fname};
    std::cout << "Stable Occ count from: " << fname << " is " << converge_seats(floor_plan) << '\n';
  }
  return EXIT_SUCCESS;
}