#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

namespace
{
  struct Schedule
  {
    int depart;
    std::vector<int> times{};
  };

  struct Bus
  {
    int id;
    int wait;
  };

  Schedule read_file(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);

    std::getline(file, line);
    Schedule schedule{std::stoi(line)};

    std::smatch match;
    const std::regex match_int = std::regex{"\\d+"};

    std::getline(file, line);

    auto match_begin = std::sregex_iterator(line.begin(), line.end(), match_int);
    auto match_end = std::sregex_iterator();
    for (auto m = match_begin; m != match_end; m++)
    {
      schedule.times.push_back(std::stoi((*m).str()));
    }
    return schedule;
  }

  Bus find_bus(Schedule const &schedule)
  {
    int id;
    int best_delta{schedule.depart};
    int delta;
    for (auto t : schedule.times)
    {
      delta = t - (schedule.depart % t);
      if (delta < best_delta)
      {
        best_delta = delta;
        id = t;
      }
    }
    return Bus{id, best_delta};
  }

  size_t provided_test_01()
  {
    std::cout << "Test case 1 target: 295" << '\n';
    Schedule schedule{read_file("day_13_01_test.data")};
    Bus best_bus{find_bus(schedule)};
    return best_bus.wait * best_bus.id;
  }
} // namespace

int main()
{

  {
    size_t res{provided_test_01()};
    std::cout << "Test case 1 result: " << res << '\n';
  }

  {
    std::string fname{"day_13_01.data"};
    Schedule schedule{read_file(fname)};
    Bus best_bus{find_bus(schedule)};
    std::cout << "Best bus to take from: " << fname << " is " << best_bus.wait * best_bus.id << '\n';
  }
  return EXIT_SUCCESS;
}