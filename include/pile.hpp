#ifndef INCLUDED_PILE_HPP
#define INCLUDED_PILE_HPP

#include <vector>
#include <cell.hpp>

class Tetrimino;

class Pile
{
  public:
    Pile() noexcept;
    Pile(CellMatrix&& cells) noexcept;
    const CellMatrix& get_data() const;
    std::vector<std::size_t> get_tops() const noexcept;
    void pile(const Tetrimino& tetrinino);

  private:
    CellMatrix body_;
};

#endif  // INCLUDED_PILE_HPP
