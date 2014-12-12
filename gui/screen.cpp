#include "screen.hpp"

#include <functional>

#include <solarsystem.hpp>
#include <updater/updaterfactory.hpp>

#include <QPainter>
#include <QTimer>

using std::placeholders::_1;

#include <QDebug>

constexpr double Screen::s_dt;

Screen::Screen(SolarSystem& solarSystem, QWidget* p) :
    QWidget(p), m_solarSystem(solarSystem), m_updater(UpdaterFactory::instance().create("UpdaterBasicEulerIntegrationWithUnits", std::ref(solarSystem)))
{
    setMinimumSize(800, 600);
    auto pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
    setAutoFillBackground(true);

    m_paintTimer = new QTimer(this);
    m_paintTimer->setInterval(s_dt * 100);
    connect(m_paintTimer, &QTimer::timeout, this, &Screen::onPaintTimerClick);
}

Screen::~Screen()
{}

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
    QPainter p(this);

    auto pen = p.pen();
    pen.setColor(Qt::white);
    pen.setWidthF(10E+8);
    p.setPen(pen);

    p.translate(m_zoomParameters.margeX, m_zoomParameters.margeY);
    p.scale(m_zoomParameters.factor, m_zoomParameters.factor);
    p.translate(m_zoomParameters.maxDistance/2, m_zoomParameters.maxDistance/2);

    p.drawLine(QPointF(0, m_zoomParameters.maxDistance), QPointF(0, -m_zoomParameters.maxDistance));
    p.drawLine(QPointF(m_zoomParameters.maxDistance, 0), QPointF(-m_zoomParameters.maxDistance, 0));


    pen.setWidthF(0.2*10E+9);
    p.setPen(pen);
    QBrush brush1(Qt::darkGray);
    p.setBrush(brush1);
    if(m_displayTraces)
    {
        drawTraces(p);
    }

    pen.setWidthF(0.5*10E+9);
    p.setPen(pen);
    QBrush brush2(Qt::white);
    p.setBrush(brush2);
    m_solarSystem.forEachBody(std::bind(&Screen::paintBody, this, std::ref(p), _1));
}

void Screen::paintBody(QPainter& painter, const Body& body)
{
    const auto& position = body.position();
    const auto diameter = std::max(body.meanRadius().value()*2, 5*10E+7);
    const auto p = QPointF(position.x().value(), position.y().value());
    painter.drawEllipse(p, diameter, diameter);
    m_traces.push_back(p);
}

void Screen::drawTraces(QPainter& painter) const
{
    for(const auto& t : m_traces)
        painter.drawPoint(t);
}

void Screen::play()
{
    qDebug() << "Screen::play()";
    m_paintTimer->start();
}

void Screen::pause()
{
    qDebug() << "Screen::pause()";
    m_paintTimer->stop();
}

void Screen::reset()
{
    qDebug() << "Screen::reset()";

}

void Screen::step()
{
    qDebug() << "Screen::step()";
    onPaintTimerClick();
}

void Screen::setDisplayTraces(bool display)
{
    m_displayTraces = display;
    m_traces.clear();
}

void Screen::onPaintTimerClick()
{
    m_updater->update(s_dt * 1000000 * boost::units::si::seconds, 100);
    update();
}
