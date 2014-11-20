#include "mainwindow.hpp"

#include <iostream>
#include <iomanip>

#include <bodyparser.hpp>

#include "screen.hpp"

MainWindow::MainWindow(QWidget* p): QMainWindow(p)
{
    loadSystem();
    auto* screen = new Screen(m_solarSystem);
    setCentralWidget(screen);
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
