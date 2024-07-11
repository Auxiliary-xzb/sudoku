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

#include "game_info/check_unit.h"

#include "cell.h"

using namespace sudoku::game_info;

CheckUnit::CheckUnit() : room_array_() {}

bool CheckUnit::IsFull() const {
  for (const auto &room : room_array_) {
    if (room->state() == Cell::CellState::kEmpty) {
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
