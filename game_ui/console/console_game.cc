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
#include <conio.h>
#include <windows.h>
#endif

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace sudoku::game_info;
using namespace sudoku::game_ui::console;

static constexpr char kSymbolLine[] = "\u2500";
static constexpr char kSymbolColumn[] = "\u2502";
static constexpr char kSymbolLeftUpCorner[] = "\u250c";
static constexpr char kSymbolRightUpCorner[] = "\u2510";
static constexpr char kSymbolDownCorner[] = "\u2514";
static constexpr char kSymbolRightDownCorner[] = "\u2518";
static constexpr char kSymbolLeftEdge[] = "\u251c";
static constexpr char kSymbolRightEdge[] = "\u2524";
static constexpr char kSymbolUpEdge[] = "\u252c";
static constexpr char kSymbolDownEdge[] = "\u2534";
static constexpr char kSymbolCross[] = "\u253c";
static constexpr char kSymbolCurrentCell[] = "\u25b2";

static constexpr char kColorStart[] = "\033[34m";  // blue
static constexpr char kColorEnd[] = "\033[0m";

static void SetConsoleEncoding();
static void ClearConsole();
static ChessBoard::GameLevel SetGameLevel();

ConsoleGame::ConsoleGame() : current_cell_index_(0) {
  chess_board_.Init();
  chess_board_edge_length_ = chess_board_.GetEdgeLength();
  SetConsoleEncoding();
}

void ConsoleGame::Start() {
  chess_board_.SetLevel(SetGameLevel());

  // 指向第一个待填充的单元格
  auto chess_board_info = chess_board_.GetChessBoardInfo();
  auto it = std::find_if(chess_board_info.begin(), chess_board_info.end(),
                         [](const Cell *cell) { return cell->value() == -1; });
  current_cell_index_ = it - chess_board_info.begin();

  Play();
}

void ConsoleGame::Play() {
  while (true) {
    Show();

#ifdef __WIN32
    char input_char = _getch();
#else
    char input_char = getchar();
#endif

    // 填充值
    char max = '0' + chess_board_edge_length_;
    if (input_char > '0' && input_char < max + 1) {
      int cell_x = current_cell_index_ % chess_board_edge_length_ + 1;
      int cell_y = current_cell_index_ / chess_board_edge_length_ + 1;
      std::cout << max << " : " << cell_x << " " << cell_y << std::endl;
      chess_board_.FillCell(cell_x, cell_y, input_char - '0');
      continue;
    }

    int next_cell_index = static_cast<int>(current_cell_index_);
    if (input_char == 'w') {
      // 上移后不应该超过棋盘最小值
      next_cell_index -= static_cast<int>(chess_board_edge_length_);
      if (next_cell_index > -1) {
        current_cell_index_ = next_cell_index;
      }
    } else if (input_char == 's') {
      // 下移不应该超过棋盘最大值
      next_cell_index += static_cast<int>(chess_board_edge_length_);
      if (next_cell_index <
          chess_board_edge_length_ * chess_board_edge_length_) {
        current_cell_index_ = next_cell_index;
      }
    } else if (input_char == 'a') {
      // 左移后当前行索引不应该比移动前大，如果大则表明移动到上一行了
      next_cell_index -= 1;
      if (next_cell_index % chess_board_edge_length_ <
          current_cell_index_ % chess_board_edge_length_) {
        current_cell_index_ = next_cell_index;
      }
    } else if (input_char == 'd') {
      // 右移后当前行索引不应该比移动前小，如果小则表明移动到下一行了
      next_cell_index += 1;
      if (next_cell_index % chess_board_edge_length_ >
          current_cell_index_ % chess_board_edge_length_) {
        current_cell_index_ = next_cell_index;
      }
    } else if (input_char == 'q') {
      exit(0);
    }
  }
}

void ConsoleGame::Show() const {
  ClearConsole();
  auto chess_board_info = chess_board_.GetChessBoardInfo();

  std::stringstream chess_board;
  chess_board << GetChessBoardUpEdge();

  auto line_count = chess_board_info.size() / chess_board_edge_length_;
  for (int i = 0; i < line_count; ++i) {
    std::stringstream line;
    line << kSymbolColumn;

    for (int j = 0; j < chess_board_edge_length_; ++j) {
      const auto *cell = chess_board_info[i * chess_board_edge_length_ + j];
      if (cell->value() == -1) {
        line << "   ";
      } else {
        line << " ";
        if (cell->state() == Cell::CellState::kUserFilled) {
          line << kColorStart;
        }
        line << std::to_string(cell->value());
        if (cell->state() == Cell::CellState::kUserFilled) {
          line << kColorEnd;
        }
        line << " ";
      }
      line << kSymbolColumn;
    }
    chess_board << line.str() << "\n";

    size_t selected_cell_index = -1;  // max is not exists
    // 选中项目在当前行，则计算行内索引
    if (current_cell_index_ / chess_board_edge_length_ == i) {
      selected_cell_index = current_cell_index_ % chess_board_edge_length_;
    }

    if (i == line_count - 1) {
      chess_board << GetChessBoardDownEdge(selected_cell_index);
    } else {
      chess_board << GetChessBoardLineSeperator(selected_cell_index);
    }
  }

  std::cout << chess_board.str();
}

void ClearConsole() {
#ifdef __WIN32
  system("cls");
#endif
}

void SetConsoleEncoding() {
#ifdef __WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
}

ChessBoard::GameLevel SetGameLevel() {
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

std::string ConsoleGame::GetChessBoardUpEdge() const {
  // 生成棋盘顶部的边框
  std::stringstream up_edge;
  up_edge << kSymbolLeftUpCorner;
  for (int i = 0; i < chess_board_edge_length_; ++i) {
    up_edge << kSymbolLine << kSymbolLine << kSymbolLine;
    if (i == chess_board_edge_length_ - 1) {
      up_edge << kSymbolRightUpCorner;
    } else {
      up_edge << kSymbolUpEdge;
    }
  }
  up_edge << "\n";

  return up_edge.str();
}

std::string ConsoleGame::GetChessBoardLineSeperator(
    size_t selected_cell_index) const {
  // 生成两行数值之间的行分隔符
  // 每个单元格的边由三个横线组成，单元格内数据和中间的横线在同一列
  // 当有单元格被选中时，将单元格数值下的横线替换为指示符
  std::stringstream line_seperator;
  line_seperator << kSymbolLeftEdge;

  for (int i = 0; i < chess_board_edge_length_; ++i) {
    if (selected_cell_index == i) {
      // 被选中单元格下方的横线被替换为指示符
      line_seperator << kSymbolLine << kSymbolCurrentCell << kSymbolLine;
    } else {
      line_seperator << kSymbolLine << kSymbolLine << kSymbolLine;
    }

    // 两个单元格之间以十字符号链接，最后一个则使用右边界符
    if (i == chess_board_edge_length_ - 1) {
      line_seperator << kSymbolRightEdge;
    } else {
      line_seperator << kSymbolCross;
    }
  }
  line_seperator << "\n";

  return line_seperator.str();
}

std::string ConsoleGame::GetChessBoardDownEdge(
    size_t selected_cell_index) const {
  // 生成棋盘的底边
  // 底边和行分隔符类似也要处理单元格被选中的情况
  std::stringstream down_edge;
  down_edge << kSymbolDownCorner;

  for (int i = 0; i < chess_board_edge_length_; ++i) {
    if (selected_cell_index == i) {
      // 被选中单元格下方的横线被替换为指示符
      down_edge << kSymbolLine << kSymbolCurrentCell << kSymbolLine;
    } else {
      down_edge << kSymbolLine << kSymbolLine << kSymbolLine;
    }

    if (i == chess_board_edge_length_ - 1) {
      down_edge << kSymbolRightDownCorner;
    } else {
      down_edge << kSymbolDownEdge;
    }
  }
  down_edge << "\n";

  return down_edge.str();
}
