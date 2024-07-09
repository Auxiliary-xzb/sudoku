#include "game_info/check_unit.h"

#include "room.h"

using namespace sudoku::game_info;

CheckUnit::CheckUnit() : room_array_() {}

bool CheckUnit::IsFull() const {
  for (const auto &room : room_array_) {
    if (room->state() == Room::RoomState::kEmpty) {
      return false;
    }
  }

  return true;
}

bool CheckUnit::IsValid() const {
  // 每一位代表一个数字
  int valid_mask = 0x1FF;

  for (const auto &room : room_array_) {
    if (room->value() == -1) {
      return false;
    }

    valid_mask &= ~(1 << (room->value() - 1));
  }

  return valid_mask == 0;
}
