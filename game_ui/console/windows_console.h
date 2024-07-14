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

namespace sudoku {
namespace game_ui {
namespace console {

class WindowsConsole {
 public:
  WindowsConsole();

  /// \brief 清除终端
  void Clear();

  /// \brief 写入终端
  /// \param data 待写入终端数据
  ///
  /// 总是应该一次写完单个终端要显示的所有内容
  void Write(const std::string &data);

 private:
  /// \brief 获取当前终端缓冲区句柄
  /// \return 终端缓冲区句柄
  HANDLE &GetCurrentConsoleBuffer();

 private:
  HANDLE first_console_buffer_;   ///< 第一个终端缓冲区
  HANDLE second_console_buffer_;  ///< 第二个终端缓冲区
  bool is_first_console_buffer_;  ///< 是否使用第一个终端缓冲区
};

}  // namespace console
}  // namespace game_ui
}  // namespace sudoku

#endif  // GAME_UI_CONSOLE_WINDOWS_CONSOLE_H_
