#include "commanddock.hpp"

#include <QVBoxLayout>
#include <QPushButton>

CommandDock::CommandDock(QWidget* p): QDockWidget(p)
{
    auto* w = new QWidget;
    auto* lay = new QVBoxLayout;

    lay->addWidget(createButton(tr("Play"), &CommandDock::play));
    lay->addWidget(createButton(tr("Pause"), &CommandDock::pause));
    lay->addWidget(createButton(tr("Reset"), &CommandDock::reset));
    lay->addWidget(createButton(tr("Step"), &CommandDock::step));

    lay->addStretch();

    w->setLayout(lay);
    w->setMinimumWidth(200);
    setWidget(w);
}

template<class T>
QPushButton* CommandDock::createButton(const QString& label, T fct)
{
    auto* b = new QPushButton(label);
    connect(b, &QPushButton::clicked, this, fct);
    return b;
}
