// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditor.h
//! @brief     Defines class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITOR_H
#define MASKEDITOR_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMainWindow>

class MaskEditorPropertyPanel;
class MaskEditorActions;
class MaskEditorToolBar;
class MaskEditorCanvas;
class QSplitter;
class MaskModel;

//! Main class to draw masks on top of intensity data map

class BA_CORE_API_ MaskEditor : public QMainWindow
{
    Q_OBJECT
public:
    MaskEditor(QWidget *parent = 0);

public slots:
    void onPropertyPanelRequest();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void init_test_model();
    void setup_connections();

    MaskEditorActions *m_itemActions;
    MaskEditorToolBar *m_toolBar;
    MaskEditorPropertyPanel *m_editorPropertyPanel;
    MaskEditorCanvas *m_editorCanvas;
    QSplitter *m_splitter;
    MaskModel *m_maskModel;
};


#endif
