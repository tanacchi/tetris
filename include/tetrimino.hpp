#ifndef INCLUDED_TETRIMINO_HPP
#define INCLUDED_TETRIMINO_HPP

#include <vector>
#include <cell.hpp>
#include <utility>

enum class Direction : short
{
  Up, Down, Left, Right
};

class Tetrimino
{
  public:
    using Position = std::pair<std::size_t, std::size_t>;

    Tetrimino() noexcept;
    explicit Tetrimino(CellMatrix&& body);  // XXX: Must not be used.
    Position::first_type  get_x() const noexcept;
    Position::second_type get_y() const noexcept;
    Position::first_type get_right_edge() const noexcept;
    const CellMatrix& get_body() const;
    void move(Direction direction);
    std::vector<Position::second_type> get_bottoms() const noexcept;

  private:
    CellMatrix body_;
    Position pos_;
};

const Tetrimino I{{
  {Cell(true), Cell(true), Cell(true), Cell(true)}
}};

const Tetrimino O{{
  {Cell(true), Cell(true)},
  {Cell(true), Cell(true)}
}};

const Tetrimino S{{
  {Cell(false), Cell(true), Cell(true)},
  {Cell(true),  Cell(true), Cell(false)},
}};

const Tetrimino Z{{
  {Cell(true),  Cell(true), Cell(false)},
  {Cell(false), Cell(true), Cell(true)},
}};

const Tetrimino J{{
  {Cell(true), Cell(false), Cell(false)},
  {Cell(true), Cell(true),  Cell(true)},
}};

const Tetrimino L{{
  {Cell(false), Cell(false), Cell(true)},
  {Cell(true),  Cell(true),  Cell(true)},
}};

const Tetrimino T{{
  {Cell(false), Cell(true), Cell(false)},
  {Cell(true),  Cell(true), Cell(true)},
}};

#endif  // INCLUDED_TETRIMINO_HPP
