#include "construction/MainWindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace construction {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      titleLabel_(new QLabel("Construction Project Dashboard"))
{
    setWindowTitle("Construction Dashboard");

    resize(1200, 750);

    auto* centralWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(centralWidget);

    titleLabel_->setStyleSheet(
        "font-size: 28px;"
        "font-weight: 600;"
        "padding: 20px;"
    );

    layout->addWidget(titleLabel_);
    layout->addStretch();

    setCentralWidget(centralWidget);
}

} 