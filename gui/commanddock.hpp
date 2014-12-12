#ifndef COMMANDDOCK_HPP
#define COMMANDDOCK_HPP

#include <QDockWidget>

class QPushButton;
class QGroupBox;

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
    void displayTraces(bool);

private:
    template<class T>
    QPushButton* createButton(const QString& label, T fct);

    QGroupBox* createGroupBoxCommands();
    QGroupBox* createGroupBoxTraces();
};

#endif // COMMANDDOCK_HPP
