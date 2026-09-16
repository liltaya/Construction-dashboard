#pragma once

#include <QMainWindow>

class QLabel;

namespace construction {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QLabel* titleLabel_;
};

} 