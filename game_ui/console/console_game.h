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

#ifndef SUDOKU_GAME_UI_CONSOLE_CONSOLE_GAME_H_
#define SUDOKU_GAME_UI_CONSOLE_CONSOLE_GAME_H_

#include "game_info/chess_board.h"

namespace sudoku {
namespace game_ui {
namespace console {

class ConsoleGame {
 public:
  ConsoleGame();

  void Start();

 private:
  /// \brief 游戏主逻辑
  void Play();

  /// \brief 显示棋盘信息
  void Show() const;

  /// \brief 构建棋盘顶部边框
  /// \return 棋盘顶部边框
  std::string GetChessBoardUpEdge() const;

  /// \brief 构建两行数值间的分隔行
  /// \param selected_cell_index 当前被选中单元在行内索引
  /// \return 两行数值间的分隔行
  ///
  /// 棋盘单元格被选中将会显示选中标识符，因此如果当前单元格被选中，则根据
  /// 提供的选中单元格在在本行的索引显示选中标识符。当本行没有单元格被修改
  /// 时，传递-1即可。
  std::string GetChessBoardLineSeperator(size_t selected_cell_index) const;

  /// \brief 构建棋盘底部边框
  /// \param selected_cell_index 当前被选中单元在行内索引
  /// \return 棋盘底部边框
  ///
  /// 和分隔行相同，当最后一排单元格被选中时则需要在底部边框显示被选中标
  /// 识符。
  std::string GetChessBoardDownEdge(size_t selected_cell_index) const;

 private:
  game_info::ChessBoard chess_board_;  ///< 棋盘
  size_t chess_board_edge_length_;     ///< 棋盘边长
  size_t current_cell_index_;          ///< 单元格索引，0~棋子总数
};

}  // namespace console
}  // namespace game_ui
}  // namespace sudoku

#endif  // SUDOKU_GAME_UI_CONSOLE_CONSOLE_GAME_H_
