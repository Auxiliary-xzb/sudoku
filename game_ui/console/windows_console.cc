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

using namespace sudoku::game_ui::console;

WindowsConsole::WindowsConsole() : is_first_console_buffer_(true) {
  SetConsoleOutputCP(CP_UTF8);
  first_console_buffer_ =
      CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, nullptr,
                                CONSOLE_TEXTMODE_BUFFER, nullptr);
  second_console_buffer_ =
      CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, nullptr,
                                CONSOLE_TEXTMODE_BUFFER, nullptr);
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

void WindowsConsole::WriteMultiLine(const std::vector<std::string>& lines) {
  DWORD bytes;
  COORD pos = {0, 0};
  auto current_console_buffer = GetCurrentConsoleBuffer();

  for (const auto& line : lines) {
    WriteConsoleOutputCharacter(current_console_buffer, line.data(),
                                line.length(), pos, &bytes);
    pos.Y++;
  }
  SetConsoleActiveScreenBuffer(current_console_buffer);
  SetConsoleCursorPosition(current_console_buffer, pos);
  is_first_console_buffer_ = !is_first_console_buffer_;
}

HANDLE& WindowsConsole::GetCurrentConsoleBuffer() {
  if (is_first_console_buffer_) {
    return first_console_buffer_;
  }

  return second_console_buffer_;
}
