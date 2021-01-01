#include <vector>
#include <string>
#include <regex>

struct Ticket
{
  std::vector<int> numbers{};
};

class Tickets
{
private:
  Ticket m_read_ticket(std::string const &line) const;

  std::vector<Ticket> m_my_tickets{};
  std::vector<Ticket> m_nearby_tickets{};

public:
  Tickets() = default;
  ~Tickets() = default;

  auto const &get_my_tickets() const { return m_my_tickets; };
  auto const &get_nearby_tickets() const { return m_nearby_tickets; };

  void add_nearby_ticket(std::string const &line);
  void add_my_ticket(std::string const &line);
};

Ticket Tickets::m_read_ticket(std::string const &line) const
{
  Ticket ret{};

  const std::regex match_range = std::regex{"(\\d+)"};
  auto match_begin = std::sregex_iterator(line.begin(), line.end(), match_range);
  auto match_end = std::sregex_iterator();
  for (auto m = match_begin; m != match_end; m++)
  {
    ret.numbers.push_back(std::stoi((*m)[1].str()));
  }
  return ret;
}

void Tickets::add_nearby_ticket(std::string const &line)
{
  m_nearby_tickets.push_back(m_read_ticket(line));
}

void Tickets::add_my_ticket(std::string const &line)
{
  m_my_tickets.push_back(m_read_ticket(line));
}