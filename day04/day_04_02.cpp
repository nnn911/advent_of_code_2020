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

  int validate_items(std::vector<key_value_pair> &passpt)
  {
    static const std::vector<std::string> req_fields{"byr", "ecl", "eyr", "hcl", "hgt", "iyr", "pid"};
    static const std::vector<std::string> opt_fields{"cid"};

    if (passpt.size() < req_fields.size())
      return false;

    std::vector<std::string> keys{};
    for (const auto &e : passpt)
      keys.push_back(e.key);
    std::sort(keys.begin(), keys.end());
    return std::includes(keys.begin(), keys.end(), req_fields.begin(), req_fields.end());
  }

  int validate_byr(const key_value_pair &pair)
  {
    int yr{std::stoi(pair.value)};
    return ((yr >= 1920) && (yr <= 2002)) ? 1 : 0;
  }

  int validate_iyr(const key_value_pair &pair)
  {
    int yr{std::stoi(pair.value)};
    return ((yr >= 2010) && (yr <= 2020)) ? 1 : 0;
  }

  int validate_eyr(const key_value_pair &pair)
  {
    int yr{std::stoi(pair.value)};
    return ((yr >= 2020) && (yr <= 2030)) ? 1 : 0;
  }

  int validate_hgt(const key_value_pair &pair)
  {
    if (pair.value.size() < 3)
      return 0;
    int hgt{std::stoi(pair.value.substr(0, pair.value.size() - 2))};
    if (pair.value.substr(pair.value.size() - 2) == "cm")
      return ((hgt >= 150) && (hgt <= 193)) ? 1 : 0;
    else if (pair.value.substr(pair.value.size() - 2) == "in")
      return ((hgt >= 59) && (hgt <= 76)) ? 1 : 0;
    else
      return 0;
  }

  int validate_hcl(const key_value_pair &pair)
  {
    static const auto hcl_match = std::regex{"^#[0-9a-f]{6}"};
    if (std::regex_match(pair.value, hcl_match))
      return 1;
    else
      return 0;
  }

  int validate_ecl(const key_value_pair &pair)
  {
    static const std::vector<std::string> valid_values{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    auto pos{std::find(valid_values.begin(), valid_values.end(), pair.value)};
    if (pos != valid_values.end())
      return 1;
    else
      return 0;
  }

  int validate_pid(const key_value_pair &pair)
  {
    static const auto pid_match = std::regex{"^[0-9]{9}"};
    if (std::regex_match(pair.value, pid_match))
      return 1;
    else
      return 0;
  }

  int validate_entry(const key_value_pair &pair)
  {
    // cannot switch based on strings
    if (pair.key == "byr")
      return validate_byr(pair);
    else if (pair.key == "iyr")
      return validate_iyr(pair);
    else if (pair.key == "eyr")
      return validate_eyr(pair);
    else if (pair.key == "hgt")
      return validate_hgt(pair);
    else if (pair.key == "hcl")
      return validate_hcl(pair);
    else if (pair.key == "ecl")
      return validate_ecl(pair);
    else if (pair.key == "pid")
      return validate_pid(pair);
    else if (pair.key == "cid")
      return 1;
    else
      return 0;
  }

  int validate(std::vector<key_value_pair> &passpt)
  {
    if (!validate_items(passpt))
      return 0;
    int retval;
    for (const auto &p : passpt)
    {
      retval = validate_entry(p);
      // std::cout << retval << ' ' << p.key << ' ' << p.value << std::endl;
      if (!retval)
        return 0;
    }
    return 1;
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

  size_t provided_test_02()
  {
    std::cout << "validate_byr: " << validate_byr(key_value_pair{"byr", "2002"}) << " target: 1\n";
    std::cout << "validate_byr: " << validate_byr(key_value_pair{"byr", "2003"}) << " target: 0\n";

    std::cout << "validate_iyr: " << validate_iyr(key_value_pair{"iyr", "2020"}) << " target: 1\n";
    std::cout << "validate_iyr: " << validate_iyr(key_value_pair{"iyr", "2021"}) << " target: 0\n";

    std::cout << "validate_eyr: " << validate_eyr(key_value_pair{"eyr", "2030"}) << " target: 1\n";
    std::cout << "validate_eyr: " << validate_eyr(key_value_pair{"eyr", "2031"}) << " target: 0\n";

    std::cout << "validate_hgt: " << validate_hgt(key_value_pair{"hgt", "190cm"}) << " target: 1\n";
    std::cout << "validate_hgt: " << validate_hgt(key_value_pair{"hgt", "194cm"}) << " target: 0\n";
    std::cout << "validate_hgt: " << validate_hgt(key_value_pair{"hgt", "60in"}) << " target: 1\n";
    std::cout << "validate_hgt: " << validate_hgt(key_value_pair{"hgt", "190in"}) << " target: 0\n";
    std::cout << "validate_hgt: " << validate_hgt(key_value_pair{"hgt", "190"}) << " target: 0\n";

    std::cout << "validate_hcl: " << validate_hcl(key_value_pair{"hcl", "#123abc"}) << " target: 1\n";
    std::cout << "validate_hcl: " << validate_hcl(key_value_pair{"hcl", "#123abz"}) << " target: 0\n";
    std::cout << "validate_hcl: " << validate_hcl(key_value_pair{"hcl", "123abc"}) << " target: 0\n";

    std::cout << "validate_ecl: " << validate_ecl(key_value_pair{"ecl", "brn"}) << " target: 1\n";
    std::cout << "validate_ecl: " << validate_ecl(key_value_pair{"ecl", "wat"}) << " target: 0\n";

    std::cout << "validate_pid: " << validate_pid(key_value_pair{"pid", "000000001"}) << " target: 1\n";
    std::cout << "validate_pid: " << validate_pid(key_value_pair{"pid", "0123456789"}) << " target: 0\n";

    const size_t num_valid{parse_passwd_batch("day_04_02_test.data")};
    std::cout << "Test case 2 target: 4" << '\n';
    return num_valid;
  }
} // namespace

int main()
{
  {
    const size_t result{provided_test_02()};
    std::cout << "Test case 2 result: " << result << '\n';
  }

  {
    std::string fname{"day_04_01.data"};
    std::cout << "Total valid in: " << fname << " is " << parse_passwd_batch(fname) << '\n';
  }

  return EXIT_SUCCESS;
}