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
