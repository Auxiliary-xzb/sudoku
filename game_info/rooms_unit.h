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
/// 1. 行：每个单独行要保证符合要求，如1-9；<br>
/// 2. 列：每个单独列要保证符合要求，如1-9；<br>
/// 3. 块(宫)：行和列交织构成的模块，也要符合要求，如1-9；<br>
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

  void SetRoom(size_t index, Room *room) { room_array_[index] = room; }
  Room *At(size_t index) const { return room_array_[index]; }

 private:
  static constexpr int kMaxRoomCount = 9;         ///< 最大单元格个数
  std::array<Room *, kMaxRoomCount> room_array_;  ///< 块内单元格数组
};

}  // namespace game_info
}  // namespace sudoku

#endif  // SUDOKU_GAME_INFO_ROOMS_UNIT_H_
