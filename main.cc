////////////////////////////////////////////////////////////////////////////////
// Copyright © 2024 XiongZhiBin <519083070@qq.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING ROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "game_info/chess_board.h"
#include "game_ui/console/console_game.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  sudoku::game_info::ChessBoard game;
  game.Init();

  if (game.IsComplete()) {
    auto size = game.GetEdgeLength();
    auto chess_board_info = game.GetChessBoardInfo();

    for (int i = 0; i < chess_board_info.size(); ++i) {
      std::cout << chess_board_info[i] << " ";
      if ((i + 1) % size == 0) {
        std::cout << std::endl;
      }
    }

    std::cout << std::endl;
  }

  sudoku::game_ui::console::ConsoleGame console_game;
  console_game.Start();

  std::system("pause");
  return 0;
}
