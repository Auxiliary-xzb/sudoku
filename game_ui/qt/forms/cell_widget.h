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

#ifndef SUDOKU_GAME_UI_QT_FORMS_CELL_WIDGET_H_
#define SUDOKU_GAME_UI_QT_FORMS_CELL_WIDGET_H_

#include <QWidget>

#include "game_info/cell.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CellWidget;
}
QT_END_NAMESPACE

namespace sudoku {
namespace game_ui {
namespace qt {

class CellWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CellWidget(game_info::Cell *cell, QWidget *parent = nullptr);
  ~CellWidget() override;

  void SetActive(bool is_active);
  bool IsEmpty() const;
  void UpdateValue();

 private:
  Ui::CellWidget *ui_;
  game_info::Cell *cell_;
};

}  // namespace qt
}  // namespace game_ui
}  // namespace sudoku
#endif  // SUDOKU_GAME_UI_QT_FORMS_CELL_WIDGET_H_
