#ifndef SUDOKU_GAME_INFO_CHESS_BOARD_H_
#define SUDOKU_GAME_INFO_CHESS_BOARD_H_

#include <array>

#include "game_info/rooms_unit.h"

namespace sudoku {
namespace game_info {

class ChessBoard {
 public:
  ChessBoard();

  /// \brief 初始化棋盘
  void Init();

  /// \brief 填充单元格
  /// \param room_x 单元格在棋盘中的x坐标
  /// \param room_y 单元格在棋盘中的y坐标
  /// \param room_value 单元格存储的值
  /// \return 填充成功返回true，否则返回false
  bool FillRoom(int room_x, int room_y, int room_value);

  /// \brief 数独游戏是否填充完成
  /// \return 填充成功返回true，填充失败返回false
  bool IsComplete() const;

 private:
  static constexpr size_t kMaxLineCount = 9;  ///< 棋盘最大列数，行数和列数相同
  std::array<RoomsUnit, kMaxLineCount> line_array_;    ///< 以行为单位的检测单元
  std::array<RoomsUnit, kMaxLineCount> column_array_;  ///< 以列为单位的检测单元
  std::array<RoomsUnit, kMaxLineCount> block_array_;   ///< 以块为单位的检测单元
};

}  // namespace game_info
}  // namespace sudoku

#endif  // SUDOKU_GAME_INFO_CHESS_BOARD_H_
