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
    const CellMatrix& get_body() const;
    std::vector<std::size_t> get_tops() const noexcept;
    bool is_touching_tetrimino(const Tetrimino& tetrinino) noexcept;
    void pile(const Tetrimino& tetrinino);
    std::vector<std::size_t> get_clearable_lines() const;

  private:
    CellMatrix body_;
};

#endif  // INCLUDED_PILE_HPP
