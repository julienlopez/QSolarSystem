#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <solarsystem.hpp>

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* p = 0);
    ~MainWindow();

private:
    SolarSystem m_solarSystem;

    void loadSystem();
};

#endif // MAINWINDOW_HPP
