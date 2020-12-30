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
    std::string m_mask{};

  public:
    Mask() = default;
    ~Mask() = default;

    void set_mask(std::string const &mask);
    void apply_mask(std::string &memory);
  };

  void Mask::set_mask(std::string const &mask)
  {
    m_mask = mask;
  }

  void Mask::apply_mask(std::string &memory)
  {
    assert(memory.size() == m_mask.size());
    for (size_t i{0}; i != m_mask.size(); i++)
    {
      if (m_mask.begin()[i] == '1')
        memory.begin()[i] = '1';
      else if (m_mask.begin()[i] == 'X')
        memory.begin()[i] = 'X';
    }
  }

  std::vector<std::string> resolve_x(std::string const &address)
  {
    std::deque<std::string> queue;
    std::vector<std::string> addresses{};
    queue.push_back(address);
    size_t pos;
    std::string tmp;
    while (!queue.empty())
    {
      tmp = queue.front();

      pos = tmp.find('X');
      if (pos != std::string::npos)
      {
        tmp.begin()[pos] = '0';
        queue.push_back(tmp);
        tmp.begin()[pos] = '1';
        queue.push_back(std::move(tmp));
      }
      else
        addresses.push_back(tmp);

      queue.pop_front();
    }
    return addresses;
  }

  auto read_file(std::string const &fname)
  {
    std::ifstream file(fname);
    std::string line;

    Mask mask{};
    std::map<unsigned long, unsigned long> memory{};

    std::smatch matches;
    auto const mask_match = std::regex{"mask = (\\w+)"};
    auto const mem_match = std::regex{"mem\\[(\\d+)\\] = (\\d+)"};

    unsigned long key_ul;
    std::string key_str;
    std::vector<std::string> key_arr;
    while (std::getline(file, line))
    {
      if (std::regex_search(line, matches, mask_match))
        mask.set_mask(matches[1].str());
      else if (std::regex_search(line, matches, mem_match))
      {
        key_str = std::bitset<BITLENGTH>{std::stoul(matches[1].str())}.to_string();
        mask.apply_mask(key_str);
        key_arr = resolve_x(key_str);
        for (auto const &k : key_arr)
        {
          key_ul = std::stoul(k, nullptr, 2);
          memory.erase(key_ul);
          memory.emplace(key_ul, std::stoul(matches[2].str()));
        }
      }
    }
    return memory;
  }

  unsigned long evaluate_program(std::map<unsigned long, unsigned long> const &memory)
  {
    unsigned long ret{0};
    for (auto const &[key, value] : memory)
    {
      ret += value;
    }
    return ret;
  }

  unsigned long provided_test_02()
  {
    std::cout << "Test case 1 target: 208" << '\n';
    auto const memory{read_file("day_14_02_test.data")};
    return evaluate_program(memory);
  }
} // namespace

int main()
{

  {
    unsigned long res{provided_test_02()};
    std::cout << "Test case 2 result: " << res << '\n';
  }

  {
    std::string fname{"day_14_01.data"};
    auto const memory{read_file(fname)};
    std::cout << "Final values in memory: " << fname << " is " << evaluate_program(memory) << '\n';
  }
  return EXIT_SUCCESS;
}