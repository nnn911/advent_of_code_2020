#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <iostream>

class Game
{
private:
  void add_number(size_t number);

  std::unordered_map<size_t, std::array<size_t, 2>> m_turns{};
  size_t m_last_number;
  size_t m_current_turn{1};

public:
  Game(std::vector<size_t> const &start_values);
  ~Game() = default;

  void take_turn();
  size_t get_current_turn() const { return m_current_turn; };
  size_t get_last_number() const { return m_last_number; };
};

void Game::add_number(size_t number)
{
  auto pos{m_turns.find(number)};
  if (pos == m_turns.end())
    m_turns.emplace(number, std::array<size_t, 2>{0, m_current_turn});
  else
  {
    std::swap(m_turns[number][0], m_turns[number][1]);
    m_turns[number][1] = m_current_turn;
  }
  m_last_number = number;
}

void Game::take_turn()
{
  auto pos{m_turns.find(m_last_number)};
  if ((pos == m_turns.end()) || (pos->second[0] == 0))
  {
    m_last_number = 0;
    add_number(m_last_number);
  }
  else
  {
    m_last_number = ((pos->second.end()[-1]) - (pos->second.end()[-2]));
    add_number(m_last_number);
  }
  m_current_turn++;
}

Game::Game(std::vector<size_t> const &start_values)
{
  for (auto const n : start_values)
  {
    m_last_number = n;
    add_number(n);
    m_current_turn++;
  }
}

namespace
{
  size_t run_game(std::vector<size_t> const &start_values, const size_t num_turns)
  {
    Game game{start_values};
    for (size_t i{game.get_current_turn() - 1}; i != num_turns; ++i)
      game.take_turn();
    return game.get_last_number();
  }

  size_t provided_test_01()
  {
    std::cout << "Test case 1 target: 175594" << '\n';
    return run_game(std::vector<size_t>{0, 3, 6}, 30000000);
  }
  size_t provided_test_02()
  {
    std::cout << "Test case 2 target: 2578" << '\n';
    return run_game(std::vector<size_t>{1, 3, 2}, 30000000);
  }
  size_t provided_test_03()
  {
    std::cout << "Test case 3 target: 3544142" << '\n';
    return run_game(std::vector<size_t>{2, 1, 3}, 30000000);
  }
  size_t provided_test_04()
  {
    std::cout << "Test case 4 target: 261214" << '\n';
    return run_game(std::vector<size_t>{1, 2, 3}, 30000000);
  }
  size_t provided_test_05()
  {
    std::cout << "Test case 5 target: 6895259" << '\n';
    return run_game(std::vector<size_t>{2, 3, 1}, 30000000);
  }
  size_t provided_test_06()
  {
    std::cout << "Test case 6 target: 18" << '\n';
    return run_game(std::vector<size_t>{3, 2, 1}, 30000000);
  }
  size_t provided_test_07()
  {
    std::cout << "Test case 7 target: 362" << '\n';
    return run_game(std::vector<size_t>{3, 1, 2}, 30000000);
  }
} // namespace

int main()
{
  {
    size_t res{provided_test_01()};
    std::cout << "Test case 1 result: " << res << '\n';
  }
  {
    size_t res{provided_test_02()};
    std::cout << "Test case 2 result: " << res << '\n';
  }
  {
    size_t res{provided_test_03()};
    std::cout << "Test case 3 result: " << res << '\n';
  }
  {
    size_t res{provided_test_04()};
    std::cout << "Test case 4 result: " << res << '\n';
  }
  {
    size_t res{provided_test_05()};
    std::cout << "Test case 5 result: " << res << '\n';
  }
  {
    size_t res{provided_test_06()};
    std::cout << "Test case 6 result: " << res << '\n';
  }
  {
    size_t res{provided_test_07()};
    std::cout << "Test case 7 result: " << res << '\n';
  }

  {
    std::cout << "Result of sequence 0,6,1,7,2,19,20: "
              << run_game(std::vector<size_t>{0, 6, 1, 7, 2, 19, 20}, 30000000) << '\n';
  }
  return EXIT_SUCCESS;
}