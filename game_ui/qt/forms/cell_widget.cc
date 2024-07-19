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

#include "cell_widget.h"

#include <QString>

#include "forms/ui_cell_widget.h"

using namespace sudoku::game_ui::qt;
using namespace sudoku::game_info;

CellWidget::CellWidget(Cell* cell, QWidget* parent)
    : QWidget(parent), ui_(new Ui::CellWidget), cell_(cell) {
  ui_->setupUi(this);
  UpdateValue();

  setFocusPolicy(Qt::StrongFocus);
  normal_color_ = palette().window().color();
  setAutoFillBackground(true);
}

CellWidget::~CellWidget() { delete ui_; }

void CellWidget::focusInEvent(QFocusEvent* event) {
  auto current_palette = palette();
  current_palette.setColor(QPalette::Background, Qt::gray);
  setPalette(current_palette);
  emit CellWidgetFocusIn(this);
}

void CellWidget::focusOutEvent(QFocusEvent* event) {
  auto current_palette = palette();
  current_palette.setColor(QPalette::Background, normal_color_);
  setPalette(current_palette);
}

void CellWidget::paintEvent(QPaintEvent* event) {
  ui_->label_value_->setText(QString::fromStdString(GetValue()));
}

bool CellWidget::IsEmpty() const {
  return cell_->state() == Cell::CellState::kEmpty;
}

void CellWidget::UpdateValue() {
  if (cell_->value() == -1) {
    ui_->label_value_->setText("");
  } else {
    ui_->label_value_->setText(std::to_string(cell_->value()).data());
  }
}

std::string CellWidget::GetValue() const {
  if (cell_->value() == -1) {
    return "";
  }

  return std::to_string(cell_->value());
}
