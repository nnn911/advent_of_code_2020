#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

namespace
{
  struct Lines
  {
    std::vector<unsigned long long> times{};
    std::vector<unsigned long long> lines{};
    std::vector<unsigned long long> offset{};
  };

  Lines process_times(std::vector<unsigned long long> &times)
  {
    Lines lines{};
    lines.times = std::move(times);
    for (unsigned int i{0}; i < lines.times.size(); i++)
    {
      if (lines.times[i] != 999)
      {
        lines.lines.push_back(lines.times[i]);
        lines.offset.push_back(i);
      }
    }
    return lines;
  }

  Lines read_file(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);

    std::getline(file, line);

    const std::regex match_int = std::regex{"[\\d|x]+"};

    std::getline(file, line);
    std::vector<unsigned long long> times{};

    auto match_begin = std::sregex_iterator(line.begin(), line.end(), match_int);
    auto match_end = std::sregex_iterator();
    for (auto m = match_begin; m != match_end; m++)
    {
      if ((*m).str() == "x")
        times.push_back(999);
      else
        times.push_back(std::stoi((*m).str()));
    }
    Lines lines{process_times(times)};
    return lines;
  }

  unsigned long long align_schedule(Lines const &line, unsigned long long start = 0)
  {
    auto pos{std::max_element(line.lines.begin(), line.lines.end())};
    const unsigned long long step_size{(*pos)};
    const unsigned long long offset{line.offset[std::distance(line.lines.begin(), pos)]};
    unsigned long long time;
    if (start == 0)
      time = step_size;
    else
      time = start;
    unsigned long long match{0};
    size_t counter{0};
    // size_t debug_counter{0};
    do
    {
      counter = 0;
      for (size_t i{0}; i < line.lines.size(); i++)
      {
        match = (time + (line.offset[i] - offset)) % line.lines[i];
        if (match == 0)
          counter += 1;
        else
          break;
      }
      if (counter == (line.offset.size()))
        return time - offset;
      time += step_size;
      // if ((debug_counter++ % 100000000) == 0)
      // std::cout << float(time) / std::numeric_limits<unsigned long long>::max() << std::endl;
    } while (time <= (std::numeric_limits<unsigned long long>::max() - step_size));
    return 0;
  }

  auto provided_test_02_00()
  {
    std::cout << "Test case 2 0 target: 1068781" << '\n';
    Lines lines{read_file("day_13_02_test_00.data")};
    const auto ret{align_schedule(lines)};
    return ret;
  }
  auto provided_test_02_01()
  {
    std::cout << "Test case 2 1 target: 3417" << '\n';
    Lines lines{read_file("day_13_02_test_01.data")};
    const auto ret{align_schedule(lines)};
    return ret;
  }
  auto provided_test_02_02()
  {
    std::cout << "Test case 2 2 target: 754018" << '\n';
    Lines lines{read_file("day_13_02_test_02.data")};
    const auto ret{align_schedule(lines)};
    return ret;
  }
  auto provided_test_02_03()
  {
    std::cout << "Test case 2 3 target: 779210" << '\n';
    Lines lines{read_file("day_13_02_test_03.data")};
    const auto ret{align_schedule(lines)};
    return ret;
  }
  auto provided_test_02_04()
  {
    std::cout << "Test case 2 4 target: 1261476" << '\n';
    Lines lines{read_file("day_13_02_test_04.data")};
    const auto ret{align_schedule(lines)};
    return ret;
  }
  auto provided_test_02_05()
  {
    std::cout << "Test case 2 5 target: 1202161486" << '\n';
    Lines lines{read_file("day_13_02_test_05.data")};
    const auto ret{align_schedule(lines)};
    return ret;
  }

} // namespace

int main()
{

  {
    size_t res{provided_test_02_00()};
    std::cout << "Test case 2 0 result: " << res << '\n';
  }
  {
    size_t res{provided_test_02_01()};
    std::cout << "Test case 2 1 result: " << res << '\n';
  }
  {
    size_t res{provided_test_02_02()};
    std::cout << "Test case 2 2 result: " << res << '\n';
  }
  {
    size_t res{provided_test_02_03()};
    std::cout << "Test case 2 3 result: " << res << '\n';
  }
  {
    size_t res{provided_test_02_04()};
    std::cout << "Test case 2 4 result: " << res << '\n';
  }
  {
    size_t res{provided_test_02_05()};
    std::cout << "Test case 2 5 result: " << res << '\n';
  }
  {
    std::string fname{"day_13_01.data"};
    Lines lines{read_file(fname)};
    std::cout << "It works in theory - but is way too slow!";
    // std::cout << "Processing " << fname << " this may take a while!" << std::endl;
    // unsigned long long start_value{99999999999708};
    // std::cout << "Best bus to take from: " << fname << " is " << align_schedule(lines, start_value) << '\n';
  }
  return EXIT_SUCCESS;
}