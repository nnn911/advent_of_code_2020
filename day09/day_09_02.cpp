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

  long int find_first_missing(std::vector<long int> &data, size_t header)
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
        return data[t - data.begin()];
    }
    return -1;
  }

  long int construct_missing(std::vector<long int> &data, long int target)
  {
    long int current;
    long int low;
    long int high;
    for (auto i{data.begin()}; i != data.end(); ++i)
    {
      current = data[i - data.begin()];
      low = current;
      high = current;
      for (auto j{i + 1}; j != data.end(); ++j)
      {
        current += data[j - data.begin()];
        if (data[j - data.begin()] < low)
          low = data[j - data.begin()];
        else if (data[j - data.begin()] > high)
          high = data[j - data.begin()];
        if (current == target)
          return low + high;
        else if (current > target)
          break;
      }
    }
    return 0;
  }

  long int provided_test_02()
  {
    std::vector<long int> data{parse_data("day_09_01_test.data")};
    size_t header{5};
    auto target{find_first_missing(data, header)};
    assert(target != -1);
    long int sum{construct_missing(data, target)};
    std::cout << "Test case 2 target: 62" << '\n';
    return sum;
  }
} // namespace

int main()
{
  {
    auto result{provided_test_02()};
    std::cout << "Test case 2 result: " << result << '\n';
  }

  {
    std::string fname{"day_09_01.data"};
    std::vector<long int> data{parse_data(fname)};
    size_t header{25};
    auto target{find_first_missing(data, header)};
    assert(target != -1);
    std::cout << "First missing number in: " << fname << " is " << construct_missing(data, target) << '\n';
  }
  return EXIT_SUCCESS;
}