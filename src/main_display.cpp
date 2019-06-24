#include <iterator>
#include <main_display.hpp>

#define HEIGHT 20

MainDisplay::MainDisplay()
  : win_{newwin(22, 12, 0, 0)}
{
}

void MainDisplay::show(const Pile& pile, const Tetrimino& tetrimino) const
{
  wclear(win_.get());
  {
    const auto& body{pile.get_body()};
    for (auto y{0ul}, height{std::size(body)}; y < height; ++y)
    {
      for (auto x{0ul}, width{std::size(body[y])}; x < width; ++x)
      {
        if (body[y][x])
        {
          mvwaddch(win_.get(), y + 1, x + 1, 'X');
        }
      }
    }
  }
  {
    const auto& body{tetrimino.get_body()};
    for (auto y{0ul}, height{std::size(body)}; y < height; ++y)
    {
      for (auto x{0ul}, width{std::size(body[y])}; x < width; ++x)
      {
        if (body[y][x])
        {
          mvwaddch(win_.get(), y + 1 + tetrimino.get_y(), x + 1 + tetrimino.get_x(), 'X');
        }
      }
    }
  }
  box(win_.get(), ACS_VLINE, ACS_HLINE);
  wrefresh(win_.get());
}
