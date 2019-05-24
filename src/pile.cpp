#include <pile.hpp>
#include <tetrimino.hpp>

Pile::Pile() noexcept
  : body_{20ul, CellMatrix::value_type{10ul}}
{
}

Pile::Pile(CellMatrix&& body) noexcept
  : body_{std::move(body)}
{
}

const CellMatrix& Pile::get_body() const
{
  return body_;
}

std::vector<std::size_t> Pile::get_tops() const noexcept
{
  const auto& body_height{body_.size()};
  std::vector<std::size_t> result(body_[0].size(), body_height);
  for (auto itr{std::begin(body_)}, end{std::end(body_)}; itr != end; ++itr)
  {
    for (std::size_t x{0ul}, size{itr->size()}; x < size; ++x)
    {
      if (result[x] == body_height && (*itr)[x])
      {
        result[x] = std::distance(std::begin(body_), itr);
      }
    }
  }
  return result;
}

bool Pile::is_touching_tetrimino(const Tetrimino& tetrimino) noexcept
{
  const auto&& teto_bottoms{tetrimino.get_bottoms()};
  const auto&& pile_tops{get_tops()};
  const auto teto_x{tetrimino.get_x()};
  const auto teto_y{tetrimino.get_y()};
  for (auto x{0ul}, size{teto_bottoms.size()}; x < size; ++x)
  {
    if (pile_tops[x + teto_x] == teto_bottoms[x] + teto_y + 1)
      return true;
  }
  return false;
}

void Pile::pile(const Tetrimino& tetrimino)
{
  const auto& new_body{tetrimino.get_body()};
  const auto& start_x{tetrimino.get_x()};
  const auto& start_y{tetrimino.get_y()};
  for (auto offset_y{0ul}, height{new_body.size()}; offset_y < height; ++offset_y)
  {
    for (auto offset_x{0ul}, width{new_body[offset_y].size()}; offset_x < width; ++offset_x)
    {
      if (new_body[offset_y][offset_x])
        body_[start_y + offset_y][start_x + offset_x].activate();
    }
  }
}
