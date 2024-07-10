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

#include "console_game.h"

#ifdef __WIN32
#include <windows.h>
#endif

#include <iostream>
#include <sstream>

using namespace sudoku::game_info;
using namespace sudoku::game_ui::console;

static constexpr char kLine[] = "\u2500";
static constexpr char kCloumn[] = "\u2502";
static constexpr char kLeftUpCorner[] = "\u250c";
static constexpr char kRightUpCorner[] = "\u2510";
static constexpr char kLeftDownCorner[] = "\u2514";
static constexpr char kRightDownCorner[] = "\u2518";
static constexpr char kLeftSide[] = "\u251c";
static constexpr char kRigtSide[] = "\u2524";
static constexpr char kUpSide[] = "\u252c";
static constexpr char kDownSide[] = "\u2534";
static constexpr char kCross[] = "\u253c";

static void SetConsoleEncoding();

ConsoleGame::ConsoleGame() {
  chess_board_.Init();
  SetConsoleEncoding();
}

void ConsoleGame::Start() {
  chess_board_.SetLevel(SetGameLevel());
  Show();
}

ChessBoard::GameLevel ConsoleGame::SetGameLevel() {
  std::cout << "Please choose game level:" << std::endl
            << "1. Easy" << std::endl
            << "2. Middle" << std::endl
            << "3. Hard" << std::endl;

  ChessBoard::GameLevel level;
  while (true) {
    char input_char;
    std::cin >> input_char;

    if (input_char == '1') {
      std::cout << "Easy" << std::endl;
      level = ChessBoard::GameLevel::kEasy;
    } else if (input_char == '2') {
      std::cout << "Middle" << std::endl;
      level = ChessBoard::GameLevel::kMiddle;
    } else if (input_char == '3') {
      std::cout << "Hard" << std::endl;
      level = ChessBoard::GameLevel::kHard;
    } else {
      continue;
    }

    break;
  }

  return level;
}

void ConsoleGame::Play() {}

void ConsoleGame::Show() {
  auto chess_board_info = chess_board_.GetChessBoardInfo();
  auto size = chess_board_.GetChessBoarSize();

  // 顶层边框
  std::stringstream up_side;
  up_side << kLeftUpCorner;
  for (int i = 0; i < size; ++i) {
    up_side << kLine << kLine << kLine;
    if (i == size - 1) {
      up_side << kRightUpCorner;
    } else {
      up_side << kUpSide;
    }
  }
  up_side << "\n";

  // 底层边框
  std::stringstream down_side;
  down_side << kLeftDownCorner;
  for (int i = 0; i < size; ++i) {
    down_side << kLine << kLine << kLine;
    if (i == size - 1) {
      down_side << kRightDownCorner;
    } else {
      down_side << kDownSide;
    }
  }
  down_side << "\n";

  // 分隔行
  std::stringstream line_seperator;
  line_seperator << kLeftSide;
  for (int i = 0; i < size; ++i) {
    line_seperator << kLine << kLine << kLine;
    if (i == size - 1) {
      line_seperator << kRigtSide;
    } else {
      line_seperator << kCross;
    }
  }
  line_seperator << "\n";

  std::stringstream chess_board;
  chess_board << up_side.str();

  auto line_count = chess_board_info.size() / size;
  for (int i = 0; i < line_count; ++i) {
    std::stringstream line;
    line << kCloumn;

    for (int j = 0; j < size; ++j) {
      if (chess_board_info[i * size + j] == -1) {
        line << "   ";
      } else {
        line << " " << std::to_string(chess_board_info[i * size + j]) << " ";
      }
      line << kCloumn;
    }
    chess_board << line.str() << "\n";

    if (i == line_count - 1) {
      chess_board << down_side.str();
    } else {
      chess_board << line_seperator.str();
    }
  }

  std::cout << chess_board.str();
}

void SetConsoleEncoding() {
#ifdef __WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
}
