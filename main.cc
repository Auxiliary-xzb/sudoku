#include <iostream>

#include "game_info/chess_board.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  sudoku::game_info::ChessBoard game;
  game.Init();

  if (game.IsComplete()) {
    auto size = game.GetChessBoarSize();
    auto chess_board_info = game.GetChessBoardInfo();

    for (int i = 0; i < chess_board_info.size(); ++i) {
      std::cout << chess_board_info[i] << " ";
      if ((i + 1) % size == 0) {
        std::cout << std::endl;
      }
    }

    std::cout << std::endl;
  }

  return 0;
}
