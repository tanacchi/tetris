#include <cell.hpp>
#include <iterator>

Cell::Cell(bool is_present) noexcept
  : is_present_{is_present}
{
}

Cell::operator bool() const noexcept
{
  return is_present_;
}

void Cell::activate() noexcept
{
  is_present_ = true;
}

void Cell::kill() noexcept
{
  is_present_ = false;
}

char Cell::to_char() const noexcept
{
  return is_present_ ? 'X' : ' ';
}
