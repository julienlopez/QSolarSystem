#include "mainwindow.hpp"

#include <iostream>
#include <iomanip>

#include <bodyparser.hpp>

#include "screen.hpp"
#include "commanddock.hpp"

MainWindow::MainWindow(QWidget* p): QMainWindow(p)
{
    loadSystem();
    auto* screen = new Screen(m_solarSystem);
    setCentralWidget(screen);

    auto* commandDock = new CommandDock;
    addDockWidget(Qt::RightDockWidgetArea, commandDock);

    connect(commandDock, &CommandDock::play, screen, &Screen::play);
    connect(commandDock, &CommandDock::pause, screen, &Screen::pause);
    connect(commandDock, &CommandDock::reset, screen, &Screen::reset);
    connect(commandDock, &CommandDock::step, screen, &Screen::step);
}

MainWindow::~MainWindow()
{}


void MainWindow::loadSystem()
{
    auto sun = BodyParser::parseFromFile("Sun");
    std::cout << sun << std::endl;
    m_solarSystem.add(std::move(sun));

    auto mercury = BodyParser::parseFromFile("Mercury");
    std::cout << mercury << std::endl;
    m_solarSystem.add(std::move(mercury));

    auto venus = BodyParser::parseFromFile("Venus");
    std::cout << venus << std::endl;
    m_solarSystem.add(std::move(venus));

    auto earth = BodyParser::parseFromFile("Earth");
    std::cout << earth << std::endl;
    m_solarSystem.add(std::move(earth));

    auto mars = BodyParser::parseFromFile("Mars");
    std::cout << mars << std::endl;
    m_solarSystem.add(std::move(mars));
}
