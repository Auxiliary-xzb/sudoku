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

#ifndef SUDOKU_GAME_INFO_CELL_H_
#define SUDOKU_GAME_INFO_CELL_H_

namespace sudoku {
namespace game_info {

/// \brief 存储数值的单元格
class Cell {
 public:
  /// \brief 单元格当前状态
  enum class CellState : uint8_t {
    kSystemFilled,  ///< 单元格被系统填充
    kUserFilled,    ///< 单元格被用户
    kEmpty,         ///< 单元格空
  };

 public:
  Cell(int x, int y, int value = -1, CellState state = CellState::kEmpty)
      : x_(x), y_(y), value_(value), state_(state) {}

  /// \brief 获取单元格x坐标
  /// \return x坐标
  int x() const { return x_; }

  /// \brief 获取单元格y坐标
  /// \return y坐标
  int y() const { return y_; }

  /// \brief 获取单元格内存储的值
  /// \return 单元格存储的值
  int value() const { return value_; }

  /// \brief 获取单元格内存储的值
  /// \param value 待设置的值
  void set_value(const int value) { value_ = value; }

  /// \brief 获取单元格当前状态
  /// \return 单元格当前状态
  CellState state() const { return state_; }

  /// \brief 设置单元格状态
  /// \param state 单元格状态
  void set_state(CellState state) { state_ = state; }

 private:
  int x_;           ///< 单元格x坐标
  int y_;           ///< 单元格y坐标
  int value_;       ///< 单元格值
  CellState state_; ///< 单元格状态
};

} // namespace game_info
} // namespace sudoku

#endif  // SUDOKU_GAME_INFO_CELL_H_
