// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewFactory.cpp
//! @brief     Implements class SampleViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/SampleViewFactory.h"
#include "GUI/coregui/Views/SampleDesigner/InterferenceFunctionViews.h"
#include "GUI/coregui/Views/SampleDesigner/LayerView.h"
#include "GUI/coregui/Views/SampleDesigner/MesoCrystalView.h"
#include "GUI/coregui/Views/SampleDesigner/MultiLayerView.h"
#include "GUI/coregui/Views/SampleDesigner/ParticleCompositionView.h"
#include "GUI/coregui/Views/SampleDesigner/ParticleCoreShellView.h"
#include "GUI/coregui/Views/SampleDesigner/ParticleDistributionView.h"
#include "GUI/coregui/Views/SampleDesigner/ParticleLayoutView.h"
#include "GUI/coregui/Views/SampleDesigner/ParticleView.h"
#include "GUI/coregui/Views/SampleDesigner/TransformationView.h"

QStringList SampleViewFactory::m_valid_item_names = QStringList()
                                                    << "MultiLayer"
                                                    << "Layer"
                                                    << "ParticleLayout"
                                                    << "Particle"
                                                    << "Rotation"
                                                    << "ParticleCoreShell"
                                                    << "ParticleComposition"
                                                    << "MesoCrystal"
                                                    << "ParticleDistribution"
                                                    << "Interference1DLattice"
                                                    << "Interference2DLattice"
                                                    << "Interference2DParaCrystal"
                                                    << "InterferenceFinite2DLattice"
                                                    << "InterferenceHardDisk"
                                                    << "InterferenceRadialParaCrystal";

bool SampleViewFactory::isValidType(const QString& name)
{
    if (name.startsWith("FormFactor")) {
        return true;
    } else {
        return m_valid_item_names.contains(name);
    }
}

IView* SampleViewFactory::createSampleView(const QString& name)
{
    if (name == "MultiLayer") {
        return new MultiLayerView();
    } else if (name == "Layer") {
        return new LayerView();
    } else if (name == "ParticleLayout") {
        return new ParticleLayoutView();
    } else if (name == "Particle") {
        return new ParticleView();
    } else if (name == "Rotation") {
        return new TransformationView();
    } else if (name == "ParticleCoreShell") {
        return new ParticleCoreShellView();
    } else if (name == "ParticleComposition") {
        return new ParticleCompositionView();
    } else if (name == "MesoCrystal") {
        return new MesoCrystalView();
    } else if (name == "ParticleDistribution") {
        return new ParticleDistributionView();
    } else if (name == "Interference1DLattice") {
        return new InterferenceFunction1DLatticeView();
    } else if (name == "Interference2DLattice") {
        return new InterferenceFunction2DLatticeView();
    } else if (name == "Interference2DParaCrystal") {
        return new InterferenceFunction2DParaCrystalView();
    } else if (name == "InterferenceFinite2DLattice") {
        return new InterferenceFunctionFinite2DLatticeView();
    } else if (name == "InterferenceHardDisk") {
        return new InterferenceFunctionHardDiskView();
    } else if (name == "InterferenceRadialParaCrystal") {
        return new InterferenceFunctionRadialParaCrystalView();
    }
    return 0;
}
