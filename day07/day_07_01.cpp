#include <cstdlib>
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <deque>

namespace
{
  struct Edge
  {
    std::string target;
    int weight;
  };

  struct Bag
  {
    std::string color;
    std::vector<Edge> to{};
    std::vector<Edge> from{};
  };

  auto find_string_bagVec(std::vector<Bag> const &rules, std::string const &toFind)
  {
    return std::find_if(std::begin(rules), std::end(rules), [&toFind](Bag const &a) { return a.color == toFind; });
  }

  void add_line_to_maps(std::string const &line, std::vector<Bag> &rules)
  {
    static const auto target_match = std::regex{"^(\\w+ \\w+)"};
    static const auto contain_match = std::regex{"(\\d+) (\\w+ \\w+)"};
    std::smatch matches;

    std::regex_search(line, matches, target_match);
    auto bag = find_string_bagVec(rules, matches[1].str());
    if (bag == rules.end())
    {
      rules.push_back(Bag{matches[1].str()});
    }
    auto pos = find_string_bagVec(rules, matches[1].str()); // This second search is mega inefficient
    auto searchStart(matches.suffix().first);
    while (std::regex_search(searchStart, line.end(), matches, contain_match))
    {
      rules[pos - rules.begin()].to.push_back(Edge{matches[2].str(), std::stoi(matches[1].str())});
      searchStart = matches.suffix().first;
    }
  }

  void add_reverse_edges(std::vector<Bag> &rules)
  {
    for (auto &r : rules)
    {
      for (auto &b : r.to)
      {
        auto pos = find_string_bagVec(rules, b.target);
        rules[pos - rules.begin()].from.push_back(Edge{r.color, 1});
      }
    }
  }

  const auto parse_rules(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    std::vector<Bag> rules;

    while (std::getline(file, line))
    {
      add_line_to_maps(line, rules);
    }
    add_reverse_edges(rules);
    return rules;
  }

  void add_all_to_queue(std::deque<Edge> &queue, std::vector<Edge> const &vec)
  {
    for (auto const &t : vec)
    {
      queue.push_back(t);
    }
  }

  const size_t count_froms(std::vector<Bag> &rules, std::string const &bagName)
  {
    std::deque<Edge> queue{};
    auto pos = find_string_bagVec(rules, bagName);
    size_t count{0};
    for (auto &r : rules)
    {
      if (r.color == bagName)
        continue;
      queue.clear();
      pos = find_string_bagVec(rules, r.color);
      add_all_to_queue(queue, rules[pos - rules.begin()].to);
      while (queue.size() > 0)
      {
        if (queue[0].target == bagName)
        {
          count += 1;
          break;
        }
        auto pos = find_string_bagVec(rules, queue[0].target);
        add_all_to_queue(queue, rules[pos - rules.begin()].to);
        queue.pop_front();
      }
    }
    return count;
  }

  size_t provided_test_01()
  {
    auto rules{parse_rules("day_07_01_test.data")};
    std::cout << "Test case 1 target: 4" << '\n';
    return count_froms(rules, "shiny gold");
  }

} // namespace

int main()
{
  {
    const size_t result{provided_test_01()};
    std::cout << "Test case 1 result: " << result << '\n';
  }
  {
    std::string fname{"day_07_01.data"};
    auto rules{parse_rules(fname)};
    std::cout << "bags leading to shiny gold in: " << fname << " are " << count_froms(rules, "shiny gold") << '\n';
  }
  return EXIT_SUCCESS;
}