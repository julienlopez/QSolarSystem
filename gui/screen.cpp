#include "screen.hpp"

#include <functional>

#include <solarsystem.hpp>

#include <QPainter>

using std::placeholders::_1;

#include <QDebug>

Screen::Screen(const SolarSystem& solarSystem, QWidget* p) :
    QWidget(p), m_solarSystem(solarSystem)
{
    setMinimumSize(800, 600);
    auto pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
    setAutoFillBackground(true);
}

void Screen::resizeEvent(QResizeEvent* evt)
{
    Q_UNUSED(evt);
    qDebug() << "Screen::resizeEvent(): " << width() << "x" << height();
    m_zoomParameters.maxDistance = 2.2 * m_solarSystem.longestDistanceFromTheCenter().value();
    qDebug() << "maxDistance = " << m_zoomParameters.maxDistance;
    m_zoomParameters.factor = std::min(width()/m_zoomParameters.maxDistance, height()/m_zoomParameters.maxDistance);
    qDebug() << "factor = " << m_zoomParameters.factor;
    m_zoomParameters.margeX = (width() - m_zoomParameters.factor * m_zoomParameters.maxDistance) / 2;
    qDebug() << "margeX = " << m_zoomParameters.margeX;
    m_zoomParameters.margeY = (height() - m_zoomParameters.factor * m_zoomParameters.maxDistance) / 2;
    qDebug() << "margeY = " << m_zoomParameters.margeY;
}

void Screen::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);
    qDebug() << "Screen::paintEvent()";

    QPainter p(this);

    auto pen = p.pen();
    pen.setColor(Qt::white);
    pen.setWidthF(0.5*10E+9);
    p.setPen(pen);

    p.translate(m_zoomParameters.margeX, m_zoomParameters.margeY);
    p.scale(m_zoomParameters.factor, m_zoomParameters.factor);
    p.translate(m_zoomParameters.maxDistance/2, m_zoomParameters.maxDistance/2);

    p.drawLine(QPointF(0, m_zoomParameters.maxDistance), QPointF(0, -m_zoomParameters.maxDistance));
    p.drawLine(QPointF(m_zoomParameters.maxDistance, 0), QPointF(-m_zoomParameters.maxDistance, 0));

    m_solarSystem.forEachBody(std::bind(&Screen::paintBody, this, std::ref(p), _1));
}

void Screen::paintBody(QPainter& painter, const Body& body)
{
    const auto& position = body.position();
    qDebug() << "drawing {" << position.x().value() << ", " << position.y().value() << "} : " << body.meanRadius().value();
    painter.drawEllipse(QPointF(position.x().value(), position.y().value()), 10E+9, 10E+9);
}
