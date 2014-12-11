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
    const std::vector<std::string> names = {{"Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto", "Charon", "Halley", "Tchouri"}};
    for(const auto& name : names)
    {
        auto body = BodyParser::parseFromFile(name);
        std::cout << body << std::endl;
        m_solarSystem.add(std::move(body));
    }
}
