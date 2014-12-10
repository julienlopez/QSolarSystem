#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <utils/noncopiable.hpp>

#include <memory>

#include <QWidget>

class Body;
class SolarSystem;
class iUpdater;

class Screen : public QWidget, private utils::noncopiable
{
    Q_OBJECT
public:
    explicit Screen(SolarSystem& solarSystem, QWidget* p = 0);
    ~Screen();

    static constexpr double s_dt = 0.04;

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

    SolarSystem& m_solarSystem;
    std::unique_ptr<iUpdater> m_updater;
    ZoomParameters m_zoomParameters;
    QTimer* m_paintTimer;

    void paintBody(QPainter& painter, const Body& body);

signals:

public slots:
    void play();
    void pause();
    void reset();
    void step();

private slots:
    void onPaintTimerClick();
};

#endif // SCREEN_HPP
