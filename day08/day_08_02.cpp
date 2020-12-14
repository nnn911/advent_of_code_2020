#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <cstdlib>
#include <utility>

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

  std::pair<int, char> find_loop(std::vector<Instruction> &program)
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
      if (pos == program.end())
        return std::make_pair(acc, 1);
    }
    return std::make_pair(acc, 0);
  }

  void reset_visited(std::vector<Instruction> &program)
  {
    for (auto &p : program)
      p.visited = 0;
  }

  int fix_loop(std::vector<Instruction> &program)
  {
    INST prev_inst;
    std::pair<int, char> ret_val;
    for (auto it = program.begin(); it != program.end(); ++it)
    {
      switch (it->op)
      {
      case JMP:
        prev_inst = JMP;
        it->op = NOP;
        break;
      case ACC:
        prev_inst = ACC;
        break;
      case NOP:
        prev_inst = NOP;
        it->op = JMP;
        break;
      }
      reset_visited(program);
      ret_val = find_loop(program);
      if (ret_val.second == 1)
        return ret_val.first;
      it->op = prev_inst;
    }
    return 0; // this should never be reached
  }

  int provided_test_02()
  {
    std::vector<Instruction> program{parse_program("day_08_01_test.data")};
    std::cout << "Test case 1 target: 8" << '\n';
    return fix_loop(program);
  }
} // namespace

int main()
{
  {
    auto result{provided_test_02()};
    std::cout << "Test case 2 result: " << result << '\n';
  }

  {
    std::string fname{"day_08_01.data"};
    std::vector<Instruction> program{parse_program(fname)};
    std::cout << "Accumulator after fix in: " << fname << " is " << fix_loop(program) << '\n';
  }
  return EXIT_SUCCESS;
}