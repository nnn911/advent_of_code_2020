#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <regex>

namespace
{
  struct key_value_pair
  {
    std::string key;
    std::string value;
  };

  // template <typename T>
  // void print_iterable(T const &vec)
  // {
  //   for (const auto &a : vec)
  //     std::cout << a << '\n';
  // }

  // void print_passpt(std::vector<key_value_pair> const &passpt)
  // {
  //   for (const auto &e : passpt)
  //     std::cout << e.key << " : " << e.value << '\n';
  // }

  static const auto key_value_match = std::regex{"(\\S+):(\\S+)"};
  auto split_string(std::string const &line)
  {
    std::smatch matches;
    auto searchStart(line.begin());
    std::vector<key_value_pair> dict{};
    while (std::regex_search(searchStart, line.end(), matches, key_value_match))
    {
      dict.push_back(key_value_pair{matches[1].str(), matches[2].str()});
      searchStart = matches.suffix().first;
    }
    // return std::move(dict);
    return dict;
  }

  int validate(std::vector<key_value_pair> &passpt)
  {
    static const std::vector<std::string> req_fields{"byr", "ecl", "eyr", "hcl", "hgt", "iyr", "pid"};
    static const std::vector<std::string> opt_fields{"cid"};
    std::vector<std::string> keys{};
    for (const auto &e : passpt)
      keys.push_back(e.key);
    std::sort(keys.begin(), keys.end());
    // std::sort(passpt.begin(), passpt.end(), [](key_value_pair const &a, key_value_pair const &b) { return a.key < b.key;});
    // there should be some way add a lambda here to make include possible usings passpt and req_files for comparison
    // similar to the sort above
    // this would remove the need for a keys vector -.-
    return std::includes(keys.begin(), keys.end(), req_fields.begin(), req_fields.end());
  }

  const size_t parse_passwd_batch(std::string const &fname)
  {
    std::string line;
    std::vector<key_value_pair> passpt;

    size_t valid{0};
    std::ifstream file(fname);
    while (std::getline(file, line))
    {
      if ((line.empty()) && (passpt.size() != 0))
      {
        valid += validate(passpt);
        passpt.clear();
      }
      else if (passpt.size() == 0)
        passpt = split_string(line);
      else
      {
        auto tmp{split_string(line)};
        passpt.reserve(passpt.size() + tmp.size());
        std::move(tmp.begin(), tmp.end(), std::back_inserter(passpt));
      }
    };
    valid += validate(passpt);
    return valid;
  }

  const size_t provided_test_01()
  {
    const size_t num_valid{parse_passwd_batch("day_04_01_test.data")};
    std::cout << "Test case 1 target: 2" << '\n';
    return num_valid;
  }
} // namespace

int main()
{
  {
    const size_t result{provided_test_01()};
    std::cout << "Test case 1 result: " << result << '\n';
  }

  {
    std::string fname{"day_04_01.data"};
    std::cout << "Total valid in: " << fname << " is " << parse_passwd_batch(fname) << '\n';
  }

  return EXIT_SUCCESS;
}