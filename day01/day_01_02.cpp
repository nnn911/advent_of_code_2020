
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace
{
  template <typename T>
  void print_iterable(T const &vec)
  {
    for (const auto &a : vec)
      std::cout << a << '\n';
  }

  // it would be nice if this could read not only ints but all datatypes
  std::vector<int> read_from_file(std::string const &fname)
  {
    std::string line;
    // it would be nice to preallocate
    std::vector<int> input;

    std::ifstream file(fname);
    while (std::getline(file, line))
    {
      input.push_back(std::stoi(line));
    }
    return input;
  }

  // modifies T1
  template <typename T1, typename T2>
  auto clean_vector(T1 &vec, T2 sum)
  {
    std::sort(vec.begin(), vec.end());

    // purge elements greater than desired max value
    auto lower = std::lower_bound(vec.begin(), vec.end(), sum);
    vec.erase(lower, vec.end());

    // remove duplicates
    auto uni = std::unique(vec.begin(), vec.end());
    vec.erase(uni, vec.end());
    return vec;
  }

  template <typename T1, typename T2>
  auto find_pair(T1 &vec, T2 sum)
  {
    for (auto a = vec.begin(); a != (vec.end() - 1); ++a)
    {
      // explicit nested loop over std::for_each so it can break early
      for (auto b = (a + 1); b != vec.end(); ++b)
      {
        if ((*a + *b) == sum)
          return *a * *b;
        else if ((*a + *b) > sum)
          continue;
      }
    }
    return -1;
  }

  template <typename T1, typename T2>
  auto find_triplet(T1 &vec, T2 sum)
  {
    for (auto a = vec.begin(); a != (vec.end() - 2); ++a)
    {
      // explicit nested loop over std::for_each so it can break early
      for (auto b = (a + 1); b != vec.end() - 1; ++b)
      {
        for (auto c = (b + 1); c != vec.end(); ++c)
        {
          if ((*a + *b + *c) == sum)
            return *a * *b * *c;
          else if ((*a + *b + *c) > sum)
            continue;
        }
      }
    }
    return -1;
  }

  auto provided_test_01()
  {
    std::cout << "Running test case 1" << '\n';
    std::vector<int> input{1721, 979, 366, 299, 675, 1456};
    int target_value{2020};
    input = clean_vector(input, target_value);
    std::cout << "Test case 1 target: 514579" << '\n';
    return find_pair(input, target_value);
  }

  auto provided_test_02()
  {
    std::cout << "Running test case 2" << '\n';
    std::vector<int> input{1721, 979, 366, 299, 675, 1456};
    int target_value{2020};
    input = clean_vector(input, target_value);
    std::cout << "Test case 2 target: 241861950" << '\n';
    return find_triplet(input, target_value);
  }
} // namespace

int main()
{
  {
    auto result{provided_test_01()};
    std::cout << "Test case 1 result: " << result << '\n';
  }

  {
    std::string fname{"day_01_01.data"};
    int target_value{2020};
    std::vector<int> input_vector{read_from_file(fname)};
    input_vector = clean_vector(input_vector, target_value);
    std::cout << "Pair product from file: " << fname << " is " << find_pair(input_vector, target_value) << '\n';
  }

  {
    auto result{provided_test_02()};
    std::cout << "Test case 2 result: " << result << '\n';
  }

  {
    std::string fname{"day_01_01.data"};
    int target_value{2020};
    std::vector<int> input_vector{read_from_file(fname)};
    input_vector = clean_vector(input_vector, target_value);
    std::cout << "Triplet product from file: " << fname << " is " << find_triplet(input_vector, target_value) << '\n';
  }
  return EXIT_SUCCESS;
}