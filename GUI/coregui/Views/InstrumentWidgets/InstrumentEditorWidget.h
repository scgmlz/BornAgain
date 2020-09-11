// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentEditorWidget.h
//! @brief     Defines class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTEDITORWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTEDITORWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class SessionItem;
class DetectorItem;
class QLineEdit;
class InstrumentPresenter;

//! Main widget of InstrumentView. Contains InstrumentPresenter
//! showing proper insturment editor for given instrument type.

class BA_CORE_API_ InstrumentEditorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentEditorWidget(QWidget* parent = nullptr);

    QSize sizeHint() const;

    void setItem(SessionItem* instrument);

signals:
    void extendedDetectorEditorRequest(DetectorItem*);

public slots:
    void onChangedEditor(const QString&);

private:
    QLayout* createTopLayout();
    void updateWidgets();

    QLineEdit* m_nameLineEdit;
    InstrumentPresenter* m_instrumentPresenter;
    SessionItem* m_currentItem;
    bool m_block_signals;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTEDITORWIDGET_H
