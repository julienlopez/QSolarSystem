#include "mainwindow.hpp"
#include <QApplication>

#include "bodyparser.hpp"
#include "solarsystem.hpp"

#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SolarSystem ss;

    auto sun = BodyParser::parseFromFile("Sun");
    std::cout << sun << std::endl;
    ss.add(std::move(sun));

    auto mercury = BodyParser::parseFromFile("Mercury");
    std::cout << mercury << std::endl;
    ss.add(std::move(mercury));

    auto venus = BodyParser::parseFromFile("Venus");
    std::cout << venus << std::endl;
    ss.add(std::move(venus));

    auto earth = BodyParser::parseFromFile("Earth");
    std::cout << earth << std::endl;
    ss.add(std::move(earth));

    auto mars = BodyParser::parseFromFile("Mars");
    std::cout << mars << std::endl;
    ss.add(std::move(mars));

    MainWindow w;
    w.show();

    return a.exec();
}

