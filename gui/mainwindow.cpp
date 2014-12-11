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

    auto jupiter = BodyParser::parseFromFile("Jupiter");
    std::cout << jupiter << std::endl;
    m_solarSystem.add(std::move(jupiter));

    auto saturn = BodyParser::parseFromFile("Saturn");
    std::cout << saturn << std::endl;
    m_solarSystem.add(std::move(saturn));

    auto uranus = BodyParser::parseFromFile("Uranus");
    std::cout << uranus << std::endl;
    m_solarSystem.add(std::move(uranus));

    auto neptune = BodyParser::parseFromFile("Neptune");
    std::cout << neptune << std::endl;
    m_solarSystem.add(std::move(neptune));

//    auto pluto = BodyParser::parseFromFile("Pluto");
//    std::cout << pluto << std::endl;
//    m_solarSystem.add(std::move(pluto));
}
