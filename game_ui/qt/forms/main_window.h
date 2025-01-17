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

#ifndef SUDOKU_GAME_UI_QT_FORMS_MAIN_WINDOW_H_
#define SUDOKU_GAME_UI_QT_FORMS_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QVector>

#include "game_info/chess_board.h"
#include "game_ui/qt/forms/cell_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace sudoku {
namespace game_ui {
namespace qt {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 public slots:
  void OnCellWidgetFocusIn(const CellWidget *cell_widget);

 private:
  Ui::MainWindow *ui_;                     ///< UI界面
  game_info::ChessBoard chess_board_;      ///< 棋盘信息
  QVector<CellWidget *> cell_widget_vec_;  ///< 棋盘显示单元格数组
  size_t current_cell_index_;
};

}  // namespace qt
}  // namespace game_ui
}  // namespace sudoku

#endif  // SUDOKU_GAME_UI_QT_FORMS_MAIN_WINDOW_H_
