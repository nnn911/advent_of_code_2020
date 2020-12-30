#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <regex>
#include <map>
#include <cassert>
#define BITLENGTH 36

namespace
{
  class Mask
  {
  private:
    std::vector<unsigned int> m_values{};
    std::vector<size_t> m_pos{};
    size_t m_size{};

  public:
    Mask() = default;
    ~Mask() = default;

    void set_mask(std::string const &mask);
    void apply_mask(std::bitset<BITLENGTH> &memory);
  };

  void Mask::set_mask(std::string const &mask)
  {
    m_values.clear();
    m_pos.clear();
    m_size = mask.size();
    for (size_t i{0}; i != mask.size(); i++)
    {
      if (mask[i] != 'X')
      {
        m_pos.push_back(m_size - 1 - i);
        m_values.push_back(mask[i] - 48); // ascii to unsigned int
      }
    }
  }

  void Mask::apply_mask(std::bitset<BITLENGTH> &memory)
  {
    assert(memory.size() == m_size);
    for (size_t i{0}; i != m_pos.size(); i++)
    {
      memory.set(m_pos[i], m_values[i]);
    }
  }

  auto read_file(std::string const &fname)
  {
    std::ifstream file(fname);
    std::string line;

    Mask mask{};
    std::map<int, std::bitset<BITLENGTH>> memory{};

    std::smatch matches;
    auto const mask_match = std::regex{"mask = (\\w+)"};
    auto const mem_match = std::regex{"mem\\[(\\d+)\\] = (\\d+)"};

    int key;
    while (std::getline(file, line))
    {
      if (std::regex_search(line, matches, mask_match))
        mask.set_mask(matches[1].str());
      else if (std::regex_search(line, matches, mem_match))
      {
        key = std::stoi(matches[1].str());
        memory.erase(key);
        memory.emplace(key, std::bitset<BITLENGTH>{std::stoul(matches[2].str())});
        mask.apply_mask(memory[key]);
      }
    }
    return memory;
  }

  unsigned long evaluate_program(std::map<int, std::bitset<BITLENGTH>> const &memory)
  {
    size_t ret{0};
    for (auto const &[key, value] : memory)
    {
      ret += std::stoul(value.to_string(), nullptr, 2);
    }
    return ret;
  }

  unsigned long provided_test_01()
  {
    std::cout << "Test case 1 target: 165" << '\n';
    auto const memory{read_file("day_14_01_test.data")};
    return evaluate_program(memory);
  }
} // namespace

int main()
{

  {
    size_t res{provided_test_01()};
    std::cout << "Test case 1 result: " << res << '\n';
  }

  {
    std::string fname{"day_14_01.data"};
    auto const memory{read_file(fname)};
    std::cout << "Final values in memory: " << fname << " is " << evaluate_program(memory) << '\n';
  }
  return EXIT_SUCCESS;
}