#include <pile.hpp>

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
  const auto& body_height{body_.size()};
  std::vector<std::size_t> result{body_[0].size()};
  for (auto itr{std::begin(body_)}, end{std::end(body_)}; itr != end; ++itr)
  {
    for (std::size_t x{0ul}, size{itr->size()}; x < size; ++x)
    {
      if (result[x] != body_height && (*itr)[x])
      {
        result[x] = std::distance(std::begin(body_), itr);
      }
    }
  }
  return result;
}
