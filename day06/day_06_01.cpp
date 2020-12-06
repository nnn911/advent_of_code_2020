#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

namespace
{
  const size_t count_unique(std::string &group)
  {
    std::sort(group.begin(), group.end());
    auto uniq = std::unique(group.begin(), group.end());
    return std::distance(group.begin(), uniq);
  }

  const size_t read_customs_data(std::string const &fname)
  {
    std::string line;
    std::string group;
    std::ifstream file(fname);
    size_t count{0};
    while (std::getline(file, line))
    {
      if (line.empty())
      {
        count += count_unique(group);
        group.clear();
      }
      else
        group.append(line);
    }
    count += count_unique(group);
    return count;
  }

  const size_t provided_test_01()
  {
    std::cout << "Test case 1 target: 11" << '\n';
    return read_customs_data("day_06_01_test.data");
  }
} // namespace

int main()
{
  {
    auto result{provided_test_01()};
    std::cout << "Test case 1 result: " << result << '\n';
  }

  {
    std::string fname{"day_06_01.data"};
    std::cout << "Total number of unique 'yes' in: " << fname << " is " << read_customs_data(fname) << '\n';
  }
  return EXIT_SUCCESS;
}