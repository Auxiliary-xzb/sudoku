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

#ifndef GAME_UI_CONSOLE_WINDOWS_CONSOLE_H_
#define GAME_UI_CONSOLE_WINDOWS_CONSOLE_H_

#include <windows.h>

#include <string>
#include <vector>

namespace sudoku {
namespace game_ui {
namespace console {

class WindowsConsole {
 public:
  WindowsConsole();

  void Clear();
  void WriteMultiLine(const std::vector<std::string> &lines);

 private:
  HANDLE &GetCurrentConsoleBuffer();

 private:
  HANDLE first_console_buffer_;
  HANDLE second_console_buffer_;
  bool is_first_console_buffer_;
};

}  // namespace console
}  // namespace game_ui
}  // namespace sudoku

#endif  // GAME_UI_CONSOLE_WINDOWS_CONSOLE_H_
