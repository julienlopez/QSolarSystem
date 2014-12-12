#include "commanddock.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>

CommandDock::CommandDock(QWidget* p): QDockWidget(p)
{
    auto* w = new QWidget;
    auto* lay = new QVBoxLayout;

    lay->addWidget(createGroupBoxCommands());
    lay->addWidget(createGroupBoxTraces());

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

QGroupBox* CommandDock::createGroupBoxCommands()
{
    auto* res = new QGroupBox(tr("Commands"));
    auto* lay = new QVBoxLayout;

    lay->addWidget(createButton(tr("Play"), &CommandDock::play));
    lay->addWidget(createButton(tr("Pause"), &CommandDock::pause));
    lay->addWidget(createButton(tr("Reset"), &CommandDock::reset));
    lay->addWidget(createButton(tr("Step"), &CommandDock::step));

    res->setLayout(lay);
    return res;
}

QGroupBox* CommandDock::createGroupBoxTraces()
{
    auto* res = new QGroupBox(tr("Commands"));
    auto* lay = new QVBoxLayout;

    auto* cb = new QCheckBox(tr("Display Traces"));
    cb->setChecked(true);
    connect(cb, &QCheckBox::toggled, this, &CommandDock::displayTraces);
    lay->addWidget(cb);

    res->setLayout(lay);
    return res;
}
