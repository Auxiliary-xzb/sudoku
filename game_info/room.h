#ifndef SUDOKU_GAME_INFO_ROOM_H_
#define SUDOKU_GAME_INFO_ROOM_H_

#include <cstdint>

namespace sudoku {
namespace game_info {

/// \brief 存储数值的单元格
class Room {
 public:
  /// \brief 单元格当前状态
  enum class RoomState : uint8_t {
    kSystemFilled,  ///< 单元格被系统填充
    kUserFilled,    ///< 单元格被用户
    kEmpty,         ///< 单元格空
  };

 public:
  Room(int x, int y, int value, RoomState state)
      : x_(x), y_(y), value_(value), state_(state) {}

  /// \brief 设置单元格坐标
  /// \param x x坐标
  /// \param y y坐标
  void SetPos(const int x, const int y) {
    x_ = x;
    y_ = y;
  }

  /// \brief 获取单元格x坐标
  /// \return x坐标
  int x() const { return x_; }

  /// \brief 设置x坐标
  /// \param x 待设置的x坐标
  void set_x(const int x) { x_ = x; }

  /// \brief 获取单元格y坐标
  /// \return y坐标
  int y() const { return y_; }

  /// \brief 设置y坐标
  /// \param y 待设置的y坐标
  void set_y(const int y) { y_ = y; }

  /// \brief 获取单元格内存储的值
  /// \return 单元格存储的值
  int value() const { return value_; }

  /// \brief 获取单元格内存储的值
  /// \param value 待设置的值
  void set_value(const int value) { value_ = value; }

  /// \brief 获取单元格当前状态
  /// \return 单元格当前状态
  RoomState state() const { return state_; }

  void set_state(RoomState state) { state_ = state; }

 private:
  int x_;           ///< 单元格x坐标
  int y_;           ///< 单元格y坐标
  int value_;       ///< 单元格值
  RoomState state_; ///< 单元格状态
};

} // namespace game_info
} // namespace sudoku

#endif  // SUDOKU_GAME_INFO_ROOM_H_
