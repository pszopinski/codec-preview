#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window),
    _timer(this)
{
    ui->setupUi(this);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    // populate your window with images, labels, etc. here
    _timer.start(10 /*call the timer every 10 ms*/);
}

void Window::on_timeout() {

}

Window::~Window()
{
    delete ui;
}
