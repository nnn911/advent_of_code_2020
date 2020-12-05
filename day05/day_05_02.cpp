#include <cstdlib>
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <numeric>
#include <algorithm>

namespace
{
  template <typename T>
  void print_iterable(T const &vec)
  {
    for (const auto &a : vec)
      std::cout << a << '\n';
  }

  const size_t get_row(std::string const &line)
  {
    static const auto row_match = std::regex{"[BFbf]+"};
    std::smatch match;
    std::regex_search(line.begin(), line.end(), match, row_match);

    static const auto f_match = std::regex{"[Ff]"};
    static const auto b_match = std::regex{"[Bb]"};
    std::string str{match[0].str()};
    str = std::regex_replace(str, f_match, "0");
    str = std::regex_replace(str, b_match, "1");

    return std::stoi(str, 0, 2);
  }

  const size_t get_seat(std::string const &line)
  {
    static const auto row_match = std::regex{"[lrLR]+"};
    std::smatch match;
    std::regex_search(line.begin(), line.end(), match, row_match);

    static const auto l_match = std::regex{"[Ll]"};
    static const auto r_match = std::regex{"[Rl]"};
    std::string str{match[0].str()};
    str = std::regex_replace(str, l_match, "0");
    str = std::regex_replace(str, r_match, "1");

    return std::stoi(str, 0, 2);
  }

  template <typename T>
  const size_t get_seatID(T const &row, T const &seat)
  {
    return row * 8 + seat;
  }

  const size_t find_max_seatID(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    size_t seatId;
    size_t max_seatId{0};
    while (std::getline(file, line))
    {
      seatId = get_seatID(get_row(line), get_seat(line));
      if (seatId > max_seatId)
        max_seatId = seatId;
    }
    return max_seatId;
  }

  const size_t find_seatIDs(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    std::vector<size_t> seatId{};
    while (std::getline(file, line))
    {
      seatId.push_back(get_seatID(get_row(line), get_seat(line)));
    }
    std::sort(seatId.begin(), seatId.end());
    size_t offset{seatId[0]};
    std::adjacent_difference(seatId.begin(), seatId.end(), seatId.begin());
    auto pos = std::find(seatId.begin(), seatId.end(), 2);
    return std::distance(seatId.begin(), pos) + offset;
  }
} // namespace

int main()
{
  {
    std::string fname{"day_05_01.data"};
    std::cout << "Maximum seat id in: " << fname << " is " << find_max_seatID(fname) << '\n';
  }

  {
    std::string fname{"day_05_01.data"};
    std::cout << "Missing seat id is: " << fname << " is " << find_seatIDs(fname) << '\n';
  }
  return EXIT_SUCCESS;
}