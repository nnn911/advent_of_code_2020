#include <string>
#include <array>
#include <cstdlib>
#include <vector>
#include <regex>
#include <cassert>

struct Rule
{
  std::string name;
  std::array<int, 2> range;
};

class Rules
{
private:
  std::vector<Rule> m_rules{};

public:
  Rules() = default;
  ~Rules() = default;

  void add_field(std::string const &line);
  bool validate_number(int const &number) const;
};

void Rules::add_field(std::string const &line)
{
  std::smatch match;
  const std::regex match_name = std::regex{"^(\\w+):"};
  std::regex_search(line, match, match_name);

  const std::regex match_range = std::regex{"(\\d+)-(\\d+)"};
  auto match_begin = std::sregex_iterator(line.begin() + match[1].str().size(),
                                          line.end(), match_range);
  auto match_end = std::sregex_iterator();
  for (auto m = match_begin; m != match_end; m++)
  {
    m_rules.push_back(Rule{match[1].str(),
                           std::array<int, 2>{std::stoi((*m)[1].str()),
                                              std::stoi((*m)[2].str())}});
  }
}

bool Rules::validate_number(int const &number) const
{
  for (auto const &r : m_rules)
  {
    if ((number >= r.range[0]) && (number <= r.range[1]))
      return true;
  }
  return false;
}
