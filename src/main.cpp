#include <iostream>
#include <tetrimino.hpp>
#include <pile.hpp>
#include <main_display.hpp>
#include <thread>
#include <chrono>

int main()
{
  Tetrimino tetrimino{T};

  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);
  timeout(200);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
    }
    periodic_tetri_motion_th.join();
    flushinp();

    if (pile.is_touching_tetrimino(tetrimino))
    {
      pile.pile(tetrimino);
    }
  }
  endwin();

  return 0;
}
