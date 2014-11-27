#ifndef COMMANDDOCK_HPP
#define COMMANDDOCK_HPP

#include <QDockWidget>

class QPushButton;

class CommandDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit CommandDock(QWidget* p = 0);
    virtual ~CommandDock() = default;

signals:
    void play();
    void pause();
    void reset();
    void step();

private:
    template<class T>
    QPushButton* createButton(const QString& label, T fct);
};

#endif // COMMANDDOCK_HPP
