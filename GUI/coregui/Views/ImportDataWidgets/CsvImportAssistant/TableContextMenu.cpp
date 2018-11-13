#include "TableContextMenu.h"

TableContextMenu::TableContextMenu(QWidget* parent)
        : QMenu(parent)
        , m_coordSubMenu(nullptr)
        , m_selectFromThisRowOn(new QAction("Set as first data row", nullptr))
        , m_selectUntilThisRow(new QAction("Set as last data row", nullptr))
        , m_resetAction(new QAction("reset", nullptr))
        , m_setAsTheta(new QAction(csv::HeaderLabels[csv::_theta_], nullptr))
        , m_setAsQ(new QAction(csv::HeaderLabels[csv::_q_], nullptr))
        , m_setAsIntensity(new QAction("Set as " + csv::HeaderLabels[csv::_intensity_] + " column", nullptr))
{
    this->addAction(m_selectFromThisRowOn);
    this->addAction(m_selectUntilThisRow);

    this->addSeparator();
    this->addAction(m_setAsIntensity);

    m_coordSubMenu = this->addMenu("Set as coordinate column...");
    m_coordSubMenu->addAction(m_setAsTheta);
    m_coordSubMenu->addAction(m_setAsQ);

    this->addSeparator();
    this->addAction(m_resetAction);

    connect(m_selectFromThisRowOn, &QAction::triggered, this, [this]() { emit setFirstRow(); });
    connect(m_selectUntilThisRow, &QAction::triggered, this, [this]() { emit setLastRow(); });
    connect(m_setAsIntensity, &QAction::triggered, this, [this]() { emit setColumnAs(csv::_intensity_); });
    connect(m_setAsTheta, &QAction::triggered, this, [this]() { emit setColumnAs(csv::_theta_); });
    connect(m_setAsQ, &QAction::triggered, this, [this]() { emit setColumnAs(csv::_q_); });
    connect(m_resetAction, &QAction::triggered, this, [this]() { emit resetTable();});

}
