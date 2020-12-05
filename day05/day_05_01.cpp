#include <cstdlib>
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

namespace
{
  struct boardingPass
  {
    size_t row;
    size_t seat;
  };

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

  const size_t get_seatID(boardingPass const &bp)
  {
    return bp.row * 8 + bp.seat;
  }

  template <typename T>
  const size_t get_seatID(T const &row, T const &seat)
  {
    return row * 8 + seat;
  }

  const std::vector<boardingPass> parse_boarding_passes(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    std::vector<boardingPass> bps{};
    while (std::getline(file, line))
    {
      bps.push_back(boardingPass{get_row(line), get_seat(line)});
    }
    return bps;
  }

  void provided_test_01()
  {
    auto bps{parse_boarding_passes("day_05_01_test.data")};

    std::cout << "Test case 1\nTarget:\n44 5 357\n70 7 567\n14 7 119\n102 4 820\nResult:\n";
    for (const auto &bp : bps)
    {
      std::cout << bp.row << " " << bp.seat << " " << get_seatID(bp) << '\n';
    }
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
} // namespace

int main()
{
  {
    provided_test_01();
  }

  {
    std::string fname{"day_05_01.data"};
    std::cout << "Maximum seat id in: " << fname << " is " << find_max_seatID(fname) << '\n';
  }
  return EXIT_SUCCESS;
}