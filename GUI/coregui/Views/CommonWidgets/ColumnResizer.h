// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ColumnResizer.h
//! @brief     Defines class ColumnResizer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: LGPL v2.1 or later (see COPYING)
 * http://agateau.com/2011/clean-up-your-layouts-with-columnresizer/
 * https://github.com/agateau/columnresizer
 */

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_COLUMNRESIZER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_COLUMNRESIZER_H

#include <QFormLayout>
#include <QList>
#include <QObject>

class QEvent;
class QGridLayout;
class QLayout;
class QWidget;
class ColumnResizerPrivate;

//! The ColumnResizer class provides vertically aligned widgets from diferent layouts.

class ColumnResizer : public QObject
{
    Q_OBJECT
public:
    ColumnResizer(QObject* parent = 0);
    virtual ~ColumnResizer();

    void addWidget(QWidget* widget);
    void addWidgetsFromLayout(QLayout*, int column);
    void addWidgetsFromGridLayout(QGridLayout*, int column);
    void addWidgetsFromFormLayout(QFormLayout*, QFormLayout::ItemRole role);

    void dropWidgetsFromGridLayout(QGridLayout* layout);

private slots:
    void updateWidth();

protected:
    void removeWidget(QWidget* widget);
    virtual bool eventFilter(QObject*, QEvent* event);

private:
    ColumnResizerPrivate* const d;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_COLUMNRESIZER_H
