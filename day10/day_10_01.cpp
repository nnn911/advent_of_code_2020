#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <cstdlib>
#include <cassert>

namespace
{
  std::vector<int> parse_data(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    std::vector<int> adapters_vec{0};
    while (std::getline(file, line))
    {
      adapters_vec.push_back(std::stoi(line));
    }
    std::sort(adapters_vec.begin(), adapters_vec.end());
    adapters_vec.push_back(adapters_vec.back() + 3);
    return adapters_vec;
  }

  size_t eval_chain(std::vector<int> const &chain)
  {
    size_t delta1{0};
    size_t delta3{0};
    for (auto pos{chain.begin() + 1}; pos != chain.end(); pos++)
    {
      if ((*pos - *(pos - 1)) == 1)
        delta1 += 1;
      else if ((*pos - *(pos - 1)) == 3)
        delta3 += 1;
    }
    return delta1 * delta3;
  }

  size_t provided_test_00()
  {
    std::vector<int> chain{parse_data("day_10_01_test_01.data")};
    std::cout << "Test case 0 target: 35" << '\n';
    return eval_chain(chain);
  }

  size_t provided_test_01()
  {
    std::vector<int> chain{parse_data("day_10_01_test_02.data")};
    std::cout << "Test case 0 target: 220" << '\n';
    return eval_chain(chain);
  }
} // namespace

int main()
{

  {
    auto res{provided_test_00()};
    std::cout << "Test case 0 result: " << res << '\n';
  }
  {
    auto res{provided_test_01()};
    std::cout << "Test case 1 result: " << res << '\n';
  }

  {
    std::string fname{"day_10_01.data"};
    std::vector<int> chain{parse_data(fname)};
    std::cout << "Chain descriptor from: " << fname << " is " << eval_chain(chain) << '\n';
  }
  return EXIT_SUCCESS;
}