#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

namespace
{
  struct Boat
  {
    int x{0};
    int y{0};
  };

  struct Waypoint
  {
    int x{10};
    int y{1};
  };

  void apply_left_rotation(Waypoint &wp, int angle)
  {
    // angle = angle % 360;
    int tmp_x;
    int tmp_y;
    switch (angle)
    {
    case 0:
      tmp_x = wp.x;
      tmp_y = wp.y;
      break;
    case 90:
      tmp_x = -wp.y;
      tmp_y = wp.x;
      break;
    case 180:
      tmp_x = -wp.x;
      tmp_y = -wp.y;
      break;
    case 270:
      tmp_x = wp.y;
      tmp_y = -wp.x;
      break;
    default:
      tmp_x = wp.x;
      tmp_y = wp.y;
      break;
    }
    wp.x = tmp_x;
    wp.y = tmp_y;
  }

  void apply_right_rotation(Waypoint &wp, int angle)
  {
    // angle = angle % 360;
    int tmp_x;
    int tmp_y;
    switch (angle)
    {
    case 0:
      tmp_x = wp.x;
      tmp_y = wp.y;
      break;
    case 90:
      tmp_x = wp.y;
      tmp_y = -wp.x;
      break;
    case 180:
      tmp_x = -wp.x;
      tmp_y = -wp.y;
      break;
    case 270:
      tmp_x = -wp.y;
      tmp_y = wp.x;
      break;
    default:
      tmp_x = wp.x;
      tmp_y = wp.y;
      break;
    }
    wp.x = tmp_x;
    wp.y = tmp_y;
  }

  Boat read_file(std::string const &fname)
  {
    Waypoint wp;
    Boat boat;

    std::string line;
    std::ifstream file(fname);
    int factor;
    while (std::getline(file, line))
    {
      if (line.empty())
        continue;
      else if (line[0] == 'N')
        wp.y += std::stoi(line.substr(1, std::string::npos));
      else if (line[0] == 'S')
        wp.y -= std::stoi(line.substr(1, std::string::npos));
      else if (line[0] == 'E')
        wp.x += std::stoi(line.substr(1, std::string::npos));
      else if (line[0] == 'W')
        wp.x -= std::stoi(line.substr(1, std::string::npos));
      else if (line[0] == 'L')
        apply_left_rotation(wp, std::stoi(line.substr(1, std::string::npos)));
      else if (line[0] == 'R')
        apply_right_rotation(wp, std::stoi(line.substr(1, std::string::npos)));
      else if (line[0] == 'F')
      {
        factor = std::stoi(line.substr(1, std::string::npos));
        boat.x += factor * wp.x;
        boat.y += factor * wp.y;
      }
    }
    return boat;
  }

  size_t get_manhattan_distance(Boat const &boat)
  {
    return std::abs(boat.x) + std::abs(boat.y);
  }

  size_t provided_test_02()
  {
    std::cout << "Test case 2 target: 286" << '\n';
    Boat boat{read_file("day_12_01_test.data")};
    return get_manhattan_distance(boat);
  }
} // namespace

int main()
{

  {
    size_t res{provided_test_02()};
    std::cout << "Test case 2 result: " << res << '\n';
  }

  {
    std::string fname{"day_12_01.data"};
    Boat boat{read_file(fname)};
    std::cout << "Stable travel distance from: " << fname << " is " << get_manhattan_distance(boat) << '\n';
  }
  return EXIT_SUCCESS;
}