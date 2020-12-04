#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class Tree_map
{
private:
  const std::vector<std::string> m_read_from_file(std::string const &fname);
  void m_fill_map(std::vector<std::string> const &map_str);
  const size_t m_wrap_col(size_t col) const;

  size_t m_rows{0};
  size_t m_cols{0};
  std::vector<int> m_map;

public:
  Tree_map(std::string const &fname);
  ~Tree_map() = default;

  void print_map() const;

  int accumulate_path(size_t step_row, size_t step_col, int value) const;
  int accumulate_path_debug(size_t step_row, size_t step_col, int value);
  // this would be better with [] operators
  // TODO: implement pbc along rows !
  void set(size_t row, size_t col, int val);
  int get(size_t row, size_t col) const;
};

Tree_map::Tree_map(std::string const &fname)
{
  std::vector<std::string> map_str{m_read_from_file(fname)};
  m_rows = map_str.size();
  m_cols = map_str[0].length();
  m_map.resize(m_rows * m_cols);
  m_fill_map(map_str);
}

const std::vector<std::string> Tree_map::m_read_from_file(std::string const &fname)
{
  std::string line;
  std::vector<std::string> map;

  std::ifstream file(fname);
  while (std::getline(file, line))
  {
    map.push_back(line);
  };
  return map;
}

void Tree_map::m_fill_map(std::vector<std::string> const &map_str)
{
  for (size_t r{0}; r != m_rows; ++r)
  {
    for (size_t c{0}; c != m_cols; ++c)
    {
      if (map_str[r][c] == '.')
        this->set(r, c, 0);
      else
        this->set(r, c, 1);
    }
  }
}

void Tree_map::print_map() const
{
  for (size_t r{0}; r != m_rows; ++r)
  {
    for (size_t c{0}; c != m_cols; ++c)
    {
      std::cout << this->get(r, c);
    }
    std::cout << '\n';
  }
}

const size_t Tree_map::m_wrap_col(size_t col) const
{
  while (col >= m_cols)
    col -= m_cols;
  return col;
}

void Tree_map::set(size_t row, size_t col, int val)
{
  m_map[row * m_cols + m_wrap_col(col)] = val;
};
int Tree_map::get(size_t row, size_t col) const
{
  return m_map[row * m_cols + m_wrap_col(col)];
};

int Tree_map::accumulate_path(size_t step_row, size_t step_col, int value = 0) const
{
  size_t c{0};
  for (size_t r{0}; r < m_rows; r += step_row)
  {
    value += this->get(r, c);
    c += step_col;
  }
  return value;
}

// int Tree_map::accumulate_path_debug(size_t step_row, size_t step_col, int value = 0)
// {
//   size_t c{0};
//   for (size_t r{0}; r < m_rows; r += step_row)
//   {
//     value += this->get(r, c);
//     this->set(r, c, 5);
//     c += step_col;
//   }
//   this->print_map();
//   return value;
// }
