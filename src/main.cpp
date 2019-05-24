#include <iostream>
#include <tetrimino.hpp>
#include <pile.hpp>
#include <main_display.hpp>

#include <unistd.h>  // XXX: sleep function
#include <algorithm>  // max_element

int main()
{
  Tetrimino tetrimino{{
    {Cell(true),  Cell(true), Cell(true)},
    {Cell(false), Cell(true), Cell(false)}
  }};

  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  refresh();

  MainDisplay disp{};
  Pile pile{};

  while (true)
  {
    disp.show(pile, tetrimino);
    sleep(1);  // XXX: Avoid to use it.
    if (pile.is_touching_tetrimino(tetrimino))
    {
      pile.pile(tetrimino);
    }
    tetrimino.move(Direction::Down);
  }
  endwin();

  return 0;
}
