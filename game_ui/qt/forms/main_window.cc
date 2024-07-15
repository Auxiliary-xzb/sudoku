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
#include <QLabel>
#include <QString>

#include "forms/ui_main_window.h"

using namespace sudoku::game_ui::qt;
using namespace sudoku::game_info;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  chess_board_.Init();
  chess_board_.SetLevel(ChessBoard::GameLevel::kEasy);

  auto chess_board_info = chess_board_.GetChessBoardInfo();
  for (auto cell : chess_board_info) {
    cell_widget_vec_.push_back(new CellWidget(cell, this));
  }

  auto edge_length = chess_board_.GetEdgeLength();
  auto grid_layout = new QGridLayout();

  for (size_t i = 0; i < cell_widget_vec_.size(); ++i) {
    grid_layout->addWidget(cell_widget_vec_[i], i / edge_length,
                           i % edge_length);
  }
  ui_->widget_main_->setLayout(grid_layout);
}

MainWindow::~MainWindow() { delete ui_; }
