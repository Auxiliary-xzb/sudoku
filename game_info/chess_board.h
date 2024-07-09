////////////////////////////////////////////////////////////////////////////////
// Copyright © 2024 XiongZhiBin <519083070@qq.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
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

#ifndef SUDOKU_GAME_INFO_CHESS_BOARD_H_
#define SUDOKU_GAME_INFO_CHESS_BOARD_H_

#include <array>
#include <vector>

#include "game_info/check_unit.h"

namespace sudoku {
namespace game_info {

class ChessBoard {
 public:
  enum class GameLevel { kEasy, kMiddle, kHard };

 public:
  ChessBoard();

  /// \brief 初始化棋盘
  void Init();

  /// \brief 设置游戏等级
  /// \param level 游戏等级
  void SetLevel(GameLevel level);

  /// \brief 填充单元格
  /// \param room_x 单元格在棋盘中的x坐标
  /// \param room_y 单元格在棋盘中的y坐标
  /// \param room_value 单元格存储的值
  /// \return 填充成功返回true，否则返回false
  bool FillRoom(int room_x, int room_y, int room_value);

  /// \brief 数独游戏是否填充完成
  /// \return 填充成功返回true，填充失败返回false
  bool IsComplete() const;

  /// \brief 获取棋盘大小
  /// \return 棋盘大小
  ///
  /// 棋盘为正方形，该返回值为正方形边长
  static size_t GetChessBoarSize() { return kMaxLineCount; }

  /// \brief 获取棋盘信息
  /// \return 棋盘信息
  std::vector<int> GetChessBoardInfo() const {
    std::vector<int> chess_board_info;

    for (auto line : line_array_) {
      for (size_t i = 0; i < line.GetRoomCount(); ++i) {
        chess_board_info.emplace_back(line[i]->value());
      }
    }

    return chess_board_info;
  }

 private:
  static constexpr size_t kMaxLineCount = 9;  ///< 棋盘最大列数，行数和列数相同
  std::array<CheckUnit, kMaxLineCount> line_array_;    ///< 以行为单位的检测单元
  std::array<CheckUnit, kMaxLineCount> column_array_;  ///< 以列为单位的检测单元
  std::array<CheckUnit, kMaxLineCount> block_array_;   ///< 以块为单位的检测单元
};

}  // namespace game_info
}  // namespace sudoku

#endif  // SUDOKU_GAME_INFO_CHESS_BOARD_H_
