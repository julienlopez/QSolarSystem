#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <QWidget>

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent* evt) override;

signals:

public slots:

};

#endif // SCREEN_HPP
