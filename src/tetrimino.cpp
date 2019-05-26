#include <sstream>
#include <iterator>
#include <tetrimino.hpp>
#include <algorithm>

Tetrimino::Tetrimino() noexcept
  : body_{}
  , pos_{}
{
}

Tetrimino::Tetrimino(CellMatrix&& body)
  : body_{std::move(body)}
  , pos_{}
{
}

Tetrimino::Position::first_type Tetrimino::get_x() const noexcept
{
  return pos_.first;
}

Tetrimino::Position::second_type Tetrimino::get_y() const noexcept
{
  return pos_.second;
}

Tetrimino::Position::first_type Tetrimino::get_right_edge() const noexcept
{
  std::vector<std::size_t> right_edge_postions{};
  for (const auto row : body_)
  {
    const auto last_itr{std::find_if(std::rbegin(row), rend(row), 
        [](const auto& cell){ return static_cast<bool>(cell);})};
    right_edge_postions.emplace_back(std::distance(std::begin(row), last_itr.base()));
  }
  return pos_.first + *std::max_element(std::begin(right_edge_postions), std::end(right_edge_postions));
}

const CellMatrix& Tetrimino::get_body() const
{
  return body_;
}

void Tetrimino::move(Direction direction)
{
  switch (direction)
  {
    case Direction::Up:
      --pos_.second; 
      break;
    case Direction::Down:
      ++pos_.second; 
      break;
    case Direction::Left:
      if (pos_.first > 0)
        --pos_.first;
      break;
    case Direction::Right: 
      if (get_right_edge() < 10)
        ++pos_.first;
      break;
  }
}

std::vector<Tetrimino::Position::second_type> Tetrimino::get_bottoms() const noexcept
{
  const auto body_height{std::size(body_)};
  std::vector<Tetrimino::Position::second_type> result(std::size(body_[0]), body_height);
  for (auto ritr{std::rbegin(body_)}, rend{std::rend(body_)}; ritr != rend; ++ritr)
  {
    for (std::size_t x{0ul}, size{std::size(*ritr)}; x < size; ++x)
    {
      if (result[x] == body_height && (*ritr)[x])
      {
        result[x] = std::distance(std::begin(body_), ritr.base()) - 1;
      }
    }
  }
  return result;
}
