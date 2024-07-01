#include <iostream>

#include "game_info/chess_board.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  sudoku::game_info::ChessBoard game;
  game.Init();

  std::cout << game.IsComplete() << std::endl;
  return 0;
}
