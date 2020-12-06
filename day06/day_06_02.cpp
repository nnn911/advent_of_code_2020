#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

namespace
{
  void get_intersection(std::string &line, std::string &intersection)
  {
    std::string tmp_str{std::move(intersection)};
    std::sort(line.begin(), line.end());
    std::sort(tmp_str.begin(), tmp_str.end()); // this is somehow necessary even though intersection should be sorted
    intersection.clear();                      // probably unnecessary
    std::set_intersection(line.begin(), line.end(),
                          tmp_str.begin(), tmp_str.end(),
                          std::back_inserter(intersection));
  }

  const size_t read_customs_data(std::string const &fname)
  {
    std::string line;
    std::string intersection;
    std::ifstream file(fname);
    size_t count{0};
    bool newGroup{true};
    while (std::getline(file, line))
    {
      if (line.empty())
      {
        count += intersection.size();
        newGroup = true;
        intersection.clear();
      }
      else if (intersection.empty() & newGroup)
      {
        intersection = std::move(line);
        newGroup = false;
      }
      else
        get_intersection(line, intersection);
    }
    if (line.empty())
      count += intersection.size();
    else
    {
      get_intersection(line, intersection); // this else block is probably never reached
      count += intersection.size();
    }
    return count;
  }

  const size_t provided_test_02()
  {
    std::cout << "Test case 2 target: 6" << '\n';
    return read_customs_data("day_06_01_test.data");
  }
} // namespace

int main()
{
  {
    auto result{provided_test_02()};
    std::cout << "Test case 6 result: " << result << '\n';
  }

  {
    std::string fname{"day_06_01.data"};
    std::cout << "Total number of combined 'yes' in: " << fname << " is " << read_customs_data(fname) << '\n';
  }
  return EXIT_SUCCESS;
}