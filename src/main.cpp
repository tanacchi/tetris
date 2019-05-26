#include <iostream>
#include <tetrimino.hpp>
#include <pile.hpp>
#include <main_display.hpp>
#include <thread>
#include <chrono>

#include <unistd.h>  // XXX: sleep function
#include <algorithm>  // max_element

int main()
{
  Tetrimino tetrimino{{
    {Cell(true),  Cell(true), Cell(true)},
    {Cell(false), Cell(true), Cell(false)}
  }};

  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);
  timeout(1000);
  noecho();
  curs_set(0);
  refresh();

  MainDisplay disp{};
  Pile pile{};

  while (true)
  {
    disp.show(pile, tetrimino);
    std::thread periodic_tetri_motion_th{
      [&]{
        std::this_thread::sleep_for(std::chrono::seconds(1));
        tetrimino.move(Direction::Down);
      }
    };

    const auto key{getch()};
    switch (key)
    {
      case KEY_LEFT:
        tetrimino.move(Direction::Left);
        break;
      case KEY_RIGHT:
        tetrimino.move(Direction::Right);
        break;
      case KEY_DOWN:
        tetrimino.move(Direction::Down);
    }
    periodic_tetri_motion_th.join();

    if (pile.is_touching_tetrimino(tetrimino))
    {
      pile.pile(tetrimino);
    }
  }
  endwin();

  return 0;
}
