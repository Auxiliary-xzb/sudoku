#ifndef SUDOKU_GAME_INFO_ROOMS_UNIT_H_
#define SUDOKU_GAME_INFO_ROOMS_UNIT_H_

#include <array>
#include <initializer_list>

#include "room.h"

namespace sudoku {
namespace game_info {

/// \brief 对数独中可检测单元的抽象
///
/// 在数独中有三种存储数据方式，即对应三种检测单元：<br>
/// 1. 行：每个单独行要保证符合要求；<br>
/// 2. 列：每个单独列要保证符合要求；<br>
/// 3. 块(宫)：块可能是行和列交织构成的，也可能是其他形状的；<br>
/// 当三种存储方式都检查通过时，数独才算成功。
class RoomsUnit {
 public:
  RoomsUnit();

  /// \brief 获取块是否填充完毕
  /// \return 块填充完毕返回true，否则返回false
  bool IsFull() const;

  /// \brief 获取块中填充数据是否有效，即是否为1-9
  /// \return 数据有效时返回true，否则返回false
  bool IsValid() const;

  /// \brief 设置可检测单元中单元格指针
  /// \param index 单元格在可检测单元中的索引
  /// \param room 单元格指针
  void SetRoom(size_t index, Room *room) { room_array_[index] = room; }

  Room *operator[](size_t index) const {
    if (index > kMaxRoomCount) {
      throw std::out_of_range("Out of rang");
    }

    return room_array_[index];
  }

  size_t GetRoomUnitSize() const { return kMaxRoomCount; }

 private:
  static constexpr int kMaxRoomCount = 9;  ///< 最大单元格个数

  // 单元格在不同的可测试单元中的顺序可能不一致，因此访问单元格的对象
  // 所需要的索引表达式的复杂程度不同。因此使用单元格指针则可以只选择
  // 访问方式最简单的可测试单元进行单元格访问，此时对单元格的修改就会
  // 直接反应到其他可测试单元
  std::array<Room *, kMaxRoomCount> room_array_;  ///< 块内单元格数组
};

}  // namespace game_info
}  // namespace sudoku

#endif  // SUDOKU_GAME_INFO_ROOMS_UNIT_H_
