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

#include "windows_console.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

using namespace sudoku::game_ui::console;

WindowsConsole::WindowsConsole() : is_first_console_buffer_(true) {
  SetConsoleOutputCP(CP_UTF8);
  first_console_buffer_ = CreateConsoleScreenBuffer(
      GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr,
      CONSOLE_TEXTMODE_BUFFER, nullptr);
  second_console_buffer_ = CreateConsoleScreenBuffer(
      GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr,
      CONSOLE_TEXTMODE_BUFFER, nullptr);

  // 设置启用转移序列，参考:
  // https://learn.microsoft.com/zh-cn/windows/console/setconsolemode
  //  https://learn.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences
  DWORD dwMode = 0;
  GetConsoleMode(first_console_buffer_, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
  SetConsoleMode(first_console_buffer_, dwMode);
  GetConsoleMode(second_console_buffer_, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
  SetConsoleMode(second_console_buffer_, dwMode);
}

void WindowsConsole::Clear() {
  // Window官方示例
  // https://learn.microsoft.com/zh-cn/windows/console/clearing-the-screen
  auto& hConsole = GetCurrentConsoleBuffer();

  DWORD cCharsWritten;
  COORD coordScreen = {0, 0};
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  // Get the number of character cells in the current buffer.
  if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    return;
  }

  DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // Fill the entire screen with blanks.
  if (!FillConsoleOutputCharacter(
          hConsole,         // Handle to console screen buffer
          (TCHAR)' ',       // Character to write to the buffer
          dwConSize,        // Number of cells to write
          coordScreen,      // Coordinates of first cell
          &cCharsWritten))  // Receive number of characters written
  {
    return;
  }

  // Get the current text attribute.
  if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    return;
  }

  // Set the buffer's attributes accordingly.
  if (!FillConsoleOutputAttribute(
          hConsole,          // Handle to console screen buffer
          csbi.wAttributes,  // Character attributes to use
          dwConSize,         // Number of cells to set attribute
          coordScreen,       // Coordinates of first cell
          &cCharsWritten))   // Receive number of characters written
  {
    return;
  }

  // Put the cursor at its home coordinates.
  SetConsoleCursorPosition(hConsole, coordScreen);
}

void WindowsConsole::Write(const std::string& data) {
  // FIXME: 是否可用operator<<替代？如何判断何时输入结束，切换终端缓冲区？
  DWORD bytes;
  auto& current_console_buffer = GetCurrentConsoleBuffer();

  WriteConsole(current_console_buffer, data.data(), data.length(), &bytes,
               nullptr);
  SetConsoleActiveScreenBuffer(current_console_buffer);
  is_first_console_buffer_ = !is_first_console_buffer_;
}

HANDLE& WindowsConsole::GetCurrentConsoleBuffer() {
  if (is_first_console_buffer_) {
    return first_console_buffer_;
  }

  return second_console_buffer_;
}
