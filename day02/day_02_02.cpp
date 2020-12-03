#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cstdlib>
#include <numeric>
#include <algorithm>

namespace
{
  struct db_line
  {
    int low;
    int high;
    char letter;
    std::string passwd;
  };

  db_line split_string(std::string const &line)
  {
    const static auto tokens = std::regex{"-| |: "};
    // this has to be slow
    auto const split = std::vector<std::string>(
        std::sregex_token_iterator{line.begin(), line.end(), tokens, -1},
        std::sregex_token_iterator{});
    db_line ret{
        .low = std::stoi(split[0]),
        .high = std::stoi(split[1]),
        .letter = split[2][0],
        .passwd = std::move(split[3]),
    };
    // maybe here hove rvo might not work into vector?
    return ret;
  }

  std::vector<db_line> read_from_file(std::string const &fname)
  {
    std::string line;
    // it would be nice to preallocate
    std::vector<db_line> db;

    std::ifstream file(fname);
    while (std::getline(file, line))
    {
      db.push_back(split_string(line));
    };
    return db;
  }

  auto check_db_line(db_line const &line)
  {
    // line is correct
    // out of bounds check might be goods
    if ((line.passwd[line.low - 1] == line.letter) ^ (line.passwd[line.high - 1] == line.letter))
      return 1;
    else
      return 0;
  }

  auto check_db_file(std::string const &fname)
  {
    std::vector<db_line> db{read_from_file(fname)};
    return std::accumulate(db.begin(), db.end(), 0, [](auto curr, const auto &e) { return curr + check_db_line(e); });
  }

  auto provided_test_02()
  {
    std::vector<db_line> db{read_from_file("day_02_01_test.data")};
    // for (const auto &a : db)
    // print_db_line(a);
    auto total_valid{std::accumulate(db.begin(), db.end(), 0, [](auto curr, const auto &e) { return curr + check_db_line(e); })};
    std::cout << "Test case 2 target: 1" << '\n';
    return total_valid;
  }
} // namespace

int main()
{
  {
    auto result{provided_test_02()};
    std::cout << "Test case 2 result: " << result << '\n';
  }

  {
    // 604 too low (index corrected by +1 instead of -1 in l55)
    // 867 too high (|| instead of xor in l55)
    std::string fname{"day_02_01.data"};
    std::cout << "Total valid in: " << fname << " is " << check_db_file(fname) << '\n';
  }
  return EXIT_SUCCESS;
}