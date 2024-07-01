#include "game_info/rooms_unit.h"

#include "room.h"

using namespace sudoku::game_info;

RoomsUnit::RoomsUnit() : room_array_() {}

bool RoomsUnit::IsFull() const {
  for (const auto &room : room_array_) {
    if (room->state() == Room::RoomState::kEmpty) {
      return false;
    }
  }

  return true;
}

bool RoomsUnit::IsValid() const {
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
