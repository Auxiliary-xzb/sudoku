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

#include "main_window.h"

#include <QGridLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <algorithm>

#include "forms/ui_main_window.h"

using namespace sudoku::game_ui::qt;
using namespace sudoku::game_info;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  // 棋盘配置
  chess_board_.Init();
  chess_board_.SetLevel(ChessBoard::GameLevel::kEasy);
  auto chess_board_info = chess_board_.GetChessBoardInfo();
  auto chess_board_edge_length = chess_board_.GetEdgeLength();
  // 找到第一个待填充单元格
  auto it = std::find_if(chess_board_info.begin(), chess_board_info.end(),
                         [](const Cell *cell) { return cell->value() == -1; });
  current_cell_index_ = it - chess_board_info.begin();

  // 界面初始化
  auto grid_layout = new QGridLayout();
  for (size_t i = 0; i < chess_board_info.size(); ++i) {
    auto cell_widget = new CellWidget(chess_board_info[i], this);
    cell_widget_vec_.push_back(cell_widget);
    grid_layout->addWidget(cell_widget, i / chess_board_edge_length,
                           i % chess_board_edge_length);
    if (i != 0) {
      setTabOrder(cell_widget_vec_[i - 1], cell_widget_vec_[i]);
    }
    connect(cell_widget, &CellWidget::CellWidgetFocusIn, this,
            &MainWindow::OnCellWidgetFocusIn);
  }
  ui_->widget_main_->setLayout(grid_layout);
  // 指向第一个待填充的单元格
  cell_widget_vec_[current_cell_index_]->setFocus();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() > Qt::Key_0 && event->key() <= Qt::Key_9) {
    auto chess_board_edge_length = chess_board_.GetEdgeLength();
    int cell_x = current_cell_index_ % chess_board_edge_length + 1;
    int cell_y = current_cell_index_ / chess_board_edge_length + 1;
    if (chess_board_.FillCell(cell_x, cell_y, event->key() - Qt::Key_0)) {
      cell_widget_vec_[current_cell_index_]->UpdateValue();
    }

    if (chess_board_.IsComplete()) {
      QMessageBox::information(this, "恭喜", "游戏结束");
    }
    return;
  }

  auto chess_board_edge_length = chess_board_.GetEdgeLength();

  bool active_cell_changed = false;
  int next_cell_index = static_cast<int>(current_cell_index_);
  if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
    // 上移后不应该超过棋盘最小值
    next_cell_index -= static_cast<int>(chess_board_edge_length);
    if (next_cell_index > -1) {
      active_cell_changed = true;
    }
  } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
    // 下移不应该超过棋盘最大值
    next_cell_index += static_cast<int>(chess_board_edge_length);
    if (next_cell_index < chess_board_edge_length * chess_board_edge_length) {
      active_cell_changed = true;
    }
  } else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
    // 左移后当前行索引不应该比移动前大，如果大则表明移动到上一行了
    next_cell_index -= 1;
    if (next_cell_index % chess_board_edge_length <
        current_cell_index_ % chess_board_edge_length) {
      active_cell_changed = true;
    }
  } else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
    // 右移后当前行索引不应该比移动前小，如果小则表明移动到下一行了
    next_cell_index += 1;
    if (next_cell_index % chess_board_edge_length >
        current_cell_index_ % chess_board_edge_length) {
      active_cell_changed = true;
    }
  }

  if (active_cell_changed) {
    current_cell_index_ = next_cell_index;
    cell_widget_vec_[current_cell_index_]->setFocus();
  }
}

void MainWindow::OnCellWidgetFocusIn(const CellWidget *cell_widget) {
  for (int i = 0; i < cell_widget_vec_.size(); ++i) {
    if (cell_widget_vec_[i] == cell_widget) {
      current_cell_index_ = i;
    }
  }
}
