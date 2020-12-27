#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

enum Seat
{
  Floor,
  Occ,
  Empty,
  Null
};

typedef std::vector<Seat> fparr;

class Floor_plan
{
private:
  void m_read_file(std::string const &fname);
  char m_convert_rep(Seat const s) const;
  void m_pushback_neigh(fparr &vec, Seat seat) const;

  size_t m_rows;
  size_t m_cols;
  fparr m_floor_plan;

public:
  Floor_plan(std::string const &fname);
  ~Floor_plan() = default;

  void apply_rules();
  size_t count_occupied() const;
  void set(size_t row, size_t col, Seat val);
  Seat get(size_t row, size_t col) const;
  Seat get_safely(size_t row, size_t col) const;
  fparr get_neighbors(size_t row, size_t col) const;
  void print() const;
};

Floor_plan::Floor_plan(std::string const &fname)
{
  m_read_file(fname);
}

void Floor_plan::m_read_file(std::string const &fname)
{
  size_t rows{0};
  size_t cols{0};

  std::string line;
  std::ifstream file(fname);
  while (std::getline(file, line))
  {
    for (auto c : line)
    {
      if (rows == 0)
        cols += 1;
      if (c == 'L')
        m_floor_plan.push_back(Empty);
      else if (c == '.')
        m_floor_plan.push_back(Floor);
      else if (c == '#')
        m_floor_plan.push_back(Occ);
    }
    rows += 1;
  }
  m_rows = rows;
  m_cols = cols;
}

void Floor_plan::set(size_t row, size_t col, Seat val)
{
  m_floor_plan[row * m_cols + col] = val;
};

Seat Floor_plan::get(size_t row, size_t col) const
{
  return m_floor_plan[row * m_cols + col];
};

Seat Floor_plan::get_safely(size_t row, size_t col) const
{
  if ((row >= 0) && (row < m_rows) && (col >= 0) && (col < m_cols))
    return m_floor_plan[row * m_cols + col];
  else
    return Null;
};

void Floor_plan::m_pushback_neigh(fparr &vec, Seat seat) const
{
  if (seat != Null)
    vec.push_back(seat);
}

fparr Floor_plan::get_neighbors(size_t row, size_t col) const
{
  fparr ret;
  ret.reserve(8);
  m_pushback_neigh(ret, get_safely(row - 1, col - 1));
  m_pushback_neigh(ret, get_safely(row - 1, col));
  m_pushback_neigh(ret, get_safely(row - 1, col + 1));
  m_pushback_neigh(ret, get_safely(row, col - 1));
  m_pushback_neigh(ret, get_safely(row, col + 1));
  m_pushback_neigh(ret, get_safely(row + 1, col - 1));
  m_pushback_neigh(ret, get_safely(row + 1, col));
  m_pushback_neigh(ret, get_safely(row + 1, col + 1));
  return ret;
}

void Floor_plan::print() const
{
  for (size_t r{0}; r != m_rows; ++r)
  {
    for (size_t c{0}; c != m_cols; ++c)
    {
      std::cout << m_convert_rep(get(r, c));
    }
    std::cout << '\n';
  }
}

char Floor_plan::m_convert_rep(Seat const s) const
{
  switch (s)
  {
  case Empty:
    return 'L';
  case Floor:
    return '.';
  case Occ:
    return '#';
  default:
    return '-';
  }
}

void Floor_plan::apply_rules()
{
  fparr tmp;
  tmp.reserve(m_floor_plan.size());
  fparr neigh;
  Seat seat;
  for (size_t r{0}; r != m_rows; ++r)
  {
    for (size_t c{0}; c != m_cols; ++c)
    {
      // print();
      // std::cout << ' ';
      seat = get(r, c);
      if (seat == Empty)
      {
        neigh = get_neighbors(r, c);
        if (std::count(neigh.begin(), neigh.end(), Occ) == 0)
          tmp.push_back(Occ);
        else
          tmp.push_back(seat);
      }
      else if (seat == Occ)
      {
        neigh = get_neighbors(r, c);
        if (std::count(neigh.begin(), neigh.end(), Occ) >= 4)
          tmp.push_back(Empty);
        else
          tmp.push_back(seat);
      }
      else
        tmp.push_back(seat);
    }
  }
  m_floor_plan = std::move(tmp);
}

size_t Floor_plan::count_occupied() const
{
  return std::count(m_floor_plan.begin(), m_floor_plan.end(), Occ);
}
