// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewFactory.h
//! @brief     Defines class SampleViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWFACTORY_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWFACTORY_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QStringList>

class IView;

class BA_CORE_API_ SampleViewFactory
{
public:
    static bool isValidType(const QString& name);
    static IView* createSampleView(const QString& name);

    static bool isValidExampleName();

private:
    static QStringList m_valid_item_names;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWFACTORY_H
