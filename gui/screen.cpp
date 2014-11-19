#include "screen.hpp"

Screen::Screen(QWidget *parent) :
    QWidget(parent)
{}

void Screen::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);
}
