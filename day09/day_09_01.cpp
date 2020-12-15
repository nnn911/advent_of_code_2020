#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <cstdlib>
#include <cassert>

namespace
{
  std::vector<long int> parse_data(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    std::vector<long int> data;

    while (std::getline(file, line))
    {
      data.push_back(std::stol(line));
    }
    return data;
  }

  std::pair<long int, char> find_first_missing(std::vector<long int> &data, size_t header)
  {
    long int target;
    long int current;
    char success;
    for (auto t{data.begin() + header}; t != data.end(); ++t)
    {
      success = 0;
      target = data[t - data.begin()];
      for (auto i{t - header}; i != t; i++)
      {
        for (auto j{i + 1}; j != t; j++)
        {
          current = data[i - data.begin()] + data[j - data.begin()];
          if (current == target)
            success = 1;
        }
        if (success)
          continue;
      }
      if (!success)
        return std::make_pair(target, 1);
    }
    return std::make_pair(0, 0);
  }

  size_t provided_test_01()
  {
    std::vector<long int> data{parse_data("day_09_01_test.data")};
    std::cout << "Test case 1 target: 127" << '\n';
    std::pair<long int, char> retval{find_first_missing(data, 5)};
    assert(retval.second == 1);
    return retval.first;
  }
} // namespace

int main()
{
  {
    auto result{provided_test_01()};
    std::cout << "Test case 1 result: " << result << '\n';
  }

  {
    std::string fname{"day_09_01.data"};
    std::vector<long int> data{parse_data(fname)};
    std::pair<long int, char> retval{find_first_missing(data, 25)};
    assert(retval.second == 1);
    std::cout << "First missing number in: " << fname << " is " << retval.first << '\n';
  }
  return EXIT_SUCCESS;
}