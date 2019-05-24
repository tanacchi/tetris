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

const CellMatrix& Pile::get_data() const
{
  return body_;
}

std::vector<std::size_t> Pile::get_tops() const noexcept
{
  std::vector<std::size_t> result(body_[0].size());
  for (auto itr{std::begin(body_)}, end{std::end(body_)}; itr != end; ++itr)
  {
    for (std::size_t x{0ul}, size{itr->size()}; x < size; ++x)
    {
      if (result[x] == 0ul && (*itr)[x])
      {
        result[x] = std::distance(std::begin(body_), itr);
      }
    }
  }
  return result;
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
