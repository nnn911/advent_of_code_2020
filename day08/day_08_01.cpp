#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <cstdlib>

namespace
{
  enum INST
  {
    ACC,
    JMP,
    NOP
  };
  struct Instruction
  {
    INST op;
    int arg;
    char visited{0};
  };

  void parse_instruction(std::string const &line, std::vector<Instruction> &program)
  {
    static const auto regex = std::regex{"^(\\w+) ([+-]?\\d+)"};
    std::smatch match;
    std::regex_match(line, match, regex);
    if (match[1].str() == "acc")
      program.push_back(Instruction{ACC, std::stoi(match[2].str())});
    else if (match[1].str() == "jmp")
      program.push_back(Instruction{JMP, std::stoi(match[2].str())});
    else if (match[1].str() == "nop")
      program.push_back(Instruction{NOP, 0});
  }

  std::vector<Instruction> parse_program(std::string const &fname)
  {
    std::string line;
    std::ifstream file(fname);
    std::vector<Instruction> program;

    while (std::getline(file, line))
    {
      parse_instruction(line, program);
    }
    return program;
  }

  int find_loop(std::vector<Instruction> &program)
  {
    int acc{0};
    auto pos{program.begin()};
    while (program[pos - program.begin()].visited == 0)
    {
      program[pos - program.begin()].visited = 1;
      switch (program[pos - program.begin()].op)
      {
      case ACC:
        acc += program[pos - program.begin()].arg;
        pos += 1;
        break;
      case JMP:
        pos += program[pos - program.begin()].arg;
        break;
      case NOP:
        pos += 1;
      }
    }
    return acc;
  }

  size_t provided_test_01()
  {
    std::vector<Instruction> program{parse_program("day_08_01_test.data")};
    std::cout << "Test case 1 target: 5" << '\n';
    return find_loop(program);
  }
} // namespace

int main()
{
  {
    auto result{provided_test_01()};
    std::cout << "Test case 1 result: " << result << '\n';
  }

  {
    std::string fname{"day_08_01.data"};
    std::vector<Instruction> program{parse_program(fname)};
    std::cout << "Value in accumulated in: " << fname << " is " << find_loop(program) << '\n';
  }
  return EXIT_SUCCESS;
}