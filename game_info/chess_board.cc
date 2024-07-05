#include "game_info/chess_board.h"

#include <algorithm>
#include <map>
#include <random>
#include <vector>

#include "game_info/room.h"

using namespace sudoku::game_info;

ChessBoard::ChessBoard() {
  for (int x = 0; x < kMaxLineCount; ++x) {
    for (int y = 0; y < kMaxLineCount; ++y) {
      auto* room = new Room(x, y, -1, Room::RoomState::kEmpty);
      line_array_[y].SetRoom(x, room);
      column_array_[x].SetRoom(y, room);

      int block_index = (y / 3) * 3 + x / 3;
      int block_room_index = (y % 3) * 3 + x % 3;
      block_array_[block_index].SetRoom(block_room_index, room);
    }
  }
}

void ChessBoard::Init() {
  // 该模式使用字母表示一个完整的数独棋盘。为了得到一个新游戏的棋盘，
  // 只需要每次将字母都映射到不同的数字即可。
  static const char* chess_pattern[] = {"ighcabfde", "cabfdeigh", "fdeighcab",
                                        "ghiabcdef", "abcdefghi", "defghiabc",
                                        "higbcaefd", "bcaefdhig", "efdhigbca"};

  std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::shuffle(values.begin(), values.end(),
               std::mt19937(std::random_device()()));
  std::map<char, int> relation_map;

  // 打乱顺序后，a ~ i分别和数组中的值对应
  for (int i = 0; i < kMaxLineCount; ++i) {
    relation_map[static_cast<char>(i + 'a')] = values[i];
  }

  // 将上述字母映射表翻译为数值映射，此时得到一个完整的数独结果
  for (int x = 0; x < kMaxLineCount; ++x) {
    for (int y = 0; y < kMaxLineCount; ++y) {
      auto* room = line_array_[y][x];
      room->set_value(relation_map[chess_pattern[x][y]]);
      room->set_state(Room::RoomState::kSystemFilled);
    }
  }

  // 可以将此时的映射结果保存，作为后续判断用户是否成功的参考，
  // 即直接比较两个数组
}

void ChessBoard::SetLevel(GameLevel level) {
  static std::default_random_engine random_engine;
  static std::uniform_int_distribution<size_t> uniform(
      0, kMaxLineCount * kMaxLineCount);

  double rate;
  if (level == GameLevel::kEasy) {
    rate = 0.2;
  } else if (level == GameLevel::kMiddle) {
    rate = 0.4;
  } else {
    rate = 0.6;
  }

  // 清空指定个数的单元格，这些方格也就是客户需要填写的了
  auto erase_count = static_cast<size_t>(kMaxLineCount * kMaxLineCount * rate);
  for (size_t i = 0; i < erase_count; ++i) {
    auto index = uniform(random_engine);
    auto* room = line_array_[index / kMaxLineCount][index % kMaxLineCount];
    room->set_value(-1);
    room->set_state(Room::RoomState::kEmpty);
  }
}

bool ChessBoard::FillRoom(int room_x, int room_y, int room_value) {
  if (room_x > kMaxLineCount || room_y > kMaxLineCount) {
    return false;
  }

  auto* room = line_array_[room_y - 1][room_x - 1];
  if (room->state() == Room::RoomState::kSystemFilled) {
    return false;
  }

  room->set_value(room_value);
  room->set_state(Room::RoomState::kUserFilled);
  return true;
}

bool ChessBoard::IsComplete() const {
  for (int i = 0; i < kMaxLineCount; ++i) {
    if (!line_array_[i].IsValid() || !column_array_[i].IsValid() ||
        !block_array_[i].IsValid()) {
      return false;
    }
  }

  return true;
}
