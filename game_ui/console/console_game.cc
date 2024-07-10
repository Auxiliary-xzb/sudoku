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
static constexpr char kCurrentItem[] = "\u25b4";

static void SetConsoleEncoding();
static std::string GetChessBoardUpSide(size_t chess_board_size);
static std::string GetChessBoardLineSeperator(size_t chess_board_size,
                                              size_t current_item_index);
static std::string GetChessBoardDownSide(size_t chess_board_size,
                                         size_t current_item_index);

ConsoleGame::ConsoleGame() : current_item_index_(11) {
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

  std::stringstream chess_board;
  chess_board << GetChessBoardUpSide(size);

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

    size_t index = -1;
    // 选中项目在当前行，则计算行内索引
    if (current_item_index_ / size == i) {
      index = current_item_index_ % size;
    }

    if (i == line_count - 1) {
      chess_board << GetChessBoardDownSide(size, index);
    } else {
      chess_board << GetChessBoardLineSeperator(size, index);
    }
  }

  std::cout << chess_board.str();
}

void SetConsoleEncoding() {
#ifdef __WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
}

std::string GetChessBoardUpSide(size_t chess_board_size) {
  std::stringstream chess_board_up_side;
  chess_board_up_side << kLeftUpCorner;
  for (int i = 0; i < chess_board_size; ++i) {
    chess_board_up_side << kLine << kLine << kLine;
    if (i == chess_board_size - 1) {
      chess_board_up_side << kRightUpCorner;
    } else {
      chess_board_up_side << kUpSide;
    }
  }
  chess_board_up_side << "\n";

  return chess_board_up_side.str();
}

std::string GetChessBoardLineSeperator(size_t chess_board_size,
                                       size_t current_item_index) {
  std::stringstream chess_board_line_seperator;
  chess_board_line_seperator << kLeftSide;

  for (int i = 0; i < chess_board_size; ++i) {
    if (current_item_index == i) {
      // 如果当前选中索引在当前分隔行中，则显示指示图标
      chess_board_line_seperator << kLine << kCurrentItem << kLine;
    } else {
      // 将current_item_index设置为-1，表示当前选中索引不在分隔行中
      chess_board_line_seperator << kLine << kLine << kLine;
    }

    if (i == chess_board_size - 1) {
      chess_board_line_seperator << kRigtSide;
    } else {
      chess_board_line_seperator << kCross;
    }
  }
  chess_board_line_seperator << "\n";

  return chess_board_line_seperator.str();
}

std::string GetChessBoardDownSide(size_t chess_board_size,
                                  size_t current_item_index) {
  std::stringstream chess_board_down_side;
  chess_board_down_side << kLeftDownCorner;

  for (int i = 0; i < chess_board_size; ++i) {
    if (current_item_index == i) {
      // 如果当前选中索引在当前分隔行中，则显示指示图标
      chess_board_down_side << kLine << kCurrentItem << kLine;
    } else {
      // 将current_item_index设置为-1，表示当前选中索引不在分隔行中
      chess_board_down_side << kLine << kLine << kLine;
    }

    if (i == chess_board_size - 1) {
      chess_board_down_side << kRightDownCorner;
    } else {
      chess_board_down_side << kDownSide;
    }
  }
  chess_board_down_side << "\n";

  return chess_board_down_side.str();
}
