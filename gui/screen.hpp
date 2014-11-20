#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <QWidget>

class Body;
class SolarSystem;

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(const SolarSystem& solarSystem, QWidget* p = 0);

protected:
    virtual void resizeEvent(QResizeEvent* evt) override;
    virtual void paintEvent(QPaintEvent* evt) override;

private:
    struct ZoomParameters
    {
        double maxDistance = 0;
        double factor = 0;
        double margeX = 0;
        double margeY = 0;
    };

    const SolarSystem& m_solarSystem;
    ZoomParameters m_zoomParameters;

    void paintBody(QPainter& painter, const Body& body);

signals:

public slots:

};

#endif // SCREEN_HPP
