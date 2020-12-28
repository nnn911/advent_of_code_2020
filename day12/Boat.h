#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cassert>

enum Direction
{
  North,
  East,
  South,
  West,
  NUM_DIRECTIONS
};

enum Rotation
{
  Left,
  Right,
};

class Boat
{
private:
  void m_read_file(std::string const &fname);
  void m_apply_direction(Direction direction, int distance);
  void m_apply_rotation(Rotation rotation, int angle);

  Direction m_direction{East};
  int m_north{0};
  int m_south{0};
  int m_east{0};
  int m_west{0};

public:
  Boat(std::string const &fname);
  ~Boat();
  size_t get_manhattan_distance() const;
};

void Boat::m_apply_direction(Direction direction, int distance)
{
  switch (direction)
  {
  case North:
    m_north += distance;
    break;
  case South:
    m_south += distance;
    break;
  case East:
    m_east += distance;
    break;
  case West:
    m_west += distance;
    break;
  case NUM_DIRECTIONS:
    assert(!"Invalid Direction enum value");
  }
}

void Boat::m_apply_rotation(Rotation rotation, int angle)
{
  angle = angle % 360; // warp angles greater than 360 degrees
  size_t increment = 360 / NUM_DIRECTIONS;
  switch (rotation)
  {
  case Left:
    m_direction = static_cast<Direction>((m_direction - (angle / increment)) % NUM_DIRECTIONS);
    break;
  case Right:
    m_direction = static_cast<Direction>((m_direction + (angle / increment)) % NUM_DIRECTIONS);
    break;
  default:
    break;
  }
}

void Boat::m_read_file(std::string const &fname)
{
  std::string line;
  std::ifstream file(fname);
  while (std::getline(file, line))
  {
    if (line.empty())
      continue;
    else if (line[0] == 'N')
      m_apply_direction(North, std::stoi(line.substr(1, std::string::npos)));
    else if (line[0] == 'S')
      m_apply_direction(South, std::stoi(line.substr(1, std::string::npos)));
    else if (line[0] == 'E')
      m_apply_direction(East, std::stoi(line.substr(1, std::string::npos)));
    else if (line[0] == 'W')
      m_apply_direction(West, std::stoi(line.substr(1, std::string::npos)));
    else if (line[0] == 'F')
      m_apply_direction(m_direction, std::stoi(line.substr(1, std::string::npos)));
    else if (line[0] == 'L')
      m_apply_rotation(Left, std::stoi(line.substr(1, std::string::npos)));
    else if (line[0] == 'R')
      m_apply_rotation(Right, std::stoi(line.substr(1, std::string::npos)));
  }
}

size_t Boat::get_manhattan_distance() const
{
  return std::abs(m_east - m_west) + std::abs(m_north - m_south);
}

Boat::Boat(std::string const &fname)
{
  m_read_file(fname);
}

Boat::~Boat()
{
}