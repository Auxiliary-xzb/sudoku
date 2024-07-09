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

#ifndef SUDOKU_GAME_INFO_CHECK_UNIT_H_
#define SUDOKU_GAME_INFO_CHECK_UNIT_H_

#include <array>

#include "game_info/room.h"

namespace sudoku {
namespace game_info {

/// \brief 由多个单元格构成的数独最小检测单元
///
/// 可以将数独分为三种集合：由行构成的集合，由列构成的集合，由宫(块)构成的集合。
/// 每一行，一列，一宫都是由1-9构成的单元格的集合。满足如下要求时，则认为数独正确：
/// 1. 数字1-9在每行只能出现1次；
/// 2. 数字1-9在每列只能出现1次；
/// 3. 数字1-9在每宫只能出现1次；
///
/// 因此将行、列、宫抽象为最小检测单元，该检测单元有效的条件为：
/// 1. 9个单元格均被填充数据；
/// 2. 单元中不存在重复的数据；
///
/// 而数独有效的判定则转变为所有行、所有列、所有宫同时有效。
class CheckUnit {
 public:
  CheckUnit();

  /// \brief 检测单元是否被全部填充
  /// \return 全部填充时返回true，否则返回false
  bool IsFull() const;

  /// \brief 检测单元是否有效
  /// \return 有效时返回true，否则返回false
  bool IsValid() const;

  /// \brief 定位检测单元中的单元格
  /// \param index 单元格索引
  /// \return 索引合法时发挥单元格指针，否则抛出异常
  Room *&operator[](size_t index) {
    if (index > kMaxRoomCount) {
      throw std::out_of_range("Out of rang");
    }

    return room_array_[index];
  }

  /// \brief 获取检测单元中单元格个数
  /// \return 检测单元中单元格个数
  static size_t GetRoomCount() { return kMaxRoomCount; }

 private:
  static constexpr int kMaxRoomCount = 9;  ///< 最大单元格个数

  // 使用指针使得单元格的修改可以反应到所有包含该单元格的测试单元中，
  // 使得变更单元格内容更加便捷，无需同时手动修改所有检测单元
  std::array<Room *, kMaxRoomCount> room_array_;  ///< 块内单元格数组
};

}  // namespace game_info
}  // namespace sudoku

#endif  // SUDOKU_GAME_INFO_CHECK_UNIT_H_
