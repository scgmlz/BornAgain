// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/PySampleWidget.h
//! @brief     Defines class PySampleWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_PYSAMPLEWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_PYSAMPLEWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class SampleModel;
class InstrumentModel;
class QTextEdit;
class QModelIndex;
class PythonSyntaxHighlighter;
class UpdateTimer;
class WarningSign;
class QShowEvent;
class QHideEvent;

//! Displays Python script representing a MultiLayer at the bottom of SampleView.

class BA_CORE_API_ PySampleWidget : public QWidget
{
    Q_OBJECT

public:
    PySampleWidget(QWidget* parent = nullptr);

    void setSampleModel(SampleModel* sampleModel);
    void setInstrumentModel(InstrumentModel* instrumentModel);

public slots:
    void onModifiedRow(const QModelIndex&, int, int);
    void onDataChanged(const QModelIndex&, const QModelIndex&);

    void updateEditor();
    void setEditorConnected(bool isConnected);

protected:
    void showEvent(QShowEvent*);
    void hideEvent(QHideEvent*);

private:
    QString generateCodeSnippet();

    QTextEdit* m_textEdit;
    SampleModel* m_sampleModel;
    InstrumentModel* m_instrumentModel;
    PythonSyntaxHighlighter* m_highlighter;
    UpdateTimer* m_updateTimer;
    WarningSign* m_warningSign;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_PYSAMPLEWIDGET_H
