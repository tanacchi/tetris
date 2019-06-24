#include <iostream>
#include <tetrimino.hpp>
#include <pile.hpp>
#include <main_display.hpp>
#include <thread>
#include <chrono>
#include <memory>

int main()
{
  std::unique_ptr<Tetrimino> tetrimino_ptr{std::make_unique<Tetrimino>(O)};

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
    disp.show(pile, *tetrimino_ptr);
    std::thread periodic_tetri_motion_th{
      [&]{
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        tetrimino_ptr->move(Direction::Down);
      }
    };

    const auto key{getch()};
    switch (key)
    {
      case KEY_LEFT:
        tetrimino_ptr->move(Direction::Left);
        break;
      case KEY_RIGHT:
        tetrimino_ptr->move(Direction::Right);
        break;
    }
    periodic_tetri_motion_th.join();
    flushinp();

    if (pile.is_touching_tetrimino(*tetrimino_ptr))
    {
      pile.pile(*tetrimino_ptr);
      tetrimino_ptr = std::make_unique<Tetrimino>(O);
    }
  }
  endwin();

  return 0;
}
