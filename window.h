#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT
    QTimer _timer;

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void on_timeout();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H

