#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Rules.h"
#include "Tickets.h"

namespace
{
  struct Information
  {
    Rules rules;
    Tickets tickets;
  };

  Information read_file(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    char section{0};

    Rules rules{};
    Tickets tickets{};

    while (std::getline(file, line))
    {
      if (line.empty())
        continue;
      else if (line == "your ticket:")
      {
        section = 1;
        continue;
      }
      else if (line == "nearby tickets:")
      {
        section = 2;
        continue;
      }
      switch (section)
      {
      case 0:
        rules.add_field(line);
        break;
      case 1:
        tickets.add_my_ticket(line);
        break;
      case 2:
        tickets.add_nearby_ticket(line);
        break;
      default:
        break;
      }
    }
    return Information{std::move(rules), std::move(tickets)};
  }

  size_t validate_tickets(Information const &info)
  {
    size_t error{0};
    for (const auto &t : info.tickets.get_nearby_tickets())
    {
      for (const auto &n : t.numbers)
      {
        if (!info.rules.validate_number(n))
          error += n;
      }
    }
    return error;
  }

  size_t provided_test_01()
  {
    std::cout << "Test case 1 target: 71" << '\n';
    Information info{read_file("day_16_01_test.data")};
    return validate_tickets(info);
  }
} // namespace

int main()
{
  {
    size_t res{provided_test_01()};
    std::cout << "Test case 1 result: " << res << '\n';
  }

  {
    std::string fname{"day_16_01.data"};
    Information info{read_file(fname)};
    std::cout << "Total reading error in: " << fname << " is " << validate_tickets(info) << '\n';
  }
  return EXIT_SUCCESS;
}